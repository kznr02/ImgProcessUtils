#pragma once

#define UTILS_EXPORTS extern "C" __declspec(dllexport)
#ifndef __UTILS_H
#define __UTILS_H

#include <cstdint>
#include <semaphore>
#include <thread>
#include <iostream>

UTILS_EXPORTS uint8_t* utils_16to8(uint16_t* raw);

UTILS_EXPORTS uint8_t* utils_pseudo_get(uint16_t* raw);

UTILS_EXPORTS void utils_pseudo_init();

UTILS_EXPORTS void utils_pc_init();

UTILS_EXPORTS void modify_gain(uint8_t gain);

int amp_img_process_thread();

int depth_img_process_thread();

int img_fetch_thread();

UTILS_EXPORTS void start_thread();

UTILS_EXPORTS void stop_thread();

UTILS_EXPORTS uint8_t* get_ret_amp_img();

UTILS_EXPORTS uint8_t* get_ret_depth_img();

UTILS_EXPORTS void recv_img(uint16_t* amp_raw, uint16_t* depth_raw);

UTILS_EXPORTS int connect_cam();

UTILS_EXPORTS void disconnect_cam();

class Utils
{
	public:
	Utils();
	~Utils();

	void start_thread();

	void stop_thread();

	uint8_t* ret_amp();

	uint8_t* ret_depth();

	bool amp_is_finished();
	bool depth_is_finished();
	bool is_pc_enable;
	uint8_t* amp_ret, * depth_ret;
	std::jthread* t3;
	bool t3_is_run;
};




#endif // __UTILS_H
