// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Graph abstract class. This ADT assumes that hte number
// of vertices is fixed when the graph is created.
#pragma once

#define UNVISITED 0
#define VISITED 1
#define INFINITY 9999

class Graph {
private:
	void operator =(const Graph&) {}		//protect assignment
	Graph(const Graph&) {}					//protect copy constructor

public:
	Graph() {}								//default constructor
	virtual ~Graph() {}						//base destructor

	//Initialize a graph of n vertices
	virtual void Init(int n) = 0;

	//Return the number of verticecs and edges
	virtual int n() = 0;
	virtual int e() = 0;

	//Return v's first neighbor
	virtual int first(int v) = 0;

	//Return v's next neighbor
	virtual int next(int v, int w) = 0;

	//Set the weight for an edge
	virtual void setEdge(int v1, int v2, int wgt) = 0;

	//Delete an edge
	virtual void deleteEdge(int v1, int v2) = 0;

	//Determine if an edge is in the graph
	//Return true if edge i,j has non-zero weight
	virtual bool isEdge(int i, int j) = 0;

	//Return an edge's weight
	//Return the weight of edge i,j or zero
	virtual int weight(int v1, int v2) = 0;

	//Get and Set the mark value for a vertex
	virtual int getMark(int v) = 0;
	virtual void setMark(int v, int val) = 0;

	
};