#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include"getfile.h"

void image_convert(char *orig_image_path,char *conv_image_path)
{
	IplImage* src;
	if ((strstr(orig_image_path, ".jpg") == NULL
		&& strstr(orig_image_path, ".bmp") == NULL
		&& strstr(orig_image_path, ".tif") == NULL
		&& strstr(orig_image_path, ".png") == NULL
		&& strstr(orig_image_path, ".ppm") == NULL)
		|| (strstr(conv_image_path, ".jpg") == NULL
		&& strstr(conv_image_path, ".bmp") == NULL
		&& strstr(conv_image_path, ".tif") == NULL
		&& strstr(conv_image_path, ".png") == NULL
		&& strstr(conv_image_path, ".ppm") == NULL))
	{
		printf("WARNING: CONV only support JPG,BMP,TIF,PPM,TGA and PPM\n");
	}
	else 
	{
		if ((src = cvLoadImage(orig_image_path, -1)) != 0) 
		{
			cvSaveImage(conv_image_path, src, 0);
			cvReleaseImage(&src);
		}
		else
		{
			printf("\n*** Read or write image fails *** \n");
		}
	}
}

//����һ��ԭͼ���ļ���·��������2��ͼ�񱣴��ļ���·��������3��ת�����ͼƬ��ʽjpg
int main(int argc, char **argv)
{
	char *orig_image_folder = argv[1];
	char *conv_image_folder = argv[2];
	char *conv_image_format = argv[3];
	vector<string> image_names;
	getFiles(orig_image_folder, "", image_names);
	int i;
	for (i = 0; i < image_names.size(); i++)
	{
		char orig_image[256];
		sprintf(orig_image, "%s", image_names[i]);
		char conv_image[256];
		sprintf(conv_image, "%s/%07d.%s", conv_image_folder, i + 1, conv_image_format);
		image_convert(orig_image, conv_image);
		printf("\n Convert %s successfully.\n", image_names[i]);
	}
	return 0;
}