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
#include <sstream>
#include <string>
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

string IN;
//CRITICAL POINT: images' paths - you need to change this path,create a string with this, create loop that adds 1 and .pgm at end
#define OUT "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\output_images\\blurred.pgm"
#define OUT2 "C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\output_images\\edge_detection.pgm"

//IMAGE DIMENSIONS
unsigned int M; //cols
unsigned int N;  //rows


//CRITICAL POINT:these arrays are defined statically. Consider creating these arrays dynamically instead.
unsigned char *frame1= nullptr;//input image N*M
unsigned char *filt = nullptr;//output filtered image N*M
unsigned char *gradient = nullptr;//output image N*M


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

int main(int argc,char*argv[]) {
	const char* filenames[] = {
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a0.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a1.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a2.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a3.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a4.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a5.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a6.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a7.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a8.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a9.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a10.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a11.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a12.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a13.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a14.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a15.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a16.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a17.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a18.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a19.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a20.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a21.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a22.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a23.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a24.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a25.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a26.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a27.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a28.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a29.pgm",
		"C:\\Users\\natas\\source\\repos\\COMP1001report\\COMP1001-master\\23_24_coursework\\Report\\question3\\VS\\code_to_start\\3bc\\3bc\\input_images\\a30.pgm",
	};

	for (const char* filename : filenames) {
		// Initialize the IN string with the current filename
		std::string IN(filename);
		read_image(IN.c_str());
		Gaussian_Blur(); //blur the image (reduce noise)
		Sobel(); //apply edge detection
		write_image2(OUT, filt); //store output image to the disc
		write_image2(OUT2, gradient); //store output image to the disc
		//detroy the array 
		delete[] frame1;
		delete[] filt;
		delete[] gradient;
	
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
	int i, j,temp;
	printf("\nReading %s image from disk ...", filename);
	finput = NULL;
	openfile(filename, &finput);
	//develop a route that dynaticlly creates the arrays
	//based on N and M values, there are 3 arrays
	frame1 = new unsigned char[M * N];
	filt = new unsigned char[M * N];
	gradient = new unsigned char[M * N];
	
	if ((header[0] == 'P') && (header[1] == '5')) { //if P5 image

		for (j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {

				//if (fscanf_s(finput, "%d", &temp,20) == EOF)
				//	exit(EXIT_FAILURE);
				temp = getc(finput);
				//3 arra
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
	int x0, y0, x, aa;

	if (( err = fopen_s(finput,filename, "rb")) != NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", filename);
		exit(-1);
	}
	
	aa = fscanf_s(*finput, "%s", header, 20);

	x0 = getint(*finput);//this is M
	y0 = getint(*finput);//this is N
	printf("\t header is %s, while x=%d,y=%d", header, x0, y0);


	//CRITICAL POINT: AT THIS POINT YOU CAN ASSIGN x0,y0 to M,N 
	M = x0;
	N = y0;
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








