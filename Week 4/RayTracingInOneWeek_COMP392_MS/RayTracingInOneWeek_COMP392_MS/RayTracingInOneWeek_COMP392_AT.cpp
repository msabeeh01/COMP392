#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

#include "triangle.h"
///
/// Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html
/// 
typedef color (*pfn_ray_color)(const ray&);

typedef color (*pfn)(const ray& r);

int f(int a) {
    return a * 2;
}

//Challenge: 
// create a pointer to a function similar to f above:
//  (accepts and int and returns an int)
//f: int -> int


/// <summary>
/// First version of ray_color
/// Returns the color of the pixel on the screen corresponding to the ray
/// </summary>
color ray_color(const ray& r) {
    return color(0, 0, 0);
}
color ray_color_listing10(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    auto white = color(1.0, 1.0, 1.0);
    auto bluish = color(0.5, 0.7, 1.0);

    return (1.0 - a) * white + a * bluish;
}
//
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - a * c;
    return (discriminant >= 0);
}

color ray_color_listing11(const ray& r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(1, 0, 0); //red color

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    auto white = color(1.0, 1.0, 0.0); //yellow
    auto bluish = color(0.2, 0.5, 1.0); //bluish2
    return (1.0 - a) * white + a * bluish; //lerp between yellow and bluish2
}

double hit_sphere_listing12(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant)) / a;
    }
}

color ray_color_listing12(const ray& r) {
    auto t = hit_sphere_listing12(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

bool hit_triangle(const point3& v0, const point3& v1, const point3& v2, const ray& r) {
    triangle tri(v0, v1, v2);
    hit_record rec{};
    return tri.hit(r, 0.0, 10.0, rec);


}
color ray_color_triangle(const ray& r) {
    if (hit_triangle(point3(-1, 0, -2), point3(1, 0, -2), point3(0, 2, -2), r)) {
        return color(0, 1, 0);

    }

    //return ray_color_gradient(r);
    //return ray_color_sphere_double(r);
    return ray_color_listing12(r);
}

/// <summary>
/// Creating the first image
/// </summary>
void Listing1() {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

}
/// <summary>
/// Listing2: Same as Listing1 but with progress reporting capability
/// </summary>
void Listing2() {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\rDone.                 \n";


}
/// <summary>
/// Final Code for the First PPM Image
/// </summary>
void Listing6() {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = color(double(i) / (image_width - 1),
                double(j) / (image_height - 1), 0);
            write_color(std::cout, pixel_color);


        }
    }

    std::clog << "\rDone.                 \n";


}
/// <summary>
/// Creating Scene Rays
/// </summary>
void Listing9() {
    // Image
    auto aspect_ratio = 16.0 / 9.0; //W/H => H=W/AR
    int image_width = 400;
    //Calculate image_height
    int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera 
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);
    //calculate Vu and Vv 
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    //calculate du and dv
    auto pixel_delta_u = viewport_u / image_width;
    //auto dx = pixel_delta_u.x();
    auto pixel_delta_v = viewport_v / image_height;
    //calculate P(0,0) => location of top left pixel (pixels are in the center)
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u + viewport_v) / 2.0;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) / 2.0;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            //auto pixel_color=color(double(i) / (image_width - 1), double(j) / (image_height - 1),0);
            auto pixel_center_loc = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center_loc - camera_center;
            ray r(camera_center, ray_direction);

            //auto pixel_color = ray_color(r);
            //auto pixel_color = ray_color_listing10(r);
            //auto pixel_color = ray_color_listing11(r);
            auto pixel_color = ray_color_listing12(r);
            write_color(std::cout, pixel_color);


        }
    }

    std::clog << "\rDone.                 \n";


}
void Listing9_HOF(pfn_ray_color f) {
    // Image
    auto aspect_ratio = 16.0 / 9.0; //W/H => H=W/AR
    int image_width = 400;
    //Calculate image_height
    int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera 
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);
    //calculate Vu and Vv 
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    //calculate du and dv
    auto pixel_delta_u = viewport_u / image_width;
    //auto dx = pixel_delta_u.x();
    auto pixel_delta_v = viewport_v / image_height;
    //calculate P(0,0) => location of top left pixel (pixels are in the center)
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u + viewport_v) / 2.0;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) / 2.0;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            //auto pixel_color=color(double(i) / (image_width - 1), double(j) / (image_height - 1),0);
            auto pixel_center_loc = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center_loc - camera_center;
            ray r(camera_center, ray_direction);

            //auto pixel_color = ray_color(r);
            //auto pixel_color = ray_color_listing10(r);
            //auto pixel_color = ray_color_listing11(r);
            //auto pixel_color = ray_color_listing12(r);
            auto pixel_color = f(r);

            write_color(std::cout, pixel_color);


        }
    }

    std::clog << "\rDone.                 \n";


}

int main() {
    //Listing1();
    //Listing2();
    //Listing6();
    //Listing9();
    
    //pfn_ray_color frc= ray_color;
    //pfn_ray_color frcl10 = ray_color_listing10;
    //pfn_ray_color frcl11 = ray_color_listing11;
    //pfn_ray_color frcl12 = ray_color_listing12;
    pfn_ray_color frct = ray_color_triangle;
    //Listing9_HOF(frc);
    //Listing9_HOF(frcl10);
    //Listing9_HOF(frcl11);
    //Listing9_HOF(frcl12);
    Listing9_HOF(frct);
}