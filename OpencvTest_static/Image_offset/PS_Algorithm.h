// define head function
#ifndef PS_ALGORITHM_H_INCLUDED
#define PS_ALGORITHM_H_INCLUDED

#include <iostream>
#include <string>
#include "cv.h"
#include "highgui.h"
#include "cxcore.hpp"
#include "math.h"

using namespace std;
using namespace cv;
void Linear_Burn(Mat& src1, Mat& src2, Mat& dst); //���Լ���
void Linear_Dodge(Mat& src1, Mat& src2, Mat& dst);//���Լ���
void Lighten(Mat& src1, Mat& src2, Mat& dst);//����
void Darken(Mat& src1, Mat& src2, Mat& dst);//�䰵
void Offset(Mat Img, Mat Img_out, int xOffset, int yOffset, int warp);/*Image offset.ͼ��ƫ��,(xOffset,yOffset)Ϊƫ������warpƫ�ƿ���*/
void circle_filter(Mat& Img, Mat& Img_out);//��Ͳ
void pinch_filter(Mat& Img, Mat& Img_out);//��ѹ
void Show_Image(Mat&, const string &);

#endif // PS_ALGORITHM_H_INCLUDED