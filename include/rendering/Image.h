#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Rendering
{

    class Pixel
    {
    public:
        Pixel() : r(0), g(0), b(0) {}
        Pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

        int r;
        int g;
        int b;
    };

    class Image
    {
    public:
        Image(int width, int height, int samples_per_pixel);

        inline int getWidth() const { return m_width; }
        inline int getHeight() const { return m_height; }
        inline int getSamplesPerPixel() const { return m_samples_per_pixel; }

        Pixel getPixel(int x, int y) const;

        void setPixel(int x, int y, const Pixel& pixel);
        void savePPM(const std::string& path) const;

    private:
        int m_width;
        int m_height;
        int m_samples_per_pixel;
        std::vector<Pixel> m_pixels;
    };
}