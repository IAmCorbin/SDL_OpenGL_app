// Move.h
// SDL_OpenGL_app Class for binding movement controls to a Shape object
 
class Move {
		protected:
			const float MOVE_SPEED;
			Shape* object;
			//disable/enable move
			bool offMove;
			Uint8* keystate;
		public:
			Move();
			void bindObject(Shape* obj);
			virtual void handle() = 0;
			void disable();
			void enable();
};

class KeyMove : public Move {
		private:
		public:
			void handle();
};

class MouseMove : public Move {
		private:
		public:
			void handle();
};

class JoyMove : public Move {
		private:
			bool up, down, left, right;
		public:
			JoyMove();
			void handle();
			void handle(SDL_Event event, SDL_Joystick* joystick);
};
