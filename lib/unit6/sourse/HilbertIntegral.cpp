#include "../include/HilbertIntegral.hpp"
#include <iostream>

/**
 * @param gammas input parameter. Grid on a circle. Node gamma i-th.
 * @param real_function_values input parameter. Real values of the function at the gamma nodes.
 * @param imaginary_function_values output parameter. Calculated imaginary values of the function at the gamma mode.
 */
void hilbert_integral(const std::vector<double> &gammas, 
                      const std::vector<double> &real_function_values, 
                      std::vector<double> &imaginary_function_values)
{
    const size_t N = real_function_values.size();
    const double PI = std::acos(-1.0);

    std::vector<double> derivative_real_function_values(N);

    derivative_real_function_values[0] = (real_function_values[1] - real_function_values[N - 2]) / 
                                         (gammas[1] - gammas[N - 2] + 2.0 * PI);
    derivative_real_function_values[N - 1] = derivative_real_function_values[0];

    for(size_t i = 1; i < N - 2; i++)
    {
        derivative_real_function_values[i] = (real_function_values[i + 1] - real_function_values[i - 1]) / 
                                             (gammas[i + 1] - gammas[i - 1]);
    }

    std::vector<double> F(N * (N - 1));

    for(size_t k = 0; k < N - 1; k++)
    {
        for(size_t j = 0; j < N - 1; j++)
        {
            if (k != j)
            {
                F[k * (N - 1) + j] = (real_function_values[k] - real_function_values[j]) / 
                                     std::tan(0.5 * (gammas[j] - gammas[k]));
            }
            else
            {
                F[k * (N - 1) + j] = -2.0 * derivative_real_function_values[k];
            }
        }
    }

    for(size_t j = 0; j < N - 1; j++)
    {
        F[(N - 1) * (N - 1) + j] = F[0 + j];
    }

    imaginary_function_values.clear();
    imaginary_function_values.resize(N);

    for(size_t j = 0; j < N - 1; j++)
    {
        double sum_F = 0.0;
        for(size_t k = 0; k < N - 1; k++)
        {
            sum_F += 0.5 * (F[k * (N - 1) + j] + F[(k + 1) * (N - 1) + j]) * (gammas[k + 1] - gammas[k]);
        }

        imaginary_function_values[j] = -1.0 / (2.0 * PI) * sum_F;
    }

    imaginary_function_values[N - 1] = imaginary_function_values[0];
}