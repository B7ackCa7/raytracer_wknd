/* Camera class has two important tasks 
 * 1. Construct and dispatch rays into the world.
 * 2. Use the results of these rays to construct the rendered image.
 *
 *
 * */

#ifndef CAMERA_H
#define CAMERA_H

#include "ca7utils.h"

#include "impactable.h"

class camera {
  public:
    double aspect_ratio      = 1.0;  // Ratio of image width over height
    int    image_width       = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 10; // Count of random samples per pixels
    int    max_depth         = 10; // Maximum number of ray bounces allowed into scene


    void render(const impactable& world) {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                  ray r = get_ray(i,j);
                  pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int image_height;           // Rendered image height
    double pixel_samples_scale; // Color scale factor for sum of pixel samples 
    point3 center;              // Camera center
    point3 pixel00_loc;         // Location of pixel 0, 0
    vec3   pixel_delta_u;       // Offset to pixel to the right
    vec3   pixel_delta_v;       // Offset to pixel below

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
      // Construct a camera ray originating from the origin and directed at
      // random sampled point around location i, j

      auto offset = sample_square();
      auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_delta_u)
                        + ((j + offset.y()) * pixel_delta_v);

      auto ray_origin = center;
      auto ray_direction = pixel_sample - ray_origin;

      return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
      // Returns the vector to a random point in the [-.5, -.5] to [+.5, +.5]
      return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray& r, int depth, const impactable& world) const {
      // no light is gathered, if ray bounce limit is exceeded
        if (depth <= 0)
            return color(0, 0, 0);
      
        hit_record rec;

        /* check for whether or not the ray hits a impactable object
         *  calculates the direction of the ray and generates a random point
         * that measures if it is on the right side of the hemisphere or inverts if not
         **/ 
        if (world.hit(r, interval(0.001, infinity), rec)) {
          vec3 direction = rec.normal + random_unit_vector();
          return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif
