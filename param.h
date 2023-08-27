#pragma once

#ifndef PARAM_H
#define PARAM_H
#include <string>

class Param {
public:
    Param();

    struct StrcParam {
        int min_PseudoColor;
        int max_PseudoColor;
        int gain;       //幅值图，增益倍数
        int xPix;       //图像像素的坐标点，用于显示素点的信息
        int yPix;       //图像像素的坐标点，用于显示素点的信息
        bool enablePointCloud;  //是否显示点云
        double c_x;
        double c_y;
        double f_x;
        double f_y;
        double f_avg;
        //保存图像
        bool img_save;
        int img_num_save;
        int index_img_save;

        //setting
        int averFrames; //深度图平均值使用的帧数
        int burst;      //曝光
        std::string devIP;   //设备ip

    };
    static Param* GetInstance();
    StrcParam param;

    void SetBurst(int burst);


};

#endif // PARAM_H
