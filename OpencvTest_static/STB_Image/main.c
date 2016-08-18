#include "box.h"
#include "image.h"
#include "matrix.h"
#include<time.h>
#include"list.h"
#include<stdio.h>
void embed_image1(image source, image dest, int dx, int dy)
//将source图像嵌入到图像dest中，（dx，dy）处
{
	int x, y, k;
	for (k = 0; k < source.c; ++k){
		for (y = 0; y < source.h; ++y){
			for (x = 0; x < source.w; ++x){
				float val = get_pixel(source, x, y, k);
				if (val<0.8)
					set_pixel(dest, dx + x, dy + y, k, val);
			}
		}
	}
}
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
	image em = load_image(argv[3], 0, 0, 3);
	image re_im = resize_image(em, 400, 100);
	embed_image1(re_im, im, 0, 900);
	//im=collapse_image_layers(im, 100);
	//im = threshold_image(im, 0.5);
	//image re_im=resize_image(im, weight/2, height/2);
	save_image(im,image_savepath);
	return 0;
}