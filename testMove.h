
//additional OpenGL Include for glBindBuffer and glBufferData
#include "SDL_OpenGL_app.cpp"
#include "Shape.cpp"
#include "Move.cpp"

class TestMove : public SDL_OpenGL_app {
	private:
		//SDL Event Structure
		SDL_Event event;
	
		KeyMove keyCharMove;
		JoyMove joyCharMove;
		Shape* Character1;
		Shape* Character2;
		Uint8* keystate;
	public:
		~TestMove();
		TestMove();
		void init(const char* titleTxt, const char* iconTxt, int width, int height, bool full);
		void run();
		void handleEvents(SDL_Event event);
		void handleKeys();
		void drawFrame();
};