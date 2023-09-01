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

	void store_img(uint8_t*& amp, uint8_t*& depth);

	int get_existed_cnt();

	uint8_t* get_ret_amp();

	uint8_t* get_ret_depth();

	void empty_buffer();

	private:
	int handle;

	Buffer<uint8_t*>* amp_ret_buf;

	Buffer<uint8_t*>* depth_ret_buf;

	Buffer<float*>* pc_ret_buf;
};

