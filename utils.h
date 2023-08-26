#pragma once

#ifdef BUILD_TEST
#define API_SYMBOL __declspec(dllexport)
#else
#define API_SYMBOL __declspec(dllimport)
#endif

#include <cinttypes>

extern "C" {
	API_SYMBOL uint16_t min(uint16_t* src);

	API_SYMBOL uint16_t max(uint16_t* src);

	API_SYMBOL uint8_t* img_8to16(uint16_t* src);
}