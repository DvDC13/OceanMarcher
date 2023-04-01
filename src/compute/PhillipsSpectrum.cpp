#include "PhillipsSpectrum.h"

namespace Ocean
{
    double generateCoefficient(const Utils::Vector2& k)
    {
        double L = Settings::windSpeed * Settings::windSpeed / Settings::gravity;
        double L2 = L * L;

        double kDotW = Utils::dot(k, Settings::windDirection);
        double kDotW2 = kDotW * kDotW;

        double k2 = Utils::lengthSquared(k);
        double k4 = k2 * k2;

        double A = 1;

        if (k2 < 0.000001) return 0.0;

        double result = A / k4 * std::exp(-1.0 / (k2 * L2)) * kDotW2;

        if (kDotW < 0.0) result *= 0.07;

        double l = L / 300.0;
        double l2 = l * l;

        double mulFactor = std::exp(-k2 * l2);

        return result * mulFactor;
    }


    void generateSpectrum()
    {
        int N = Settings::SCREEN_WIDTH;
        int M = Settings::SCREEN_HEIGHT;

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
            }
        }
    }

    void updateHeights(double t)
    {
        int N = Settings::SCREEN_WIDTH;
        int M = Settings::SCREEN_HEIGHT;

        for (int i = 0; i < N * M; i++)
            spectrumReel[i] = spectrumFreq[i];

        Ocean::IFFT(spectrumReel, M);

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int index = i * N + j;
                double h = spectrumReel[index].getReal();
                heights[index] = h;
            }
        }
    }

} // namespace Ocean