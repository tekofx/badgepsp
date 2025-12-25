#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// Define screen dimensions
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

  // Enable png support for SDL2_image
  IMG_Init(IMG_INIT_PNG);

  // Enable ttf support
  TTF_Init();

  SDL_Window *window =
      SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Load the texture
  SDL_Surface *pixels = IMG_Load("image.png");
  SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, pixels);
  SDL_FreeSurface(pixels);

  // Load the ttf
  TTF_Font *font = TTF_OpenFont("font.ttf", 24); // Load font
  SDL_Color textColor = {0, 0, 0, 255};
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font, "Center Text", textColor);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  // Store the dimensions of the sprite
  SDL_Rect sprite_rect;
  SDL_QueryTexture(sprite, NULL, NULL, &sprite_rect.w, &sprite_rect.h);

  // Define size and position of sprite
  sprite_rect.w = 150; // new width
  sprite_rect.h = 150; // new height
  sprite_rect.x = 0;
  sprite_rect.y = (SCREEN_HEIGHT - sprite_rect.h) / 2;

  // Store the dimensions of the text
  SDL_Rect textRect;
  SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

  // Define position of the text
  textRect.x = (480 - textRect.w) / 2;
  textRect.y = (272 - textRect.h) / 2;

  int running = 1;
  SDL_Event event;
  while (running) {
    // Process input
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
        break;
      }
    }

    // Clear the screen
    SDL_RenderClear(renderer);

    // Draw sprite
    SDL_RenderCopyEx(renderer, sprite, NULL, &sprite_rect, 270, NULL,
                     SDL_FLIP_NONE);

    // Draw the text
    SDL_RenderCopyEx(renderer, textTexture, NULL, &textRect, 270, NULL,
                     SDL_FLIP_NONE);

    // Draw everything on a white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
