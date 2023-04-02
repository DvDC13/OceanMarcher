#pragma once

#include "Complex.h"

namespace Ocean
{
    void FFT(Utils::Complex *x, int size);
    void IFFT(Utils::Complex *x, int size);
    void IFFT2D(Utils::Complex *x, int width, int height);
}