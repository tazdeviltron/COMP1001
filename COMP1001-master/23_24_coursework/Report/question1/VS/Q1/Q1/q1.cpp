/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h>
#include <time.h>
#include <pmmintrin.h>
#include <process.h>
#include <chrono>
#include <iostream>
#include <immintrin.h>
#include <omp.h>

#define M 1024*512
#define ARITHMETIC_OPERATIONS1 3*M
#define TIMES1 1

#define N 8192
#define ARITHMETIC_OPERATIONS2 4*N*N
#define TIMES2 1


//function declaration
void initialize();
void routine1(float alpha, float beta);
void routine2(float alpha, float beta);
void routine1_vec(float alpha, float beta);
void routine2_vec(float alpha, float beta);
//extern unsigned short int equal(float a, float b);

__declspec(align(64)) float  y[M], z[M] ;
__declspec(align(64)) float A[N][N], x[N], w[N];

int main() {

    float alpha = 0.023f, beta = 0.045f;
    double run_time, start_time;
    unsigned int t;

    initialize();

    printf("\nRoutine1:");
    start_time = omp_get_wtime(); //start timer

    for (t = 0; t < TIMES1; t++)
        routine1(alpha, beta);

    run_time = omp_get_wtime() - start_time; //end timer
    printf("\n Time elapsed is %f secs \n %e FLOPs achieved\n", run_time, (double)(ARITHMETIC_OPERATIONS1) / ((double)run_time / TIMES1));

    printf("\nRoutine2:");
    start_time = omp_get_wtime(); //start timer

    for (t = 0; t < TIMES2; t++)
        routine2(alpha, beta);

    run_time = omp_get_wtime() - start_time; //end timer
    printf("\n Time elapsed is %f secs \n %e FLOPs achieved\n", run_time, (double)(ARITHMETIC_OPERATIONS2) / ((double)run_time / TIMES2));

    printf("\nRoutine1_vec:");
    start_time = omp_get_wtime(); //start timer

    for (t = 0; t < TIMES1; t++)
        routine1_vec(alpha, beta);

    run_time = omp_get_wtime() - start_time; //end timer
    printf("\n Time elapsed is %f secs \n %e FLOPs achieved\n", run_time, (double)(ARITHMETIC_OPERATIONS1) / ((double)run_time / TIMES1));

    printf("\nRoutine2_vec:");
    start_time = omp_get_wtime(); //start timer

    for (t = 0; t < TIMES2; t++)
        routine2_vec(alpha, beta);

    run_time = omp_get_wtime() - start_time; //end timer
    printf("\n Time elapsed is %f secs \n %e FLOPs achieved\n", run_time, (double)(ARITHMETIC_OPERATIONS2) / ((double)run_time / TIMES2));
    return 0;
}

void initialize() {

    unsigned int i, j;

    //initialize routine2 arrays
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = (i % 99) + (j % 14) + 0.013f;
        }

    //initialize routine1 arrays
    for (i = 0; i < N; i++) {
        x[i] = (i % 19) - 0.01f;
        w[i] = (i % 5) - 0.002f;
    }

    //initialize routine1 arrays
    for (i = 0; i < M; i++) {
        z[i] = (i % 9) - 0.08f;
        y[i] = (i % 19) + 0.07f;
    }


}



//old code
void routine1(float alpha, float beta) {

    unsigned int i;


    for (i = 0; i < M; i++)
        y[i] = alpha * y[i] + beta * z[i];

}

void routine2(float alpha, float beta) {

    unsigned int i, j;


    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            w[i] = w[i] - beta + alpha * A[i][j] * x[j];


}
//new function for q1 using x86-64 SSE/SSE2/SSE4/AVX/AVX2
void routine1_vec(float alpha, float beta) {
    //need to change to x86..
    unsigned short int Add_SSE(); 
        __m128 num1, num2, num3,a,b,multi1,multi2;
        unsigned int i;


        for (i = 0; i < M; i++)
            num1 = _mm_loadu_ps(&y[i]);//loads 4
            a = _mm_loadu_ps(&alpha);
            b = _mm_loadu_ps(&beta);
            num2 = _mm_loadu_ps(&z[i]);//loads 4 
            multi1 = _mm_mul_ps(num1, a);
            multi2 = _mm_mul_ps(num2, b);
            num3 = _mm_add_ps(multi1, multi2);//adding together
            _mm_storeu_ps(&y[i], num3); //stored here
}

void routine2_vec(float alpha, float beta) {
    //need to change to x86..
    unsigned short int Add_SSE1();
    __m128 num1, a, alp, b,xx,multi1,add,div,multi2;
    unsigned int i, j;
    //times first, then add, then div

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            num1 = _mm_loadu_ps(&w[i]);//load
            alp = _mm_loadu_ps(&alpha);//load
            b = _mm_loadu_ps(&beta);//load
            a = _mm_loadu_ps(&A[i][j]);//load
            xx = _mm_loadu_ps(&x[j]);//load
            multi1 = _mm_mul_ps(alp, a);//alpha*A[i][j]
            multi2 = _mm_mul_ps(multi1, xx);//*x[j]
            add = _mm_add_ps(multi2, b);//adding beta
            div = _mm_sub_ps(num1, add); //sub the rest
            _mm_storeu_ps(&w[i], div); //store here
           
}

//unsigned short int Compare_Add1(float alpha, float beta) {


 //   for (int i = 0; i < M; i++) {
//        y[i] = alpha * y[i] + beta * z[i];
//    }

//    for (int i = 0; i < M; i++)
//        if (equal(y[i], y[i]) == 1) {
 //           printf("\n j=%d\n", i);
//            return 1;
//        }

//    return 0;
//}
//unsigned short int Compare_Add2(float alpha, float beta) {

//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < N; j++)
 //           w[i] = w[i] - beta + alpha * A[i][j] * x[j];


//    for (int j = 0; j < N; j++)
//        if (equal(w[j], w[j]) == 1) {
//            printf("\n j=%d\n", j);
//            return 1;
//        }

//    return 0;
//}


