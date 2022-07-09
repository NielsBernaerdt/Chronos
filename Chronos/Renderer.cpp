#include "ChronosPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);
	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, Rect srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	if (srcRect.width == 0 || srcRect.height == 0) //Invalid sourceRect
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}
	else
	{
		SDL_Rect src{};
		src.x = static_cast<int>(srcRect.left);
		src.y = static_cast<int>(srcRect.bottom);
		src.w = static_cast<int>(srcRect.width);
		src.h = static_cast<int>(srcRect.height);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	}
}
void Renderer::RenderTextureRotated(const Texture2D& texture, float x, float y, double angle, Rect srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	if (srcRect.width == 0 || srcRect.height == 0) //Invalid sourceRect
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, NULL, SDL_FLIP_NONE);
	}
	else
	{
		SDL_Rect src{};
		src.x = static_cast<int>(srcRect.left);
		src.y = static_cast<int>(srcRect.bottom);
		src.w = static_cast<int>(srcRect.width);
		src.h = static_cast<int>(srcRect.height);
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, angle, NULL, SDL_FLIP_NONE);
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, Rect srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	if (srcRect.width == 0 || srcRect.height == 0) //Invalid sourceRect
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}
	else
	{
		SDL_Rect src{};
		src.x = static_cast<int>(srcRect.left);
		src.y = static_cast<int>(srcRect.bottom);
		src.w = static_cast<int>(srcRect.width);
		src.h = static_cast<int>(srcRect.height);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	}
}

void Renderer::RenderTextureRotated(const Texture2D& texture, float x, float y, float width, float height, double angle, Rect srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	if (srcRect.width == 0 || srcRect.height == 0) //Invalid sourceRect
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, NULL, SDL_FLIP_NONE);
	}
	else
	{
		SDL_Rect src{};
		src.x = static_cast<int>(srcRect.left);
		src.y = static_cast<int>(srcRect.bottom);
		src.w = static_cast<int>(srcRect.width);
		src.h = static_cast<int>(srcRect.height);
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, angle, NULL, SDL_FLIP_NONE);
	}
}