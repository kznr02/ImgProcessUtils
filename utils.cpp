#include "pch.h"
#include "module/imgprogcess/imgprogcess.h"
#include "utils.h"
#include <iostream>
#include "module/cam_api/cam_api.h"
#include "const.h"

Utils utils;
CamAPI cam_instance;

//	图像处理接口暴露封装
uint8_t* utils_16to8(uint16_t* raw) {
	return img_16to8(raw);
};

void modify_gain(uint8_t gain) {
	param->param.gain = gain;
}

void utils_pseudo_init() {
	initPseudoColorLUT();
}

void utils_pc_init() {
	InitViewConvLUT();
}

uint8_t* ret_pseudo = new uint8_t[IMG_WIDTH * IMG_HEIGHT * 3] { 0 };
uint8_t* utils_pseudo_get(uint16_t* raw) {
	uint8_t* tmp;
	auto index { 0 };
	for (auto&& y = 0; y < IMG_HEIGHT; y++) {
		for (auto&& x = 0; x < IMG_WIDTH; x++) {
			tmp = getPseudoColor(param->param.min_PseudoColor, param->param.max_PseudoColor, 
				raw[index], TRUE);
			ret_pseudo[(3 * index)] = tmp[0];
			ret_pseudo[(3 * index)+1] = tmp[1];
			ret_pseudo[(3 * index)+2] = tmp[2];
			index++;
		}
	}
	return ret_pseudo;
}

float* ret_pc = new float[IMG_WIDTH * IMG_HEIGHT * 3];
uint8_t* utils_pc_get(uint16_t* depth) {
	auto index{ 0 };
	for (auto&& y = 0; y < IMG_HEIGHT; y++) {
		for (auto&& x = 0; x < IMG_WIDTH; x++) {
			auto tmp = Depth2PointCloud(ret_pc, depth[index], x, y);
			ret_pc[index * 3] = tmp[0];
			ret_pc[index * 3 + 1] = tmp[1];
			ret_pc[index * 3 + 2] = tmp[2];
		}
	}
}

//	线程管理
void start_thread() {
	utils.start_thread();
}

void stop_thread() {
	utils.stop_thread();
}

//	线程定义
int img_fetch_thread() {
	while (utils.t3_is_run) {
		auto tmp = cam_instance.get_img();
		if (tmp != NULL) {
			auto&& ret_depth = utils_pseudo_get(tmp->img_depth.data);
			if (utils.is_pc_enable) {
				//	todo
			} else {
				auto&& ret_amp = utils_16to8(tmp->img_amplitude.data);
				cam_instance.store_img(ret_amp, ret_depth);
			}
			
			
		}
	}
	cam_instance.empty_buffer();
	std::cout << "fetch thread exit" << std::endl;

	return 0;
}

//	图像结果获取函数
uint8_t* get_ret_amp_img() {
	return cam_instance.get_ret_amp();
}

uint8_t* get_ret_depth_img() {
	return cam_instance.get_ret_depth();
}


//	CamAPI对外导出函数
int connect_cam() {
	return cam_instance.connect(param->param.devIP.data(), PORT_SERVER);
}

void disconnect_cam() {
	cam_instance.disconnect();
}

//	Utils类成员函数实现
Utils::Utils() {
	std::cout << "Instance create" << std::endl;
	this->amp_ret = nullptr;
	this->depth_ret = nullptr;
	this->t3 = nullptr;
	this->t3_is_run = false;
	this->is_pc_enable = false;
}

Utils::~Utils() {
	delete this->t3;
}

void Utils::start_thread() {
	this->t3_is_run = true;
	this->t3 = new std::jthread{ img_fetch_thread };
}

void Utils::stop_thread() {
	this->t3_is_run = false;
	delete this->t3;
}

uint8_t* Utils::ret_amp() {
	return this->amp_ret;
}

uint8_t* Utils::ret_depth() {
	return this->depth_ret;
}
