#include "fcalc.h"

// Определения глобальных переменных
HINSTANCE hSpline = NULL;
FC_SPLINE fc_spline = NULL;
FC_SPLINE_VAL fc_spline_val = NULL;
FC_SPLINE_INT fc_spline_int = NULL;
FC_SPLINE_DER fc_spline_der = NULL;

// Реализация функции загрузки DLL
int LoadSplineDLL()
{
    hSpline = LoadLibrary(L"fcalc.dll");
    if (hSpline == NULL) return -1;
    
    fc_spline = (FC_SPLINE)GetProcAddress(hSpline, "FC_SPLINE");
    if (fc_spline == NULL) return -1;
    
    fc_spline_val = (FC_SPLINE_VAL)GetProcAddress(hSpline, "FC_SPLINE_VAL");
    if (fc_spline_val == NULL) return -1;
    
    fc_spline_int = (FC_SPLINE_INT)GetProcAddress(hSpline, "FC_SPLINE_INT");
    if (fc_spline_int == NULL) return -1;
    
    fc_spline_der = (FC_SPLINE_DER)GetProcAddress(hSpline, "FC_SPLINE_DER");
    if (fc_spline_der == NULL) return -1;
    
    return 0;
}

// Реализация функции выгрузки DLL
void FreeSplineDLL()
{
    fc_spline = NULL;
    fc_spline_val = NULL;
    fc_spline_int = NULL;
    fc_spline_der = NULL;
    
    if (hSpline != NULL) {
        FreeLibrary(hSpline);
        hSpline = NULL;
    }
}