#include "param.h"
#include "const.h"
#include "pch.h"

Param::Param() {
    param.max_PseudoColor = DEF_MAX_PSEUDO_COLOR;
    param.min_PseudoColor = DEF_MIN_PSEUDO_COLOR;
    param.xPix = 0;
    param.yPix = 0;
    param.enablePointCloud = false;
    param.c_x = 315.3;
    param.c_y = 233.79;
    param.f_x = 581.85;
    param.f_y = 582.52;
    param.f_avg = (param.f_x + param.f_y) / 2.0f;
    param.img_save = false;
    param.img_num_save = 0;
    param.index_img_save = 0;

    param.averFrames = 1;//DEF_AVERAGE_FRAMES ;
    param.burst = 1;
    param.devIP = IP_SERVER;

}


void Param::SetBurst(int burst) {
    param.burst = burst;
}

Param* Param::GetInstance() {
    static Param mParam;
    return &mParam;
}
