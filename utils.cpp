#include "pch.h"
#include "module/imgprogcess/imgprogcess.h"
#include "utils.h"
#include <iostream>
#include "module/cam_api/cam_api.h"
#include "const.h"

Utils utils;
CamAPI cam_instance;

//	ͼ����ӿڱ�¶��װ
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

void utils_pc_enable() {
	param->param.enablePointCloud = true;
}

void utils_pc_disable() {
	param->param.enablePointCloud = false;
}

bool utils_pc_is_enabled() {
	return param->param.enablePointCloud;
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
float* utils_pc_get(uint16_t* depth) {
	auto index{ 0 };
	for (auto&& y = 0; y < IMG_HEIGHT; y++) {
		for (auto&& x = 0; x < IMG_WIDTH; x++) {
			auto tmp = Depth2PointCloud(depth[index], x, y);
			ret_pc[index * 3] = tmp[0];
			ret_pc[index * 3 + 1] = tmp[1];
			ret_pc[index * 3 + 2] = tmp[2];
			index++;
		}
	}
	return ret_pc;
}

//	�̹߳���
void start_thread() {
	utils.start_thread();
}

void stop_thread() {
	utils.stop_thread();
}

//	�̶߳���
int img_fetch_thread() {
	while (utils.t3_is_run) {

		#ifdef _DEBUG
		auto&& before = std::chrono::steady_clock::now();
		#endif // _DEBUG

		auto tmp = cam_instance.get_img();
		if (tmp != NULL) {
			auto&& ret_depth = utils_pseudo_get(tmp->img_depth.data);
			cam_instance.store_pseudo(ret_depth);
			if (param->param.enablePointCloud) {
				auto&& ret_pc = utils_pc_get(tmp->img_depth.data);
				cam_instance.store_pc(ret_pc);

			} else {
				auto&& ret_amp = utils_16to8(tmp->img_amplitude.data);
				cam_instance.store_amp(ret_amp);
			}
		}

		#ifdef _DEBUG
		auto&& after = std::chrono::steady_clock::now();
		std::cout << "buffer cap: " 
			<< cam_instance.get_existed_cnt() 
			<< " run time: " 
			<< std::chrono::duration<double, std::milli>(after - before).count() 
			<< "ms" 
			<< std::endl;
		#endif // _DEBUG

	}
	cam_instance.empty_buffer();
	std::cout << "fetch thread exit" << std::endl;

	return 0;
}

//	ͼ������ȡ����
uint8_t* get_ret_amp_img() {
	return cam_instance.get_ret_amp();
}

uint8_t* get_ret_depth_img() {
	return cam_instance.get_ret_depth();
}

float* get_ret_pc_img() {
	return cam_instance.get_ret_pc();
}


//	CamAPI���⵼������
int connect_cam() {
	return cam_instance.connect(param->param.devIP.data(), PORT_SERVER);
}

void disconnect_cam() {
	cam_instance.disconnect();
}

//	Utils���Ա����ʵ��
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
