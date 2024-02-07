#include "Graphm.h"
#include <iostream>
#include <fstream>
#include <fstream>

const int range{ 6 };

using namespace std;


void AddEdgetoMST(unique_ptr<Graphm>& g, int x1, int x2, unique_ptr<Graphm>& mst)
{
	cout << "Add edge: " << x1 << " to " << x2 << endl;
	int w = g->weight(x1, x2);
	mst->setEdge(x1, x2, w);
}

void print(unique_ptr<Graphm>& G, ofstream& output)
{
	cout << endl;
	for (int row = 0; row < range; ++row)
	{
		for (int col = 0; col < range; col++)
		{
			cout << G->weight(row, col) << " ";
			output << G->weight(row, col) << " ";
		}
		cout << endl;
		if (row < range - 1)output << endl;
	}
}

int minVertex(unique_ptr<Graphm>& G, int* D) { // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i = 0; i < G->n(); i++)
		if (G->getMark(i) == UNVISITED) {
			v = i;
			break;
		}
	for (i++; i < G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
			v = i;
	return v;
}

//Prim's Algorithm
void Prim(unique_ptr<Graphm>& G, int* D, int s, unique_ptr<Graphm>& mst) {

	int* V = new int[G->n()];
	int i, w;
	for (int i = 0; i < G->n(); i++) // Initialize
	{
		D[i] = INFINITY;
		V[i] = s;
	}
	D[s] = 0;
	for (i = 0; i < G->n(); i++) { // Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, VISITED);
		if (v != s)
			AddEdgetoMST(G, V[v], v, mst); // Add edge to MST
		if (D[v] == INFINITY) return; // Unreachable vertices
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
			if (D[w] > G->weight(v, w)) {
				D[w] = G->weight(v, w); // Update distance
				V[w] = v; // Where it came from
			}
	}
}

void reset(unique_ptr<Graphm>& g)
{
	for (int i = 0; i < range; ++i)
		if (g->getMark(i) == VISITED) g->setMark(i, UNVISITED);
}

void process(unique_ptr<Graphm>& g, string fileName, int s)
{
	unique_ptr<Graphm> MST(new Graphm(range));
	int* D = new int[range];
	reset(g);
	Prim(g, D, s, MST);
	cout << endl;
	ofstream output(fileName);
	print(MST, output);
	output.close();
	delete[] D;
	MST.reset();
}

void read(unique_ptr<Graphm>& g, string fileName)
{
	ifstream input(fileName);

	int in{ 0 };
	for (int row = 0; row < range; ++row)
	{
		for (int col = 0; col < range; ++col)
		{
			input >> in;
			if (in != 0)
				g->setEdge(row, col, in);
		}
	}
	input.close();
}


int main()
{
	unique_ptr<Graphm> graph(new Graphm(range));

	read(graph,"original_matrix.txt");

	cout << "Number of vertices is " << graph->n() << endl;
	cout << "Number of edges is " << graph->e() << endl;

	ofstream output("original_matrix.txt");
	cout << "Matrix is: " << endl;
	print(graph, output);
	output.close();

	cout << "\nBegin MST 1 starting at Vertex 0\n";
	process(graph, "original_matrixMST1.txt", 0);
	cout << "End of MST 1\n";

	cout << "\nBegin MST 2 starting at Vertex 4\n";
	process(graph, "original_matrixMST2.txt", 4);
	cout << "End of MST 2\n";

	cout << "\nBegin MST 3 starting at Vertex 2\n";
	process(graph, "original_matrixMST3.txt", 2);
	cout << "End of MST 3\n\n";

	graph.reset();
	return 0;
}
