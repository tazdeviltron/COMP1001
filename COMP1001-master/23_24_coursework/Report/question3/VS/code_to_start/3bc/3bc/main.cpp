/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <emmintrin.h>
#include <limits.h>
#include <pmmintrin.h>
#include <immintrin.h>
#include <iostream>
#include <fstream>
using namespace std;

//function declarations
void Gaussian_Blur();
void Sobel();
int initialize_kernel();
void read_image(const char* filename);
void read_image_and_put_zeros_around(char* filename);
void write_image2(const char* filename, unsigned char* output_image);
void openfile(const char* filename, FILE** finput);
int getint(FILE* fp);

//CRITICAL POINT: images' paths - you need to change this path
#define IN "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a1.pgm"
#define IN0 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a0.pgm"
#define IN2 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a2.pgm"
#define IN3 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a3.pgm"
#define IN4 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a4.pgm"
#define IN5 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a5.pgm"
#define IN6 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a6.pgm"
#define IN7 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a7.pgm"
#define IN8 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a8.pgm"
#define IN9 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a9.pgm"
#define IN10 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a10.pgm"
#define IN11 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a11.pgm"
#define IN12 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a12.pgm"
#define IN13 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a13.pgm"
#define IN14 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a14.pgm"
#define IN15 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a15.pgm"
#define IN16 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a16.pgm"
#define IN17 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a17.pgm"
#define IN18 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a18.pgm"
#define IN19 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a19.pgm"
#define IN20 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a20.pgm"
#define IN21 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a21.pgm"
#define IN22 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a22.pgm"
#define IN23 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a23.pgm"
#define IN24 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a24.pgm"
#define IN25 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a25.pgm"
#define IN26 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a26.pgm"
#define IN27 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a27.pgm"
#define IN28 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a28.pgm"
#define IN29 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a29.pgm"
#define IN30 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a30.pgm"

#define OUT "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\output_images\\blurred.pgm"
#define OUT2 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\output_images\\edge_detection.pgm"

//IMAGE DIMENSIONS
#define M 512  //cols
#define N 512  //rows


//CRITICAL POINT:these arrays are defined statically. Consider creating these arrays dynamically instead.
unsigned char frame1[N * M];//input image
unsigned char filt[N * M];//output filtered image
unsigned char gradient[N * M];//output image


const signed char Mask[5][5] = {//2d gaussian mask with integers
	{2,4,5,4,2} ,
	{4,9,12,9,4},
	{5,12,15,12,5},
	{4,9,12,9,4},
	{2,4,5,4,2}
};

const signed char GxMask[3][3] = {
	{-1,0,1} ,
	{-2,0,2},
	{-1,0,1}
};

const signed char GyMask[3][3] = {
	{-1,-2,-1} ,
	{0,0,0},
	{1,2,1}
};

char header[100];
errno_t err;

int main() {
	int i = 0;
	while (i < 31) {
		i++;
		switch (i) {
		case 1:
			read_image(IN);
			
		case 2:
			read_image(IN0);
			
		case 3:
			read_image(IN2);
			
		case 4:
			read_image(IN3);
			
		case 5:
			read_image(IN4);
			
		case 6:
			read_image(IN5);
			
		case 7:
			read_image(IN6);
			
		case 8:
			read_image(IN7);
			
		case 9:
			read_image(IN8);
			
		case 10:
			read_image(IN9);
			
		case 11:
			read_image(IN10);
			
		case 12:
			read_image(IN11);
		case 13:
			read_image(IN12);
		case 14:
			read_image(IN13);
		case 15:
			read_image(IN14);
		case 16:
			read_image(IN15);
		case 17:
			read_image(IN16);
		case 18:
			read_image(IN17);
		case 19:
			read_image(IN18);
		case 20:
			read_image(IN19);
		case 21:
			read_image(IN20);
		case 22:
			read_image(IN21);
		case 23:
			read_image(IN22);
		case 24:
			read_image(IN23);
		case 25:
			read_image(IN24);
		case 26:
			read_image(IN25);
		case 27:
			read_image(IN26);
		case 28:
			read_image(IN27);
		case 29:
			read_image(IN28);
		case 30:
			read_image(IN29);
		case 31:
			read_image(IN30);
		}
		Gaussian_Blur(); //blur the image (reduce noise)
		Sobel(); //apply edge detection
		write_image2(OUT, filt); //store output image to the disc
		write_image2(OUT2, gradient); //store output image to the disc
	}

	
	return 0;
}





void Gaussian_Blur() {

	int row, col, rowOffset, colOffset;
	int newPixel;
	unsigned char pix;
	//const unsigned short int size=filter_size/2;
	const unsigned short int size = 2;

	/*---------------------- Gaussian Blur ---------------------------------*/
	for (row = 0; row < N; row++) {
		for (col = 0; col < M; col++) {
			newPixel = 0;
			for (rowOffset = -size; rowOffset <= size; rowOffset++) {
				for (colOffset = -size; colOffset <= size; colOffset++) {

					if ((row + rowOffset < 0) || (row + rowOffset >= N) || (col + colOffset < 0) || (col + colOffset >= M))
						pix = 0;
					else
						pix = frame1[M * (row + rowOffset) + col + colOffset];

					newPixel += pix * Mask[size + rowOffset][size + colOffset];

				}
			}
			filt[M * row + col] = (unsigned char)(newPixel / 159);

		}
	}

}

