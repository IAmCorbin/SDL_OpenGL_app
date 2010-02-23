// Shapes.cpp
// Class for creating simple OpenGL shapes
#include "Shape.h"

std::vector<Shape*>* Shape::shapes;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//::::::::::::::::::Shape CLASS METHODS::::::::::::::::::::::::::::::://
Shape::Shape() : gradient(false), colorShift(0.30f), redShift(0.0f), greenShift(0.0f), blueShift(0.0f), red2(0.0f), green2(0.0f), blue2(0.0f) { 
}
Shape::~Shape() {
	
}
void Shape::set(float newX, float newY, float newZ, float width, float depth, float height, float r, float g, float b, float r2, float g2, float b2) { 
		//set colors
		red=r;
		green=g;
		blue=b;
		
	
		//check color and set shift
		if(red>0.7f)
			redShift = -colorShift;
		else if(red>0.3)
			redShift = colorShift;
		else
			redShift = 0.0f;
		
		if(green>0.7f)
			greenShift = -colorShift;
		else if(green>0.3)
			greenShift = colorShift;
		else
			greenShift = 0.0f;
		
		if(blue>0.7f)
			blueShift = -colorShift;
		else if(blue<0.3)
			blueShift = colorShift;
		else
			blueShift = 0.0f;
		
		//set gradient colors if passed
		if( r2>0.0f || g2>0.0f || b2>0.0f ) {
			red2=r2;
			green2=g2;
			blue2=b2;
		}
		
		//set position
		x=newX;
		y=newY;
		z=newZ;
		//set size
		w=width;
		d=depth;
		h=height;
}
float Shape::getX() { return x; }
float Shape::getY() { return y; }
float Shape::getZ() { return z; }
void Shape::addToX(float n) { 
	x += n; 
	setVertices();
}
void Shape::addToY(float n) { 
	y += n; 
	setVertices();
}
void Shape::addToZ(float n) { 
	z += n; 
	setVertices();
}
void Shape::clearFaces() {
	while(faces.size() > 0) {
		faces.pop_back();
		faceColors.pop_back();
	}
}
void Shape::applyGradient() {
	//check for gradient
	if(red2>=0.1f || green2>=0.1f || blue2>=0.1f)
		gradient = true;
	if(gradient) {
			float swapColor;
			//red
			swapColor = red2;
			red2=red;
			red=swapColor;
			//green
			swapColor = green2;
			green2=green;
			green=swapColor;
			//blue
			swapColor = blue2;
			blue2=blue;
			blue=swapColor;
			
		}
}
void Shape::addNew(Shape* newShape) { 
	//if there is no shapes container, create one
	if(!Shape::shapes)
		Shape::shapes = new std::vector<Shape*>();
	//Add the new shape to the container
	Shape::shapes->push_back(newShape);
}

void Shape::drawAll() {
	for(int n=0; n<(int)Shape ::shapes->size(); n++)
		Shape::shapes->at(n)->draw();
}

