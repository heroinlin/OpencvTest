#include "box.h"
#include "image.h"
#include<time.h>
#include"list.h"
#include<stdio.h>
#define MAX 100
char *fgetl(FILE *fp)
{
	size_t size;
	if (feof(fp)) return 0;
	size = 512;
	char *line = malloc(size*sizeof(char));
	if (!fgets(line, size, fp)){
		free(line);
		return 0;
	}

	size_t curr = strlen(line);

	while ((line[curr - 1] != '\n') && !feof(fp)){
		if (curr == size - 1){
			size *= 2;
			line = realloc(line, size*sizeof(char));
			if (!line) {
				printf("%ld\n", size);
				fprintf(stderr, "Malloc error\n");
				exit(-1);
			}
		}
		size_t readsize = size - curr;
		if (readsize > INT_MAX) readsize = INT_MAX - 1;
		fgets(&line[curr], readsize, fp);
		curr = strlen(line);
	}
	if (line[curr - 1] == '\n') line[curr - 1] = '\0';

	return line;
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
	for (int i = 0; i < m; i++)
	{
		if (!paths[i])
		{
			printf("load error!\n");
			break;
		}
		image im = load_image(paths[i], 0, 0, channels);
		//printf("load %s", paths[i]);
		int j = 0;
		char labels_path[32];
		printf("save to images/%07d.txt\n", i + 1);
		sprintf(labels_path, "./labels/%07d.txt", i + 1);
		FILE * fp;
		fp = fopen(labels_path, "w+");//以读写方式打开labels_path路径的文件，没有则新建
		while (j < 2)//每张图标两个box
		{
			j++;
			//产生随机框
			//srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待
			float x = rand() % MAX*0.005 + 0.3;
			float y = rand() % MAX*0.005 + 0.3;
			float w = rand() % MAX*0.005 + 0.3;
			float h = rand() % MAX*0.005 + 0.3;
			float x1 = (1 - x) > x ? x : (1 - x);//x离边界距离
			float y1 = (1 - y) > y ? y : (1 - y);//y离边界距离
			if (w > 2 * x1)  w = 2 * x1 - 0.01;//保证宽不超出边界
			if (h > 2 * y1) h = 2 * y1 - 0.01;//保证高不超出边界

			/*float x[4];
			for (int i = 0; i < 4; i++)
			x[i] = rand() % MAX*0.01;//MAX为最大值，其随机域为(0~MAX-1)*0.01
			box box = { x[0],x[1],x[2],x[3]};*/
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
			fprintf(fp, "1 %f %f %f %f\n", x, y, w, h);//将box写入到fp中
		}
		fclose(fp);
		//char save_path[256];
		//sprintf(save_path, "./images/%07d", i+1);
		//im = crop_image(im, (x - 0.5*w) *im.w, (y - 0.5*h)*im.h, w*im.w, h*im.h);
		//show_image(im, save_path);
		free_image(im);
	}
}
