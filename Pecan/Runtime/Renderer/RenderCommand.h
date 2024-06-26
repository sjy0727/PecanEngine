#pragma once

#include "SDL.h"
#include "SDL_image.h"

namespace Pecan
{

    class RenderCommand
    {
    public:
        inline static void SetClearColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        {
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
        }

        inline static void Clear(SDL_Renderer* renderer) { SDL_RenderClear(renderer); }

        inline static void
        RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect)
        {
            SDL_RenderCopy(renderer, texture, srcRect, dstRect);
        }

        inline static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* fileName)
        {
            SDL_Surface* tempSurface = IMG_Load(fileName);
            SDL_Texture* tex         = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_FreeSurface(tempSurface);

            return tex;
        }
    };

} // namespace Pecan