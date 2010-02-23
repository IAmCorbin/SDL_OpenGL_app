// SDL_OpenGL_app.cpp
// Class for creating a new SDL and OpenGL Application
#include "SDL_OpenGL_app.h"
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::SDL_OpenGL_app CLASS METHODS:::::::::::::::::://
	SDL_OpenGL_app::SDL_OpenGL_app() : fov(45.0f), zNear(0.1f), zFar(500.0f), incAngle(0.1f), incZoom(0.01f), xMove(0.0f), yMove(0.0f), zoom(-30.0f), angleX(-45.0f), angleY(0.0f), angleZ(15.0f), mousemove(false), gameover(false) { }

	void SDL_OpenGL_app::init(const char* titleTxt, const char* iconTxt, int width=800, int height=600, bool full=false) {
		fullscreen = full;
		//START SDL and error check
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)==-1) {
			//error initializing SDL
			fprintf(stderr,"Could not initialize SDL!\n");
			exit(1);	
		} else {
			//SDL initialized
			fprintf(stdout,"SDL initialized!\n");
			atexit(SDL_Quit);
		}
		
		//Initialize Joystick if present
		if(SDL_NumJoysticks()>0) {
			//grab the first joystick
			joystick =SDL_JoystickOpen(0);
			//get the number of buttons
			joystickButtons = SDL_JoystickNumButtons(joystick);
			//enable joystick events
			SDL_JoystickEventState(SDL_ENABLE);
		}	
		
		//Set Window Title
		SDL_WM_SetCaption(titleTxt,iconTxt);
		//initialize OpenGL
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8 );
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32 );
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glShadeModel(GL_SMOOTH);
		
		resize(width,height);
	}

	void SDL_OpenGL_app::run() {
		//SDL Event Structure
		SDL_Event event;
		
		while(!this->isGameover())
		{
			//draw the current frame
			this->drawFrame();
			//swap OpenGL Buffers
			SDL_GL_SwapBuffers();
			
			//EVENTS
			if(SDL_PollEvent(&event)) {
				this->handleEvents(event);
			} else {
				this->handleKeys();
			}
		}
	}
	void SDL_OpenGL_app::resize(int width, int height) {
		//Resize
		WIDTH = width;
		HEIGHT  = height;
		
		//load window and error check
		if(fullscreen)
			MainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);	
		else
			MainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,0,SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
		if(!MainWindow) {
			fprintf(stderr,"Error with SDL_SetVideoMove!\n");
			exit(1);
		}else {
			fprintf(stderr,"SDL_SetVideoMode Successfull!\n");	
		}
		
		glViewport(0, 0, WIDTH, HEIGHT);
	 		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if (height <= 0)
			height = 1;
	 
		int aspectratio = WIDTH / HEIGHT;
		gluPerspective(fov, aspectratio, zNear, zFar);
		
		glMatrixMode(GL_MODELVIEW);
		
		//enable culling for performance and proper display
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		//enable depth testing for proper display
		glEnable(GL_DEPTH_TEST);
		
		glLoadIdentity();
		
	}

	Uint8* SDL_OpenGL_app::getKeystate() { keystate = SDL_GetKeyState(NULL); return keystate; }
	
	
	//Mouse, Quit and Resize events
	void SDL_OpenGL_app::handleEvents(SDL_Event event) {
		switch(event.type) {
			//hangle resize
			//handle mouse movements
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT) {
					if(!mousemove)
						mousemove = true;
				} else if(event.button.button == SDL_BUTTON_WHEELUP ) {
					if(abs(zoom)>zNear)
						zoom += 1.0f;
				} else if(event.button.button == SDL_BUTTON_WHEELDOWN ) {
					if(abs(zoom)<zFar)
						zoom -= 1.0f;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT)
					if(mousemove)
						mousemove = false;
				break;
			case SDL_MOUSEMOTION:
				if(mousemove) {
					if(event.motion.xrel > 0 )
						angleY += 1.0f;
					if(event.motion.xrel < 0 )	
						angleY -= 1.0f;
					if(event.motion.yrel > 0 )	
						angleX += 1.0f;
					if(event.motion.yrel < 0 )	
						angleX -= 1.0f;
				}
				break;
			case SDL_VIDEORESIZE:
				resize(event.resize.w, event.resize.h);
				break;
			//handle quit
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						gameover = true;
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				gameover = true;
				break;
			default:
				break;
				}
	}
	void SDL_OpenGL_app::handleKeys() {
		//grab keyboard state
		SDL_OpenGL_app::getKeystate();
		//process key data
		
		
		//TRANSLATE
		//zoom in
		if (keystate[SDLK_i] ) {
			if(abs(zoom)>zNear) {
				zoom += incZoom;
			}
		}//zoom out
		if (keystate[SDLK_o] ) {
			if(abs(zoom)<zFar) {
				zoom -= incZoom;
			}
		}//translate world camera X
		if (keystate[SDLK_LEFT] ) {
			xMove += .01;
		}
		if (keystate[SDLK_RIGHT] ) {
			xMove -= .01;
		}
		//translate world camera Y
		if (keystate[SDLK_DOWN] ) {
			yMove += .01;
		}
		if (keystate[SDLK_UP] ) {
			yMove -= .01;
		}
		
		//ROTATE
		//rotate world around X
		if (keystate[SDLK_KP8] ) { 
			angleX += incAngle;
		}
		if (keystate[SDLK_KP2] ) { 
			angleX -= incAngle; 
		}
		//rotate world around Y
		if (keystate[SDLK_KP4] ) {
			angleY += incAngle;
			if(angleY == 360)
				angleY = 0;
			
		}
		if (keystate[SDLK_KP6] ) {
			angleY -= incAngle;
			if(angleY == 0)
				angleY = 360;
		}
		//rotate world around Z
		if (keystate[SDLK_KP1] ) { 
			angleZ += incAngle; 
		}
		if (keystate[SDLK_KP3] ) { 
			angleZ -= incAngle; 
		}
		
	}
	void SDL_OpenGL_app::drawFrame() {
		SDL_OpenGL_app::drawFrame_Open();
	}
	void SDL_OpenGL_app::drawFrame_Open() {
			//CLEAR
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//DRAW
			glLoadIdentity();
			//apply camera location and zoom
			glTranslatef(xMove,yMove,zoom);
			//apply X Rotation
			glRotatef(angleX, 1.0f, 0.0f, 0.0f);
			//apply Y Rotation
			glRotatef(angleY, 0.0f, 1.0f, 0.0f);
			//apply Z Rotation
			glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
			
			//Let OpenGL know about Vertex and Color array
			glEnableClientState(GL_VERTEX_ARRAY);   //We want a vertex array
			glEnableClientState(GL_COLOR_ARRAY);    //and a color array
	}
	void SDL_OpenGL_app::drawFrame_Close() {
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
	}

			//gluPerspective
			//fovy
			//	Specifies the field of view angle, in degrees, in the y direction.
			//aspect
			// 	Specifies the aspect ratio that determines
			//	the field of view in the x direction.
			//	The aspect ratio is the ratio of x (width) to y (height).
			//zNear
			//	Specifies the distance from the viewer to the near clipping plane (always positive).
			//zFar
			//	Specifies the distance from the viewer to the far clipping plane (always positive).
			    
	void SDL_OpenGL_app::gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
		GLdouble xmin, xmax, ymin, ymax;
		
		ymax = zNear * tan(fovy * M_PI / 360.0);
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;
				
		glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	}
	
	void SDL_OpenGL_app::setGameover() {
			gameover = true;
	}
	bool SDL_OpenGL_app::isGameover() {
		return gameover;
	}
//:::::::::::::SDL_OpenGL_app CLASS METHODS:::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://