void Shape::cleanupShapes() {
	//memory cleanup of all shapes and shapes container  - call when done with shapes
	fprintf(stdout,"cleanupShapes: Empty shapes container\n");
	int numofshapes = Shape::shapes->size();
	int n = 0;
	while(n<numofshapes) {
			fprintf(stdout,"        cleanupShapes: Delete shape %d\n",n);
			delete Shape::shapes->at(n);
			n++;
	}
	fprintf(stdout,"cleanupShapes: Delete shapes container\n");
	delete Shape::shapes;
}
//::::::::::::::::::Shape CLASS METHODS::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//::::::::::::::::::::::Cube CLASS METHODS:::::::::::::::::::::::::::://
	Cube::Cube(float newX, float newY, float newZ, float width=2.0f, float depth=2.0f, float height=2.0f, float r=1.0f, float g=0.0f, float b=0.0f, float r2=0.0f, float g2=0.0f, float b2=0.0f) {  
		Shape::set(newX, newY, newZ, width, depth, height, r, g, b, r2, g2, b2);
		setVertices();
	}
	/*Cube::~Cube() {
		Shape::~Shape();
	}*/
	void Cube::setVertices() {	
		//VERTICES
		//point 1
		points[0].x = x-(w/2.0f);
		points[0].y = y+(d/2);
		points[0].z = z+(h/2.0f); 
		//point 2
		points[1].x = x-(w/2.0f); 
		points[1].y = y+(d/2); 
		points[1].z = z-(h/2);
		//point 3
		points[2].x = x+(w/2.0f); 
		points[2].y = y+(d/2.0f);
		points[2].z = z-(h/2.0f); 
		//point 4
		points[3].x = x+(w/2.0f); 
		points[3].y = y+(d/2.0f);
		points[3].z = z+(h/2.0f);
		
		//point 5
		points[4].x = x+(w/2.0f);
		points[4].y = y-(d/2.0f);
		points[4].z = z+(h/2.0f); 
		//point 6
		points[5].x = x+(w/2.0f); 
		points[5].y = y-(d/2.0f);
		points[5].z = z-(h/2.0f); 
		//point 7
		points[6].x = x-(w/2.0f); 
		points[6].y = y-(d/2.0f);
		points[6].z = z-(h/2.0f); 
		//point 8
		points[7].x = x-(w/2.0f); 
		points[7].y = y-(d/2.0f);
		points[7].z = z+(h/2.0f); 

		//COLORS
		//point 1
		pointColors[0].r = red;
		pointColors[0].g = green;
		pointColors[0].b = blue; 
		//point 2
		pointColors[1].r = red;
		pointColors[1].g = green;
		pointColors[1].b = blue; 
		//point 5
		pointColors[4].r = red+redShift;
		pointColors[4].g = green+greenShift;
		pointColors[4].b = blue+blueShift; 
		//point 6
		pointColors[5].r = red+redShift;
		pointColors[5].g = green+greenShift;
		pointColors[5].b = blue+blueShift; 
		
		applyGradient();
		
		//point 3
		pointColors[2].r = red;
		pointColors[2].g = green;
		pointColors[2].b = blue; 
		//point 4
		pointColors[3].r = red;
		pointColors[3].g = green;
		pointColors[3].b = blue;
		//point 7
		pointColors[6].r = red+redShift;
		pointColors[6].g = green+greenShift;
		pointColors[6].b = blue+blueShift; 
		//point 8
		pointColors[7].r = red+redShift;
		pointColors[7].g = green+greenShift;
		pointColors[7].b = blue+blueShift; 
		
		//now assemble faces
		setFaces();
	}
	void Cube::setFaces() {		
		//FACES
		//Front Face
		faces.push_back(points[0]);
		faces.push_back(points[1]);
		faces.push_back(points[2]);
		faces.push_back(points[3]);
		//Back Face
		faces.push_back(points[4]);
		faces.push_back(points[5]);
		faces.push_back(points[6]);
		faces.push_back(points[7]);
		//Left Face
		faces.push_back(points[0]);
		faces.push_back(points[7]);
		faces.push_back(points[6]);
		faces.push_back(points[1]);
		//Right Face
		faces.push_back(points[3]);
		faces.push_back(points[2]);
		faces.push_back(points[5]);
		faces.push_back(points[4]);
		//Top Face
		faces.push_back(points[0]);
		faces.push_back(points[3]);
		faces.push_back(points[4]);
		faces.push_back(points[7]);
		//Bottom Face
		faces.push_back(points[1]);
		faces.push_back(points[6]);
		faces.push_back(points[5]);
		faces.push_back(points[2]);
		
		
		//COLORS
		//Front Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[1]);
		faceColors.push_back(pointColors[2]);
		faceColors.push_back(pointColors[3]);
		//Back Face
		faceColors.push_back(pointColors[4]);
		faceColors.push_back(pointColors[5]);
		faceColors.push_back(pointColors[6]);
		faceColors.push_back(pointColors[7]);
		//Left Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[7]);
		faceColors.push_back(pointColors[6]);
		faceColors.push_back(pointColors[1]);
		//Right Face
		faceColors.push_back(pointColors[3]);
		faceColors.push_back(pointColors[2]);
		faceColors.push_back(pointColors[5]);
		faceColors.push_back(pointColors[4]);
		//Top Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[3]);
		faceColors.push_back(pointColors[4]);
		faceColors.push_back(pointColors[7]);
		//Bottom Face
		faceColors.push_back(pointColors[1]);
		faceColors.push_back(pointColors[6]);
		faceColors.push_back(pointColors[5]);
		faceColors.push_back(pointColors[2]);
	}
	void Cube::draw() {
		//set vertex and color vectors
		glVertexPointer(3, GL_FLOAT, sizeof(faces.at(0)), &faces.at(0));
		glColorPointer(3, GL_FLOAT, sizeof(faceColors.at(0)), &faceColors.at(0));
		//Draw Cube
		glDrawArrays(GL_QUADS, 0, 24 );    
	}
