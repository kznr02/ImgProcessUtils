#pragma once
#include <string>
#include "../buffer/buffer.h"
#include "api.h"

class CamAPI
{
	public:
	CamAPI();
	~CamAPI();
	int connect(std::string host, int port);

	void disconnect();

	STRC_IMG_ALL* get_img();

	void store_amp(uint8_t*& amp);

	void store_pseudo(uint8_t*& pseudo);

	void store_pc(float*& pc);

	int get_existed_cnt();

	uint8_t* get_ret_amp();

	uint8_t* get_ret_depth();

	float* get_ret_pc();

	void empty_buffer();

	private:
	int handle;

	Buffer<uint8_t*>* amp_ret_buf;

	Buffer<uint8_t*>* depth_ret_buf;

	Buffer<float*>* pc_ret_buf;
};

