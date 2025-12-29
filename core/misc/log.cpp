#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "include/log.hpp"

/* 
 *  Using ANSI color code to display colored messages:
 *  \033[	Escape Code
 *  4		Underlined
 *  Fore Back
 *  30 	40 	Black 	
 *  31 	41 	Red 	
 *  32 	42 	Green 	
 *  33 	43 	Yellow 	
 *  34 	44 	Blue 	
 *  35 	45 	Magenta
 *  36 	46 	Cyan
 *  37 	47 	White
 *  90 	100 	Gray
 *  91 	101 	Bright Red
 *  92 	102 	Bright Green
 *  93 	103 	Bright Yellow
 *  94 	104 	Bright Blue
 *  95 	105 	Bright Magenta
 *  96 	106 	Bright Cyan
 *  97 	107 	Bright White 
 *  0		Reset
 *  m		End escape code
 */

void debug_b() {
	std::cout << "\033[0;90m<==================================Starting debug==============================>\033[0m" << std::endl;
}

void sdl_error(const char* s) {
	std::cout << "\033[4;31m[✗] " << s << ": " << SDL_GetError() << "\033[0m" << std::endl;
	exit(EXIT_FAILURE);
}

void error(const char* s) {
	std::cout << "\033[4;31m[✗] " << s << "\033[0m" << std::endl;
	exit(EXIT_FAILURE);
}

void warning(const char* s) {
	std::cout << "\033[0;33m[!] " << s << "\033[0m" << std::endl;
}

void success(const char* s) {
	std::cout << "\033[0;32m[✓] " << s << "\033[0m" << std::endl;
}

void message(const char* s) {
	std::cout << "\033[0;90m[.] " << s << "\033[0m" << std::endl;
}
