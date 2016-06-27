#include "box.h"
#include "image.h"
#include<time.h>
#define MAX 100
int main(int argc, char **argv)
{
	char* input = argv[1];
	int channels = 3;
		image im = load_image(input, 0, 0, channels);

		//产生随机框
		srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待
		float x = rand() % MAX*0.005 + 0.3;
		float y = rand() % MAX*0.005 + 0.3;
		float w = rand() % MAX*0.005 + 0.3;
		float h = rand() % MAX*0.005 + 0.3;
		if (w > 2 * (1 - x))  w = 2 * (1 - x) - 0.01;
		if (y > 2 * (1 - x))  y = 2 * (1 - x) - 0.01;

		/*float x[4];
		for (int i = 0; i < 4; i++)
		x[i] = rand() % MAX*0.01;//MAX为最大值，其随机域为(0~MAX-1)*0.01
		box box = { x[0],x[1],x[2],x[3]};*/
		box box = { x, y, w, h };
		//box box = { 0.5, 0.5, 0.2, 0.3 }; 
		draw_bbox(im, box, 1, 1, 0, 0);
		//flip_image(im);
		//translate_image(im, 10);
		//scale_image(im, 0.6);
		//im=crop_image(im, 50, 50, 30, 30);
		//image em = crop_image(im, 50, 50, 80, 80); embed_image(em,im, 100, 100);
		//im=collapse_image_layers(im, 100);
		//im = threshold_image(im, 0.5);
		show_image(im, "draw_box");
	}
