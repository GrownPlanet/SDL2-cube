#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const int windowHeight = 448;
const int windowWidth = 800;

const int fov = 30;

struct Vector2
{
  float x, y;
};

struct Vector3
{
  float x, y, z;
};

struct Triangle
{
  Vector3 A, B, C;
};

Vector2 project(Vector3 point)
{
  float pScreenX = (fov * point.x / (point.z - fov)) + windowWidth / 2;
  float pScreenY = (fov * point.y / (point.z - fov)) + windowHeight / 2;
  return {pScreenX, pScreenY};
}

void drawTriangle(Triangle triangle, Vector3 camera, SDL_Renderer* renderer)
{
  Vector2 p_triangle1[3] = {
    {project({triangle.A.x + camera.x, triangle.A.y + camera.y, triangle.A.z + camera.z})},
    {project({triangle.B.x + camera.x, triangle.B.y + camera.y, triangle.B.z + camera.z})},
    {project({triangle.C.x + camera.x, triangle.C.y + camera.y, triangle.C.z + camera.z})}
  };

  SDL_SetRenderDrawColor(renderer, 0,0,0,255);
  SDL_RenderDrawLine(renderer, p_triangle1[0].x, p_triangle1[0].y, p_triangle1[1].x, p_triangle1[1].y);
  SDL_RenderDrawLine(renderer, p_triangle1[0].x, p_triangle1[0].y, p_triangle1[2].x, p_triangle1[2].y);
  SDL_RenderDrawLine(renderer, p_triangle1[1].x, p_triangle1[1].y, p_triangle1[2].x, p_triangle1[2].y);
}

int main(int argc, char* args[])
{
  SDL_Init(SDL_INIT_EVERYTHING);

  const int fps = 60;
  const int frameDelay = 1000 / fps;

  Uint32 frameStart;
  int frameTime;

  SDL_Window* window = SDL_CreateWindow("3d test (this was not worth four days)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Event event;

  bool running = true;

  Vector3 camera = {x:windowWidth/2, y:windowHeight/2, z:0};

  vector<Triangle> triangles;

  Vector3 A = {x:100, y:100, z:100};
  Vector3 B = {x:700, y:100, z:100};
  Vector3 C = {x:700, y:348, z:100};
  Vector3 D = {x:100, y:348, z:100};
  Vector3 E = {x:100, y:100, z:200};
  Vector3 F = {x:700, y:100, z:200};
  Vector3 G = {x:700, y:348, z:200};
  Vector3 H = {x:100, y:348, z:200};

  triangles.push_back({A: A, B: B, C: C});
  triangles.push_back({A: E, B: H, C: G});
  triangles.push_back({A: E, B: A, C: D});
  triangles.push_back({A: C, B: G, C: F});
  triangles.push_back({A: E, B: F, C: B});
  triangles.push_back({A: H, B: C, C: D});

  while (running)
  {
    frameStart = SDL_GetTicks();
  	while (SDL_PollEvent(&event))
  	{
  		if (event.type == SDL_QUIT) // check if the window was closed
  		{
  			running = false; // closing the window
  		}
      if (event.type == SDL_KEYDOWN )
      {
        switch (event.key.keysym.sym){
          case SDLK_UP:
            camera.y -= 10;
            break;
          case SDLK_DOWN:
            camera.y += 10;
            break;
          case SDLK_LEFT:
            camera.x -= 10;
            break;
          case SDLK_RIGHT:
            camera.x += 10;
            break;
        }
      }
  	}

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer); // clearing the screan

    SDL_SetRenderDrawColor(renderer, 16, 143, 14, 255);
    SDL_Rect bottomHalf = {0, windowHeight/2 - camera.y/5, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &bottomHalf);

    for (Triangle t: triangles){
      drawTriangle(t, camera, renderer);
    }

    SDL_RenderPresent(renderer); // rendering the current screen

    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime)
    	SDL_Delay(frameDelay - frameTime);
  }

  return 0;
}
