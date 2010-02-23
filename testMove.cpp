// testVBO.cpp
// Testing OpenGL Vertex Buffer Objects
#include "testMove.h"




//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::TestVBO CLASS METHODS:::::::::::::::::::::::::::::::://
TestMove::TestMove() {
	SDL_OpenGL_app::SDL_OpenGL_app();
}
TestMove::~TestMove() {
	Shape::cleanupShapes();
}
void TestMove::init(const char* titleTxt, const char* iconTxt, int width, int height, bool full=false) {
	SDL_OpenGL_app::init(titleTxt,iconTxt,width,height,full);
	
	//Setup Shapes
	
	//floor
	Shape::addNew(new Cube(0.0f,0.0f,-0.5f, 25.0f,40.0f,1.0f));
	
	//walls
	Shape::addNew(new Cube(12.0f,0.0f,10.0f,1.0f,40.0f,20.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f));
	Shape::addNew(new Cube(-12.0f,0.0f,10.0f,1.0f,40.0f,20.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f));
	
	//Mountains
	Shape::addNew(new Tetra(5.0f,8.0f,4.0f, 10.0f,10.0f,8.0f, 1.0f,1.0f,1.0f, 0.0f,0.0f,0.3f)); //location and size 
	Shape::addNew(new Tetra(0.0f,10.0f,3.0f, 7.0f,7.0f,6.0f, 1.0f,1.0f,1.0f, 0.0f,0.0f,0.3f)); //location and size 
	
	//blue block
	Shape::addNew(new Cube(0.0f,0.0f,1.5f, 2.0f,4.0f,3.0f, 0.0f,0.2f,0.2f));
	
	//basic cube and tetra with default options
	Shape::addNew(new Cube(-5.0f,0.0f,30.0f));
	Shape::addNew(new Tetra(5.0f,0.0f,30.0f));
	
	
	//array of floating blocks
	float z = -14.0f;
	float r = 0.0f;
	float g = 0.0f;
	float b= 0.0f;
	
	for(float x=-10.0f; x<10.0f; x+=4.0f) {
		z+=2.0f;
		for(float y=-15.0f; y<15.0f; y+=5.0f) {
			Shape::addNew(new Cube(x,y,z, 1.0f,1.0f,1.0f,r+=0.05,g+=0.05,b+=0.05,0.5f,0.f,0.2f ));
		}
	}
	
	//test Room Class
	Shape::addNew(new Room(0.0f,0.0f,-100.0f,          300.0f,300.0f,300.0f,   0.3f,0.2f,0.0f,   0.4f,0.3f,0.7f));
	Shape::addNew(new Room(-70.0f,-70.0f,-50.0f,  20.0f,20.0f,50.0f,    0.3f,0.3f,0.3f,   0.1f,0.1f,0.1f));
	
	//Character
	Character1 = new Cube(-10.0f,10.0f,0.2f, 0.2f,0.2f,0.4f, 0.0f,1.0f,0.4f);
	Character2 = new Tetra(5.0f,-10.0f,0.2f,  0.2f,0.2f,0.4f, 0.0f,0.4f,1.0f);
	//bind controls
	//bind keyboard controls
	keyCharMove.bindObject(Character1);
	//bind joystick controls
	joyCharMove.bindObject(Character2);
	
}

void TestMove::run() {	
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

void TestMove::handleEvents(SDL_Event event) {
	//handle resize, quit, and mouse camera movement
	SDL_OpenGL_app::handleEvents(event);
	
	//handle joystick events
	joyCharMove.handle(event,joystick);
	
	switch(event.type) {
		default:
			break;
	}
	
}
void TestMove::handleKeys() {
	//handle basic camera movement
	SDL_OpenGL_app::handleKeys();
	
	keystate = SDL_OpenGL_app::getKeystate();
	
	//change polygon drawing mode
	if(keystate[SDLK_9]) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	if(keystate[SDLK_8]) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	
	//handle character movement
	keyCharMove.handle();
	joyCharMove.handle();
	
}


void TestMove::drawFrame() {
	//Start openGL Drawing Calls
	SDL_OpenGL_app::drawFrame_Open();
	
	//draw all shape objects in shapes container ( anything added with Shape::addNew() )
	Shape::drawAll();
	
	//draw 
	Character1->draw();
	Character2->draw();
	
	//Clean up openGL drawing calls
	SDL_OpenGL_app::drawFrame_Close();
}
//:::::::::::::TestVBO CLASS METHODS:::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://


int main(int argc, char* argv[]) {
	
	//The Application - initialize
	TestMove Move_App;
	Move_App.init("Move Object Test","Move Object Test",1024,768);
	//run the program
	Move_App.run();
	
	
	
	fprintf(stdout, "Normal Program Termination.\n");
	return 0;
}