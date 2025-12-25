#include <SDL.h>
#include <SDL_image.h>
// Define screen dimensions
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

int running = 1;
int angle = 0;
int show = 0;

void renderImage(SDL_Renderer *renderer, SDL_Texture *sprite, int angle) {
  SDL_Rect sprite_rect;
  SDL_QueryTexture(sprite, NULL, NULL, &sprite_rect.w, &sprite_rect.h);
  sprite_rect.w = 150;
  sprite_rect.h = 150;
  sprite_rect.x = 0;
  sprite_rect.y = (SCREEN_HEIGHT - sprite_rect.h) / 2;
  SDL_RenderCopyEx(renderer, sprite, NULL, &sprite_rect, angle, NULL,
                   SDL_FLIP_NONE);
}

void handleInput(SDL_Event event) {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      // End the loop if the programs is being closed
      running = 0;
      break;
    case SDL_CONTROLLERDEVICEADDED:
      // Connect a controller when it is connected
      SDL_GameControllerOpen(event.cdevice.which);
      break;
    case SDL_CONTROLLERBUTTONDOWN:
      if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
        // Close the program if start is pressed
        running = 0;
      }

      if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
        // L button pressed
        angle -= 90;
      }

      if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
        // R button pressed
        angle += 90;
      }

      if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
        // Close the program if start is pressed

        if (show == 0) {
          show = 1;
        } else {
          show = 0;
        }
      }
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
  IMG_Init(IMG_INIT_PNG);

  SDL_Window *window =
      SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Load image
  SDL_Surface *imgSurface = IMG_Load("assets/image.png");
  SDL_Texture *sprite1 = SDL_CreateTextureFromSurface(renderer, imgSurface);
  SDL_FreeSurface(imgSurface);

  SDL_Event event;
  while (running) {
    handleInput(event);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if (show == 0) {
      renderImage(renderer, sprite1, angle);
    }

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(sprite1);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
