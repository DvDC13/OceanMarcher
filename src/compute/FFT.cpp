#include "FFT.h"

namespace Ocean
{
    void FFT(Utils::Complex *x, int size)
    {
        if (size <= 1) return;

        Utils::Complex *even = new Utils::Complex[size / 2];
        Utils::Complex *odd = new Utils::Complex[size / 2];

        for (int i = 0; i < size / 2; i++)
        {
            even[i] = x[2 * i];
            odd[i] = x[2 * i + 1];
        }

        FFT(even, size / 2);
        FFT(odd, size / 2);

        for (int i = 0; i < size / 2; i++)
        {
            Utils::Complex t = Utils::exp(-2 * M_PI * i / size) * odd[i];
            x[i] = even[i] + t;
            x[i + size / 2] = even[i] - t;
        }

        delete[] even;
        delete[] odd;
    }

    void IFFT(Utils::Complex *x, int size)
    {
        for (int i = 0; i < size; i++)
            x[i] = x[i].conjugate();

        FFT(x, size);

        for (int i = 0; i < size; i++)
            x[i] = x[i].conjugate();
    }

    void IFFT2D(Utils::Complex *x, int width, int height)
    {
        for (int i = 0; i < height; i++)
            IFFT(x + i * width, width);

        Utils::Complex *col = new Utils::Complex[height];

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
                col[j] = x[j * width + i];

            IFFT(col, height);

            for (int j = 0; j < height; j++)
                x[j * width + i] = col[j];
        }

        delete[] col;
    }
} // namespace Ocean