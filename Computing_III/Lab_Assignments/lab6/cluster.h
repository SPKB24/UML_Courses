//**                                 **//
//                                     //
// PROGRAM NAME: cluster.h             //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: May 1, 2015                   //
//                                     //
//**                                 **//

#ifndef CLUSTER_H
#define CLUSTER_H

#include <iostream>
#include <vector>
#include <string>
#include "point.h"

class Cluster
{
public:
	// Default Constructor
	Cluster() :centroid(0) {}

	// Custom Constructor
	Cluster(vector<double> &arg)
	{
		Point temp((int) arg.size(), arg);
		
		pointCollection.push_back(temp);

		comparePointDimensions();

		findCentroid();
	}

	// Addition Operator
	Cluster operator+(const Cluster &arg)
	{
		Cluster temp;
		for (int i = 0; i < pointCollection.size(); i++)
			temp.pointCollection.push_back(pointCollection[i]);

		for (int i = 0; i < pointCollection.size(); i++)
			temp.pointCollection.push_back(arg.pointCollection[i]);

		temp.centroid = setCentroid();

		return temp;
	}

	void addPoint(Point arg)
	{
		pointCollection.push_back(arg);
	}

	int numberOfPoints()
	{
		return pointCollection.size();
	}

	void findCentroid()
	{
		double sum = 0;

		for (int i = 0; i < (int) pointCollection.size(); i++)
			sum += pointCollection[i].findAverage();

		centroid = sum / pointCollection.size();
	}

	double setCentroid()
	{
		double sum = 0;
		double _centroid = 0;

		for (int i = 0; i < (int)pointCollection.size(); i++)
			sum += pointCollection[i].findAverage();

		_centroid = sum / pointCollection.size();

		return _centroid;
	}

	double getCentroid()
	{
		return centroid;
	}

	void printPoints()
	{
		for (int i = 0; i < pointCollection.size(); i++)
			pointCollection[i].printAll();
	}

	int getDimensions()
	{
		return pointCollection[0].getDimension();
	}

	~Cluster()
	{
		pointCollection.clear();
	}

private:
	double centroid;
	vector<Point> pointCollection;

	void comparePointDimensions()
	{
		if ((int) pointCollection.size() > 1)
			for (int i = 0; i < pointCollection.size() - 1; i++)
				if (pointCollection[i].getDimension() != pointCollection[i + 1].getDimension())
					printError("ERROR: Points have different dimentions");
	}

	void printError(string error)
	{
		cout << error << endl;
		exit(1);
	}
};

#endif
