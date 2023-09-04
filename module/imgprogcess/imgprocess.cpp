#include "imgprogcess.h"
#include "pch.h"

uint8_t img_8bit[IMG_HEIGHT * IMG_WIDTH]{};

//  常规工具

//  16位图转8位图
uint8_t* img_16to8(uint16_t* raw) {
	auto index = 0;
	for (auto&& y = 0; y < IMG_HEIGHT; y++) {
		for (auto&& x = 0; x < IMG_WIDTH; x++) {

			img_8bit[index] = Grayscale_lut[raw[index] << param->param.gain];

			index++;
		}
	}
	return img_8bit;
}

//  伪彩图转换 
void initPseudoColorLUT1D(unsigned char channel_id, const double channel_param[5][3]) {
    float ratio, factor, value;
    unsigned int param_idx = 0, lut_idx;
    for (lut_idx = 0; lut_idx < NUM_COLOR_SINGLE_CHANNEL; lut_idx++) {
        ratio = (float)lut_idx / (NUM_COLOR_SINGLE_CHANNEL - 1);
        if (ratio < 1.0 && ratio >= channel_param[param_idx + 1][0])
            param_idx++;
        factor = (ratio - channel_param[param_idx][0]) / (channel_param[param_idx + 1][0] - channel_param[param_idx][0]);
        value = channel_param[param_idx][2] + (channel_param[param_idx + 1][1] - channel_param[param_idx][2]) * factor;
        pseudo_color_lut[3 * lut_idx + channel_id] = (NUM_COLOR_SINGLE_CHANNEL - 1) * value;
    }
    pseudo_color_lut[NUM_COLOR_SINGLE_CHANNEL * 3 + channel_id] = 0;
}

void initPseudoColorLUT(void) {
    initPseudoColorLUT1D(0, red_param);
    initPseudoColorLUT1D(1, green_param);
    initPseudoColorLUT1D(2, blue_param);
}

uint8_t* getPseudoColor(unsigned int min_val, unsigned int max_val, unsigned int val, bool is_rev) {
    if (val < min_val) val = min_val;
    if (val > max_val) val = max_val;
    double ratio = (double)(val - min_val) / (max_val - min_val);
    if (is_rev) ratio = 1.0f - ratio;
    unsigned int offset = (unsigned int)(NUM_COLOR_SINGLE_CHANNEL * ratio);
    return &pseudo_color_lut[offset * 3];
}

//  点云转换
float* view_conv_lut = new float[3 * IMG_HEIGHT * IMG_WIDTH] { 0 };

float* Depth2PointCloud(uint16_t& depth, int x, int y) {
    int offset = y * IMG_WIDTH + x;
    float pc[3]{ 0 };
    pc[0] = *(view_conv_lut + offset * 3) * (depth);
    pc[1] = *(view_conv_lut + offset * 3 + 1) * (depth);
    pc[2] = depth;
    return pc;
}

void InitViewConvLUT() {
    double img_diag, inner_r;
    float tmpFloat;
    float* pData = view_conv_lut;
    for (int y = 0; y < IMG_HEIGHT; y++) {
        tmpFloat = (y - param->param.c_y) / param->param.f_y; // y_div_z
        for (int x = 0; x < IMG_WIDTH; x++) {
            *(pData++) = (x - param->param.c_x) / param->param.f_x;
            *(pData++) = tmpFloat;
            img_diag = sqrt(pow(x - param->param.c_x, 2) + pow(y - param->param.c_y, 2));
            inner_r = sqrt(pow(img_diag, 2) + pow(param->param.f_avg, 2));
            *(pData++) = param->param.f_avg / inner_r; // cos_theta
        }
    }
}