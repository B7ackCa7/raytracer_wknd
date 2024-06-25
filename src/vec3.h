#ifndef VEC3_H
#define VEC3_H


class vec3 {

public:
    // data members
    double e[3]; // Array to store the coordinates x, y, z

    
    // constructors
    vec3() : e{0,0,0} {} // default constructor initializes to (0, 0, 0)
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // constructor to set specifix values

    double x() const { return e[0]; } // returns x coordinate
    double y() const { return e[1]; } // returns y coordinate
    double z() const { return e[2]; } // returns z coordinate
    
    // Operator overloading
    // unary minus operator
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    
    // subscript operator for reading 
    double operator[] (int i) const { return e[i]; }
    
    // subscript operator for writing 
    double& operator[] (int i) { return e[i]; }

    // compund assignmennt operators
    vec3&operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3&operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3&operator/=(double t) {
        return *this /= 1/t;
    }

    // length-related functions
    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random() {
      return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
      return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }


};

// point3 is just an alias for vec3, a point in 3D space
using point3 = vec3;


// Vector Utility Functions

// output stream operator
inline std::ostream& operator<< (std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// addition operator
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// subtraction operator
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// component-wise multiplication operator 
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// scalar multiplication (left and right multiplication)
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}


inline vec3 operator*(const vec3& v, double t) {
    return t * v; // delegates to the scalar multiplication above
}

// scalar division 
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// dot product of two vectors 
inline double dot(const vec3& u, const vec3& v) {
     return u.e[0] * v.e[0]
          + u.e[1] * v.e[1]
          + u.e[2] * v.e[2];
}

// cross product of two vectors
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// a vector with length 1 in the direction of the given vector
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

// create random points in a unit sphere and returns the accepted point [-1, 1  ]
inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() < 1)
        return p;
  }
}

inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
   return -on_unit_sphere; // dot product is negative, then we need to invert the vector
}

#endif
