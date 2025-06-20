
#pragma once
#include <cmath>
#include <iostream>
#include <utility.h>

class vec3 {
public:
    float x, y, z;
    vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }    static vec3 random()  {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }

    static vec3 randomInRange(float min, float max) {
        return vec3(randomDouble(min,max) , randomDouble(min,max), randomDouble(min,max));
    }

     static vec3 randomUnitvector()
    {
        while( true)
        {
            auto rand = vec3::randomInRange(-1, 1);
            auto squaredLength = rand.x * rand.x + rand.y * rand.y + rand.z * rand.z;
           if(squaredLength <= 1 &&  squaredLength > 1e-160)
           {
            return rand/ std::sqrt(squaredLength); // Normalize the vector
           }
        }
    }

     static vec3 randomInHemisphere(const vec3& normal) {
        vec3 inUnitSphere = randomUnitvector();
        if (inUnitSphere.dot(normal) < 0.0f) {
            inUnitSphere = -inUnitSphere; // Ensure the vector is in the same hemisphere as the normal
        }
        return inUnitSphere;
    }



	vec3& operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }
	vec3& operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}   

    vec3 operator*(const vec3& other) const {
        return vec3(x * other.x, y * other.y, z * other.z);
    }
	vec3& operator*=(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}


    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

	vec3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

    vec3 operator/(float scalar) const {
        if (scalar != 0.0f) {
            return vec3(x / scalar, y / scalar, z / scalar);
        }
        return vec3(0.0f, 0.0f, 0.0f); // Avoid division by zero
    }
	vec3& operator/=(float scalar) {
		if (scalar != 0.0f) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}
		return *this; // Avoid division by zero
	}
            


    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }
    vec3 cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    vec3 normalize() const {
        float len = length();
        if (len > 0.0f) {
            return vec3(x / len, y / len, z / len);
        }
        return vec3(0.0f, 0.0f, 0.0f);
    }  
    
    
   

};