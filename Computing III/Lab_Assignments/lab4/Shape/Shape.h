//**                                 **//
//                                     //
// PROGRAM NAME: Shape.h               //
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

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

/***** (BASE) SHAPE CLASS *****/
class Shape
{
public:
	Shape(double _height = 10, double _width = 5, double _length = 20);

	virtual double getArea() const;

	virtual double getVolume() const;

	virtual string getName() const;

	virtual bool isTwoDimentional() const;

	virtual void printSizes() const;

protected:
	string shape_name;
	double pi = 3.14159265;
};

/***** TWO DIMENTIONAL SHAPE CLASS *****/
class TwoDimentionalShape : public Shape
{
public:
	TwoDimentionalShape();

	virtual double getArea() const;

	virtual bool isTwoDimentional() const;
};

/***** CIRCLE CLASS *****/
class Circle : public TwoDimentionalShape
{
public:
	Circle(double _radius = 10);

	virtual double getArea() const;

	virtual string getName() const;

	virtual void printSizes() const;

private:
	double radius;
};

/***** SQUARE CLASS *****/
class Square : public TwoDimentionalShape
{
public:
	Square(double _side = 10);

	virtual double getArea() const;

	virtual string getName() const;

	virtual void printSizes() const;

private:
	double side;
};

/***** TRIANGLE CLASS *****/
class Triangle : public TwoDimentionalShape
{
public:
	Triangle(double _base = 10, double _height = 10);

	virtual double getArea() const;

	virtual string getName() const;

	virtual void printSizes() const;

private:
	double base;
	double height;
};

/***** THREE DIMENTIONAL SHAPE CLASS *****/
class ThreeDimentionalShape : public Shape
{
public:
	ThreeDimentionalShape();

	virtual double getArea() const;

	virtual double getVolume() const;

	virtual bool isTwoDimentional() const;
};

/***** SPHERE CLASS *****/
class Sphere : public ThreeDimentionalShape
{
public:
	Sphere(double _radius = 10);

	virtual string getName() const;

	virtual double getArea() const;

	virtual double getVolume() const;

	virtual void printSizes() const;

private:
	double radius;
};

/***** CUBE CLASS *****/
class Cube : public ThreeDimentionalShape
{
public:
	Cube(double _side = 10);

	virtual string getName() const;

	virtual double getArea() const;

	virtual double getVolume() const;

	virtual void printSizes() const;

private:
	double side;
};

/***** TETRAHEDRON CLASS *****/
class Tetrahedron : public ThreeDimentionalShape
{
public:
	Tetrahedron(double _side1B = 10, double _side1H = 10, double _side2B = 10,
				double _side2H = 10, double _side3B = 10, double _side3H = 10,
				double _side4B = 10, double _side4H = 10);

	virtual string getName() const;

	virtual double getArea() const;

	virtual double getVolume() const;

	virtual void printSizes() const;

	double getTriangleArea(double base, double height) const;

private:
	double side1B;
	double side1H;
	double side2B;
	double side2H;
	double side3B;
	double side3H;
	double side4B;
	double side4H;
};

#endif
