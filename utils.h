#pragma once

#define UTILS_EXPORTS extern "C" __declspec(dllexport)

#include <cstdint>
#include <semaphore>
#include <thread>

UTILS_EXPORTS uint8_t* utils_16to8(uint16_t* raw);

UTILS_EXPORTS uint8_t* utils_pseudo_get(uint16_t* raw);

UTILS_EXPORTS void utils_pseudo_init();

UTILS_EXPORTS void modify_gain(uint8_t gain);

UTILS_EXPORTS void img_process_thread();

UTILS_EXPORTS void start_thread();

UTILS_EXPORTS uint8_t* get_ret_img();

UTILS_EXPORTS void recv_img(uint16_t* raw);

class Utils
{
	public:
	Utils();
	~Utils();

	void start_thread();

	void stop_thread();

	void recv_img(uint16_t* amp_raw, uint16_t* depth_raw);

	uint8_t* ret_amp();
	uint8_t* ret_depth();

	std::counting_semaphore<1> *cs;
	std::binary_semaphore* bs;
	uint16_t *amp_raw, *depth_raw;
	uint8_t *amp_ret, *depth_ret;
	uint16_t message;
	
	std::jthread* t1;

};

