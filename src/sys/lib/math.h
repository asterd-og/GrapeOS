#pragma once

#include <stdint.h>
#include <stddef.h>

#define PI 3.14159265359
#define modd(x, y) ((x) - (int)((x) / (y)) * (y))

int abs(int n);
int Clamp(int value, int min, int max);
double floor(double num);
float sin(float x);
double cos(double x);