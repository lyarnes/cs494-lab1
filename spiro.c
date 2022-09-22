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

#define PRECISION 100
#define XSIZE 4
#define YSIZE 4

int main(int argc, char **argv) {
	
	/* For now, will provide the number of line segments as parameter */
	if (argc != 3) {
		fprintf(stderr, "usage: spiro outer-radius inner-radius\n");
		exit(1);
	}
	int out_rad, in_rad;
	//Top and bottom halves of the circle
	double *top, *bottom;
	
	char *end;

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

	top = malloc(sizeof(double) * 2 * PRECISION * out_rad);
	bottom = malloc(sizeof(double) * 2 * PRECISION * out_rad);

	//The beginning of a graph in jgraph spec */
	printf("newgraph\n");	
	printf("xaxis nodraw max %d min %d size %d\n", out_rad, -1*out_rad, XSIZE);
	printf("yaxis nodraw max %d min %d size %d\n", out_rad, -1*out_rad, YSIZE);

	//Graph a circle using the equation for a circle
	printf("newline pts");
	double x, y;
	int counter = 0;
	for (int i = out_rad*-1; i < out_rad; i++) {
		for (int j = 0; j < PRECISION; j++) {
			x = (double)i + ((double)j / (double)PRECISION);
			y = sqrt(out_rad*out_rad - x*x);
			top[counter * PRECISION + j] = y;
			bottom[counter * PRECISION + j] = y * -1;
		}
		counter++;
	}
	for (int i = 0; i < 2*PRECISION*out_rad; i++) {
		printf(" %.2f %f", ((double)i/(double)PRECISION) - out_rad, top[i]);
	}
	printf("\nnewline pts");
	for (int i = 2*PRECISION*out_rad; i > 0; i--) {
		printf(" %.2f %f", ((double)i/(double)PRECISION) - out_rad, bottom[i]);
	}
	printf("\n");
	
	//Our bottom-left corner is 0,0, therefore begin plotting there
	/*for (int i = 0; i < num_segs; i++) {
		printf("newcurve pts");
		for (int j = 0; j < seg_len; j++) {
			printf(" %d %d", i, j);
		}
		printf("\n");
	}*/

	return 0;
}
