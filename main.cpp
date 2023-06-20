#include <iostream>

#include <chrono>
#include <algorithm>
#include <limits>

#include "Image.h"
#include "Ray.h"
#include "Scene.h"
#include "Hit.h"
#include "PhillipsSpectrum.h"

Utils::Color3 envColor(const Utils::Vector3& direction, double frame, double threshold)
{
    double t = (std::sqrt(std::abs(direction.getY())));

    Utils::Color3 SunColor = Utils::Color3(1.0, 1.0, 0.7);

    Utils::Color3 Sky = Utils::Color3(0.3, 0.65, 1.0);
    Utils::Color3 Sunset = (1.0 - t) * Utils::Color3(1.0, 0.5, 0.0) + t * Utils::Color3(0.3, 0.65, 1.0);

    double sunPeriod = -4.0 + frame * (Settings::maxSunP - Settings::minSunP) / Settings::NUM_FRAMES;

    Utils::Color3 HorizonColor = Utils::Color3(0.0, 0.0, 0.0);
    if (threshold >= frame)
    {
        double p = frame / threshold;
        HorizonColor = (1.0 - p) * Sky + p * Sunset;
    }
    else
    {
        double p = (frame - threshold) / (Settings::NUM_FRAMES - threshold);
        Utils::Color3 NightColor = Utils::Color3(0.0, 0.05, 0.22);
        HorizonColor = (1.0 - p) * Sunset + p * NightColor;
    }

    Utils::Vector3 sunDirection = Utils::normalize(Utils::Vector3(2.0, sunPeriod, -10.0));

    double SunIntensity = std::pow(std::max(-Utils::dot(direction, sunDirection), 0.0), 1500.0);
    Utils::Color3 Sun = SunIntensity * SunColor;
    return HorizonColor + Sun;
}

Utils::Color3 ray_cast(Rendering::Ray& ray, const Rendering::Scene& world, double frame, double threshold)
{
    ray.setDirection(Utils::normalize(ray.getDirection()));
    
    Rendering::Intersection_record record;

    bool hit_anything = worldIntersects(ray, world, record, std::numeric_limits<double>::infinity());

    Utils::Color3 pixel_color = envColor(ray.getDirection(), frame, threshold) * ray.getIntensity();

    if (hit_anything)
    {   
        Utils::Point3 n_origin = record.point + record.normal * 0.005;
        Utils::Vector3 n_direction = Utils::reflect(Utils::normalize(ray.getDirection()), record.normal);

        double kr = Utils::fresnel(Utils::normalize(ray.getDirection()), record.normal, 1.333);
        Utils::Color3 n_intensity = ray.getIntensity() * kr;

        Rendering::Ray n_ray(n_origin, n_direction, n_intensity);
        
        return ray_cast(n_ray, world, frame, threshold);
    }
    else
    {
        return pixel_color;
    }
}

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

void render(Rendering::Image& image, const Rendering::Scene& world, double frame, double threshold)
{
    for (int j = image.getHeight() - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image.getWidth(); i++)
        {
            Utils::Color3 pixel_color(0.0, 0.0, 0.0);

            for (int k = 0; k < image.getSamplesPerPixel(); k++)
            {
                double u = double(i + Utils::Randomdouble()) / (image.getWidth() - 1);
                double v = double(j + Utils::Randomdouble()) / (image.getHeight() - 1);

                Rendering::Ray ray = world.getCamera().getRay(u, v);
                pixel_color += ray_cast(ray, world, frame, threshold);
            }

            Rendering::Pixel pixel = processImageColor(pixel_color, image.getSamplesPerPixel());
            image.setPixel(i, j, pixel);
        }
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    Rendering::Image image(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, 1);

    std::vector<std::shared_ptr<Rendering::Object>> objects;
    Rendering::Scene world(objects);

    Rendering::Water water;
    world.addObject(std::make_shared<Rendering::Water>(water));

    Ocean::generateSpectrum();

    double threshold = 0.0;
    for (int frame = 0; frame < Settings::NUM_FRAMES; frame++)
    {
        double sunPeriod = -4.0 + frame * (Settings::maxSunP - Settings::minSunP) / Settings::NUM_FRAMES;
        if (sunPeriod >= 0.0)
        {
            threshold = frame;
            break;
        }
    }

    system("mkdir -p output");

    for (int frame = 0; frame < Settings::NUM_FRAMES; frame++)
    {
        std::cout << "Frame " << frame << std::endl;

        Ocean::updateHeights(frame * 0.01666667f);

        render(image, world, frame, threshold);

        std::string path = "output/frame_" + std::to_string(frame) + ".ppm";
        image.savePPM(path);
    }

    system("ffmpeg -y -i output/frame_%d.ppm output/ocean.mp4");

    delete[] Ocean::spectrumFreq;
    delete[] Ocean::spectrumReel;
    delete[] Ocean::heights;
    delete[] Ocean::pulsations;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds." << std::endl;

    return EXIT_SUCCESS;
}