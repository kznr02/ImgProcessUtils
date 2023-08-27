#pragma once

#ifndef __IMGPROCESS_H
#define __IMGPROCESS_H
#endif

#include <cstdint>
#include "../../const.h"
#include "../../param.h"
#include "../../pch.h"
static Param* param = Param::GetInstance();


static uint8_t Grayscale_lut[] = {
	#include "Grayscale_16_to_8.bin"
};

// 常规工具
uint8_t* img_16to8(uint16_t* raw);

// 伪彩图转换
#define NUM_COLOR_SINGLE_CHANNEL 256

static uint8_t pseudo_color_lut[(NUM_COLOR_SINGLE_CHANNEL + 1) * 3];

static const double red_param[5][3] = {
    {0.0,0,0},
    {0.35,0,0},
    {0.66,1,1},
    {0.89,1,1},
    {1,0.5,0.5}
};

static const double green_param[6][3] = {
    {0.0,0,0},
    {0.125,0,0},
    {0.375,1,1},
    {0.64,1,1},
    {0.91,0,0},
    {1,0,0}
};

static const double blue_param[5][3] = {
    {0.0,0.5,0.5},
    {0.11,1,1},
    {0.34,1,1},
    {0.65,0,0},
    {1,0,0}
};

void initPseudoColorLUT1D(unsigned char channel_id, const double channel_param[5][3]);

void initPseudoColorLUT(void);

uint8_t* getPseudoColor(unsigned int min_val, unsigned int max_val, unsigned int val, bool is_rev);