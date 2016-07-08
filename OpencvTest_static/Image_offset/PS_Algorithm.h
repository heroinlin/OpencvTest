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
void Linear_Burn(Mat& src1, Mat& src2, Mat& dst); //线性加深
void Linear_Dodge(Mat& src1, Mat& src2, Mat& dst);//线性减淡
void Lighten(Mat& src1, Mat& src2, Mat& dst);//变亮
void Darken(Mat& src1, Mat& src2, Mat& dst);//变暗
void Offset(Mat Img, Mat Img_out, int xOffset, int yOffset, int warp);/*Image offset.图像偏移,(xOffset,yOffset)为偏移量，warp偏移开关*/
void circle_filter(Mat& Img, Mat& Img_out);//万花筒
void pinch_filter(Mat& Img, Mat& Img_out);//挤压
void Show_Image(Mat&, const string &);

#endif // PS_ALGORITHM_H_INCLUDED