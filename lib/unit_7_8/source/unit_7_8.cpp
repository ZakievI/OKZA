#include "../include/unit_7_8.hpp"

pair<vector<double>, vector<double>> splineAkim(int n, vector<double> x, vector<double>y)
{
    vector<double> bb;
    vector<double> cc;
    bb.resize(n);
    cc.resize(4 * n);
    if (fc_spline(&n, &x[0], &y[0], &bb[0], &cc[0]) < 0)
    {
        cerr << "ORESHNIK STRIKE: SPLINE CONSTRUCTION" << endl;
    }
    return pair<vector<double>, vector<double>>(bb, cc);
}


complex<double> f1g(double gamma_arg, double u0, double beta, vector<double>svv1_bb, vector<double>svv1_cc, vector<double>tetav_bb, vector<double>tetav_cc)
{
    complex<double> brr = complex<double>(0, -beta);
    complex<double> koef = complex<double>(0, u0);
    complex<double> dzeta_brr = complex<double>(0, gamma_arg);
    complex<double> dzeta = exp(dzeta_brr);
    complex<double> rrr = koef * exp(brr) * (dzeta - complex<double>(1, 0)) * exp(-h1v(dzeta, svv1_bb, svv1_cc, tetav_bb, tetav_cc));
    return rrr;

}

complex<double> h1v(complex<double> dzeta_arg, vector<double>svv1_bb, vector<double>svv1_cc, vector<double>tetav_bb, vector<double>tetav_cc)
{
    double eiGamm_arg = arg(dzeta_arg);//(log(dzeta_arg)/complex<double>(0,1)).real(); //if(<0) +2pi
    double pi = 4 * atan(1);//3.14159265359
    if (eiGamm_arg < 0)eiGamm_arg += 2 * pi; //� ��� � ���� ������ �� 0 �� 2��, � �� �� -�� �� �� ��� � ���������. ������ �� ��� 4*������(1)
    int n = svv1_bb.size();
    return complex<double>(fc_spline_val(&n, &eiGamm_arg, &svv1_bb[0], &svv1_cc[0]), fc_spline_val(&n, &eiGamm_arg, &tetav_bb[0], &tetav_cc[0]));
    //�� �� ��� ����� ������������
}

double specialInt(int n, double a, double b, pair<vector<double>, vector<double>> data)
{
    return fc_spline_int(&n, &a, &b, &data.first[0], &data.second[0]);
}

pair<vector<double>, vector<double>> splineAkimSpecific(int n, int start, vector<double> x, vector<double> y)
{
    vector<double> bb;
    vector<double> cc;
    bb.resize(n);
    cc.resize(4 * n);
    if (fc_spline(&n, &x[start], &y[start], &bb[0], &cc[0]) < 0)
    {
        cerr << "ORESHNIK STRIKE: SPLINE CONSTRUCTION" << endl;
    }
    return pair<vector<double>, vector<double>>(bb, cc);
}

