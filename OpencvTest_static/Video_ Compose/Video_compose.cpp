//ͼƬ�ϳ�Ϊ��Ƶ
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	CvSize size = cvSize(480, 360);
	double fps = 1;
	char *output = "out.avi";
	//����һ��д��Ƶ �豸writer 
	CvVideoWriter* writer = cvCreateVideoWriter(output, CV_FOURCC('X', 'V', 'I', 'D'), fps, size,1);
	/*����һ���ļ����µ�����ͼƬ*/
	int image_id = 1;
	char filename[256];
	char *filepath=argv[1];
	sprintf(filename, "%s/%07d.jpg", filepath,image_id);
	printf("%s\n",filename);
	//����ͼ��
	IplImage* src = cvLoadImage(filename);
	if (!src)
	{
		return 0;
	}
	//Ϊresize���ͼ�����ռ�
	IplImage* src_resize = cvCreateImage(size, 8, 3);
	cvNamedWindow("avi");
	while (src)
	{
		/*��ʾͼ�� �����費�Ǳ����*/
		cvShowImage("avi", src_resize);
		cvWaitKey(1);
		/*resizeͼ�� ʹ��д����Ƶ�ļ���ͼ��src_resize �� ��Ƶ�ļ��Ŀ� �� ��һ���� ��Ƶ�ļ��Ŀ� ����CvSize size = cvSize(480,360);*/
		cvResize(src, src_resize);
		/*��ͼ��src_resize д�뵽��Ƶ�豸writer*/
		cvWriteFrame(writer, src_resize);
		/*�ͷ��ڴ�ռ�*/
		cvReleaseImage(&src);
		//�����ļ����е���һ��ͼ�� 
		image_id++;
		sprintf(filename, "%s/%07d.jpg", filepath, image_id);
		src = cvLoadImage(filename);
	}
	/*�ͷ�д�豸*/
	cvReleaseVideoWriter(&writer);
	/*�ͷ�ͼ��ռ�*/
	cvReleaseImage(&src_resize);
	return 0;

}