#pragma once

#include <string>

#include "Runtime/Core/Base.h"

#include "SDL.h"
#include "SDL_image.h"

namespace Pecan
{

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const      = 0;
        virtual uint32_t GetHeight() const     = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const          = 0;
        virtual bool operator==(const Texture& other) const = 0;

    protected:
        void* m_Texture;
    };

    class Texture2D
    {
    public:
        SDL_Texture* m_Texture;
        SDL_Rect     m_SrcRect;
        SDL_Rect     m_DstRect;

    public:
        Texture2D(SDL_Renderer* renderer, const std::string& path);

        static Ref<Texture2D> Create(SDL_Renderer* renderer, const std::string& path);
        void                  RenderCopy(SDL_Rect srcRect, SDL_Rect dstRect) const;
    };

    class TileMap2D
    {
    public:
        SDL_Rect     m_SrcRect;
        SDL_Rect     m_DstRect;
        SDL_Texture* m_PlatformTex;

        int m_Map[20][25];

    public:
        TileMap2D();
        ~TileMap2D() = default;

        static Ref<TileMap2D> Create();
        void                  RenderCopy();

        void LoadMap(int arr[20][25]);
        void DrawMap();
    };

} // namespace Pecan