#pragma once

#include "Complex.h"

namespace Ocean
{
    void FFT(Utils::Complex *x, int N);
    void IFFT(Utils::Complex *x, int N);
}