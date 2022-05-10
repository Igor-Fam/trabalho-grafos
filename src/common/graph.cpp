#include "graph.h"
#include <iostream>

using namespace std;

bool Graph::nodeExists(int id){
    return firstNode->nodeExists(id);
}

void Graph::addNode(int id, float weight){
    if(firstNode == nullptr){
        Node* newNode = new Node(id, weight);
        firstNode = newNode;
    } else if(firstNode->id == id){
        cout << "No ja existente!" << endl;
        return;
    } else if(id < firstNode->id){
        Node* newNode = new Node(id, weight);
        newNode->nextNode = firstNode;
        firstNode = newNode;
    } else {
        firstNode->addNode(id, weight);
    }
}

void Graph::addEdge(int id1, int id2, float weight){
    if(nodeExists(id2))
        firstNode->addEdge(id1, id2, weight);
    else
        cout << "No " << id2 << " nao existe!" << endl;
}

void Graph::printGraph(){
    if(firstNode == nullptr)
        cout << "Grafo vazio!" << endl;
    else
        firstNode->printEdgeList();
}