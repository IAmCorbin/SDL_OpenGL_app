// SDL_OpenGL_app.h
// Class for creating a new SDL and OpenGL Application
#include "SDL.h"
#include "SDL_opengl.h"
#include <math.h> //for glyPerspective

class SDL_OpenGL_app {
	protected:
		//initial window size
		int WIDTH;
		int HEIGHT;
		bool fullscreen;
	
		//window
		SDL_Surface* MainWindow;
		float zNear;
		float zFar;
		
		//controls
		//keyboard
		Uint8* keystate;
		//mouse
		bool mousemove;
		//joystick
		SDL_Joystick* joystick;
		//joystick buttons
		int joystickButtons;
		//joystick axis position(read only first two)
		int joystickAxis[2];
	
		//set speed options
		float incAngle;
		float incZoom;
   
		//camera and rotation options
		float fov;
		float xMove;
		float yMove;
		float zoom; 
		float angleX; 
		float angleY; 
		float angleZ;
				
		//gameover flag
		bool gameover;
	
	public:
		SDL_OpenGL_app();
		void init(const char* titleTxt, const char* iconTxt, int width, int height, bool full);
		void run();
		Uint8* getKeystate();
		void resize(int width,int height);
		virtual void drawFrame();
		void drawFrame_Open();
		void drawFrame_Close();
		void handleEvents(SDL_Event event);
		void handleKeys();
		void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
		//GAMEOVER
		void setGameover();
		bool isGameover();
};