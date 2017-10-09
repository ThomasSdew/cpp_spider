#pragma once

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

std::string		translateUpperKey(int code);
std::string		translateAltgrKey(int code);
std::string		translateNormalKey(int code, int last);
void			translateNormalKeyForSending(int code, int last, struct Packet *str);

#endif /* !KEYBOARD_H_ */