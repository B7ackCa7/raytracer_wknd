#ifndef COLOR_H
#define COLOR_H

/* defintions to write a single pixel color out to the standard output stream
 *
 *
 * */

#include "vec3.h"


// type alias
using color = vec3;

/* Parameters : out ~ ( like std::cout or a file stream )
 *            : pixel_color ~ a color object ( a vec3 )
 * */
void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // translate the [0,1] component values to the byte range [0,255]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write out the pixel color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif
