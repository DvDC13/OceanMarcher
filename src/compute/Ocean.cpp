#include "Ocean.h"

namespace Ocean
{
    double generateCoefficient(const Utils::Vector2& k)
    {
        double L = Settings::windSpeed * Settings::windSpeed / Settings::gravity;
        double L2 = L * L;

        double kDotW = Utils::dot(k, Settings::windDirection);
        double kDotW2 = kDotW * kDotW;

        double k2 = Utils::lengthSquared(k);
        double k6 = k2 * k2 * k2;

        double A = 1;

        if (k2 < 0.000001) return 0.0;

        double result = A / k6 * std::exp(-1.0 / (k2 * L2)) * kDotW2;

        if (kDotW < 0.0) result *= 0.07;

        double l = L / 300.0;
        double l2 = l * l;

        double mulFactor = std::exp(-k2 * l2);

        return result * mulFactor;
    }

    void generateSpectrum()
    {
        int N = Settings::heightMapWidth;
        int M = Settings::heightMapHeight;

        for (int i = -M/2; i < M/2; i++)
        {
            for (int j = -N/2; j < N/2; j++)
            {
                double kx = (2.0 * M_PI * j) / Settings::Lx;
                double ky = (2.0 * M_PI * i) / Settings::Ly;

                Utils::Vector2 k(kx, ky);

                double phk = std::sqrt(generateCoefficient(k) / 2.0);

                int index = (i + M/2) * N + (j + N/2);

                double er = Utils::GaussianNumber();
                double ei = Utils::GaussianNumber();

                spectrumFreq[index] = Utils::Complex(phk * er, phk * ei);

                pulsations[index] = std::sqrt(Settings::gravity * length(k));
            }
        }
    }

    Utils::Complex oppositeIndex(int i, int j, int width, int height)
    {
        Utils::Complex result = spectrumFreq[i * width + j];
        if (i == 0 && j == 0) result = Ocean::spectrumFreq[width * height - 1];
        if (i == 0 && j != 0) result = Ocean::spectrumFreq[width * (height - 1) + (width - j - 1)];
        if (i != 0 && j == 0) result = Ocean::spectrumFreq[(height - i - 1) * width + (width - 1)];
        if (i != 0 && j != 0) result = Ocean::spectrumFreq[(height - i) * width + (height - j)];
        return result;
    }

    void updateHeights(double t)
    {   
        int N = Settings::heightMapWidth;
        int M = Settings::heightMapHeight;

        minValue = 0.0;
        maxValue = 0.0;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int index = i * N + j;

                Utils::Complex h = spectrumFreq[index];
                Utils::Complex opposite = oppositeIndex(i, j, N, M);
                Utils::Complex conj = opposite.conjugate();

                double wt = pulsations[index] * t;

                Utils::Complex result = h * Utils::exp(wt) + conj * Utils::exp(-wt);

                spectrumReel[index] = result;
            }
        }

        Ocean::IFFT2D(spectrumReel, N, M);

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int index = i * N + j;

                double sign = (i + j) % 2 == 0 ? 1.0 : -1.0;

                double h = spectrumReel[index].getReal();

                heights[index] = sign * h;

                if (heights[index] < minValue) minValue = heights[index];
                if (heights[index] > maxValue) maxValue = heights[index];
            }
        }
    }
} // namespace Ocean