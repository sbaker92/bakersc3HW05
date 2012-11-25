#include "GraphAlgs.h"

#include <algorithm>
using namespace std;

/*
 * Solves the Traveling Salesperson Problem: finding the shortest cycle through a graph that 
 * vists every node exactly once (with exception of the first node, which is repeated as the 
 * last node in the cycle.)
 * 
 * Return value: Return a pair, with the first element being a vector of length n listing the 
 *  order of the nodes in the cycle (do NOT list the start node twice), and the second element
 *  being the length of that path (do NOT forget to include the edge from the last node back to
 *  the start node in the total length.
 *
 * Preconditions: 
 *     G is undirected.
 *     Every pair of nodes u,v  (u != v) has an edge connecting the of weight > 0.
 */
std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){
	// Shortest distance travelled
	double distance = 0;
	// Current distance
	double curDis;
	// Order of nodes visited
	std::vector<NodeID> tour;
	std::vector<NodeID> curTour;
	
	// Sets the NodeIDs to values 0 to n-1
	for(unsigned int i = 0; i < G->size(); i++){
		curTour.push_back(i);
	}
	tour.operator=(curTour);

	// Calculate the first tour to set distance
	for(unsigned int i = 0; i < G->size(); i++){
		if(i == G->size() - 1){
			distance += G->weight(i, 0);
		}
		else{
			distance += G->weight(i, i+1);
		}
	}

	do{
		curDis = 0;
		for(unsigned int i = 0; i < G->size(); i++){
		if(i == G->size() - 1){
			curDis += G->weight(i, 0);
		}
		else{
			curDis += G->weight(i, i+1);
		}
		if(curDis < distance){
			distance = curDis;
			tour = curTour;
		}
	}
	}while(next_permutation(curTour.front(), curTour.back()));
	
	std::pair<std::vector<NodeID>, double> kittens(tour, distance);
	return kittens;
}