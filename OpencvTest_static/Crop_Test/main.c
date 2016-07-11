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
	float x1, y1, x2, y2;
	int id=0;
	int count = 0;
	while (fscanf(file, "%f,%f,%f,%f", &x1, &y1, &x2, &y2) == 4){
		boxes = realloc(boxes, (count + 1)*sizeof(box_label));
		boxes[count].id = id;
		boxes[count].x = x1  ;
		boxes[count].y =y1 ;
		boxes[count].w = (x2 - x1)  ;
		boxes[count].h = (y2 - y1) ;
		boxes[count].left = x1 / 1280;
		boxes[count].right = x2 / 1280;
		boxes[count].top = y1 / 720;
		boxes[count].bottom = y2  / 720;
		++count;
	}
	fclose(file);
	*n = count;
	return boxes;
}
char *get_basename(char* mystr) {
	char *retstr;
	char *lastdot;
	if (mystr == NULL)
		return NULL;
	if ((retstr = malloc(strlen(mystr) + 1)) == NULL)
		return NULL;
	char *basename = strrchr(mystr, '/');
	if (basename == NULL){
		strcpy(retstr, mystr);
	}
	else{
		strcpy(retstr, basename + 1);
	}
	lastdot = strrchr(retstr, '.');
	if (lastdot != NULL)
		*lastdot = '\0';
	return retstr;
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
	char labelpath[256];
	sprintf(labelpath, "../labels/01_5_1.txt");
	int count = 0;
	box_label *boxes = read_boxes(labelpath, &count);
	for (int i = 0; i < m; i++)
	{
		if (!paths[i])
		{
			printf("load error!\n");
			break;
		}
		image im = load_image(paths[i], 0, 0, channels);

		printf("load %s", paths[i]);
		float x, y, w, h;
			count_label++;
			x = boxes[i].x;
			y = boxes[i].y;
			w = boxes[i].w;
			h = boxes[i].h;
			box box = { x, y, w, h };
			char *save_path1 = get_basename(paths[i]);
			char save_path[256];
			sprintf(save_path, "./images/%s", save_path1);
			//show_image(im, save_path);
			image crop_im = crop_image(im, x,y,w,h);
			printf(" %f %f %f %f \n", x,y,w,h);
			show_image(crop_im, save_path);
			free_image(crop_im);
	     	free_image(im);
	}
}
