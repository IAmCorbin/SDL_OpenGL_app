#include <vector>
// Shapes.h
// Class for creating simple OpenGL shapes

class Shape { 
	private:
		
	protected:
		//coordinates
		float x,y,z; 
		//width //depth //height
		float w,d,h; 
		//color
		float red, green, blue; 
		//color gradient
		bool gradient;
		float red2, green2, blue2; 
		float redShift, greenShift, blueShift, colorShift; 
	
		//vertex and vertex colors
		struct vertex { float x,y,z; }; 
		struct vertexColor { float r,g,b; };  
		//groups of vertices to create faces and groups of colors to match faces
		std::vector<vertex> faces;
		std::vector<vertexColor> faceColors;
		
		//STATIC DATA
		
	public:
		//vector to hold pointers to all existent shapes
		static std::vector<Shape*>* shapes;
	
		Shape();
		~Shape();
		void set(float newX, float newY, float newZ, float width, float depth, float height, float r, float g, float b, float r2, float g2, float b2);
		//return individual coordinate positions
		float getX();
		float getY();
		float getZ();
		//manipulate coordinates
		void addToX(float n);
		void addToY(float n);
		void addToZ(float n);
	
		virtual void setVertices() = 0;
		virtual void setFaces() = 0;
		void clearFaces();
		//swap colors to apply to 2nd half of vertices while defining
		void applyGradient();
		virtual void draw() = 0;
		
		//STATIC METHODS
		//draw all shapes
		static void drawAll();
		//add a new shape
		static void addNew(Shape* newShape);
		//delete all shapes and shapes container
		static void cleanupShapes();
};

class Cube : public Shape {
	private:
		vertex points[8];
		vertexColor pointColors[8];
	public:
		//constructor
		Cube(float xx, float yy, float zz, float width, float depth, float height, float r, float g, float b, float r2, float g2, float b2);

		void setVertices();
		void setFaces();
		void draw();
};
class Tetra : public Shape {
	private:
		vertex points[4];
		vertexColor pointColors[4];
	public:
		//constructors
		Tetra(float xx, float yy, float zz, float width, float depth, float height, float r, float g, float b, float r2, float g2, float b2);

		void setVertices();
		void setFaces();
		void draw();
};


class Room : public Shape {
	private:
		Cube* walls[6];
	public:
		//constructor
		Room(float xx, float yy, float zz, float width, float depth, float height, float r, float g, float b, float r2, float g2, float b2);
		
		void setVertices();
		void setFaces();
		void draw();
};

