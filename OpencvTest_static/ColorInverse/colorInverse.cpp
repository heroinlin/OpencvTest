//视频反色
#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "getfile.h"

void VideoInverse(CvCapture* pCapture, char* output_name)
{
	//声明IplImage指针
	IplImage* pFrame = NULL;
	uchar *data;
	int nFrmNum = 0;
	//创建窗口
	//cvNamedWindow("video", 1);
	static CvVideoWriter* output_video = NULL;    // cv::VideoWriter output_video
	//视频参数信息
	int frameH = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FPS);
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	CvSize size;
	{
		size.width = frameW, size.height = frameH;
	}
	//逐帧读取视频
	while (pFrame = cvQueryFrame(pCapture))
	{
		nFrmNum++;
		printf("当前帧:%d,视频总帧数:%d\n",nFrmNum,numFrames);
			data = (uchar *)pFrame->imageData;
			int height = pFrame->height;                     // 图像高度 
			int width = pFrame->width;                       // 图像宽度（像素为单位） 
			int step = pFrame->widthStep;                 // 相邻行的同列点之间的字节数 
			int channels = pFrame->nChannels;             // 颜色通道数目 (1,2,3,4) 
			//反色操作
			for (int i = 0; i != height; ++i)
			{
				for (int j = 0; j != width; ++j)
				{
					for (int k = 0; k != channels; ++k)
					{
						data[i*step + j*channels + k] = 255-data[i*step + j*channels + k];//可以进行亮度的调整，如*.5
						//data[i*step + j*channels + k] = (data[i*step + j*channels + k]>255)?255:((data[i*step + j*channels + k]<0)?0:data[i*step + j*channels + k]);
					}
				}
			}
			if (output_video == NULL)
			{
				//char* output_name = "out.avi";
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('H', '2', '6', '4'), 25, size, 1);
				output_video = cvCreateVideoWriter(output_name, CV_FOURCC('D', 'I', 'V', 'X'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('X', 'V', 'I', 'D'), fps, size, 1);
				//output_video = cvCreateVideoWriter(output_name, CV_FOURCC('M', 'J', 'P', 'G'), 25, size, 1);
			}
			//显示图像
			cvWriteFrame(output_video, pFrame);
			//cvShowImage("video", pFrame);
			//如果有按键事件，则跳出循环
			//此等待也为cvShowImage函数提供时间完成显示
			//等待时间可以根据CPU速度调整
			if (cvWaitKey(1) >= 0)
				break;
		}
	cvReleaseVideoWriter(&output_video);
	cvReleaseImage(&pFrame);
}
int main(int argc, char** argv)
{
	
	/*
	//单视频处理  ColorInverse.exe [video_file_name]  [video_savefile_name]
	CvCapture* pCapture = NULL;
	if (argc > 3)
	{
		fprintf(stderr, "Usage: bkgrd [video_file_name]  [video_savefile_name]\n");
		return -1;
	}
	//打开摄像头
	if (argc == 1)
		if (!(pCapture = cvCaptureFromCAM(-1)))
		{
			fprintf(stderr, "Can not open camera.\n");
			return -2;
		}
	//打开视频文件
	if (argc >= 2)
		if (!(pCapture = cvCaptureFromFile(argv[1])))
		{
			fprintf(stderr, "Can not open video file %s\n", argv[1]);
			return -2;
		}
	char* output_name = argv[2];
	VideoInverse(pCapture,output_name);
	return 1;
	*/
	//视频文件夹处理 ColorInverse.exe [video_file_fold]
	if (argc != 2)
	{
		fprintf(stderr, "Usage: bkgrd [videofile_fold]\n");
		return -1;
	}
	char *video_list = argv[1];
	vector<string> image_names;
	getFiles(video_list, "", image_names);
	for (int i = 0; i < image_names.size(); i++)
	{
		CvCapture* pCapture = NULL;
		string fileName = image_names[i];
		cout << "file name:" << fileName << endl;
		pCapture = cvCaptureFromFile(fileName.c_str());
		char output_name[256];
		sprintf(output_name, "./videos_result/%03d.avi", i);
		VideoInverse(pCapture, output_name);
	}
	return 1;
}
	