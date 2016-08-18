#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
CvCapture* g_capture = NULL;//����һ��CvCapture����ָ��,���ڽ���cvCreateFileCapture�ķ���ֵ
int countFrames = 0;//����Ƶ֡���м����ı���

void videoplayer(CvCapture* capture,char *folder_path)
{
	//��ȡ��Ƶ����֡��
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
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
		//������ ������Ƶ�Ĳ��� �����ƶ�
		
	}
	cvReleaseCapture(&capture);
	//cvDestroyWindow("videoplayer");
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //����һ����Ƶ�ļ�
	char *folder_path = argv[2];
	//cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	videoplayer(g_capture, folder_path);
	//Invplayer(g_capture);
	return 0;
}