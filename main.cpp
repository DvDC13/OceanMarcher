#include <iostream>

#include <chrono>
#include <algorithm>
#include <limits>

#include "CommandLineOptions.h"
#include "Image.h"
#include "Ray.h"
#include "Scene.h"
#include "Texture.h"
#include "PhillipsSpectrum.h"

const double precision = 255.0;

bool intersects(const Rendering::Ray& ray, const auto& object, Rendering::Intersection_record& record, double closest_so_far)
{
    double distanceFromOrigin = 0.0;
    for (double p = 0; p < precision; p++)
    {
        Utils::Point3 hitPoint = ray.getPointAt(distanceFromOrigin);
        double distanceFromObject = object->getDistance(hitPoint);

        if (distanceFromObject < 0.001)
        {
            if (distanceFromOrigin >= closest_so_far) return false;

            record.point = hitPoint;
            record.t = distanceFromOrigin;
            object->getNormalAt(hitPoint, ray, record);

            return true;
        }

        if (distanceFromOrigin > 1000) return false;

        distanceFromOrigin += distanceFromObject;
    }

    return false;
}

Utils::Color3 ray_cast(const Rendering::Ray& ray, const Rendering::Scene& world, int limit)
{
    // Grayscale
    // double grey = (Ocean::heights[j * image.getWidth() + i] - Ocean::minValue) / (Ocean::maxValue - Ocean::minValue);
    // pixel_color += Utils::Color3(grey, grey, grey);

    if (limit <= 0) { return Utils::Color3(0.0, 0.0, 0.0); }

    Rendering::Intersection_record record;

    bool hit_anything = false;
    double closest_so_far = std::numeric_limits<double>::max();
    Rendering::Intersection_record tmp_record;

    for (const auto& object : world.getObjects())
    {
        if (intersects(ray, object, record, closest_so_far))
        {
            hit_anything = true;
            closest_so_far = record.t;
            tmp_record = record;
        }
    }

    if (hit_anything)
    {
        return 0.5 * Utils::Color3(tmp_record.normal.getX() + 1, tmp_record.normal.getY() + 1, tmp_record.normal.getZ() + 1);
    }
    else
    {
        Utils::Vector3 unit_direction = Utils::normalize(ray.getDirection());
        double t = (std::sqrt(unit_direction.getY()));
        Utils::Color3 Sky = (1.0 - t) * Utils::Color3(1.0, 0.5, 0.0) + t * Utils::Color3(0.4, 0.75, 1.0);
        
        Utils::Color3 SunColor = Utils::Color3(1.0, 1.0, 0.7);
        Utils::Vector3 sunDirection = Utils::normalize(Utils::Vector3(2.0, 0.0, 10.0));
        double SunIntensity = std::pow(Utils::dot(unit_direction, sunDirection), 250.0);
        Utils::Color3 Sun = SunIntensity * SunColor;
        return Sky + Sun;
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
                pixel_color += ray_cast(ray, world, 1);
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

    auto materialUniform = std::make_shared<Rendering::UniformTexture>(Utils::Color3(0.5, 0.5, 0.5), 0.5, 0.5);
    auto materialMirror = std::make_shared<Rendering::MirrorTexture>(Utils::Color3(0.5, 0.5, 0.5));
    //Rendering::Sphere sphere(Utils::Point3(0.0, 0.0, 0.0), 0.5);
    //world.addObject(std::make_shared<Rendering::Sphere>(sphere));

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