#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// Define screen dimensions
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

void renderImage(SDL_Renderer *renderer, SDL_Texture *sprite) {
  SDL_Rect sprite_rect;
  SDL_QueryTexture(sprite, NULL, NULL, &sprite_rect.w, &sprite_rect.h);
  sprite_rect.w = 150;
  sprite_rect.h = 150;
  sprite_rect.x = 0;
  sprite_rect.y = (SCREEN_HEIGHT - sprite_rect.h) / 2;
  SDL_RenderCopyEx(renderer, sprite, NULL, &sprite_rect, 270, NULL,
                   SDL_FLIP_NONE);
}

void renderText(SDL_Renderer *renderer, SDL_Texture *textTexture) {
  SDL_Rect textRect;
  SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
  textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
  textRect.y = (SCREEN_HEIGHT - textRect.h) / 2;
  SDL_RenderCopyEx(renderer, textTexture, NULL, &textRect, 270, NULL,
                   SDL_FLIP_NONE);
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  SDL_Window *window =
      SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Load image
  SDL_Surface *imgSurface = IMG_Load("image.png");
  SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, imgSurface);
  SDL_FreeSurface(imgSurface);

  // Load font and render text
  TTF_Font *font = TTF_OpenFont("font.ttf", 24);
  SDL_Color color = {0, 0, 0, 255};
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Center Text", color);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    renderImage(renderer, sprite);
    renderText(renderer, textTexture);

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(textTexture);
  SDL_DestroyTexture(sprite);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
