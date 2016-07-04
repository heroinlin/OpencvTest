#include "cv.h"
#include "highgui.h"
CvCapture* g_capture = NULL;//声明一个CvCapture类型指针,用于接收cvCreateFileCapture的返回值
int g_slider_pos = 0;//记录滚动条的当前位置
int frame_count = 0;//对视频帧进行计数的变量

//滚动条的回调函数  参数int pos 是指当前滚动条所在位置
void on_changed(int pos)
{
	//设置g_capture的属性,使得从位置pos开始播放视频
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
	//在拉动滚动条后  保持变量frame_count与滚动条的位置是同步的
	frame_count = pos;
}
void videoplayer(CvCapture* capture)
{
	//获取视频的总帧数
	int framecount = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//在窗口show上创建名字为Position的滚动条
	if (framecount > 0)
	{
		cvCreateTrackbar("Position","videoplayer",&g_slider_pos,framecount,on_changed);
	}
	while (1)
	{
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("videoplayer", frame);
		char c = cvWaitKey(1);
		if (c == 27) break;
		//滚动条 随着视频的播放 进行移动
		cvSetTrackbarPos("Position", "videoplayer", frame_count);
		frame_count++;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("videoplayer");
	}
void Invplayer(CvCapture* pCapture)
//反色播放视频
{
	//声明IplImage指针
	IplImage* pFrame = NULL;
	uchar *data;
	int nFrmNum = 0;
	//创建窗口
	//cvNamedWindow("video", 1);
	//视频参数信息
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	//逐帧读取视频
	if (numFrames > 0)
	{
		cvCreateTrackbar("Position", "videoplayer", &g_slider_pos, numFrames, on_changed);
	}
	while (pFrame = cvQueryFrame(pCapture))
	{
		nFrmNum++;
		printf("当前帧:%d,视频总帧数:%d\n", nFrmNum, numFrames);
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
					data[i*step + j*channels + k] = 255 - data[i*step + j*channels + k];//可以进行亮度的调整，如*.5
					//data[i*step + j*channels + k] = (data[i*step + j*channels + k]>255)?255:((data[i*step + j*channels + k]<0)?0:data[i*step + j*channels + k]);
				}
			}
		}
		if (!pFrame) break;
		cvShowImage("videoplayer", pFrame);
		char c = cvWaitKey(33);
		if (c == 27) break;
		//滚动条 随着视频的播放 进行移动
		cvSetTrackbarPos("Position", "videoplayer", frame_count);
		frame_count++;
	}
	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoplayer");	
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //打开有一个视频文件

	cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	// videoplayer(g_capture);
	Invplayer(g_capture);
	return 0;
}