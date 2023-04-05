#pragma once

#include <iostream>

#include "Settings.h"
#include "Complex.h"
#include "Vector2.h"
#include "Gaussian.h"
#include "FFT.h"

namespace Ocean
{
    static Utils::Complex* spectrumFreq = new Utils::Complex[Settings::SCREEN_HEIGHT * Settings::SCREEN_WIDTH];
    static Utils::Complex* spectrumReel = new Utils::Complex[Settings::SCREEN_HEIGHT * Settings::SCREEN_WIDTH];

    inline double* heights = new double[Settings::SCREEN_HEIGHT * Settings::SCREEN_WIDTH];
    inline double* pulsations = new double[Settings::SCREEN_HEIGHT * Settings::SCREEN_WIDTH];

    inline double minValue;
    inline double maxValue;

    double generateCoefficient(const Utils::Vector2& k);

    void generateSpectrum();

    void updateHeights(double t);
} // namespace Ocean