//::::::::::::::::::::Cube CLASS METHODS::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//::::::::::::::::::::::Tetra CLASS METHODS:::::::::::::::::::::::::::://
	//Tetra::Tetra() { }
	Tetra::Tetra(float newX, float newY, float newZ, float width=2.0f, float depth=2.0f, float height=2.0f, float r=0.0f, float g=1.0f, float b=0.0f, float r2=0.0f, float g2=0.0f, float b2=0.0f) {  
		Shape::set(newX, newY, newZ, width, depth, height, r, g, b,r2,g2,b2);
		setVertices();
	}
	void Tetra::setVertices() {	
		//VERTICES
		//point 1
		points[0].x = x;
		points[0].y = y;
		points[0].z = z+(h/2.0f); 
		//point 2
		points[1].x = x-(w/2.0f); 
		points[1].y = y+(d/2.0f);
		points[1].z = z-(h/2.0f); 
		//point 3
		points[2].x = x+(w/2.0f); 
		points[2].y = y+(d/2.0f);
		points[2].z = z-(h/2.0f); 
		//point 4
		points[3].x = x; 
		points[3].y = y-(d/2.0f);
		points[3].z = z-(h/2.0f); 
		
		
		//COLORS
		//point 1
		pointColors[0].r = red;
		pointColors[0].g = green;
		pointColors[0].b = blue; 
		
		applyGradient();
		
		//point 2
		pointColors[1].r = red+redShift;
		pointColors[1].g = green+greenShift;
		pointColors[1].b = blue+blueShift; 
		//point 3
		pointColors[2].r = red+redShift;
		pointColors[2].g = green+greenShift;
		pointColors[2].b = blue+blueShift; 
		//point 4
		pointColors[3].r = red+redShift;
		pointColors[3].g = green+greenShift;
		pointColors[3].b = blue+blueShift; 
		
		
		setFaces();
	}
	void Tetra::setFaces() {
		//FACES
		//Front Face
		faces.push_back(points[0]);
		faces.push_back(points[1]);
		faces.push_back(points[2]);
		//Left Face
		faces.push_back(points[0]);
		faces.push_back(points[3]);
		faces.push_back(points[1]);
		//Right Face
		faces.push_back(points[0]);
		faces.push_back(points[2]);
		faces.push_back(points[3]);
		//Bottom Face
		faces.push_back(points[2]);
		faces.push_back(points[1]);
		faces.push_back(points[3]);
		
		//COLORS
		//Front Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[1]);
		faceColors.push_back(pointColors[2]);
		//Back Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[3]);
		faceColors.push_back(pointColors[1]);
		//Left Face
		faceColors.push_back(pointColors[0]);
		faceColors.push_back(pointColors[2]);
		faceColors.push_back(pointColors[3]);
		//Right Face
		faceColors.push_back(pointColors[2]);
		faceColors.push_back(pointColors[1]);
		faceColors.push_back(pointColors[3]);
	}
	void Tetra::draw() {
			//Assign Vertex and Color Arrays
			glVertexPointer(3, GL_FLOAT, 0, &faces.at(0));   //All values are grouped to three Floats, we start at the beginning of the array (offset=0) and want to use m_vertices as VertexArray
			glColorPointer(3, GL_FLOAT, 0, &faceColors.at(0));      //Same here, but use m_colors
			//Draw Tetra
			glDrawArrays(GL_TRIANGLES, 0, 12); 

	}
//::::::::::::::::::::Tetra CLASS METHODS::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://
	
	
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//::::::::::::::::::::::Room CLASS METHODS:::::::::::::::::::::::::::://
	Room::Room(float newX, float newY, float newZ, float width=20.0f, float depth=30.0f, float height=20.0f, float r=0.0f, float g=1.0f, float b=0.0f, float r2=0.0f, float g2=0.0f, float b2=0.0f) {  
		Shape::set(newX, newY, newZ, width, depth, height, r, g, b,r2,g2,b2);
		
		//floor
		walls[0] = new Cube(x,y,z,                               w,d,1.0f,  red,green,blue, red2,green2,blue2);
		//front
		walls[1] = new Cube(x,y-(d/2)+0.5f,z+(h/2)+0.5f,    w-1.0f,1.0f,h,                   red+redShift,green+greenShift,blue+blueShift, red2+redShift,green2+greenShift,blue2+blueShift);
		//back
		walls[2] = new Cube(x,y+(d/2)-0.5f,z+(h/2)+0.5f,   w-1.0f,1.0f,h,                   red,green,blue, red2,green2,blue2);
		//left
		walls[3] = new Cube(x-(w/2)+0.5f,y,z+(h/2)+0.5f,    1.0f,d-1.0f,h,                    red+redShift,green+greenShift,blue+blueShift, red2+redShift,green2+greenShift,blue2+blueShift);
		//right
		walls[4] = new Cube(x+(w/2)-0.5f,y,z+(h/2)+0.5f,   1.0f,d-1.0f,h,                   red,green,blue, red2,green2,blue2);
		//ceiling
		walls[5] = new Cube(x,y,z+h+1.0f,                   w,d,1.0f,  red+redShift,green+greenShift,blue+blueShift, red2+redShift,green2+greenShift,blue2+blueShift);
	
		setVertices();
	}
	void Room::setVertices() {		
		
		setFaces();
	}
	void Room::setFaces() {

	}
	void Room::draw() {
		for(int n=0; n<6; n++) {
			walls[n]->draw();
		}
	}
//::::::::::::::::::::Room CLASS METHODS::::::::::::::::::::::::::::::://
//:::::END:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::END::::::://
	