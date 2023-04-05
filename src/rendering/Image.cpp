#include "Image.h"

namespace Rendering
{
    Image::Image(int width, int height, int samples_per_pixel)
        : m_width(width), m_height(height), m_samples_per_pixel(samples_per_pixel), m_pixels(width * height)
    {}

    Pixel Image::getPixel(int x, int y) const
    {
        return m_pixels[y * m_width + x];
    }

    void Image::setPixel(int x, int y, const Pixel& pixel)
    {
        m_pixels[y * m_width + x] = pixel;
    }

    void Image::savePPM(const std::string& path, bool binary_output) const
    {
        if (binary_output)
        {
            std::ofstream file(path, std::ios::out | std::ios::binary);
            if (!file.is_open())
            {
                std::cerr << "Error: Could not open file " << path << std::endl;
                exit(EXIT_FAILURE);
            }

            file << "P6" << std::endl;
            file << m_width << " " << m_height << std::endl;
            file << "255" << std::endl;

            for (int y = m_height - 1; y >= 0; y--)
            {
                for (int x = 0; x < m_width; x++)
                {
                    Pixel pixel = getPixel(x, y);
                    file << static_cast<unsigned char>(pixel.r) << static_cast<unsigned char>(pixel.g) << static_cast<unsigned char>(pixel.b);
                }
            }

            file.close();
        }
        else
        {
            std::ofstream file;
            file.open(path);
            if (!file.is_open())
            {
                std::cerr << "Error: Could not open file " << path << std::endl;
                exit(EXIT_FAILURE);
            }

            file << "P3" << std::endl;
            file << m_width << " " << m_height << std::endl;
            file << "255" << std::endl;

            for (int y = m_height - 1; y >= 0; y--)
            {
                for (int x = 0; x < m_width; x++)
                {
                    Pixel pixel = getPixel(x, y);
                    file << pixel.r << " " << pixel.g << " " << pixel.b << std::endl;
                }
            }

            file.close();
        }
    }
};