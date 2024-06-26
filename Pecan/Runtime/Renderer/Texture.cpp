#include "pcpch.h"

#include "Runtime/Core/Application.h"
#include "Runtime/Core/Assert.h"

#include "Runtime/Renderer/RenderCommand.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Renderer/Texture.h"

#include "SDL.h"
#include "SDL_image.h"

namespace Pecan
{
    int lvl1[20][25] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Texture2D::Texture2D(SDL_Renderer* renderer, const std::string& path)
    {
        m_Texture = RenderCommand::LoadTexture(renderer, path.c_str());
    }

    Ref<Texture2D> Texture2D::Create(SDL_Renderer* renderer, const std::string& path)
    {
        return CreateRef<Texture2D>(renderer, path);
    }

    void Texture2D::RenderCopy(SDL_Rect srcRect, SDL_Rect dstRect) const
    {
        RenderCommand::RenderCopy(Application::GetRenderer(), m_Texture, &srcRect, &dstRect);
    }

    TileMap2D::TileMap2D()
    {
        m_PlatformTex = RenderCommand::LoadTexture(Application::GetRenderer(), "../../assets/sprites/platforms.png");
        LoadMap(lvl1);

        m_SrcRect.x = m_SrcRect.y = 0;
        m_SrcRect.w = m_DstRect.w = 32;
        m_SrcRect.h = m_DstRect.h = 32;

        m_DstRect.x = m_DstRect.y = 0;
    }

    Ref<TileMap2D> TileMap2D::Create() { return CreateRef<TileMap2D>(); }

    void TileMap2D::LoadMap(int arr[20][25])
    {
        for (int row = 0; row < 20; ++row)
        {
            for (int col = 0; col < 25; ++col)
            {
                m_Map[row][col] = arr[row][col];
            }
        }
    }

    void TileMap2D::RenderCopy() { DrawMap(); }

    void TileMap2D::DrawMap()
    {
        int type = 0;
        for (int row = 0; row < 20; ++row)
        {
            for (int col = 0; col < 25; ++col)
            {
                type = m_Map[row][col];

                m_DstRect.x = col * 32;
                m_DstRect.y = row * 32;

                switch (type)
                {
                    case 0:
                        RenderCommand::RenderCopy(Application::GetRenderer(), m_PlatformTex, &m_SrcRect, &m_DstRect);
                        break;

                    default:
                        break;
                }
            }
        }
    }

} // namespace Pecan