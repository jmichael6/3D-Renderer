#include <canvas.h>
#include <stdio.h>
#include <stdlib.h>

tuple pixel_at(canvas *cnv, int x, int y) {
	if(x >= 0 && y >= 0 && x < cnv->width && y < cnv->height) {
		int pixel_num = y * cnv->width + x;
		return cnv->pixels[pixel_num];
	} else
		return color(0, 0, 0);
}

void write_pixel(canvas* cnv, int x, int y, tuple c) {	
	if(x >= 0 && y >= 0 && x < cnv->width && y < cnv->height) 
		cnv->pixels[y * cnv->width + x] = c;
}

void init_canvas(canvas *cnv) {
	for(int i = 0; i < cnv->width; i++) 
		for(int j = 0; j < cnv->height; j++) 
			write_pixel(cnv, i, j, color(0, 0, 0));
}


canvas* make_canvas(int width, int height) {
	canvas* cnv = malloc(sizeof(canvas));
	cnv->width = width;
	cnv->height = height;
	cnv->pixels = malloc(sizeof(tuple) * width * height);

	init_canvas(cnv);
	return cnv;
}



void delete_canvas(canvas* cnv) {
	free(cnv->pixels);
	free(cnv);
}


int clamp_color(float f) {
	if(f < 0)
		return 0;
	else if (f > 255)
		return 255;
	else 
		return round(f);
}

void canvas_to_ppm(canvas* cnv, FILE *ppm) {
	fprintf(ppm, "P3\n");
	fprintf(ppm, "%d %d\n", cnv->width, cnv->height);
	fprintf(ppm, "255\n");


	int pixel_count = 0;
	for(int j = 0; j < cnv->height; j++) {
		for(int i = 0; i < cnv->width; i++) {
			tuple pixel = pixel_at(cnv, i, j);
			int r = clamp_color(255 * pixel.x);
			int g = clamp_color(255 * pixel.y);
			int b = clamp_color(255 * pixel.z);
			fprintf(ppm, "%d %d %d ", r, g, b);

			pixel_count++;
			if(pixel_count == 5) {
				fprintf(ppm, "\n");
				pixel_count = 0;
			}
		}
	}
	fprintf(ppm, "\n");
}




