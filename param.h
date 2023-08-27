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
        int gain;       //��ֵͼ�����汶��
        int xPix;       //ͼ�����ص�����㣬������ʾ�ص����Ϣ
        int yPix;       //ͼ�����ص�����㣬������ʾ�ص����Ϣ
        bool enablePointCloud;  //�Ƿ���ʾ����
        double c_x;
        double c_y;
        double f_x;
        double f_y;
        double f_avg;
        //����ͼ��
        bool img_save;
        int img_num_save;
        int index_img_save;

        //setting
        int averFrames; //���ͼƽ��ֵʹ�õ�֡��
        int burst;      //�ع�
        std::string devIP;   //�豸ip

    };
    static Param* GetInstance();
    StrcParam param;

    void SetBurst(int burst);


};

#endif // PARAM_H
