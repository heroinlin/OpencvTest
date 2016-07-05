#include "box.h"
#include "image.h"
#include "matrix.h"
#include<time.h>
#include"list.h"
#include<stdio.h>
int main(int argc,char**argv)
{
	char* imagepath = argv[1];
	char* image_savepath = argv[2];
	image im = load_image(imagepath,0,0,3);
	int weight = im.w;
	int height = im.h;
	//flip_image(im);
	//translate_image(im, 10);
	//scale_image(im, 0.6);
	//im=crop_image(im, 50, 50, 30, 30);
	//image em = crop_image(im, 50, 50, 80, 80); embed_image(em,im, 100, 100);
	//im=collapse_image_layers(im, 100);
	//im = threshold_image(im, 0.5);
	image re_im=resize_image(im, weight/2, height/2);
	save_image(re_im,image_savepath);
	return 0;
}