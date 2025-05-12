#include <fstream>
#include <vector>
#include <string>

#include "lib/unit6/include/HilbertIntegral.hpp"


int main()
{
    std::vector<double> gammas;
    std::vector<double> theta_u;
    std::vector<double> theta_v;

    // Start test part
    std::ifstream in("resourse/gam.dat");
    size_t n;
    std::string str;
    std::string s_, s_gamma, s_theta_u;

    in >> str;

    n = std::stoi(str) + 1;

    gammas.resize(n);
    theta_u.resize(n);

    in >> s_gamma >> s_ >> s_ >> s_ >> s_ >> s_ >> s_theta_u >> s_ >> s_ >> s_ >> s_ >> s_ >> s_;

    for(int i = 0; i < n; i++)
    {
        in >> s_gamma >> s_ >> s_ >> s_ >> s_ >> s_theta_u >> s_ >> s_ >> s_ >> s_ >> s_ >> s_ >> s_;
        gammas[i] = std::stod(s_gamma);
        theta_u[i] = std::stod(s_theta_u);
    }

    theta_v.resize(n);
    // End test part

    hilbert_integral(gammas, theta_u, theta_v);

    return 0;
}