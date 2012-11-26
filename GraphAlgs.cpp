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
	// Shortest distance traveled
	double distance = 0;
	// Order of nodes visited
	std::vector<NodeID> tour;
	std::vector<NodeID> empty;
	std::vector<NodeID> bestTour;
	
	// Sets the NodeIDs to values 0 to n-1
	for(unsigned int i = 0; i < G->size(); i++){
		tour.push_back(i);
	}

	// Calculate the first tour to set distance
	for(unsigned int i = 0; i < tour.size(); i++){
		if(i == G->size() - 1){
			distance += G->weight(i, 0);
		}
		else{
			distance += G->weight(i, i+1);
		}
	}
	bestTour.operator=(tour);

	std::pair<std::vector<NodeID>, EdgeWeight> kittens;
	kittens = permute(tour, empty, G, distance, bestTour);
	return kittens;
}

std::pair<std::vector<NodeID>, EdgeWeight> permute(std::vector<NodeID> full, std::vector<NodeID> empty, Graph* G, double distance, std::vector<NodeID> bestTour){
	std::pair<std::vector<NodeID>, EdgeWeight> panda;
	if(full.size() == 0){
		double length = 0;
		for(int i = 0; i < empty.size(); i++){
			if(i == empty.size()-1){
				length += G->weight(empty.at(i), empty.at(0));
				if(length < distance){
					distance = length;
					bestTour.operator=(empty);
				}
				panda.first = bestTour;
				panda.second = distance;
				return panda;
			}
			else if(distance < length){
				panda.first = bestTour;
				panda.second = distance;
				return panda;
			}
			else{
				length += G->weight(empty.at(i), empty.at(i+1));
			}
		}
	}
	else{
		for(int i = 0; i < full.size(); i++){
			std::vector<NodeID> temp(full);
			empty.push_back(full.at(i));
			panda;
			full.erase(full.begin() + i);
			panda.operator=(permute(full, empty, G, distance, bestTour));

			full.operator=(temp);
			empty.pop_back();
			return panda;
		}
	}
}