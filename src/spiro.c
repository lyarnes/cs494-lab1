/* 
 * Lucas Yarnes
 * CS494 - Lab1 - Jgraph
 * This program takes a series of parameters on stdin, specified later,
 * and outputs a series of jgraph instructions to stdout. To be useful,
 * the output ought to be redirected to a file or piped directly into
 * jgraph to generate a graph. The intent is for this program to create a 
 * spirograph based on the parameters provided
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 100    /* Number of x-points plotted per 1 point of diameter */
#define XSIZE 4          /* Number of inches long the x-axis is in the graph   */
#define YSIZE 4          /* Number of inches tall the y-axis is in the graph   */

#define PI 3.14159265358979323846

double *generate_circle_half(int radius, int half);
int LCM(int num1, int num2);

int main(int argc, char **argv) {

	/* For now, will provide the number of line segments as parameter */
	if (argc != 4) {
		fprintf(stderr, "usage: spiro outer-radius inner-radius trace-point\n");
		fprintf(stderr, "out-radius: radius of outer circle in spirograph\
										 inner_radius: radius of inner circle in spirograph\
										 trace-point: distance from center of inner circle where\
																	tracing should occur. Must be between 0 and\
																	inner-radius, inclusive\n");
		exit(1);
	}
	int out_rad, in_rad;
	double h;
	double *top, *bottom;
	
	char *end;

	int print_guide = 1;

	/* Ensure the params passed are in correct format */
	out_rad = strtol(argv[1], &end, 10);
	if (*end != '\0') {
		fprintf(stderr, "error: param 1 must be a valid base 10 integer\n");
		exit(1);
	}
	in_rad = strtol(argv[2], &end, 10);
	if (*end != '\0') {
		fprintf(stderr, "error: param 2 must be a valid base 10 integer\n");
		exit(1);
	}
	h = strtod(argv[3], &end);
	if (*end != '\0') {
		fprintf(stderr, "error: param 3 must be a valid floating point number\n");
		exit(1);
	}

	/* Generate the top and bottom halves of a circle. These will serve as
	 * guidelines for the spirograph that will go within the outer circle */
	top = generate_circle_half(out_rad, 0);
	bottom = generate_circle_half(out_rad, 1);
	if (top == NULL || bottom == NULL) {
		fprintf(stderr, "Error generating outer circle!\n");
		exit(1);
	}

	/* Setup new jgraph */
	printf("newgraph\n");	
	printf("xaxis nodraw max %d min %d size %d\n", out_rad, -1*out_rad, XSIZE);
	printf("yaxis nodraw max %d min %d size %d\n", out_rad, -1*out_rad, YSIZE);

	/* Use the outer circle guideline arrays to print out the outer circle,
	 * if desired */
	if (print_guide) {
		printf("newcurve marksize 0.01 0.01 pts");
		for (int i = 0; i <= 2*PRECISION*out_rad; i++) {
			printf(" %.2f %f", ((double)i/(double)PRECISION) - out_rad, top[i]);
		}
		printf("\nnewcurve marksize 0.01 0.01 pts");
		for (int i = 2*PRECISION*out_rad; i >= 0; i--) {
			printf(" %.2f %f", ((double)i/(double)PRECISION) - out_rad, bottom[i]);
		}
		printf("\n");
	}

	/* Begin the spirograph */
	/* According to math, in order to complete a spirograph, you must loop
	 * through the circle p number of times, where p is the simplified
	 * denominator of the fraction r/R, where r is the radius of the inner
	 * circle and R the radius of the outer circle */
	
	printf("newcurve linetype solid marksize 0.01 0.01 pts");
	int p = (LCM(out_rad, in_rad) / out_rad);
	//int bound;
	double x, y;
	double t;
	int counter = 0;
	for (int i = 1; i <= p; i++) {
		//bound = (out_rad - (out_rad - in_rad)) * PRECISION;
		for (int j = -1*out_rad; j < out_rad; j++) {
			for (int k = 0; k < PRECISION; k++) {
				t = ((counter * PRECISION + k) * 2 * PI * p) / PRECISION;
				x = (out_rad-in_rad) * cos(t) + (h * cos( ((out_rad-in_rad) * t) / in_rad));
				y = (out_rad-in_rad) * sin(t) - (h * sin( ((out_rad-in_rad) * t) / in_rad));
				printf(" %f %f", x, y);
			} 
			counter++;
		}
	}
	
	return 0;
}

double *generate_circle_half(int radius, int half) {
	double *arr = malloc(sizeof(double)*2*PRECISION*radius);
	double x, y;
	int counter = 0;
	for (int i = radius*-1; i < radius; i++) {
		for (int j = 0; j < PRECISION; j++) {
			x = (double)i + ((double)j / (double)PRECISION);
			y = sqrt(radius*radius - x*x);
			if (half == 0) {
				arr[counter * PRECISION + j] = y;
			} else if (half == 1) {
				arr[counter * PRECISION + j] = y * -1;
			} else {
				return NULL; 
			}
		}
		counter++;
	}
	return arr;
}

int LCM(int num1, int num2) {
	int res = (num1 >= num2) ? num1 : num2;
	while(1) {
		if (res % num1 == 0 && res % num2 == 0) return res;
		res++;
	}
}
	
