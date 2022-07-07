#include "aresta.h"
#include "no.h"
#include <iostream>
#include <set>
#include <unordered_map>

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

void Aresta::fechoTransitivoDireto(set<int>* ftd, Grafo* g){
    if(!ftd->count(this->id)){
        g->mapa[this->id]->fechoTransitivoDireto(ftd, g);
    }
    if(proxAresta != nullptr){
        proxAresta->fechoTransitivoDireto(ftd, g);
    }
}

bool Aresta::fechoTransitivoIndireto(int id, Grafo* g, set<int>* fti, set<int>* nosVisitados){
    if(this->id == id)
        return true;
    if(!nosVisitados->count(this->id))
        return g->mapa[this->id]->fechoTransitivoIndireto(id, g, fti, nosVisitados);
    if(this->proxAresta != nullptr)
        return proxAresta->fechoTransitivoIndireto(id, g, fti, nosVisitados);
    else
        return false;
}