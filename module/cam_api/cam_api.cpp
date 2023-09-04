#include "cam_api.h"
#include "pch.h"
#include <cstdint>

int CamAPI::connect(std::string host, int port) {
	this->handle = api_connect(host.data(), port);
	return this->handle;
}

void CamAPI::disconnect() {
	api_disconnect(this->handle);
}

STRC_IMG_ALL* CamAPI::get_img() {
	STRC_IMG_ALL* tmp{ nullptr };
	tmp = api_get_img(this->handle);
	return tmp;
}

void CamAPI::store_amp(uint8_t*& amp) {
	this->amp_ret_buf->add_item(amp);
}

void CamAPI::store_pseudo(uint8_t*& pseudo) {
	this->depth_ret_buf->add_item(pseudo);
}

void CamAPI::store_pc(float*& pc) {
	this->pc_ret_buf->add_item(pc);
}

int CamAPI::get_existed_cnt() {
	return this->amp_ret_buf->get_capcity();
}

uint8_t* CamAPI::get_ret_amp() {
	auto tmp = this->amp_ret_buf->take();
	if (tmp == nullptr) {
		return nullptr;
	} else {
		return tmp;
	}
}

uint8_t* CamAPI::get_ret_depth() {
	auto tmp = this->depth_ret_buf->take();
	if (tmp == nullptr) {
		return nullptr;
	} else {
		return tmp;
	}
}

float* CamAPI::get_ret_pc() {
	auto tmp = this->pc_ret_buf->take();
	if (tmp == nullptr) {
		return nullptr;
	} else {
		return tmp;
	}
}

void CamAPI::empty_buffer() {
	this->amp_ret_buf->reset();
	this->depth_ret_buf->reset();
}

CamAPI::CamAPI() {
	this->handle = 0;
	this->amp_ret_buf = new Buffer<uint8_t*>(128);
	this->depth_ret_buf = new Buffer<uint8_t*>(128);
	this->pc_ret_buf = new Buffer<float*>(32);
}

CamAPI::~CamAPI() {
	delete this->amp_ret_buf;
	delete this->depth_ret_buf;
	delete this->pc_ret_buf;
}