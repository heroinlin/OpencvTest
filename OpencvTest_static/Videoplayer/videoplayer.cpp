#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <stdio.h>
CvCapture* g_capture = NULL;//����һ��CvCapture����ָ��,���ڽ���cvCreateFileCapture�ķ���ֵ
int g_slider_pos = 0;//��¼�������ĵ�ǰλ��
int countFrames = 0;//����Ƶ֡���м����ı���
int key;
int stopflag = 1;
int speed = 33;
//�������Ļص�����  ����int pos ��ָ��ǰ����������λ��
void on_changed(int pos)
{
	//����g_capture������,ʹ�ô�λ��pos��ʼ������Ƶ
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
	//��������������  ���ֱ���frame_count���������λ����ͬ����
	countFrames = pos;
}
void videoplayer(CvCapture* capture)
{
	//��ȡ��Ƶ����֡��
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	//�ڴ���show�ϴ�������ΪPosition�Ĺ�����
	if (numFrames > 0)
	{
		cvCreateTrackbar("Position", "videoplayer", &g_slider_pos, numFrames, on_changed);
	}
	while (countFrames<numFrames)
	{
		IplImage* frame = cvQueryFrame(capture);
		if (!frame) break;
		countFrames++;
		cvShowImage("videoplayer", frame);
		char savename[256];
		sprintf(savename,"./images/%07d.jpg",countFrames);
		if (stopflag == 1)
			key = cvWaitKey(speed);
		else key = cvWaitKey(0);
		switch (key)
		{
		case 32:{ stopflag = !stopflag; break; }
		case 'c':{ countFrames -= 1; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'C':{  countFrames -= 1;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'd':{ countFrames -= 2; if (countFrames < 0)countFrames = 0; cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'D':{ countFrames -= 2; if (countFrames < 0)countFrames = 0;  cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 's':{ cvSaveImage(savename, frame, 0); break; }
		case 'S':{ cvSaveImage(savename, frame, 0); break; }
		case 'o':{ speed += 10; break; }
		case 'i':{ speed -= 10; break; }
		case 'l':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		case 'L':{ countFrames += 5; if (countFrames < numFrames) cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, countFrames); break; }
		default:{}
		}
		//������ ������Ƶ�Ĳ��� �����ƶ�
		cvSetTrackbarPos("Position", "videoplayer", countFrames);
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
		/*�ڱ�ǩ����ʾ�����֣���ʾ����������;�� "Position"
		  �����Ļ�����Ҫ���ô�������� "videoplayer"
		  ��������ȡֵ��Χ�� 0 �� numFrames(��Сֵֻ��Ϊ zero).
		  �������ֵ����� g_slider_pos ������
		  ÿ����������ֵ�ı�, �ͻ���� on_changed �ص�����*/
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
		cvSetTrackbarPos("Position", "videoplayer", countFrames);
		countFrames++;
	}
	cvReleaseCapture(&pCapture);
	cvDestroyWindow("videoplayer");	
}
int main(int argc, char* argv[])
{
	char *videopath = argv[1];
	g_capture = cvCreateFileCapture(videopath); //����һ����Ƶ�ļ�

	cvNamedWindow("videoplayer", CV_WINDOW_AUTOSIZE);
	 videoplayer(g_capture);
	//Invplayer(g_capture);
	return 0;
}