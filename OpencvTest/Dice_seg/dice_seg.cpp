#include <cv.h>
#include <highgui.h>
#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>


int main(int argc, char* argv[])
{
	IplImage *src = 0; //����Դͼ��ָ��

	IplImage *tmp = 0; //������ʱͼ��ָ��

	IplImage *src_back = 0; //����Դͼ�񱳾�ָ��

	IplImage *dst_gray = 0; //����Դ�ļ�ȥ���������Ŀ��Ҷ�ͼ��ָ��

	IplImage *dst_bw = 0; //����Դ�ļ�ȥ���������Ŀ���ֵͼ��ָ��

	IplImage *dst_contours = 0; //��������ͼ��ָ��

	IplConvKernel *element = 0; //������̬ѧ�ṹָ��

	int Number_Object = 0; //����Ŀ���������

	int contour_area_tmp = 0; //����Ŀ����������ʱ�Ĵ���

	int contour_area_sum = 0; //����Ŀ�����ж�������ĺ�

	int contour_area_ave = 0; //����Ŀ��������ƽ��ֵ

	int contour_area_max = 0; //����Ŀ�����������ֵ

	CvMemStorage *stor = 0;
	CvSeq * cont = 0;
	CvContourScanner contour_scanner;
	CvSeq * a_contour = 0;

	//1.��ȡ����ʾͼ��

	/* the first command line parameter must be image file name */
	if (argc == 2 && (src = cvLoadImage(argv[1], 0)) != 0)
	{
		;
	}
	else
	{
		src = cvLoadImage("rice.jpg", 0);
	}
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvShowImage("src", src);
	//cvSmooth(src, src, CV_MEDIAN, 3, 0, 0, 0); //��ֵ�˲�������С��������

	//2.����ͼ�񱳾�

	tmp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	src_back = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	//�����ṹԪ��

	element = cvCreateStructuringElementEx(4, 4, 1, 1, CV_SHAPE_ELLIPSE, 0);
	//�øýṹ��Դͼ�������ѧ��̬ѧ�Ŀ������󣬹��Ʊ�������

	cvErode(src, tmp, element, 10);
	cvDilate(tmp, src_back, element, 10);
	cvNamedWindow("src_back", CV_WINDOW_AUTOSIZE);
	cvShowImage("src_back", src_back);

	//3.��Դͼ���м�������ͼ��

	dst_gray = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvSub(src, src_back, dst_gray, 0);
	cvNamedWindow("dst_gray", CV_WINDOW_AUTOSIZE);
	cvShowImage("dst_gray", dst_gray);

	//4.ʹ����ֵ������ͼ��ת��Ϊ��ֵͼ��

	dst_bw = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvThreshold(dst_gray, dst_bw, 50, 255, CV_THRESH_BINARY); //ȡ��ֵΪ50��ͼ��תΪ��ֵͼ��

	//cvAdaptiveThreshold( dst_gray, dst_bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5 );

	cvNamedWindow("dst_bw", CV_WINDOW_AUTOSIZE);
	cvShowImage("dst_bw", dst_bw);

	//5.���ͼ���е�Ŀ���������

	stor = cvCreateMemStorage(0);
	cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), stor);
	Number_Object = cvFindContours(dst_bw, stor, &cont, sizeof(CvContour),
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0)); //�ҵ���������

	printf("Number_Object: %d\n", Number_Object);

	//6.����ͼ���ж����ͳ������

	dst_contours = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvThreshold(dst_contours, dst_contours, 0, 255, CV_THRESH_BINARY_INV); //�ڻ�����ǰ�Ȱ�ͼ���ɰ�ɫ

	for (; cont; cont = cont->h_next)
	{
		cvDrawContours(dst_contours, cont, CV_RGB(255, 0, 0), CV_RGB(255, 0, 0), 0, 1, 8, cvPoint(0, 0)); //���Ƶ�ǰ����

		contour_area_tmp = fabs(cvContourArea(cont, CV_WHOLE_SEQ)); //��ȡ��ǰ�������

		if (contour_area_tmp > contour_area_max)
		{
			contour_area_max = contour_area_tmp; //�ҵ������������

		}
		contour_area_sum += contour_area_tmp; //�����������������

	}
	contour_area_ave = contour_area_sum / Number_Object; //�������������ƽ��ֵ

	printf("contour_area_ave: %d\n", contour_area_ave);
	printf("contour_area_max: %d\n", contour_area_max);
	cvNamedWindow("dst_contours", CV_WINDOW_AUTOSIZE);
	cvShowImage("dst_contours", dst_contours);

	cvWaitKey(-1); //�ȴ��˳�

	cvReleaseImage(&src);
	cvReleaseImage(&tmp);
	cvReleaseImage(&src_back);
	cvReleaseImage(&dst_gray);
	cvReleaseImage(&dst_bw);
	cvReleaseImage(&dst_contours);
	cvReleaseMemStorage(&stor);
	cvDestroyWindow("src");
	cvDestroyWindow("src_back");
	cvDestroyWindow("dst_gray");
	cvDestroyWindow("dst_bw");
	cvDestroyWindow("dst_contours");
	//void cvDestroyAllWindows(void);

	return 0;
}