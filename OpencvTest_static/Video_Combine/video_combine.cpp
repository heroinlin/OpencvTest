//两视频着帧相加
#include <string>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <fstream>
#include <iostream>
#include<vector>
using namespace std;
using namespace cv;
extern void getFiles(string path, string exd, vector<string>& files);

string num2str(int i);
void video_combine(string& video_path1, string& video_path2)
{
	
	vector<string> video_names;
	getFiles(video_path1, "avi", video_names);
	vector<string> video_names2;
	getFiles(video_path2, "avi", video_names2);
//********************//
	for (unsigned video_index = 0; video_index < video_names.size(); video_index++)
	{
		//视频
		string name = video_names[video_index];
		cout << "process " << video_names[video_index] << endl;
		VideoCapture video_cap(name);
		if (video_cap.isOpened() == false)
		{
			cout << " video_cap.isOpened() == false " << endl;
			system("pause");
		}
		
		string name2 = video_names2[video_index];
		VideoCapture video_cap2(name2);
		if (video_cap2.isOpened() == false)
		{
			cout << " video_cap2.isOpened() == false " << endl;
			system("pause");
		}
		IplImage* pFrame = NULL;
		Mat frame;
		Mat frame2;
		namedWindow("avi");
		int frameH = (int)video_cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		int frameW = (int)video_cap.get(CV_CAP_PROP_FRAME_WIDTH);
		int fps = (int)video_cap.get(CV_CAP_PROP_FPS);
		int numframe = (int)video_cap.get(CV_CAP_PROP_FRAME_COUNT);
		int fnumber = 0;//当前帧数
		static CvVideoWriter* output_video = NULL;
		CvSize size;
		{
			size.width = frameW, size.height = frameH;
		}
//*************************//
		while (fnumber<numframe)
		{
			if (!video_cap.read(frame))
				break;
			//*****按帧读入****//
			if (!video_cap2.read(frame2))
				break;
			fnumber++;
			printf("当前帧:%d,视频总帧数:%d\n", fnumber, numframe);
			if (output_video == NULL)
			{
				char output_name [256];
				sprintf(output_name, "./videos_result/%03d.avi", video_index);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('H', '2', '6', '4'), 25, size, 1);
				output_video = cvCreateVideoWriter(output_name, CV_FOURCC('D', 'I', 'V', 'X'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('X', 'V', 'I', 'D'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('M', 'J', 'P', 'G'), 25, size, 1);
			}
			Mat frame1 = 0.5*frame + 0.5*frame2;

			pFrame = (&(IplImage)frame1 );//convert  mat -> iplimage*    //Mat mtx(img); // convert IplImage* -> Mat
			cvWriteFrame(output_video, pFrame);
			//imshow("avi", frame1);
			cvShowImage("avi", pFrame);
				cvWaitKey(1);
		}
		cvReleaseVideoWriter(&output_video);
		cvDestroyWindow("avi");
	}
}
void main(int argc,char**argv)
{
	string video_path = argv[1];
	string video_path2 = argv[2];
	//string save_path = argv[3];
	video_combine(video_path, video_path2);
}