#include "node.h"
#include <iostream>

using namespace std;

Node::Node(int id, float weight){
    this->id = id;
    this->weight = weight;
    this->firstEdge = nullptr;
    this->nextNode = nullptr;
}

bool Node::nodeExists(int id){
    if(this == nullptr)
        return false;
    if(this->id == id)
        return true;
    return nextNode->nodeExists(id);
}

void Node::addEdge(int id1, int id2, float weight){
    if(this->id == id1){
        if(firstEdge == nullptr){
            Edge* newEdge = new Edge(id2, weight);
            firstEdge = newEdge;
        } else if(firstEdge->id == id2){
            cout << "Aresta ja existente!" << endl;
            return;
        } else if(id2 < firstEdge->id){
            Edge* temp = new Edge(id2, weight);
            temp->nextEdge = firstEdge;
            firstEdge = temp;
        } else
            firstEdge->addEdge(id2, weight);
    } else {
        if(nextNode == nullptr){
            cout << "No " << id1 << " nao existe!";
        }
        nextNode->addEdge(id1, id2, weight);
    }
    
}

void Node::addNode(int id, float weight){
    if(nextNode == nullptr){
        Node* newNode = new Node(id, weight);
        nextNode = newNode;
    } else if(nextNode->id == id){
        cout << "No ja existente!" << endl;
        return;
    } else if(id < nextNode->id){
        Node* newNode = new Node(id, weight);
        newNode->nextNode = nextNode;
        nextNode = newNode;
    } else {
        nextNode->addNode(id, weight);
    }
}

void Node::printEdgeList(){
    cout << id;
    if(firstEdge == nullptr){
        cout << " -|| ";
    }
    else {
        cout << " -> ";
        firstEdge->printList();
    }
    cout << endl;
    if(nextNode == nullptr)
        cout << " -||" << endl;
    else
        nextNode->printEdgeList();
}