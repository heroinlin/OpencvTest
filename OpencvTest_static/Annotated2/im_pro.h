#ifndef   IM_PRO_H
#define  IM_PRO_H
#include "box.h"
#include "getfile.h"
#include <cmath>
#define OPENCV

#ifdef OPENCV
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.hpp"
#include <opencv2/opencv.hpp> 
using namespace cv;
#endif

void anno_video_list(char *filename, float scale);
void anno_images_list(char *filename, float scale);
#endif
