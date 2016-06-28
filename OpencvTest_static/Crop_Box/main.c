#include "box.h"
#include "image.h"
#include "matrix.h"
#include<time.h>
#include"list.h"
#include<stdio.h>
#define MAX 100
typedef struct{
	int w, h;
	matrix X;
	matrix y;
	int shallow;
} data;
typedef struct{
	int id;
	float x, y, w, h;
	float left, right, top, bottom;
} box_label;

box_label *read_boxes(char *filename, int *n)
{
	box_label *boxes = calloc(1, sizeof(box_label));
	FILE *file = fopen(filename, "r");
	if (!file) file_error(filename);
	float x, y, h, w;
	int id;
	int count = 0;
	while (fscanf(file, "%d %f %f %f %f", &id, &x, &y, &w, &h) == 5){
		boxes = realloc(boxes, (count + 1)*sizeof(box_label));
		boxes[count].id = id;
		boxes[count].x = x;
		boxes[count].y = y;
		boxes[count].h = h;
		boxes[count].w = w;
		boxes[count].left = x - w / 2;
		boxes[count].right = x + w / 2;
		boxes[count].top = y - h / 2;
		boxes[count].bottom = y + h / 2;
		++count;
	}
	fclose(file);
	*n = count;
	return boxes;
}
list *get_paths(char *filename)
{
	list *lines = NULL;  //add by frisch // list *lines;
	char *path;
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Couldn't open file: %s\n", filename);
		exit(0);
	}
	lines = make_list();
	while ((path = fgetl(file))){
		list_insert(lines, path);
	}
	fclose(file);
	return lines;
}
int main(int argc, char **argv)
{
	char* input = argv[1];
	int channels = 3;
	list *plist = get_paths(input);
	//int N = plist->size;
	char **paths = (char **)list_to_array(plist);
	int m = plist->size;
	int count_label = 0;
	for (int i = 0; i < m; i++)
	{
		if (!paths[i])
		{
			printf("load error!\n");
			break;
		}
		image im = load_image(paths[i], 0, 0, channels);
		printf("load %s", paths[i]);
		char *labelpath = find_replace(paths[i], "images", "labels");
		labelpath = find_replace(labelpath, "JPEGImages", "labels");
		labelpath = find_replace(labelpath, ".jpg", ".txt");
		labelpath = find_replace(labelpath, ".JPEG", ".txt");
		int count = 0;
		box_label *boxes = read_boxes(labelpath, &count);
		//产生随机框
		//srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待
		/*float x = rand() % MAX*0.005 + 0.3;
		float y = rand() % MAX*0.005 + 0.3;
		float w = rand() % MAX*0.005 + 0.3;
		float h = rand() % MAX*0.005 + 0.3;
		if (w > 2 * (1 - x))  w = 2 * (1 - x) - 0.01;
		if (y > 2 * (1 - x))  y = 2 * (1 - x) - 0.01;*/

		/*float x[4];
		for (int i = 0; i < 4; i++)
		x[i] = rand() % MAX*0.01;//MAX为最大值，其随机域为(0~MAX-1)*0.01
		box box = { x[0],x[1],x[2],x[3]};*/
		float x, y, w, h;
		for (int j = 0; j < count; j++)
		{
			count_label++;
			x = boxes[j].x;
			y = boxes[j].y;
			w = boxes[j].w;
			h = boxes[j].h;
			box box = { x, y, w, h };
			//box box = { 0.5, 0.5, 0.2, 0.3 }; 
			//draw_bbox(im, box, 1, 1, 0, 0);
			//flip_image(im);
			//translate_image(im, 10);
			//scale_image(im, 0.6);
			//im=crop_image(im, 50, 50, 30, 30);
			//image em = crop_image(im, 50, 50, 80, 80); embed_image(em,im, 100, 100);
			//im=collapse_image_layers(im, 100);
			//im = threshold_image(im, 0.5);
			char save_path[256];
			sprintf(save_path, "./images/%07d", count_label);
			//show_image(im, save_path);
			image crop_im = crop_image(im, (x - 0.5*w) *im.w, (y - 0.5*h)*im.h, w*im.w, h*im.h);
			show_image(crop_im, save_path);
			free_image(crop_im);
		}
		free_image(im);
	}
}
