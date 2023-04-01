#include "FFT.h"

namespace Ocean
{
    void FFT(Utils::Complex *x, int N)
    {
        if (N <= 1) return;

        Utils::Complex *even = new Utils::Complex[N / 2];
        Utils::Complex *odd = new Utils::Complex[N / 2];

        for (int i = 0; i < N / 2; i++)
        {
            even[i] = x[2 * i];
            odd[i] = x[2 * i + 1];
        }

        FFT(even, N / 2);
        FFT(odd, N / 2);

        for (int i = 0; i < N / 2; i++)
        {
            Utils::Complex t = Utils::exp(-2 * M_PI * i / N) * odd[i];
            x[i] = even[i] + t;
            x[i + N / 2] = even[i] - t;
        }
    }

    void IFFT(Utils::Complex *x, int size)
    {
        for (int i = 0; i < size; i++)
            x[i] = x[i].conjugate();

        FFT(x, size);

        for (int i = 0; i < size; i++)
            x[i] = x[i].conjugate();
    }

} // namespace Ocean