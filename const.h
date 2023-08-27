#pragma once

#ifndef CONST_H
#define CONST_H

#define IP_SERVER "192.168.10.100"
#define PORT_SERVER 65300


#define NUM_IMG_RECV 4   //�������Ͻ��յ���ͼ����󻺴�
#define IMG_HEIGHT  480
#define IMG_WIDTH   640
#define PIX_SIZE    2
#define MAX_LEN_IMG_DATA (IMG_HEIGHT*IMG_WIDTH*PIX_SIZE)

#define DEF_MIN_PSEUDO_COLOR 0
#define DEF_MAX_PSEUDO_COLOR 4000

#define PIXEL_DEPTH_INVALID 0  //���ֵ��Ч

#define CAPTURE_IMG_DIR "capture"


#define MAX_DEPTH 50000
#define DEF_MAX_DEPTH 5000
#define DEF_AVERAGE_FRAMES 3
#define MAX_AVERAGE_FRAMES 64
#endif // CONST_H
