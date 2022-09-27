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

#define PRECISION 500    /* Number of x-points plotted per 1 point of diameter */
#define XSIZE 4          /* Number of inches long the x-axis is in the graph   */
#define YSIZE 5          /* Number of inches tall the y-axis is in the graph   */

#define PI 3.14159265358979323846

double *generate_circle_half(int radius, int half);
long LCM(long a, long b);
long GCD(long a, long b);

int main(int argc, char **argv) {

	/* For now, will provide the number of line segments as parameter */
	if (argc != 5 && argc != 8) {
		fprintf(stderr, "usage: spiro outer-radius inner-radius trace-point print-guide rcolor[OPT] gcolor[OPT] bcolor[OPT]\n\n");
		fprintf(stderr, "out-radius:       radius of outer circle in spirograph\n"
										"inner_radius:     radius of inner circle in spirograph\n"
										"trace-point:      distance from center of inner circle where\n"
										"                  tracing should occur. Must be between 0 and\n"
										"                  inner-radius, inclusive\n"
										"print-guide:      specify if outer circle should be printed (0 or 1)\n"
										"color [OPTIONAL]: specify RGB values in that order, where\n"
										"                  each value is a floating point number\n" 
										"                  between 0 and 1, inclusive\n");
		exit(1);
	}
	int out_rad, in_rad;
	double h;
	int print_guide;
	double r_val, g_val, b_val;
	double *top, *bottom;
	
	char *end;

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
	print_guide = strtol(argv[4], &end, 10);
	if (*end != '\0') {
		fprintf(stderr, "error: param 4 must be a valid base 10 integer\n");
		exit(1);
	}
	if (argc == 8) {
		r_val = strtod(argv[5], &end);
		if (*end != '\0') {
			fprintf(stderr, "error: param 5 must be a valid floating point number\n");
			exit(1);
		}
		g_val = strtod(argv[6], &end);
		if (*end != '\0') {
			fprintf(stderr, "error: param 6 must be a valid floating point number\n");
			exit(1);
		}
		b_val = strtod(argv[7], &end);
		if (*end != '\0') {
			fprintf(stderr, "error: param 7 must be a valid floating point number\n");
			exit(1);
		}
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
	
	printf("newcurve linetype solid marksize 0.01 0.01 ");
	if (argc == 8) {
		printf("color %f %f %f ", r_val, g_val, b_val);
	}
	printf("pts ");
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

long LCM(long a, long b) {
	if (a > b) {
		return (a/GCD(a,b)*b);
	} else {
		return (b/GCD(a,b)*a);
	}
}

long GCD(long a, long b) {
	if (b == 0) {
		return a;
	}
	return GCD(b, a%b);
}

	
