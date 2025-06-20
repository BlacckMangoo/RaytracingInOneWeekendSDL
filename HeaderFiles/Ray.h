
#pragma once
#include <vec3.h>
class Ray{
public:
    vec3 origin;
    vec3 direction;

    Ray(const vec3& origin, const vec3& direction) : origin(origin), direction(direction) {}

    vec3 pointAt(float t) const {
        return origin + direction * t;
    }
};