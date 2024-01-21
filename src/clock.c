#include <transform.h>
#include <canvas.h>

void plot_clock(int r, int x, int y, canvas *cnv) {
	tuple unit = point(1, 0, 0);

	for(int i = 0; i < 12; i++) {
		matrix transforms[] = {scaling(r, 0, 0),
							   rotation_z(PI * i / 6),
							   translation(x, y, 0)};
		
		tuple pt = apply(chain_transforms(transforms, 3), 
				         unit);


		write_pixel(cnv, round(pt.x), round(pt.y), color(1, 1, 0));
	}

	FILE *F = fopen("clock.ppm", "w");
	canvas_to_ppm(cnv, F);
	fclose(F);
}

int main() {
	canvas* cnv = make_canvas(300, 300);
	plot_clock(40, 150, 150, cnv);
}


