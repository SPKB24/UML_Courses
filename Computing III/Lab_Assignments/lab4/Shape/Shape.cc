//**                                 **//
//                                     //
// PROGRAM NAME: Shape.cc              //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: April 15, 2015                //
//                                     //
//**                                 **//

#include <iostream>
#include <string>
#include "Shape.h"
#include <math.h>

using namespace std;

// NOT PART OF CLASS DEFINITION
// HELPER FUNCTION
double isValid(double length)
{
	if (length > 0)
		return length;

	return 10;
}

/***** (BASE) SHAPE CLASS *****/
Shape::Shape(double _height, double _width, double _length)
{
}

double Shape::getArea() const
{
	return 0;
}

double Shape::getVolume() const
{
	return 0;
}

string Shape::getName() const
{
	return NULL;
}

bool Shape::isTwoDimentional() const
{
	return NULL;
}

void Shape::printSizes() const 
{ }

/***************************************/
/***** TWO DIMENTIONAL SHAPE CLASS *****/
/***************************************/
TwoDimentionalShape::TwoDimentionalShape()
{ }

double TwoDimentionalShape::getArea() const
{
	return 0;
}

bool TwoDimentionalShape::isTwoDimentional() const
{
	return true;
}

/***** CIRCLE CLASS *****/
Circle::Circle(double _radius)
{
	shape_name = "CIRCLE";
	radius = isValid(_radius);
}

double Circle::getArea() const
{
	// Area = πr^2
	return pi * pow(radius, 2);
}

string Circle::getName() const
{
	return shape_name;
}

void Circle::printSizes() const
{
	cout << "- Radius: " << radius << endl;
}

/***** SQUARE CLASS *****/
Square::Square(double _side)
{
	shape_name = "SQUARE";
	side = isValid(_side);
}

double Square::getArea() const
{
	// Area = side^2
	return pow(side, 2);
}

string Square::getName() const
{
	return shape_name;
}

void Square::printSizes() const
{
	cout << "- Side: " << side << endl;
}

/***** TRIANGLE CLASS *****/
Triangle::Triangle(double _base, double _height)
{
	shape_name = "TRIANGLE";
	base = isValid(_base);
	height = isValid(_height);
}

double Triangle::getArea() const
{
	// Area = (Base * Height) / 2
	return (base * height) / 2;
}

string Triangle::getName() const
{
	return shape_name;
}

void Triangle::printSizes() const
{
	cout << "- Base: " << base << " Height: " << height << endl;
}

/*****************************************/
/***** THREE DIMENTIONAL SHAPE CLASS *****/
/*****************************************/
ThreeDimentionalShape::ThreeDimentionalShape()
{ }

double ThreeDimentionalShape::getArea() const
{
	return 0;
}

double ThreeDimentionalShape::getVolume() const
{
	return 0;
}

bool ThreeDimentionalShape::isTwoDimentional() const
{
	return false;
}

/***** SPHERE CLASS *****/
Sphere::Sphere(double _radius)
{
	shape_name = "SPHERE";
	radius = isValid(_radius);
}

string Sphere::getName() const
{
	return shape_name;
}

double Sphere::getArea() const
{
	// Area = 4πr^2
	return 4 * pi * pow(radius, 2);
}

double Sphere::getVolume() const
{
	// Volume = (4/3)πr^3
	return (4 / 3) * pi * pow(radius, 3);
}

void Sphere::printSizes() const
{
	cout << "- Radius: " << radius << endl;
}

/***** CUBE CLASS *****/
Cube::Cube(double _side)
{
	shape_name = "CUBE";
	side = isValid(_side);
}

string Cube::getName() const
{
	return shape_name;
}

double Cube::getArea() const
{
	// Area = 6 * side^2
	return 6 * pow(side, 2);
}

double Cube::getVolume() const
{
	// Area = Length * Width * Height = side^3
	return pow(side, 3);
}

void Cube::printSizes() const
{
	cout << "- Side: " << side << endl;
}

/***** TETRAHEDRON CLASS *****/
Tetrahedron::Tetrahedron(double _side1B, double _side1H, double _side2B,
						 double _side2H, double _side3B, double _side3H,
						 double _side4B, double _side4H)
{
	shape_name = "TETRAHEDRON";

	side1B = isValid(_side1B);
	side1H = isValid(_side1H);
	
	side2B = isValid(_side2B);
	side2H = isValid(_side2H);
	
	side3B = isValid(_side3B);
	side3H = isValid(_side3H);
	
	side4B = isValid(_side4B);
	side4H = isValid(_side4H);
}

string Tetrahedron::getName() const
{
	return shape_name;
}

double Tetrahedron::getArea() const
{
	// Area = Side1Area + Side2Area + Side3Area + Side4Area
	// Side1Area = ( base * height ) / 2
	double area = Tetrahedron::getTriangleArea(side1B, side1H);
		   area += Tetrahedron::getTriangleArea(side2B, side2H);
		   area += Tetrahedron::getTriangleArea(side3B, side3H);
		   area += Tetrahedron::getTriangleArea(side4B, side4H);
	return area;
}

double Tetrahedron::getVolume() const
{
	// Volume = (sqrt(2) / 12) * side^3 
	return (pow(2, 1 / 2) / 12) * pow(side1B, 3);
}

void Tetrahedron::printSizes() const
{
	cout << "- Side 1 | Base: " << side1B << " Height: " << side1H << endl
		 << "- Side 2 | Base: " << side2B << " Height: " << side2H << endl
		 << "- Side 3 | Base: " << side3B << " Height: " << side3H << endl
		 << "- Side 4 | Base: " << side4B << " Height: " << side4H << endl;
}

double Tetrahedron::getTriangleArea(double base, double height) const
{
	return (height * base) / 2;
}

