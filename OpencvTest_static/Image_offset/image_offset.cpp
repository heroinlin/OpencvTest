#include "PS_Algorithm.h"

int main(int argc, char** argv)
{
	//char*  Image_name=argv[1];
	char*  Image_name = "../images/cat.jpg";
	Mat Img = imread(Image_name);
	Mat Img_out(Img.size(), CV_8UC3);
	/**********************Offset******************************************/
	/*  
	int warp, xOffset, yOffset;
	xOffset = 300;
	yOffset = 200;
	warp = 1;
	Offset(Img,Img_out,xOffset,yOffset,warp);
	*/
	/***********************circle_filter**********************************/
	//circle_filter(Img, Img_out);
	/********************pinch_filter**************************************/
	pinch_filter(Img, Img_out);

	Show_Image(Img_out, "New_img");

	// cout<<"All is well."<<endl;
	// cout<<xOffset<<endl;
	// cout<<yOffset<<endl;
	waitKey();
}