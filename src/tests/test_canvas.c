#include <canvas.h>
#include <tuple.h>
#include "unit_test.h"

void test_canvas() {
	new_test("CANVAS");

	sub_test("Creation of the canvas");
	
	canvas* cnv = make_canvas(10, 20);
	
	display("  Checking width: ");
	if(cnv->width == 10) passed(); else failed();
	display("  Checking height: ");
	if(cnv->height == 20) passed(); else failed();

	display("  Checking if all pixels are accessible and black: ");
	bool test_passed = true;
	for(int i = 0; i < 10; i++) 
		for(int j = 0; j < 20; j++) 
			if(!eqv(color(0, 0, 0), pixel_at(cnv, i, j)))
				test_passed = false;
	if(test_passed) passed(); else failed();
	

	sub_test("Writing to pixels");
	tuple red = color(1, 0, 0);
	write_pixel(cnv, 2, 3, red);
	if(eqv(pixel_at(cnv, 2, 3), red)) passed(); else failed();
	
	
	display("\nDeleting the canvas\n");
	delete_canvas(cnv);

	sub_test("Writing a new canvas to a ppm file");

	cnv = make_canvas(5, 3);
	tuple c1 = color(1.5, 0, 0);
	tuple c2 = color(0, 0.5, 0);
	tuple c3 = color(-0.5, 0, 1);
	write_pixel(cnv, 0, 0, c1);
	write_pixel(cnv, 2, 1, c2);
	write_pixel(cnv, 4, 2, c3);	

	FILE *F = fopen("test_img.ppm", "w");
	canvas_to_ppm(cnv, F);
	fclose(F);
	display("  Check if the file was properly written !!");


	sub_test("Writing a new canvas to check all lines are under 70 chars");

	cnv = make_canvas(10, 2);
	for(int i = 0; i < 10; i++) 
		for(int j = 0; j < 2; j++) 
			write_pixel(cnv, i, j, color(1, 0.8, 0.6));
	
	F = fopen("test_img2.ppm", "w");
	canvas_to_ppm(cnv, F);
	fclose(F);
	display("  Open the file and check");

	end_test();

}


int main() {
	test_canvas();
}
