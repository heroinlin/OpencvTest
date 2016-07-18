/************************************************************************/
/* 1.����Ŀ�꡾�ɶ����

2.��n��������һ֡�����浱ǰ��Ŀ�����굽txt�ı����ɶ����

3.��c�������ǰ֡�����ѱ궨���������з����ʱ�򡿻�����һ֡����������

�ļ������ʽ��֡���  Ŀ����  �������Ͻ�����   �������½�����          */
/************************************************************************/
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//ȫ�ֱ���
bool is_drawing = false;
vector<CvRect> biaozhu_boxs;
CvRect drawing_box;
IplImage *img, *img1;


static void help();
static void onMouse(int event, int x, int y, int, void*);

int main(int argc, char** argv)
{
	CvFont font;
	CvScalar scalar;
	char text[10];
	char *txt_path = argv[1];
	char *video_path = argv[2];
	// ��ʼ������
	double hScale = 1;
	double vScale = 1;
	int lineWidth = 3;// �൱��д�ֵ�����
	scalar = CV_RGB(255, 0, 0);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hScale, vScale, 0, lineWidth);//��ʼ�����壬׼��д��ͼƬ�ϵ� 

	int frame_counter = 0;
	int obj_id = 0;

	CvCapture *capture = cvCreateFileCapture(video_path);
	img = cvQueryFrame(capture);
	img1 = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	cvCopy(img, img1);

	ofstream outfile(txt_path);
	help();

	for (vector<CvRect>::iterator it = biaozhu_boxs.begin(); it != biaozhu_boxs.end(); ++it)
	{
		cvRectangle(img1, cvPoint((*it).x, (*it).y), cvPoint((*it).x + (*it).width, (*it).y + (*it).height), CV_RGB(0, 255, 0));
	}
	cvShowImage("video", img);

	cvSetMouseCallback("video", onMouse, 0);

	while (1)
	{
		int c = cvWaitKey(0);
		if ((c & 255) == 27)
		{
			cout << "Exiting ...\n";
			break;
		}

		switch ((char)c)
		{
		case 'n':
			//read the next frame
			++frame_counter;
			img = cvQueryFrame(capture);
			cvCopy(img, img1);
			if (!img){
				cout << "\nVideo Finished!" << endl;
				return 0;
			}

			//save all of the labeling rects
			for (vector<CvRect>::iterator it = biaozhu_boxs.begin(); it != biaozhu_boxs.end(); ++it)
			{
				cvRectangle(img1, cvPoint((*it).x, (*it).y), cvPoint((*it).x + (*it).width, (*it).y + (*it).height), CV_RGB(0, 255, 0));
				_itoa(obj_id, text, 10);
				cvPutText(img1, text, cvPoint((*it).x, (*it).y), &font, CV_RGB(255, 255, 255));//��ͼƬ������ַ�
				outfile << frame_counter << " " << obj_id << " " << (*it).x << " "
					<< (*it).y << " " << (*it).width << " "
					<< (*it).height << endl;
				obj_id++;
			}
			obj_id = 0;
			biaozhu_boxs.clear();//�����һ֡��ע
			break;
		case 'c':
			//clear all the rects on the image
			biaozhu_boxs.clear();
			cvCopy(img, img1);
		}
		cvShowImage("video", img1);
	}

	cvNamedWindow("video", 0);
	cvReleaseCapture(&capture);
	cvDestroyWindow("video");
	return 0;
}

static void help()
{
	cout << "This program designed for labeling video \n"
		<< "Coded by L. Wei on 9/4/2013\n" << endl;
	cout << "Use the mouse to draw rectangle on the image for labeling.\n" << endl;
	cout << "Hot keys: \n"
		"\tESC - quit the program\n"
		"\tn - next frame of the video\n"
		"\tc - clear all the labels\n"
		<< endl;
}

static void onMouse(int event, int x, int y, int, void*)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		//the left up point of the rect
		is_drawing = true;
		drawing_box.x = x;
		drawing_box.y = y;
		break;
	case CV_EVENT_MOUSEMOVE:
		//adjust the rect (use color blue for moving)
		if (is_drawing){
			drawing_box.width = x - drawing_box.x;
			drawing_box.height = y - drawing_box.y;
			cvCopy(img, img1);
			for (vector<CvRect>::iterator it = biaozhu_boxs.begin(); it != biaozhu_boxs.end(); ++it)
			{
				cvRectangle(img1, cvPoint((*it).x, (*it).y), cvPoint((*it).x + (*it).width, (*it).y + (*it).height), CV_RGB(0, 255, 0));
			}
			cvRectangle(img1, cvPoint(drawing_box.x, drawing_box.y), cvPoint(drawing_box.x + drawing_box.width, drawing_box.y + drawing_box.height), CV_RGB(255, 0, 0));
		}
		break;
	case CV_EVENT_LBUTTONUP:
		//finish drawing the rect (use color green for finish)
		if (is_drawing){
			drawing_box.width = x - drawing_box.x;
			drawing_box.height = y - drawing_box.y;
			cvCopy(img, img1);
			for (vector<CvRect>::iterator it = biaozhu_boxs.begin();
				it != biaozhu_boxs.end(); ++it){
				cvRectangle(img1, cvPoint((*it).x, (*it).y), cvPoint((*it).x + (*it).width, (*it).y + (*it).height), CV_RGB(0, 255, 0));
			}
			cvRectangle(img1, cvPoint(drawing_box.x, drawing_box.y), cvPoint(drawing_box.x + drawing_box.width, drawing_box.y + drawing_box.height), CV_RGB(255, 0, 0));
			biaozhu_boxs.push_back(drawing_box);
		}
		is_drawing = false;
		break;
	}
	cvShowImage("video", img1);
	return;
}