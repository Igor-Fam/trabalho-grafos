#include "cluster.h"
#include "grafo.h"
#include <iostream>

using namespace std;

Cluster::Cluster(int noInicial_, Grafo* g, float limiteInferior, float limiteSuperior){
    noInicial = g->getNo(noInicial_);
    this->limiteInferior = limiteInferior;
    this->limiteSuperior = limiteSuperior;
}