//change this for part c using x86-64 SSE/SSE2/SSE4/AVX/AVX2
void Sobel() {

	int row, col, rowOffset, colOffset;
	int Gx, Gy;

	/*---------------------------- Determine edge directions and gradient strengths -------------------------------------------*/
	for (row = 1; row < N - 1; row++) {
		for (col = 1; col < M - 1; col++) {

			Gx = 0;
			Gy = 0;

			/* Calculate the sum of the Sobel mask times the nine surrounding pixels in the x and y direction */
			for (rowOffset = -1; rowOffset <= 1; rowOffset++) {
				for (colOffset = -1; colOffset <= 1; colOffset++) {

					Gx += filt[M * (row + rowOffset) + col + colOffset] * GxMask[rowOffset + 1][colOffset + 1];
					Gy += filt[M * (row + rowOffset) + col + colOffset] * GyMask[rowOffset + 1][colOffset + 1];
				}
			}

			gradient[M * row + col] = (unsigned char)sqrt(Gx * Gx + Gy * Gy); /* Calculate gradient strength		*/
			//gradient[row][col] = abs(Gx) + abs(Gy); // this is an optimized version of the above

		}
	}


}




void read_image(const char* filename)
{

	int c;
	FILE* finput;
	int i, j, temp;

	printf("\nReading %s image from disk ...", filename);
	finput = NULL;
	openfile(filename, &finput);

	if ((header[0] == 'P') && (header[1] == '5')) { //if P5 image

		for (j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {

				//if (fscanf_s(finput, "%d", &temp,20) == EOF)
				//	exit(EXIT_FAILURE);
				temp = getc(finput);

				frame1[M * j + i] = (unsigned char)temp;
			}
		}
	}
	else if ((header[0] == 'P') && (header[1] == '2'))  { //if P2 image
		for (j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {

				if (fscanf_s(finput, "%d", &temp,20) == EOF)
					exit(EXIT_FAILURE);

				frame1[M * j + i] = (unsigned char)temp;
			}
		}
	}
	else {
		printf("\nproblem with reading the image");
		exit(EXIT_FAILURE);
	}

	fclose(finput);
	printf("\nimage successfully read from disc\n");

}



void write_image2(const char* filename, unsigned char* output_image)
{

	FILE* foutput;
	int i, j;



	printf("  Writing result to disk ...\n");

	if ((err = fopen_s(&foutput,filename, "wb")) != NULL) {
		fprintf(stderr, "Unable to open file %s for writing\n", filename);
		exit(-1);
	}

	fprintf(foutput, "P2\n");
	fprintf(foutput, "%d %d\n", M, N);
	fprintf(foutput, "%d\n", 255);

	for (j = 0; j < N; ++j) {
		for (i = 0; i < M; ++i) {
			fprintf(foutput, "%3d ", output_image[M * j + i]);
			if (i % 32 == 31) fprintf(foutput, "\n");
		}
		if (M % 32 != 0) fprintf(foutput, "\n");
	}
	fclose(foutput);


}




void openfile(const char* filename, FILE** finput)
{
	int x0, y0, x , aa;

	if (( err = fopen_s(finput,filename, "rb")) != NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", filename);
		exit(-1);
	}

	aa = fscanf_s(*finput, "%s", header, 20);

	x0 = getint(*finput);//this is M
	y0 = getint(*finput);//this is N
	printf("\t header is %s, while x=%d,y=%d", header, x0, y0);


	//CRITICAL POINT: AT THIS POINT YOU CAN ASSIGN x0,y0 to M,N 
	x0 = M;
	y0 = N;
	 printf("\n Image dimensions are M=%d,N=%d",M,N);


	x = getint(*finput); /* read and throw away the range info */
	printf("\n range info is %d",x);

}



//CRITICAL POINT: you can define your routines here that create the arrays dynamically; now, the arrays are defined statically.



int getint(FILE* fp) /* adapted from "xv" source code */
{
	int c, i, firstchar;//, garbage;

	/* note:  if it sees a '#' character, all characters from there to end of
	   line are appended to the comment string */

	   /* skip forward to start of next number */
	c = getc(fp);
	while (1) {
		/* eat comments */
		if (c == '#') {
			/* if we're at a comment, read to end of line */
			char cmt[256], * sp;

			sp = cmt;  firstchar = 1;
			while (1) {
				c = getc(fp);
				if (firstchar && c == ' ') firstchar = 0;  /* lop off 1 sp after # */
				else {
					if (c == '\n' || c == EOF) break;
					if ((sp - cmt) < 250) *sp++ = c;
				}
			}
			*sp++ = '\n';
			*sp = '\0';
		}

		if (c == EOF) return 0;
		if (c >= '0' && c <= '9') break;   /* we've found what we were looking for */

		/* see if we are getting garbage (non-whitespace) */
	   // if (c!=' ' && c!='\t' && c!='\r' && c!='\n' && c!=',')
		//	garbage=1;

		c = getc(fp);
	}

	/* we're at the start of a number, continue until we hit a non-number */
	i = 0;
	while (1) {
		i = (i * 10) + (c - '0');
		c = getc(fp);
		if (c == EOF) return i;
		if (c < '0' || c>'9') break;
	}
	return i;
}








