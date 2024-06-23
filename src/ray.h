#ifndef RAY_H
#define RAY_H


#include "vec3.h"


class ray {
public:
    ray() {} // initalizes an empty ray object

    // initalizes a ray with a given origin point and direction vector 
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    // accessor methods
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }
    
    /* Computes the position along the ray at parameter t 
     * the `t` parameter is a scalar that moves the point along the direction 
     * of the ray starting from the origin 
     * */
    point3 at(double t) const {
        return orig + t*dir;
    }

// data members
private:
    point3 orig; // origin point of the ray
    vec3 dir; // direction vector of the ray

};


#endif
