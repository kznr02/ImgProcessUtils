#pragma once

#define UTILS_EXPORTS extern "C" __declspec(dllexport)

#include <cstdint>

UTILS_EXPORTS uint8_t* utils_16to8(uint16_t* raw);

UTILS_EXPORTS uint8_t* utils_pseudo_get(uint16_t* raw);

UTILS_EXPORTS void utils_pseudo_init();

UTILS_EXPORTS void modify_gain(uint8_t gain);
