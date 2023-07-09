#ifndef APP_H
#define APP_H
#include "SDL2/SDL.h"
#include <memory>

#include "enumerations.h"
#include "RendererInterface.h"

class App
{
public:
	App();
	~App();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();


	void SetIsRunning(bool isRunning);
	bool IsRunning();
	void CreateRenderer();

    SDL_Renderer* sdl_renderer;
    SDL_Window* sdl_window;

private:
	bool m_isRunning = false;
	std::unique_ptr<RendererInterface> m_renderer;
	RENDERER_API m_rendererAPI;
};


#endif
