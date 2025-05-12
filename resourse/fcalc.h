//���������� ���������� ��������

#define _UNICODE
#define UNICODE
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

HINSTANCE hSpline=NULL;
FC_SPLINE fc_spline = NULL;
FC_SPLINE_VAL fc_spline_val = NULL;
FC_SPLINE_INT fc_spline_int = NULL;
FC_SPLINE_DER fc_spline_der = NULL;

int LoadSplineDLL()
//�������� ���������� ��������
{
    // измененные строки
    DWORD error = GetLastError();

    hSpline=LoadLibrary(L"resourse\\fcalc.dll");
    if (!hSpline) {
        DWORD error = GetLastError();
        std::cerr << "Ошибка загрузки DLL! Код: " << error << std::endl;
        return 0;
    }
    //
    if (hSpline==NULL) return -1;
    fc_spline = (FC_SPLINE) GetProcAddress(hSpline,"FC_SPLINE");
    if (fc_spline == NULL) return -1;
    fc_spline_val = (FC_SPLINE_VAL) GetProcAddress(hSpline,"FC_SPLINE_VAL");
    if (fc_spline_val == NULL) return -1;
    fc_spline_int = (FC_SPLINE_INT) GetProcAddress(hSpline,"FC_SPLINE_INT");
    if (fc_spline_int == NULL) return -1;
    fc_spline_der = (FC_SPLINE_DER) GetProcAddress(hSpline,"FC_SPLINE_DER");
    if (fc_spline_der == NULL) return -1;
    return 0;
}

void FreeSplineDLL()
//�������� ���������� ��������
{
    fc_spline = NULL;
    fc_spline_val = NULL;
    fc_spline_int = NULL;
    fc_spline_der = NULL;
    if (hSpline == NULL) return;
    FreeLibrary(hSpline);
}