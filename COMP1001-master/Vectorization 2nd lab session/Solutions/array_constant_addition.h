#pragma once


#include <stdio.h>
#include <time.h>
#include <pmmintrin.h>
#include <process.h>
#include <chrono>
#include <iostream>
#include <immintrin.h>

//MVM initialization 
#define M 10000000


void initialization_ConstAdd();

unsigned short int ConstAdd_default();
unsigned short int ConstAdd_SSE();
unsigned short int ConstAdd_SSE_all_sizes();
unsigned short int ConstAdd_AVX();
unsigned short int ConstAdd_AVX()_all_sizes();
unsigned short int Compare_ConstAdd();
unsigned short int equal(float a, float b);
#define EPSILON 0.01


