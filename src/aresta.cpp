#include "aresta.h"
#include <iostream>

using namespace std;

Aresta::Aresta(int id, float peso){
    this->id = id;
    this->peso = peso;
    proxAresta = nullptr;
}

void Aresta::addAresta(int id, float peso){
    if(proxAresta == nullptr){
        Aresta* newAresta = new Aresta(id, peso);
        proxAresta = newAresta;
    } else if(proxAresta->id == id){
        //cout << "Aresta ja existente!" << endl;
        return;
    } else if(id < proxAresta->id){
        Aresta* newAresta = new Aresta(id, peso);
        newAresta->proxAresta = proxAresta;
        proxAresta = newAresta;
    } else {
        proxAresta->addAresta(id, peso);
    }
}

void Aresta::printList(){
    cout << id;
    if(proxAresta != nullptr){
        cout << " -> ";
        proxAresta->printList();
    } else {
        cout << " -|| ";
    }
}