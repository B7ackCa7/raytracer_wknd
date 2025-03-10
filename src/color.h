#ifndef COLOR_H
#define COLOR_H

/* defintions to write a single pixel color out to the standard output stream
 *
 *
 * */

#include "interval.h"
#include "vec3.h"


// type alias
using color = vec3;

/* add gamma correcton :: using gamma 2 transformation
*  to go from linear space to gamma space take the exponent of 1/gamma (square root)
* 
**/
inline double linear_to_gamma(double linear_component) {
  if (linear_component > 0)
    return sqrt(linear_component);

  return 0;
}

/* Parameters : out ~ ( like std::cout or a file stream )
 *            : pixel_color ~ a color object ( a vec3 )
 * */
void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // apply a linear to gamma transformatio for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // translate the [0,1] component values to the byte range [0,255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif
