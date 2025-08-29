#include <SDL3/SDL.h>
#include <utility.h>
#include <vector>
#include <sphere.h>
#include <hittable.h>
#include <hittableList.h>
#include <camera.h>
#include <color.h>


constexpr int HEIGHT = 600;
constexpr int WIDTH = 1200;
constexpr int samplesPerPixel = 20; 


vec3 SampleSquare()  {
	return  vec3(randomDouble()-0.5, randomDouble() - 0.5, 0.0f); // between 
}

Ray getRay(int i, int j, Camera& camera) {
    vec3 offset = SampleSquare();
    float u = (i + offset.x) / (WIDTH - 1);
    float v = (HEIGHT - 1 - j + offset.y) / (HEIGHT - 1); // Flip Y coordinate for proper image orientation
    
    vec3 pixel_center = camera.lower_left_corner + camera.horizontal * u + camera.vertical * v;
    vec3 direction = pixel_center - camera.camera_pos;
    return Ray(camera.camera_pos, direction.normalize());
}





void renderScene(Camera& camera, HittableList& world, std::vector<uint32_t>& pixels) {
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            vec3 color(0.0f, 0.0f, 0.0f);

            for(int s = 0; s < samplesPerPixel; s++) {
                Ray ray = getRay(i, j, camera);
                color += ColorPixel(ray, world);
            }
            
            // Average the samples
            color /= static_cast<float>(samplesPerPixel);
            
            
            // Clamp to [0,1] range
            color.x = std::max(0.0f, std::min(1.0f, color.x));
            color.y = std::max(0.0f, std::min(1.0f, color.y));
            color.z = std::max(0.0f, std::min(1.0f, color.z));
            
            // Gamma correction 
            color.x ? color.x > 0  : std::sqrt(color.x) , 0.0f;
            color.y ? color.y > 0  : std::sqrt(color.y) , 0.0f;
            color.z ? color.z > 0  : std::sqrt(color.z) , 0.0f;
       
         
            // Convert to 8-bit color
            uint8_t r = static_cast<uint8_t>(color.x * 255.0f);
            uint8_t g = static_cast<uint8_t>(color.y * 255.0f);
            uint8_t b = static_cast<uint8_t>(color.z * 255.0f);
            
            pixels[j * WIDTH + i] = toARGB(r, g, b, 255);
        }
    }
}

int main() {
    Camera camera(2.0f, 1.0f, vec3(0.0f, 0.0f, 0.7f));
    HittableList world;
	world.add(make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
    world.add(make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f)); // Ground sphere

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("SDL Raytracer", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
     SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);


    std::vector<uint32_t> pixels(WIDTH * HEIGHT);

    // Camera movement setup
    vec3 forward, right, up;
    float speed = 0.15f;
    bool needsRerender = true;

    // Calculate initial direction vectors
    forward = (camera.lower_left_corner + camera.horizontal * 0.5f + camera.vertical * 0.5f - camera.camera_pos).normalize();
    right = forward.cross(vec3(0.0f, 1.0f, 0.0f)).normalize();
    up = right.cross(forward).normalize();

    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        // Handle keyboard input
        const bool* keys = SDL_GetKeyboardState(NULL);
        vec3 movement(0.0f, 0.0f, 0.0f);

        if (keys[SDL_SCANCODE_W]) movement = movement + forward;
        if (keys[SDL_SCANCODE_S]) movement = movement - forward;
        if (keys[SDL_SCANCODE_A]) movement = movement - right;
        if (keys[SDL_SCANCODE_D]) movement = movement + right;
        if (keys[SDL_SCANCODE_SPACE]) movement = movement + up;
        if (keys[SDL_SCANCODE_LSHIFT]) movement = movement - up;

        // Update camera position if movement occurred
        if (movement.length() > 0) {
            camera.camera_pos = camera.camera_pos + movement.normalize() * speed;
            camera.lower_left_corner = camera.camera_pos - vec3(camera.viewPortWidth / 2.0f, camera.viewPortHeight / 2.0f, 1.0f);

            // Recalculate direction vectors
            forward = (camera.lower_left_corner + camera.horizontal * 0.5f + camera.vertical * 0.5f - camera.camera_pos).normalize();
            right = forward.cross(vec3(0.0f, 1.0f, 0.0f)).normalize();
            up = right.cross(forward).normalize();

            needsRerender = true;
        }

        if (needsRerender) {
            renderScene(camera, world, pixels);
            SDL_UpdateTexture(texture, nullptr, pixels.data(), WIDTH * sizeof(uint32_t));
            needsRerender = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}