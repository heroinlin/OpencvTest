#ifndef _GETFILE_H_
#define _GETFILE_H_

//OpencvDirTraverse.cpp : Defines the entry point for the console application.
#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "opencv\cv.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace std;
using namespace cv;
void getFiles(string path, string exd, vector<string>& files);
#endif // !_GETFILE_H_
