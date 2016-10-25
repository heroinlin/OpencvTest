#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
#include  <time.h>
/*
视频录像，截取视频片段，截图
无参数则打开外部摄像头，附加视频路径则打开本地视频
按下'r'键进行录像，重新按下退出录像功能
鼠标在视频窗口点击保存当前帧图像
*/
IplImage *frame = 0;
int button_down_count = 0;

void mouseHandler(int event, int x, int y, int flags, void *param);

int main(int argc, char **argv)
{
	CvCapture *capture = 0;

	int flag = 1;
	int frame_num = 0;
	int iscolor = 1;
	int fps = 25;
	int press = 0;
	CvVideoWriter    *writer = NULL;

	if (argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
	{
		capture = cvCaptureFromCAM(0);
	}
	else if (argc == 2)
	{
		capture = cvCaptureFromAVI(argv[1]);
	}

	if (!capture)
	{
		fprintf(stderr, "Could not initialize capturing.../n");
		return -1;
	}

	cvNamedWindow("video", 0);

	cvSetMouseCallback("video", mouseHandler, NULL);
	for (;;)
	{
		frame = cvQueryFrame(capture);
		if (!frame & frame_num > 0)
		{
			break;
		}
		if (frame_num > 0)
		{
			if (flag == 0)
			{
				cvWriteFrame(writer, frame);	
			}
			cvShowImage("video", frame);
			press = cvWaitKey(33);
			if (press == 'r')
			{
				if (flag == 1)
				{
					writer = cvCreateVideoWriter("./out.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, cvSize(frame->width, frame->height),1);
					printf("Starting Record the Video!\n");
					flag = 0;
				}
				else
				{
					cvReleaseVideoWriter(&writer);
					printf("Stop the recording!\n");
					flag = 1;
				}
			}
			else if (press == 27)
			{
				break;
			}

		}
		frame_num++;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("video");
	return 0;
}

void mouseHandler(int event, int x, int y, int flags, void *param)
{
	time_t curtime = time(NULL);
	char *date = ctime(&curtime);

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		printf("Get a picture named %07d.jpg at %s\n", button_down_count, date + 11);
		sprintf(date, "./%07d.jpg", button_down_count++);
		cvSaveImage(date, frame,0);
		break;
	default:
		break;
	}
}

