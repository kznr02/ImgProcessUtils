#pragma once
#include <cstdint>
#include <queue>

template<class T>
class Buffer
{
	public:
	Buffer(uint8_t cnt);
	~Buffer();
	int add_item(T& item);
	T take();
	int get_capcity();
	void reset();

	private:
	std::queue<T>* inner_buf;
	uint8_t max_size;
	uint8_t cur_cnt;
	uint8_t cur_idx;
};

template<class T>
Buffer<T>::Buffer(uint8_t cnt) {
	this->inner_buf = new std::queue<T>;
	this->cur_cnt = 0;
	this->cur_idx = 0;
	this->max_size = cnt;
}

template<class T>
Buffer<T>::~Buffer() {
	delete this->inner_buf;
}

template<class T>
int Buffer<T>::add_item(T& item) {
	if (this->inner_buf->size() < this->max_size) {
		this->inner_buf->push(item);
		return ++(this->cur_cnt);
	} else {
		return -1;
	}
}

template<class T>
T Buffer<T>::take() {
	if (this->inner_buf->size() > 0) {
		T tmp = this->inner_buf->front();
		this->inner_buf->pop();
		this->cur_cnt--;
		return tmp;
	} else {
		return nullptr;
	}
}
	

template<class T>
int Buffer<T>::get_capcity() {
	return this->inner_buf->size();
}

template<class T>
void Buffer<T>::reset() {
	for (auto&& i = 0; i < this->cur_cnt;i++) {
		this->inner_buf->pop();
	}
	this->cur_cnt = 0;
}