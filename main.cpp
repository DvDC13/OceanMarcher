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

    int ir = static_cast<int>(256 * std::clamp(r, 0.0, 0.999));
    int ig = static_cast<int>(256 * std::clamp(g, 0.0, 0.999));
    int ib = static_cast<int>(256 * std::clamp(b, 0.0, 0.999));

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
                
                double grey = 0.05 * Ocean::heights[j * image.getWidth() + i] + 0.5;
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