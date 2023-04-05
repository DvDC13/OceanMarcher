#include <iostream>

#include <chrono>
#include <algorithm>

#include "Image.h"
#include "PhillipsSpectrum.h"

Rendering::Pixel processImageColor(Utils::Color3& pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.getX();
    auto g = pixel_color.getY();
    auto b = pixel_color.getZ();

    auto scale = 1.0f / samples_per_pixel;

    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    int ir = std::min(255.0, std::max(0.0, r * 255.99));
    int ig = std::min(255.0, std::max(0.0, g * 255.99));
    int ib = std::min(255.0, std::max(0.0, b * 255.99));

    Rendering::Pixel pixel(ir, ig, ib);
    return pixel;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    Rendering::Image image(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, 1);

    Ocean::generateSpectrum();
    Ocean::updateHeights(0.0);

    for (int j = image.getHeight() - 1; j >= 0; j--)
    {
        for (int i = 0; i < image.getWidth(); i++)
        {
            Utils::Color3 pixel_color(0.0, 0.0, 0.0);

            for (int k = 0; k < image.getSamplesPerPixel(); k++)
            {
                // double u = double(i + Utils::Randomdouble()) / (image.getWidth() - 1);
                // double v = double(j + Utils::Randomdouble()) / (image.getHeight() - 1);
                
                // Binary
                // double grey = (Ocean::heights[j * image.getWidth() + i] + 1.0) / 2.0;

                // Grayscale
                double grey = (Ocean::heights[j * image.getWidth() + i] - Ocean::minValue) / (Ocean::maxValue - Ocean::minValue);

                pixel_color += Utils::Color3(grey, grey, grey);
            }

            Rendering::Pixel pixel = processImageColor(pixel_color, image.getSamplesPerPixel());
            image.setPixel(i, j, pixel);
        }
    }

    image.savePPM("image.ppm");

    delete[] Ocean::spectrumFreq;
    delete[] Ocean::spectrumReel;
    delete[] Ocean::heights;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds." << std::endl;

    return EXIT_SUCCESS;
}