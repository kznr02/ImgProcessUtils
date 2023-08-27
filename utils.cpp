#include "pch.h"
#include "module/imgprogcess/imgprogcess.h"

uint8_t* utils_16to8(uint16_t * raw) {
	return img_16to8(raw);
};

void modify_gain(uint8_t gain) {
	param->param.gain = gain;
}

void utils_pseudo_init() {
	initPseudoColorLUT();
}

uint8_t ret[IMG_WIDTH * IMG_HEIGHT * 3]{ 0 };
uint8_t* utils_pseudo_get(uint16_t* raw) {
	uint8_t* tmp;
	auto index { 0 };
	for (auto&& y = 0; y < IMG_HEIGHT; y++) {
		for (auto&& x = 0; x < IMG_WIDTH; x++) {
			tmp = getPseudoColor(param->param.min_PseudoColor, param->param.max_PseudoColor, 
				raw[index], TRUE);
			ret[(3 * index)] = tmp[0];
			ret[(3 * index)+1] = tmp[1];
			ret[(3 * index)+2] = tmp[2];
			index++;
		}
	}
	return ret;
}