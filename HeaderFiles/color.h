#pragma once

#include <sphere.h>
#include <utility.h>
#include <interval.h>


int32_t toARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return (static_cast<int32_t>(a) << 24) | (static_cast<int32_t>(r) << 16) |
		(static_cast<int32_t>(g) << 8) | static_cast<int32_t>(b);
}


vec3 ray_color(const Ray& ray, const Hittable& world, int depth);

vec3 ColorPixel(const Ray& ray, const Hittable& world) {
	return ray_color(ray, world, 4); // Start with max depth of 10
}

vec3 ray_color(const Ray& ray, const Hittable& world, int depth) {
	
	if (depth <= 0) {
		return vec3(0, 0, 0);
	}

	hitRecord rec;
	 if (world.hit(ray, Interval(0.001f, infinity), rec)) {
 	   vec3 direction =  rec.normal + vec3::randomUnitvector();
		
		Ray r(rec.pointOfIntersection, direction);

		return ray_color(r, world, depth - 1) * 0.5f;
	}
	
	// Background color (sky gradient)
	vec3 unit_direction = ray.direction.normalize();
	float t = 0.5f * (unit_direction.y + 1.0f);
	return vec3(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3(0.5f, 0.7f, 1.0f) * t;
}
	