void unit_7_8(double &u0_in, double &beta_in, double &db, vector<double>& gamma_in, vector<double>& sg_in, vector<double>& tetav_in, vector<double>&x_out, vector<double>&y_out, vector<double> &s_out, double &b, double &alpha, double &relative_thickness)
{
    int n = gamma_in.size();
    pair<vector<double>, vector<double>> res_slot1 = splineAkim(n, gamma_in, sg_in); //�����������: ���� �� ���, ������� ����� ������ � �����
    //vector<double> bb_one = sg_res.first;
    //vector<double> cc_one = sg_res.second;

    pair<vector<double>, vector<double>> res_slot2 = splineAkim(n, gamma_in, tetav_in); //�����������: ���� �� ���, ������� ����� ������ � �����
    //vector<double> bb_sec = tetav_res.first;
    //vector<double> cc_sec = tetav_res.second;


    vector<double> f1RE;
    vector<double> f1IM;
    f1RE.resize(n);
    f1IM.resize(n);


    for (int i = 0; i < n; i++)
    {
        f1RE[i] = (f1g(gamma_in[i], u0_in, beta_in, res_slot1.first, res_slot1.second, res_slot2.first, res_slot2.second).real());
        f1IM[i] = (f1g(gamma_in[i], u0_in, beta_in, res_slot1.first, res_slot1.second, res_slot2.first, res_slot2.second).imag());
    }

    res_slot1 = splineAkim(n, gamma_in, f1RE); //f1re_res
    res_slot2 = splineAkim(n, gamma_in, f1IM); //f1im_res

    f1RE.clear();
    f1IM.clear();
    x_out.resize(n);
    y_out.resize(n);
    x_out[0] = 0;
    y_out[0] = 0;

    for (int j = 0; j < n - 1; j++)
    {
        x_out[j+1] = (x_out[j] + specialInt(n, gamma_in[j], gamma_in[j + 1], res_slot1));
        y_out[j+1] = (y_out[j] + specialInt(n, gamma_in[j], gamma_in[j + 1], res_slot2));
    }

    s_out.resize(n);
    int ib = 0;
    double mem = 0;
    for (int j = 0; j < n - 1; j++)
    {
        s_out[j + 1] = s_out[j] + sqrt(pow(x_out[j + 1] - x_out[j], 2) + pow(y_out[j + 1] - y_out[j], 2));
        
    }
    vector<double>s180(n, 0); //::clown_face::
    for (int j = 0; j < n - 1; j++)
    {
        s180[j] = s_out[n - 1 - j];
        if (sqrt(x_out[j] * x_out[j] + y_out[j] * y_out[j]) > mem ) //�� s0 ���������� �����, ��� ������ ���������� ����, ����� ��� ������ ���.
        {
            ib = j;
            mem = sqrt(x_out[j] * x_out[j] + y_out[j] * y_out[j]);
        }
    }
    for (int j = 0; j < n - 1; j++) //::clown_face::
    {
        s_out[j] = s180[j];
    }
    s180.clear();
    b=sqrt(x_out[ib] * x_out[ib] + y_out[ib] * y_out[ib]);
    alpha = 0;
    if (y_out[ib] >= 0)
    {
        alpha = 4 * atan(1) - atan2(y_out[ib], x_out[ib]);
    }
    else
    {
        alpha = -4 * atan(1) - atan2(y_out[ib], x_out[ib]);
    }

  
    //vector<double> xrot(n, 0);
    //vector<double> yrot(n, 0);
    f1RE.resize(n);
    f1IM.resize(n);
    //������� ��� ������������, ������������. ����� �����, ������ ��� �� ����� ����� ����� ��� ������� (���� �������)
    int nup = 0;
    int ndown = 0;
    for (int i = 0; i < n; i++)
    {
        //������� �� ������� ���� ���� �������� > 0
        //-alpha �� "�� ������" ����� �� �������
        f1RE[i] = x_out[i] * cos(-alpha) + y_out[i] * sin(-alpha);
        f1IM[i] = -x_out[i] * sin(-alpha) + y_out[i] * cos(-alpha);
        
    }
    //�� �� ������� ���������. �� �������� ������ ib+1 �����. ������ � ������
        //����� ������ ������� � ���������. ������
    nup = ib;
    ndown = n - ib;

    //pair<vector<double>, vector<double>> upAkim; first slot
    //pair<vector<double>, vector<double>> downAkim; second slot

    res_slot1 = splineAkimSpecific(nup, 0, f1RE, f1IM);
    res_slot2 = splineAkimSpecific(ndown, ib + 1, f1RE, f1IM);

    vector<double> thickness(b / db, 0); //���� ��������� ������������ ������ � ����� 
    double maxthickness = 0;

    for (int i = 0; i < thickness.size(); i++)
    {
        mem = -i * db;
        double splineUp = fc_spline_val(&nup, &mem, &res_slot1.first[0], &res_slot1.second[0]);
        double splineDown = fc_spline_val(&ndown, &mem, &res_slot2.first[0], &res_slot2.second[0]);
        thickness[i] = splineUp - splineDown;
        if (thickness[i] > maxthickness)maxthickness = thickness[i];
    }

    relative_thickness = maxthickness / b;
}