#include <stdio.h>
#include <canvas.h>

struct projectile {
	tuple position;
	tuple velocity;
};

struct environment {
	tuple gravity;
	tuple wind;
};

struct projectile tick(struct projectile p, struct environment e, float dt) {
	tuple new_position = add(p.position, mul(p.velocity, dt));
	tuple new_velocity = add(p.velocity, add(mul(e.gravity, dt),
				                                 e.wind));
	struct projectile new_p = {new_position, new_velocity};
	return new_p;
}

void throw_projectile(struct projectile p, struct environment e, canvas* cnv, int height) {
	float dt = 1;
	float time = 0;

	tuple start_position = p.position;

	while(p.position.y > 0) {
		printf("Position at t=%f seconds: x=%f y=%f\n", time, p.position.x, p.position.y);
		write_pixel(cnv, round(p.position.x), height - round(p.position.y), color(1, 0, 0));
		p = tick(p, e, dt);
		time += dt;
	}

	printf("\nThe time taken to hit the ground is: %f\n", time);
	printf("The distance traveled is %f\n", magnitude(sub(start_position, p.position)));
}

int main() {
	canvas* cnv = make_canvas(1000, 500);

	for(int i = 0; i < 1000; i++)
		for(int j = 0; j < 500; j++) 
			write_pixel(cnv, i, j, color(0, 1, 1));

	struct projectile p = {point(0, 40, 0), mul(normalize(vector(1, 1, 0)), 30)};
	struct environment e = {vector(0, -1, 0), vector(-0.5, 0, 0)};
	throw_projectile(p, e, cnv, 500);

	FILE *F = fopen("trajectory.ppm", "w");
	canvas_to_ppm(cnv, F);
	fclose(F);
}
