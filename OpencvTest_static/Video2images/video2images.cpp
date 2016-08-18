#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
CvCapture* g_capture = NULL;//声明一个CvCapture类型指针,用于接收cvCreateFileCapture的返回值
int countFrames = 0;//对视频帧进行计数的变量

void videoplayer(CvCapture* capture,char *folder_path)
{
	//获取视频的总帧数
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//在窗口show上创建名字为Position的滚动条
	while (countFrames<numFrames)
	{
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) break;
		countFrames++;
		//cvShowImage("videoplayer", frame);
		char savename[256];
		sprintf(savename, "%s/%07d.jpg", folder_path,countFrames);
		printf("save  %s/%07d.jpg", folder_path, countFrames);
		cvSaveImage(savename, frame, 0);
		//滚动条 随着视频的播放 进行移动
		
	}
	cvReleaseCapture(&capture);
	//cvDestroyWindow("videoplayer");
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //打开有一个视频文件
	char *folder_path = argv[2];
	//cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	videoplayer(g_capture, folder_path);
	//Invplayer(g_capture);
	return 0;
}