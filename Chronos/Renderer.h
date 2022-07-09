#pragma once
#include "Rect.h"
#include "Singleton.h"

class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_clearColor{};
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y, Rect srcRect = { 0,0,0,0 }) const;
	void RenderTextureRotated(const Texture2D& texture, float x, float y, double angle, Rect srcRect = { 0 ,0,0,0 }) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, Rect srcRect = { 0 ,0,0,0 }) const;
	void RenderTextureRotated(const Texture2D& texture, float x, float y, float width, float height, double angle, Rect srcRect = { 0 ,0,0,0 }) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
};