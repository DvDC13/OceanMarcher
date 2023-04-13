#pragma once

#include <iostream>

#include "Settings.h"
#include "Complex.h"
#include "Vector2.h"
#include "Gaussian.h"
#include "FFT.h"

namespace Ocean
{
    inline Utils::Complex* spectrumFreq = new Utils::Complex[Settings::heightMapHeight * Settings::heightMapWidth];
    inline Utils::Complex* spectrumReel = new Utils::Complex[Settings::heightMapHeight * Settings::heightMapWidth];

    inline double* heights = new double[Settings::heightMapHeight * Settings::heightMapWidth];
    inline double* pulsations = new double[Settings::heightMapHeight * Settings::heightMapWidth];

    inline double minValue;
    inline double maxValue;

    double generateCoefficient(const Utils::Vector2& k);

    void generateSpectrum();

    void updateHeights(double t);
} // namespace Ocean