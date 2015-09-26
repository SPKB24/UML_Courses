//**                                 **//
//                                     //
// PROGRAM NAME: cluster_user.cc       //
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

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include "cluster.h"
#include "point.h"
using namespace std;

double getDistance(Cluster a, Cluster b)
{
	if (a.getCentroid() == b.getCentroid())
		return 0;

	double distance = a.getCentroid() - b.getCentroid();

	if (distance < 0)
		distance = 0 - distance;

	return distance;
}

vector<Cluster> putIntoClusters(vector<Cluster>& _collection, int _k)
{
	int countedClusters = (int)_collection.size(); //Ex. 5 Clusters | _k = 2
	int gridLength = (int)_collection.size();
	vector< vector<double> > distances;
	vector<double> lineOfDistances;
	vector<Cluster> newClusterVector;
	int runCount = 0;

	while (countedClusters != _k)
	{
		// Add distances to 2D array
		for (int row = 0; row < gridLength; row++)
		{
			for (int column = 0; column < gridLength; column++)
				lineOfDistances.push_back(
						getDistance(_collection[row]
						          , _collection[column]));

			distances.push_back(lineOfDistances);
			lineOfDistances.clear();
		}

		vector<int> smallestPairs;      // hold smallest pair
		smallestPairs.reserve(2);       // only needs 2 ints
		double smallestItem = 1001;     // hold smallest distance

		// Find smallest distance
		for (int row = 0; row < gridLength; row++)
			for (int column = 0; column < gridLength; column++)
				if (row != column)
				{
					if (smallestItem == 1001)
					{
						smallestItem = distances[row][column];
						smallestPairs.push_back(row);
						smallestPairs.push_back(column);
					}

					if (distances[row][column] < smallestItem)
					{
						smallestPairs.clear();
						smallestItem = distances[row][column];
						smallestPairs.push_back(row);
						smallestPairs.push_back(column);
					}
				}

		// Put both points in a new Cluster
		Cluster newCluster = _collection[smallestPairs[0]].operator+(
				     _collection[smallestPairs[1]]);
		
		int count = 0;
		// Remove those points from the cluster
		for (vector<Cluster>::iterator it = _collection.begin();
							 it != _collection.end(); it++)
		{
			if (count == smallestPairs[0])
			{
				_collection.erase(it);
				break;
			}
			count++;
		}
		int sub = 0;
		if (smallestPairs[1] > smallestPairs[0])
			sub = 1;
		count = 0;
		for (vector<Cluster>::iterator it = _collection.begin();
							 it != _collection.end(); it++)
		{
			if (count == smallestPairs[1] - sub)
			{
				_collection.erase(it);
				break;
			}
			count++;
		}

		// Add newCluster to Vector of Clusters
		_collection.push_back(newCluster);
		
		countedClusters = (int)_collection.size();
		gridLength = (int)_collection.size();
		distances.clear();
		smallestPairs.clear();
	}

	for (int i = 0; i < _collection.size(); i++)
	{
		cout << "Cluster #" << i+1 << endl;
		_collection[i].printPoints();
		cout << endl;
	}

	return newClusterVector;
}

Cluster newCluster(vector<double> _array)
{
	Cluster temp(_array);
	return temp;
}

int main(int argc, char * argv[])
{
	int k = argc;

	vector<Cluster> clusterCollection; // Main Vector | hold all clusters
	
	char* fileInputString = new char[256];
	// holds one line of input from txt file as string
	
	vector<double> holdArrayDoubles;
	// holds all doubles from individual lines, puts in inputLines after
	
	stringstream ss3;
	// Creates a stream using the holdString
	
	double holdDouble;	
	// holds doubles from string
	
	/////////////// CHANGE INPUTFILE TO CIN ///////////////
	for (int i = 0; cin.getline(fileInputString, 256, '\n'); i++) //Get entire line
	{
		ss3 << fileInputString;

		for (int j = 0; ss3 >> holdDouble; j++)
			holdArrayDoubles.push_back(holdDouble);

		clusterCollection.push_back(newCluster(holdArrayDoubles));
		
		if (clusterCollection.size() > 1) // Check point dimensions
			if (clusterCollection[i - 1].getDimensions() != 
				clusterCollection[i].getDimensions())
			{
				cout << "ERROR: DIMENSION MISMATCH" << endl;
				exit(1);
			}

		holdArrayDoubles.clear();
		ss3.clear();
	}

	putIntoClusters(clusterCollection, k);

	return 0;
}
