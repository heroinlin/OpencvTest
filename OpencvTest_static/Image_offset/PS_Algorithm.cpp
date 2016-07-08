// define the show image
#include "PS_Algorithm.h"
#include <iostream>
#include <string>
#define pi 3.1415926
#ifdef _DEBUG 

#pragma comment( lib, "opencv_core249d.lib" )
#pragma comment( lib, "opencv_highgui249d.lib" )
#pragma comment( lib, "opencv_imgproc249d.lib" )
#pragma comment( lib, "IlmImfd.lib")
#pragma comment( lib, "libjasperd.lib")
#pragma comment( lib, "libjpegd.lib")
#pragma comment( lib, "libpngd.lib")
#pragma comment( lib, "libtiffd.lib")
#pragma comment( lib, "zlibd.lib")
#else 
#pragma comment( lib, "opencv_core249.lib" )
#pragma comment( lib, "opencv_highgui249.lib" )
#pragma comment( lib, "opencv_imgproc249.lib" )
#pragma comment( lib, "IlmImf.lib")
#pragma comment( lib, "libjasper.lib")
#pragma comment( lib, "libjpeg.lib")
#pragma comment( lib, "libpng.lib")
#pragma comment( lib, "libtiff.lib")
#pragma comment( lib, "zlib.lib")
#endif
#pragma comment( lib, "vfw32.lib" )  
#pragma comment( lib, "comctl32.lib" ) 
using namespace std;
using namespace cv;

void Linear_Burn(Mat& src1, Mat& src2, Mat& dst)
{
	for (int index_row = 0; index_row < src1.rows; index_row++)
	{
		for (int index_col = 0; index_col < src1.cols; index_col++)
		{
			for (int index_c = 0; index_c < 3; index_c++)
				dst.at<Vec3f>(index_row, index_col)[index_c] = max(
				src1.at<Vec3f>(index_row, index_col)[index_c] +
				src2.at<Vec3f>(index_row, index_col)[index_c] - 1, (float)0.0);
		}
	}
}

// linear dodge
void Linear_Dodge(Mat& src1, Mat& src2, Mat& dst)
{
	for (int index_row = 0; index_row < src1.rows; index_row++)
	{
		for (int index_col = 0; index_col < src1.cols; index_col++)
		{
			for (int index_c = 0; index_c < 3; index_c++)
				dst.at<Vec3f>(index_row, index_col)[index_c] = min(
				src1.at<Vec3f>(index_row, index_col)[index_c] +
				src2.at<Vec3f>(index_row, index_col)[index_c], (float)1.0);
		}
	}
}

// Lighten
void Lighten(Mat& src1, Mat& src2, Mat& dst)
{
	for (int index_row = 0; index_row < src1.rows; index_row++)
	{
		for (int index_col = 0; index_col < src1.cols; index_col++)
		{
			for (int index_c = 0; index_c < 3; index_c++)
				dst.at<Vec3f>(index_row, index_col)[index_c] = max(
				src1.at<Vec3f>(index_row, index_col)[index_c],
				src2.at<Vec3f>(index_row, index_col)[index_c]);
		}
	}
}

// Darken
void Darken(Mat& src1, Mat& src2, Mat& dst)
{
	for (int index_row = 0; index_row < src1.rows; index_row++)
	{
		for (int index_col = 0; index_col < src1.cols; index_col++)
		{
			for (int index_c = 0; index_c < 3; index_c++)
				dst.at<Vec3f>(index_row, index_col)[index_c] = min(
				src1.at<Vec3f>(index_row, index_col)[index_c],
				src2.at<Vec3f>(index_row, index_col)[index_c]);
		}
	}
}

void Offset(Mat Img, Mat Img_out, int xOffset, int yOffset, int warp)
{

	int width = Img.cols;
	int height = Img.rows;

	if (warp)
	{
		while (xOffset < 0)
			xOffset = xOffset + width;

		while (yOffset < 0)
			yOffset = yOffset + height;

		xOffset = xOffset%width;
		yOffset = yOffset%height;
	}

	int new_x, new_y;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (warp)
			{
				new_x = (x + width - xOffset) % width;
				new_y = (y + height - yOffset) % height;
			}
			else
			{
				new_x = x - xOffset;
				new_y = y - yOffset;
			}

			if (new_x < 0)         new_x = 0;
			if (new_x >= width - 1)  new_x = width - 2;
			if (new_y < 0)         new_y = 0;
			if (new_y >= height - 1) new_y = height - 2;


			for (int k = 0; k < 3; k++)
			{
				Img_out.at<Vec3b>(y, x)[k] = Img.at<Vec3b>(new_y, new_x)[k];

			}

		}

	}
}

