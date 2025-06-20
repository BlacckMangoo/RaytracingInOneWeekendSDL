#pragma once 
#include <hittable.h>
#include <vector>
#include <memory>
#include <interval.h>
using std::shared_ptr;
using std::make_shared;


class HittableList : public Hittable {

public:
	std::vector<shared_ptr<Hittable>> hittableObjects;
	HittableList() {};
	HittableList(shared_ptr<Hittable> object) {
		hittableObjects.push_back(object);
	}

	void clear() {
		hittableObjects.clear();
	}
	void add(shared_ptr<Hittable> object) {
		hittableObjects.push_back(object);
	}

	bool hit(const Ray& ray, Interval ray_t, hitRecord& rec) const override {
		hitRecord tempRec;
		bool hitAnything = false;
		double closestSoFar = ray_t.max;
		for (const auto& object : hittableObjects) {
			if (object->hit(ray, Interval(ray_t.min,closestSoFar), tempRec)) {
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec; // Update the record with the closest hit
			}
		}
		return hitAnything;
	}

};


