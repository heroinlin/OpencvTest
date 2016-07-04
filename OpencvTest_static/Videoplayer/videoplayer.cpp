#include "cv.h"
#include "highgui.h"
CvCapture* g_capture = NULL;//����һ��CvCapture����ָ��,���ڽ���cvCreateFileCapture�ķ���ֵ
int g_slider_pos = 0;//��¼�������ĵ�ǰλ��
int frame_count = 0;//����Ƶ֡���м����ı���

//�������Ļص�����  ����int pos ��ָ��ǰ����������λ��
void on_changed(int pos)
{
	//����g_capture������,ʹ�ô�λ��pos��ʼ������Ƶ
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
	//��������������  ���ֱ���frame_count���������λ����ͬ����
	frame_count = pos;
}
void videoplayer(CvCapture* capture)
{
	//��ȡ��Ƶ����֡��
	int framecount = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
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
		//������ ������Ƶ�Ĳ��� �����ƶ�
		cvSetTrackbarPos("Position", "videoplayer", frame_count);
		frame_count++;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("videoplayer");
	}
void Invplayer(CvCapture* pCapture)
//��ɫ������Ƶ
{
	//����IplImageָ��
	IplImage* pFrame = NULL;
	uchar *data;
	int nFrmNum = 0;
	//��������
	//cvNamedWindow("video", 1);
	//��Ƶ������Ϣ
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	//��֡��ȡ��Ƶ
	if (numFrames > 0)
	{
		cvCreateTrackbar("Position", "videoplayer", &g_slider_pos, numFrames, on_changed);
	}
	while (pFrame = cvQueryFrame(pCapture))
	{
		nFrmNum++;
		printf("��ǰ֡:%d,��Ƶ��֡��:%d\n", nFrmNum, numFrames);
		data = (uchar *)pFrame->imageData;
		int height = pFrame->height;                     // ͼ��߶� 
		int width = pFrame->width;                       // ͼ���ȣ�����Ϊ��λ�� 
		int step = pFrame->widthStep;                 // �����е�ͬ�е�֮����ֽ��� 
		int channels = pFrame->nChannels;             // ��ɫͨ����Ŀ (1,2,3,4) 
		//��ɫ����
		for (int i = 0; i != height; ++i)
		{
			for (int j = 0; j != width; ++j)
			{
				for (int k = 0; k != channels; ++k)
				{
					data[i*step + j*channels + k] = 255 - data[i*step + j*channels + k];//���Խ������ȵĵ�������*.5
					//data[i*step + j*channels + k] = (data[i*step + j*channels + k]>255)?255:((data[i*step + j*channels + k]<0)?0:data[i*step + j*channels + k]);
				}
			}
		}
		if (!pFrame) break;
		cvShowImage("videoplayer", pFrame);
		char c = cvWaitKey(33);
		if (c == 27) break;
		//������ ������Ƶ�Ĳ��� �����ƶ�
		cvSetTrackbarPos("Position", "videoplayer", frame_count);
		frame_count++;
	}
	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoplayer");	
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //����һ����Ƶ�ļ�

	cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	// videoplayer(g_capture);
	Invplayer(g_capture);
	return 0;
}