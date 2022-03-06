#pragma once

#include <cmath>
#include <iostream>


using std::sqrt;
/// <summary>
/// A simple class defining a 3d vector.
/// The vector consists of a fixed array of 3 integers, representing x,y,z coordinates respectively.
/// The class does not provide range-checking.
/// </summary>
class vec3 {
public:
    vec3() : elem{ 0,0,0 } {}
    vec3(double e0, double e1, double e2) : elem{ e0, e1, e2 } {}

    double x() const { return elem[0]; }
    double y() const { return elem[1]; }
    double z() const { return elem[2]; }

    vec3 operator-() const { return vec3(-elem[0], -elem[1], -elem[2]); }
    double operator[](int i) const { return elem[i]; }// for const vectors
    double& operator[](int i) { return elem[i]; } //non-const vectors

    vec3& operator+=(const vec3& v) {
        elem[0] += v.elem[0];
        elem[1] += v.elem[1];
        elem[2] += v.elem[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        elem[0] *= t;
        elem[1] *= t;
        elem[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length_squared() const {
        return elem[0] * elem[0] + elem[1] * elem[1] + elem[2] * elem[2];
    }

    double length() const {
        return sqrt(length_squared());
    }

    inline static vec3 random() { //generates a vector with random elements
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) { //generates a random vector whose elements are bounded between min and max
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    // Returns 0 if the vector is near zero in all components
    bool near_zero() const
    {
        const auto s = 1e-8;
        return (fabs(elem[0]) < s) && (fabs(elem[1]) < s) && (fabs(elem[2]) < s);
    }

public:
    double elem[3];
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color


// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.elem[0] << ' ' << v.elem[1] << ' ' << v.elem[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.elem[0] + v.elem[0], u.elem[1] + v.elem[1], u.elem[2] + v.elem[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.elem[0] - v.elem[0], u.elem[1] - v.elem[1], u.elem[2] - v.elem[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.elem[0] * v.elem[0], u.elem[1] * v.elem[1], u.elem[2] * v.elem[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.elem[0], t * v.elem[1], t * v.elem[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.elem [0] * v.elem[0]
        + u.elem[1] * v.elem[1]
        + u.elem[2] * v.elem[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.elem[1] * v.elem[2] - u.elem[2] * v.elem[1],
        u.elem[2] * v.elem[0] - u.elem[0] * v.elem[2],
        u.elem[0] * v.elem[1] - u.elem[1] * v.elem[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

// Function to return a refracted ray as a sum of parallel and perp components to the surface normal
vec3 refract(const vec3& uv, const vec3& n, double e_in_over_e_out)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = e_in_over_e_out * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;

}
