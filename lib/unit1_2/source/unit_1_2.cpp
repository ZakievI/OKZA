#include"../include/unit_1_2.hpp"

void svWriter(std::string Sout, std::vector<double>& S, std::vector<double>& V)
{
    std::ifstream in(Sout);
    size_t N = 0;
    in >> N;
    in.ignore();

    std::vector<double> S1(N+1);
    std::vector<double> V1(N+1);


    std::string header;
    std::getline(in, header);

    for (int i = 0; i <= N; i++)
    {
        in >> S1[i];
        in >> V1[i];
        std::getline(in, header);
    }

    S = S1;
    V = V1;
    //Fis = Fis1;
    in.close();
}
void SaCompute(std::vector<double> S, std::vector<double> V, double& sa)
{
    size_t n = V.size();
    size_t k1;
    size_t k2;

    for (int i = 1; i < n - 1; i++)
    {
        if (V[i] == 0)
        {
            k1 = i + 1;
            k2 = i - 1;
            break;
        }
        else if (V[i + 1] > 0 && V[i] < 0)
        {
            k1 = i + 1;
            k2 = i;
            break;
        }

    }

    sa = S[k2] - (-V[k2] * (S[k1] - S[k2]) / (V[k1] + V[k2]));
}

void FiCompute(double sa, std::vector<double> S, std::vector<double> V, std::vector<double>& Fi, double& fi0, double& fi1)
{
    int n = V.size();
    std::vector<double> bb(n);
    std::vector<double> cc(4 * n);
    std::vector<double> fi11(n);

    double s0 = 0.0;

    fc_spline(&n, &S[0], &V[0], &bb[0], &cc[0]);

    fi11[0] = -fc_spline_int(&n, &s0, &sa, &bb[0], &cc[0]);

    for (int i = 0; i < n - 1; i++)
    {
        fi11[i + 1] = fi11[i] + fc_spline_int(&n, &S[i], &S[i + 1], &bb[0], &cc[0]);
    }

    fi0 = fi11[0];
    fi1 = fi11[n - 1];
    Fi = fi11;
}

void GCompute(double fi0, double fi1, double& G)
{
    G = fi1 - fi0;
}

void svWriterGCRS(std::string sIn, std::vector<double>& S, std::vector<double>& V)
{
    std::ifstream in(sIn);
    size_t nj; size_t ns; double s1; double s2; double s3; double l; double v1; double v2; double k;
    std::string sHelp;
    in >> nj;
    std::getline(in, sHelp);
    in >> ns;
    std::getline(in, sHelp);
    in >> s1;
    std::getline(in, sHelp);
    in >> s2;
    std::getline(in, sHelp);
    in >> s3;
    std::getline(in, sHelp);
    in >> l;
    std::getline(in, sHelp);
    in >> v1;
    std::getline(in, sHelp);
    in >> v2;
    std::getline(in, sHelp);
    in >> k;

    double D = (pow((v1 / v2), 1.0 / k) - 1.0) / (l - s3);

    std::vector<double> S1(ns + 1);
    std::vector<double> V11(ns + 1);

    for (int i = 0; i <= ns; i++)
    {
        S1[i] = l * i / ns;
    }

    for (int i = 0; i <= ns; i++)
    {
        if (S1[i] >= 0 && S1[i] <= s1)
        {
            V11[i] = -v1;
        }

        else if (S1[i] > s1 && S1[i] < s2)
        {
            V11[i] = (v2 + v1) * (S1[i] - s1) / (s2 - s1) - v1;
        }

        else if (S1[i] >= s2 && S1[i] <= s3)
        {
            V11[i] = v2;
        }

        else if (S1[i] > s3 && S1[i] <= l)
        {
            V11[i] = v2 * pow((1 + D * (S1[i] - s3)), k);
        }
    }

    S = S1;
    V = V11;

}