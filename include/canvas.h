#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <tuple.h>
#include <stdio.h>

typedef struct canvas {
	int width;
	int height;
	tuple* pixels;
} canvas;


canvas* make_canvas(int width, int height);
void delete_canvas(canvas* cnv);

tuple pixel_at(canvas *cnv, int x, int y);
void write_pixel(canvas* cnv, int x, int y, tuple c);
void canvas_to_ppm(canvas* cnv, FILE *ppm);

#endif
