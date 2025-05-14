//���������� ���������� ��������

#ifndef _FCALC
#define _FCALC
#include <windows.h>
#include <iostream>
#include <unistd.h>

typedef int (__stdcall *FC_SPLINE)(int* n, double* x, double* y, double* bb, double* cc); 
/*
���������� ������� �����
n - ����� ����� (n>=4)
x - ������ x �����
y - ������ y �����
bb,cc - ������������ ������������ �������
������������ ��������: 0 - ��� ��, -1 - ������
*/
typedef double (__stdcall *FC_SPLINE_VAL)(int* n, double* x, double* bb, double* cc); 
/*
���������� �������� ������� � �����
n - ����� ����� �������
x - �����, � ������� ����� ��������� ������
bb,cc - ������������ ������������ ������� �� FC_SPLINE
������������ ��������: �������� ������� � �����
*/
typedef double (__stdcall *FC_SPLINE_INT)(int* n, double* a, double* b, double* bb, double* cc); 
/*
���������� ��������� �� �������
n - ����� ����� �������
a,b - ������� ���������, �� ������� ����������� ��������
bb,cc - ������������ ������������ ������� �� FC_SPLINE
������������ ��������: ����������� ��������
*/

typedef double (__stdcall *FC_SPLINE_DER)(int* n, int* ider, double* x, double* bb, double* cc); 
/*
���������� ����������� �� �������
ider - ����� �����������
n - ����� ����� �������
x - �����, � ������� ����� ��������� ����������� �������
bb,cc - ������������ ������������ ������� �� FC_SPLINE
������������ ��������: ����������� ��������
*/

extern HINSTANCE hSpline;
extern FC_SPLINE fc_spline;
extern FC_SPLINE_VAL fc_spline_val;
extern FC_SPLINE_INT fc_spline_int;
extern FC_SPLINE_DER fc_spline_der;

int LoadSplineDLL();
void FreeSplineDLL();
#endif