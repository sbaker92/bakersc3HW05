#include "Graph.h"
#include "MatrixGraph.h"

// Creates a matrix with all weights equal to 0; logic
// seen in marcusrm's MatrixGraph.cpp
MatrixGraph::MatrixGraph(unsigned num_nodes){
	for(int i = 0; i < num_nodes; i++){
		M.push_back(*new std::vector<EdgeWeight>());
		for(int j = 0; j < num_nodes; j++){
			M.at(i).push_back(0);
		}
	}
}

// The destructor! Because these are important and stuff.
// Borrowed from marcusrm's MatrixGraph.cpp
MatrixGraph::~MatrixGraph(){
	for(int i = 0; i < M.size(); i++){
		M.at(i).pop_back();
	}
}

// Adds a weighted edge between nodes u and v with the given weight
void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	if(u >= 0 && u < M.size() && v >= 0 && v < M.size() && u!= v && M.at(u).at(v) == 0 && M.at(v).at(u) == 0 && weight > 0){
		M.at(u).at(v) = weight;
		M.at(v).at(u) = weight;
		num_edges++;
	}
}

// Returns the weight of the edge between two nodes
EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const{
	if(u >= 0 && u < M.size() && v >= 0 && v < M.size()){
		return M.at(u).at(v);
	}
	else
		return 0;
}

// Returns a list of NodeID/EdgeWeight pairs adjacent to the edge;
// logic seen in marcusrm's MatrixGraph.cpp
std::list<NWPair> MatrixGraph::getAdj(NodeID u) const{
	if(u >= 0 && u < M.size()){
		EList* neighbors = new EList;
		for(int i = 0; i < M.at(u).size(); i++){
			NWPair cur(i, M.at(u).at(i));
			if(cur.second != 0)
				neighbors->push_back(cur);
		}

		return *neighbors;
	}
}

// Returns the number of nodes neighboring node u
unsigned MatrixGraph::degree(NodeID u) const{
	if(u >= 0 && u < M.size()){
		return getAdj(u).size();
	}
}

// Returns the number of nodes in the graph
unsigned MatrixGraph::size() const{
	return M.size();
}

// Returns the number of edges in the graph
unsigned MatrixGraph::numEdges() const{
	// For some reason, returning num_edges caused test 9 to
	// fail, so I switched to this because it works. I have
	// no idea why returning num_edges works for ListGraph, 
	// but not MatrixGraph.
	int edges = 0;
	for(int i = 0; i < M.size(); i++){
		for(int j = i+1; j < M.at(i).size(); j++){
			if(M.at(i).at(j) != 0)
				edges++;
		}
	}

	return edges;
}