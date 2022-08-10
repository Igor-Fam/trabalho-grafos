#include "cluster.h"
#include "grafo.h"
#include <iostream>
#include <list>

using namespace std;

Cluster::Cluster(int noInicial_, Grafo* g, float limiteInferior, float limiteSuperior){
    No *v = g->getNo(noInicial_);
    nos[noInicial_] = v;
    this->limiteInferior = limiteInferior;
    this->limiteSuperior = limiteSuperior;
    this->pesoVertices = 0;
    this->pesoArestas = 0;
}