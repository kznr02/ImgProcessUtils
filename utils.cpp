#include "pch.h"
#include "module/imgprogcess/imgprogcess.h"
#include <semaphore>
#include <thread>
#include <mutex>
#include "utils.h"
#include <iostream>

static Utils utils;

uint8_t* utils_16to8(uint16_t* raw) {
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

void start_thread() {
	utils.start_thread();
}

void stop_thread() {
	utils.stop_thread();
}

void img_process_thread() {
	while (true) {
		utils.cs->acquire();
		utils.amp_ret = utils_16to8(utils.amp_raw);
		utils.depth_ret = utils_pseudo_get(utils.depth_raw);
	}
}

uint8_t* get_ret_img() {
	return utils.send_img();
}

void recv_img(uint16_t* amp_raw, uint16_t* depth_raw) {
	utils.recv_img(amp_raw, depth_raw);
}

void Utils::start_thread() {
	this->t1 = new std::jthread{ img_process_thread };
}

void Utils::stop_thread() {
	this->t1->request_stop();
}

void Utils::recv_img(uint16_t* amp_raw, uint16_t* depth_raw) {
	this->amp_raw = amp_raw;
	this->depth_raw = depth_raw;
	this->cs->release(1);
}

uint8_t* Utils::ret_amp() {
	return this->amp_ret;
}

uint8_t* Utils::ret_depth() {
	return this->depth_ret;
}

Utils::Utils() {
	std::cout << "Instance create" << std::endl;
	this->cs = new std::counting_semaphore<1>{ 0 };
	this->bs = new std::binary_semaphore{ 0 };
	this->amp_raw = nullptr;
	this->depth_raw = nullptr;
	this->amp_ret = nullptr;
	this->depth_ret = nullptr;
	this->t1 = nullptr;
	this->message = 0;
}

Utils::~Utils() {
	delete this->cs;
	delete this->amp_raw;
	delete this->depth_raw;
	this->t1->request_stop();
}