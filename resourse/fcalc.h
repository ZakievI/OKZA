//библиотека вычисления сплайнов

#include <windows.h>

typedef int (__stdcall *FC_SPLINE)(int* n, double* x, double* y, double* bb, double* cc); 
/*
построение сплайна Акима
n - число точек (n>=4)
x - массив x точек
y - массив y точек
bb,cc - коэффициенты построенного сплайна
возвращаемое значение: 0 - все Ок, -1 - ошибка
*/
typedef double (__stdcall *FC_SPLINE_VAL)(int* n, double* x, double* bb, double* cc); 
/*
вычисление значения сплайна в точке
n - число точек сплайна
x - точка, в которой нужно вычислить сплайн
bb,cc - коэффициенты построенного сплайна из FC_SPLINE
возвращаемое значение: значение сплайна в точке
*/
typedef double (__stdcall *FC_SPLINE_INT)(int* n, double* a, double* b, double* bb, double* cc); 
/*
вычисление интеграла от сплайна
n - число точек сплайна
a,b - границы интервала, на котором вычисляется интеграл
bb,cc - коэффициенты построенного сплайна из FC_SPLINE
возвращаемое значение: вычисленный интеграл
*/

typedef double (__stdcall *FC_SPLINE_DER)(int* n, int* ider, double* x, double* bb, double* cc); 
/*
вычисление производной от сплайна
ider - поряд кроизводной
n - число точек сплайна
x - точка, в которой нужно вычислить производную сплайна
bb,cc - коэффициенты построенного сплайна из FC_SPLINE
возвращаемое значение: вычисленный интеграл
*/

HINSTANCE hSpline=NULL;
FC_SPLINE fc_spline = NULL;
FC_SPLINE_VAL fc_spline_val = NULL;
FC_SPLINE_INT fc_spline_int = NULL;
FC_SPLINE_DER fc_spline_der = NULL;

int LoadSplineDLL()
//загрузка библиотеки сплайнов
{
    hSpline=LoadLibrary(L"fcalc.dll");
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
//выгрузка библиотеки сплайнов
{
    fc_spline = NULL;
    fc_spline_val = NULL;
    fc_spline_int = NULL;
    fc_spline_der = NULL;
    if (hSpline == NULL) return;
    FreeLibrary(hSpline);
}