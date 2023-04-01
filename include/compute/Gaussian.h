#pragma once

#include <random>

namespace Utils
{
    // Returns a random number from a uniform distribution between 0 and 1
    double Randomdouble();

    // Returns a random number from a Gaussian distribution with mean 0 and standard deviation 1
    double GaussianNumber();
} // namespace Utils