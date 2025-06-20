
#include "vec3.h"
#include <color.h>



class Camera {

public:
	int viewPortWidth ; 
	int viewPortHeight;
	vec3 position;
	vec3 lower_left_corner;
	vec3 upper_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 camera_pos;
		Camera(float viewport_width = 4.0f, float viewport_height = 2.0f, vec3 startPos = vec3(0,0,0)) {
		viewPortWidth = static_cast<int>(viewport_width);
		viewPortHeight = static_cast<int>(viewport_height);
		position = startPos; 
		lower_left_corner = position - vec3(viewport_width / 2.0f, viewport_height / 2.0f, 1.0f);
		upper_left_corner = position + vec3(viewport_width / 2.0f, viewport_height / 2.0f, -1.0f);
		horizontal = vec3(viewport_width, 0.0f, 0.0f);
		vertical = vec3(0.0f, viewport_height, 0.0f);
		camera_pos = position; // Set the camera position
	}

 




};