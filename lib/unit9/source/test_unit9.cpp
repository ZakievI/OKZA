#include <iostream>
#include "test_unit9.hpp"
#include <cmath>

vec read_vector(std::ifstream& in, int col) {
    vec data;

    std::string first_line;
    std::getline(in, first_line);
    int size;
    std::istringstream first_line_stream(first_line);
    first_line_stream >> size;
    size++;
    std::getline(in, first_line);
    std::string data_line;
    while (std::getline(in, data_line), data.size() < size) {
        std::istringstream iss(data_line);
        double value;
        int column = 0;
        while (iss >> value) {
            if (column == col) {
                data.push_back(value);
                break;
            }
            column++;
        }
    }
    if (in.fail() && !in.eof()) {
        std::cerr << "Ошибка чтения файла!" << std::endl;
        in.clear();
    }
    return data;
}

std::pair<double, double> compute_cxcy(double bbb, vec v, vec theta_p, vec& theta_p_s, vec x, vec y, vec& s, vec& v_s) {
    int n = v.size();
    vec gamma(n, 0.0);
    for (int i = 0; i < n; i++) {
        gamma[i] = 2 * M_PI * i / (n - 1);
    }
    for (int i = 0; i < n - 1; i++) {
        double a = (x[i + 1] - x[i]) * (x[i + 1] - x[i]) + (y[i + 1] - y[i]) * (y[i + 1] - y[i]);
        s[i + 1] = s[i] + std::sqrt(a);
    }
    vec bb(n, 0.0);
    vec cc(4 * n, 0.0);
    if (fc_spline(&n, &s[0], &gamma[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }

    vec gamma_s(n, 0.0);
    vec vec_int(n, 0.0);

    double xx;
    for (size_t i = 0; i < n; i++) {
        xx = s[i];
        gamma_s[i] = fc_spline_val(&n, &xx, &bb[0], &cc[0]);
    }
    if (fc_spline(&n, &gamma[0], &v[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }
    for (size_t i = 0; i < n; i++) {
        xx = gamma_s[i];
        v_s[i] = fc_spline_val(&n, &xx, &bb[0], &cc[0]);
    }
    if (fc_spline(&n, &gamma[0], &theta_p[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }
    for (size_t i = 0; i < n; i++) {
        xx = gamma_s[i];
        theta_p_s[i] = fc_spline_val(&n, &xx, &bb[0], &cc[0]);
    }

    for (size_t i = 0; i < n; i++) {
        vec_int[i] = (1.0 - v_s[i] * v_s[i]) * sin(theta_p_s[i]);
    }
    if (fc_spline(&n, &s[0], &vec_int[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }
    double a = s[0];
    double b = s.back();
    double cx = fc_spline_int(&n, &a, &b, &bb[0], &cc[0]);

    for (size_t i = 0; i < n; i++) {
        vec_int[i] = (1.0 - v_s[i] * v_s[i]) * cos(theta_p_s[i]);
    }
    if (fc_spline(&n, &s[0], &vec_int[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }

    double cy = fc_spline_int(&n, &a, &b, &bb[0], &cc[0]);
    auto p = std::make_pair(cx / bbb, -cy / bbb);
    return p;
}

vec compute_delta(vec& s, vec& v_s, double sa) {
    /*double a = 1.17;
    double b = 4.75;
    double m = 6.0;
    double A = 6.55e-3;*/
    /* double f_0 = -1.86;
     double a = 0.45;
     double m = 1;
     double b = 5.35;
     double A = 1;*/
    double f0 = -5.18;
    double a = 1.25;
    double m = 4.0;
    double b = 4.86;
    double A = 1.256e-2;

    double nu = 1.51e-5;
    int n = v_s.size();
    double v_inf = 1.0;

    vec bb(n, 0.0);
    vec cc(4 * n, 0.0);

    std::reverse(v_s.begin(), v_s.end());

    if (fc_spline(&n, &s[0], &v_s[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }
    vec der(n);
    int p = 1;
    for (int i = 0; i < n; i++) {
        der[i] = fc_spline_der(&n, &p, &s[i], &bb[0], &cc[0]);
    }

    vec v_int(n);
    for (int i = 0; i < n; i++) {
        v_int[i] = std::pow(std::abs(v_s[i]), b - 1);
    }

    if (fc_spline(&n, &s[0], &v_int[0], &bb[0], &cc[0]) < 0) {
        std::cout << "fc_spline error" << std::endl;
    }

    double s_star = 0;
    double s_star1 = 0;
    double delta2_star = 0.0;
    for (int i = 0; i <n; i++) {
        if (v_s[i] > 0.3) {
            s_star = s[i];
            break;
        }
    }
    for (int i = n-1; i >= 0; i--) {
        if (v_s[i] < -0.3) {
            s_star1 = s[i];
            break;
        }
    }
    
    vec f(n);
    for (int i = 0; i < n; i++) {
        if ((s[i] > sa && s[i] < s_star) || (s[i] > s_star1 && s[i] < sa)) {
            f[i] = a / b;
        }
        else if ((s[i] > sa && s[i] < s_star1) || (s[i] > s_star1 && s[i] < sa)) {

        }
        else {
            double coef = a * der[i] /
                std::pow(std::abs(v_s[i]), b);
            f[i] = coef * std::abs(fc_spline_int(&n, &sa, &s[i], &bb[0], &cc[0]));
        }
    }

    vec delta2(n);
    for (int i = 0; i < n; i++) {
        double p = std::pow(A * std::abs(v_s[i]) * f[i] / der[i], m);
        double t = nu / std::abs(v_s[i]);
        double k = 1 / (m + 1);
        delta2[i] = std::pow(p * t, k);
    }
    size_t id;
    for (int i = n-1; i >= 0; i--) {
        if ((s[i] > sa && s[i] < s_star)) {
            delta2_star = delta2[i - 1];
            break;
        }
    }
    double delta2_star1 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] > s_star1 && s[i] < sa) {
            delta2_star1 = delta2[i];
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if ((s[i] > sa && s[i] < s_star)) {
            delta2[i] = delta2_star;
        }
        else if (s[i] > s_star1 && s[i] < sa) {
            delta2[i] = delta2_star1;
        }
    }

    auto H = [](double f) {return 1.35 - 0.0701 * f + 0.02913 * f * f + 0.01083 * f * f * f + 0.001606 * f * f * f * f; };

    vec delta1(n);
    for (int i = sa; i < n; i++) {
        delta1[i] = H(f[i]) * delta2[i];
    }
    return delta1;
}

void draw_graph(vec delta1, vec& teta_p, vec x, vec y) {
    size_t n = x.size();
    std::vector<std::complex<double>> xy(n);

    for (size_t i = 0; i < n; i++) {
        std::complex<double> o = std::complex<double>(0, 1) * teta_p[i];
        std::complex<double> normal = std::complex<double>(0, 1) * std::exp(o);
        xy[i] = std::complex<double>(x[i], y[i]) + delta1[n -i-1] * normal;
    }
    std::ofstream out1("foil.dat");
    std::ofstream out2("foil_ps.dat");
    if (!out1.is_open() || !out2.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return;
    }
    vec s(n, 0.0);
    for (int i = 0; i < n - 1; i++) {
        double a = (x[i + 1] - x[i]) * (x[i + 1] - x[i]) + (y[i + 1] - y[i]) * (y[i + 1] - y[i]);
        s[i + 1] = s[i] + std::sqrt(a);
    }
    for (size_t i = 0; i < n - 1; i++) {
        out2 << xy[i].real() << "\t" << xy[i].imag() << "\r\n";
    }
    for (size_t i = 0; i < n; i++) {
        out1 << x[i] << "\t" << y[i] << "\r\n";
    }
    out1.close();
    out2.close();
}