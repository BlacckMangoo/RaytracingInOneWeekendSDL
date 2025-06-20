
#include <utility.h>
#include <interval.h>
#pragma once

struct hitRecord {
public :
	vec3 pointOfIntersection; 
	vec3 normal;
	double t; 

};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& ray, Interval interval_t, hitRecord& rec) const = 0;
};