void Show_Image(Mat& Image, const string& str)
{
	namedWindow(str.c_str(), CV_WINDOW_AUTOSIZE);
	imshow(str.c_str(), Image);

}

float Triangle(float x)
{
	float temp_r = fmod(x, 1.0);
	if (temp_r < 0.5)
	{
		return 2 * temp_r;
	}
	else
	{
		return 2 * (1 - temp_r);
	}

}

void circle_filter(Mat& Img, Mat& Img_out)
{
	int width = Img.cols;
	int height = Img.rows;
	float angle = pi / 4;
	float angle2 = pi / 4;
	float centreX = 0.5;
	float centreY = 0.5;
	float sides = 10;
	float icentreX = width*centreX;
	float icentreY = height*centreY;
	float radius = 150;
	float dx, dy, new_x, new_y;
	float p, q, x1, y1;
	float c, r, theta, temp_theta, radius_c;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			dx = x - icentreX;
			dy = y - icentreY;
			theta = atan2(dy, dx) - angle - angle2;
			r = sqrt(dy*dy + dx*dx);
			temp_theta = theta / pi*sides*0.5;
			theta = Triangle(temp_theta);
			if (radius)
			{
				c = cos(theta);
				radius_c = radius / c;
				r = radius_c * Triangle(r / radius_c);
			}
			theta = theta + angle;
			new_x = r * cos(theta) + icentreX;
			new_y = r * sin(theta) + icentreY;

			if (new_x < 0)         new_x = 0;
			if (new_x >= width - 1)  new_x = width - 2;
			if (new_y < 0)         new_y = 0;
			if (new_y >= height - 1) new_y = height - 2;
			//  if (new_x<0)     continue;
			//  if (new_x>=width-1)   continue;
			//  if (new_y>=height-1)  continue;
			//  if (new_y<0)  continue;
			x1 = (int)new_x;
			y1 = (int)new_y;
			p = new_x - x1;
			q = new_y - y1;
			for (int k = 0; k < 3; k++)
			{
				Img_out.at<Vec3b>(y, x)[k] = (1 - p)*(1 - q)*Img.at<Vec3b>(y1, x1)[k] +
					(p)*(1 - q)*Img.at<Vec3b>(y1, x1 + 1)[k] +
					(1 - p)*(q)*Img.at<Vec3b>(y1 + 1, x1)[k] +
					(p)*(q)*Img.at<Vec3b>(y1 + 1, x1 + 1)[k];
			}
		}
	}
}

void pinch_filter(Mat& Img, Mat& Img_out)
{

		Img.copyTo(Img_out);
		int width = Img.cols;
		int height = Img.rows;
		float angle = pi / 2;
		float centreX = 0.5;
		float centreY = 0.5;
		float radius = 200;
		float amount = 0.5;
		if (radius == 0) radius = std::min(width, height) / 2;
		float icentreX = width*centreX;
		float icentreY = height*centreY;
		float radius2 = radius*radius;

		float dx, dy, new_x, new_y;
		float p, q, x1, y1;
		float distance;
		float a, d, t, s, c, e;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x<width; x++)
			{

				dx = x - icentreX;
				dy = y - icentreY;

				distance = dx*dx + dy*dy;

				if (distance>radius2 || distance == 0)
				{
					new_x = x;
					new_y = y;
				}
				else
				{
					d = sqrt(distance / radius2);
					t = pow(sin(pi*0.5 * d), -amount);

					dx = dx* t;
					dy = dy* t;

					e = 1 - d;
					a = angle * e * e;

					s = sin(a);
					c = cos(a);

					new_x = icentreX + c*dx - s*dy;
					new_y = icentreY + s*dx + c*dy;
				}

				if (new_x < 0)         new_x = 0;
				if (new_x >= width - 1)  new_x = width - 2;
				if (new_y < 0)         new_y = 0;
				if (new_y >= height - 1) new_y = height - 2;

				x1 = (int)new_x;
				y1 = (int)new_y;

				p = new_x - x1;
				q = new_y - y1;

				for (int k = 0; k < 3; k++)
				{
					Img_out.at<Vec3b>(y, x)[k] = (1 - p)*(1 - q)*Img.at<Vec3b>(y1, x1)[k] +
						(p)*(1 - q)*Img.at<Vec3b>(y1, x1 + 1)[k] +
						(1 - p)*(q)*Img.at<Vec3b>(y1 + 1, x1)[k] +
						(p)*(q)*Img.at<Vec3b>(y1 + 1, x1 + 1)[k];
				}

			}
		}
}


