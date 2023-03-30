#include <iostream>

#include "PhillipsSpectrum.h"

int main()
{
    Ocean::generateSpectrum();
    Ocean::updateHeights(0.0);

    for (int i = 0; i < 50; i++)
    {
        std::cout << Ocean::heights[i] << "\t";
    }

    return EXIT_SUCCESS;
}