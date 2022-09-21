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

#define PRECISION 10

int main(int argc, char **argv) {
	
	/* For now, will provide the number of line segments as parameter */
	if (argc != 3) {
		fprintf(stderr, "usage: spiro num-segments seg-length\n");
		exit(1);
	}
	int radius, num_segs, seg_len;
	char *end;

	radius = 5;

	num_segs = strtol(argv[1], &end, 10);
	if (*end != '\0') {
		fprintf(stderr, "error: param 1 must be a valid base 10 integer\n");
		exit(1);
	}
	seg_len = strtol(argv[2], &end, 10);
	if (*end != '\0') {
		fprintf(stderr, "error: param 2 must be a valid base 10 integer\n");
		exit(1);
	}

	//The beginning of a graph in jgraph spec */
	printf("newgraph\n");	

	//Graph a circle using the equation for a circle
	printf("newcurve pts");
	double y;
	for (double x = (radius*-1.0); x <= radius; x+=(1.0/PRECISION)) {
		y = sqrt((radius*radius - x*x));
		printf(" %f %f", x, y);
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
