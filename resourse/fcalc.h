#pragma once
#define _UNICODE
#define UNICODE

#include <windows.h>

// Объявления типов функций
typedef int (__stdcall *FC_SPLINE)(int* n, double* x, double* y, double* bb, double* cc);
typedef double (__stdcall *FC_SPLINE_VAL)(int* n, double* x, double* bb, double* cc);
typedef double (__stdcall *FC_SPLINE_INT)(int* n, double* a, double* b, double* bb, double* cc);
typedef double (__stdcall *FC_SPLINE_DER)(int* n, int* ider, double* x, double* bb, double* cc);

// Объявления глобальных переменных (без инициализации)
extern HINSTANCE hSpline;
extern FC_SPLINE fc_spline;
extern FC_SPLINE_VAL fc_spline_val;
extern FC_SPLINE_INT fc_spline_int;
extern FC_SPLINE_DER fc_spline_der;

// Объявления функций
int LoadSplineDLL();
void FreeSplineDLL();