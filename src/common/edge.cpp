#include "edge.h"
#include <iostream>

using namespace std;

Edge::Edge(int id, float weight){
    this->id = id;
    this->weight = weight;
    nextEdge = nullptr;
}

void Edge::addEdge(int id, float weight){
    if(nextEdge == nullptr){
        Edge* newEdge = new Edge(id, weight);
        nextEdge = newEdge;
    } else if(nextEdge->id == id){
        cout << "Aresta ja existente!" << endl;
        return;
    } else if(id < nextEdge->id){
        Edge* newEdge = new Edge(id, weight);
        newEdge->nextEdge = nextEdge;
        nextEdge = newEdge;
    } else {
        nextEdge->addEdge(id, weight);
    }
}

void Edge::printList(){
    cout << id;
    if(nextEdge != nullptr){
        cout << " -> ";
        nextEdge->printList();
    } else {
        cout << " -|| ";
    }
}