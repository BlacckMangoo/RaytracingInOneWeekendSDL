#pragma once
#include<interval.h>
#include <Hittable.h>


class Sphere : public Hittable{

  public:
	vec3 center; // Center of the sphere
	float radius; // Radius of the sphere
	Sphere(const vec3& center, float radius) : center(center), radius(radius) {}
	bool hit(const Ray& ray, Interval ray_t, hitRecord& rec) const override {
		vec3 oc = ray.origin - center;
		double a = ray.direction.dot(ray.direction);
		double b = 2.0 * oc.dot(ray.direction);
		double c = oc.dot(oc) - radius * radius;
		double discriminant = b * b - 4 * a * c;
		
		if (discriminant < 0) {
			return false; // No intersection
		}
		
		auto sqrtd = std::sqrt(discriminant);
		
		// Try the nearest root first
		auto root = (-b - sqrtd) / (2.0 * a);
		if (!ray_t.surrounds(root)) {
			// If nearest root is not in range, try the farther root
			root = (-b + sqrtd) / (2.0 * a);
			if (!ray_t.surrounds(root)) {
				return false; // No valid intersection in range
			}
		}
		
		rec.t = root;
		rec.pointOfIntersection = ray.pointAt(root);
		vec3 outward_normal = (rec.pointOfIntersection - center) / radius;
		
		// Determine if we're hitting the front face or back face
		bool front_face = ray.direction.dot(outward_normal) < 0;
		rec.normal = front_face ? outward_normal : -outward_normal;

		return true;
	}
};
