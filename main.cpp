#include <iostream>

#include <chrono>
#include <algorithm>
#include <limits>

#include "CommandLineOptions.h"
#include "Image.h"
#include "Ray.h"
#include "Scene.h"
#include "Hit.h"
#include "PhillipsSpectrum.h"

Utils::Color3 envColor(const Utils::Vector3& direction)
{
    double t = (std::sqrt(std::abs(direction.getY())));
    Utils::Color3 Sky = (1.0 - t) * Utils::Color3(1.0, 0.5, 0.0) + t * Utils::Color3(0.3, 0.65, 1.0);
    Utils::Color3 SunColor = Utils::Color3(1.0, 1.0, 0.7);
    Utils::Vector3 sunDirection = Utils::normalize(Utils::Vector3(2.0, 0.0, -10.0));
    double SunIntensity = std::pow(std::max(-Utils::dot(direction, sunDirection), 0.0), 1500.0);
    Utils::Color3 Sun = SunIntensity * SunColor;
    return Sky + Sun;
}

Utils::Color3 ray_cast(Rendering::Ray& ray, const Rendering::Scene& world)
{
    ray.setDirection(Utils::normalize(ray.getDirection()));

    Utils::Color3 pixel_color = envColor(ray.getDirection()) * ray.getIntensity();
    
    Rendering::Intersection_record record;

    bool hit_anything = worldIntersects(ray, world, record, std::numeric_limits<double>::infinity());

    if (hit_anything)
    {   
        Utils::Point3 n_origin = record.point + record.normal * 0.002;
        Utils::Vector3 n_direction = Utils::reflect(Utils::normalize(ray.getDirection()), record.normal);

        double fresnel = std::abs(Utils::dot(Utils::normalize(ray.getDirection()), record.normal));
        Utils::Color3 n_intensity = ray.getIntensity() * (1.0 - 0.9 * fresnel);

        //double kr = Utils::fresnel(Utils::normalize(ray.getDirection()), record.normal, 1.0, 1.33);
        //Utils::Color3 n_intensity = ray.getIntensity() * kr;

        //Utils::Color3 n_intensity = ray.getIntensity();

        Rendering::Ray n_ray(n_origin, n_direction, n_intensity);
        
        return ray_cast(n_ray, world);
        //return pixel_color + ray_cast(n_ray, world);
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

void render(Rendering::Image& image, const Rendering::Scene& world)
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
                pixel_color += ray_cast(ray, world);
            }

            Rendering::Pixel pixel = processImageColor(pixel_color, image.getSamplesPerPixel());
            image.setPixel(i, j, pixel);
        }
    }
}

int main(int argc, char** argv)
{
    Utils::CommandLineOptions options;
    Utils::CommandLineOptions::Status status = options.parse(argc, argv);

    if (status == Utils::CommandLineOptions::Status::HELP) { return EXIT_SUCCESS; }
    if (status == Utils::CommandLineOptions::Status::VERSION) { return EXIT_SUCCESS; }

    auto start = std::chrono::high_resolution_clock::now();

    Rendering::Image image(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, 1);

    std::vector<std::shared_ptr<Rendering::Object>> objects;
    Rendering::Scene world(objects);
    //Rendering::Sphere sphere(Utils::Point3(0.0, 0.2, 0.8), 0.2);
    //world.addObject(std::make_shared<Rendering::Sphere>(sphere));

    Rendering::Water water;
    world.addObject(std::make_shared<Rendering::Water>(water));

    Ocean::generateSpectrum();

    for (int t = 0; t < Settings::NUM_FRAMES; t++)
    {
        std::cout << "Frame " << t << std::endl;

        Ocean::updateHeights(t * 0.04);

        render(image, world);

        std::string path = "output/frame_" + std::to_string(t) + ".ppm";
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