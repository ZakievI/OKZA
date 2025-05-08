#include "HilbertIntegral.hpp"

void hilbert_integral(const std::vector<double> &gammas, 
                      const std::vector<double> &real_function_values, 
                      std::vector<double> &imaginary_function_values)
{
    const size_t N = real_function_values.size();
    const double PI = std::acos(-1.0);

    std::vector<double> derivative_real_function_values(N);

    derivative_real_function_values[0] = (real_function_values[1] - real_function_values[N - 2]) / 
                                         (gammas[1] - gammas[N - 2] - 2.0 * PI);
    derivative_real_function_values[N - 1] = derivative_real_function_values[0];

    for(size_t i = 1; i < N - 2; i++)
    {
        derivative_real_function_values[i] = (real_function_values[i + 1] - real_function_values[i - 1]) / 
                                             (gammas[i + 1] - gammas[i - 1]);
    }

    
}