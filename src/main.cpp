/* This program is a basic example of an RGB immage in the ppm format 
 * with a new line character at the end of each line
 * P3 means that the colors are in ASCII, there are 3 columns and 2 rows
 * 255 value for the max color RGB are written as triplets
 * */

#include "ca7utils.h"

#include "camera.h"
#include "impactable.h"
#include "impactable_list.h"
#include "sphere.h"


int main() {

    impactable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 800;

    cam.render(world);
    }
