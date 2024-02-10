
1. C++ Related things:
	
	1.1) Using Smart Pointers with SDL Pointers:		{
		Since SDL Objects (ex. SDL_Window*, SDL_Renderer*) require specific destructors (ex. SDL_DestroyWindow, SDL_DestroyRenderer)
		they must have custom deleters if they're being wrapped with C++ smart pointers.
		
		So when declaring the smart pointer, you need to specify it's deleter:
			
			std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;

		And in a member initialization list, the deleter must be specified:
			
			: m_window(nullptr, SDL_DestroyWindow)

		Since the creation of a window is a specific SDL function, you have to create it as 
		a raw pointer, and transfer ownership to the unique pointer.  This transfer of ownership 
		is done using the .reset() method on smart pointers.
		_____________________________________________________________________________________
		| SDL_Window* pWindow = SDL_CreateWindow("SDL Renderer",
		|  		SDL_WINDOWPOS_CENTERED,
		|  		SDL_WINDOWPOS_CENTERED,
		|  		Renderer::WindowWidth,
		|  		Renderer::WindowHeight,
		|  		SDL_WINDOW_RESIZABLE);
		|  if (!pWindow)
		|  {
		|  		std::cout << "Failed to create SDL Window: " << SDL_GetError() << std::endl;
		|		throw std::runtime_error(SDL_GetError());
		|  }
		|  m_window.reset(pWindow);
		|____________________________________________________________________________________

		How .reset() works:
			- if a smart pointer currently owns an object, then it destroys that object
			- if a smart pointer currently owns nullptr, .reset() will transfer the object to it
				effectively calling "std::make_unique"
			- if called without an argument, it release ownership of whatever it has
	}
