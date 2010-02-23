// Move.cpp
// SDL_OpenGL_app Class for binding movement controls to a Shape object
#include "Move.h"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::Move CLASS METHODS::::::::::::::::::::::::::::::::::::://
Move::Move() : offMove(false), MOVE_SPEED(0.01f) { }

void Move::bindObject(Shape* obj) {
	object = obj;
}
void Move::disable() {
	offMove = true;
}
void Move::enable() {
	offMove = false;
}
//:::::::::::::Move CLASS METHODS:::::::::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::KeyMove CLASS METHODS::::::::::::::::::::::::::::::::::::://
void KeyMove::handle() { 
	
	keystate = SDL_GetKeyState(NULL);
	if(keystate[SDLK_w]) {
		object->addToY(MOVE_SPEED);
	}
	if(keystate[SDLK_a]) {
		object->addToX(-MOVE_SPEED);
	}
	if(keystate[SDLK_s]) {
		object->addToY(-MOVE_SPEED);
	}
	if(keystate[SDLK_d]) {
		object->addToX(MOVE_SPEED);
	}
	object->clearFaces();
	object->setFaces();
}
//:::::::::::::KeyMove CLASS METHODS:::::::::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::MouseMove CLASS METHODS::::::::::::::::::::::::::::::::::::://
void MouseMove::handle() { 
		
	
}
//:::::::::::::MouseMove CLASS METHODS:::::::::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//:::::::::::::JoyMove CLASS METHODS::::::::::::::::::::::::::::::::::::://
JoyMove::JoyMove() : up(false), down(false), left(false), right(false) {  }
//for key handling
void JoyMove::handle() { 
	if(up)
		object->addToY(-MOVE_SPEED);
	if(down)
		object->addToY(MOVE_SPEED);
	if(left)
		object->addToX(-MOVE_SPEED);
	if(right)
		object->addToX(MOVE_SPEED);
	
	object->clearFaces();
	object->setFaces();	
}
//for event
void JoyMove::handle(SDL_Event event, SDL_Joystick* joystick) { 
	if(event.type==SDL_JOYAXISMOTION) {
		if(event.jaxis.axis==0)
			if(event.jaxis.value>0) {
				left = false;
				right = true;
			}
			else if(event.jaxis.value<0) {
				left = true;
				right = false;
			}
			else if(event.jaxis.value==0) {
				left = false;
				right = false;
			}
		if(event.jaxis.axis==1) 
			if(event.jaxis.value>0) {
				up = true;
				down = false;
			}
			else if(event.jaxis.value<0) {
				up = false;
				down = true;
			}
			else if(event.jaxis.value==0) {
				up = false;
				down = false;
			}
	}
}
//:::::::::::::JoyMove CLASS METHODS:::::::::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://