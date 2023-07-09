#include "App.h"
#include <iostream>
#include "SDL2/SDL.h"

class Renderer_GL;
class Renderer_Vulk;
class Renderer_DX;

App::App() :
    m_isRunning(false),
    m_rendererAPI(Renderer_API_Open_GL) 
{
    CreateRenderer();
}

App::~App() {
    
}


void App::Setup()
{
    SetIsRunning(true);

    m_renderer->Init();

    std::cout << "App successfully Set Up\n";
}

void App::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) 
        {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    m_isRunning = false;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) 
                    std::cout << "wheel forward\n";                                    
                else if (event.wheel.y < 0) 
                    std::cout << "wheel backward\n";                    
                break;
        }

    }
}

void App::Update()
{
   m_renderer->Update(); 
}

void App::Render()
{
    m_renderer->Render();
}

void App::Destroy()
{
    // Deallocate resources to subsystems 
    std::cout << "App successfully destroyed\n";
}


bool App::IsRunning() {
    return m_isRunning;
}

void App::SetIsRunning(bool isRunning) {
    m_isRunning = isRunning;
}

void App::CreateRenderer() {
    m_renderer = RendererInterface::MakeRenderer(m_rendererAPI);
}



