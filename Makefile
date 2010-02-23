# Program Name
PROG = testMove
#Dependencies
DEPENDS = SDL_OpenGL_app.h SDL_OpenGL_app.cpp Shape.h Shape.cpp Move.h Move.cpp
# SDL Options
SDL_OPTS = `sdl-config --cflags --libs` -g
# Linked Libraries
LL = -lGL

all: $(PROG)

clean:
	rm $(PROG)

$(PROG): $(PROG).h $(PROG).cpp $(DEPENDS)
	g++ $(SDL_OPTS) $(LL) -o $@ $(PROG).cpp


