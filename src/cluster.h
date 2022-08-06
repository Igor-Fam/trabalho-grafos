#ifndef CLUSTER_H
#define CLUSTER_H

#include "no.h"

using namespace std;

class No;
class Aresta;

class Cluster
{
private:
    No* noInicial;
    Aresta* listaArestas;
    int* vertices;
    float pesoVertices;
    float pesoArestas;
    float limiteInferior;
    float limiteSuperior;
public:
    Cluster(){}
    Cluster(int noInicial_, Grafo* g, float limiteInferior, float limiteSuperior);

    float getPesoVertices() const { return pesoVertices; }
    void setPesoVertices(float pesoVertices_) { pesoVertices = pesoVertices_; }

    float getPesoArestas() const { return pesoArestas; }
    void setPesoArestas(float pesoArestas_) { pesoArestas = pesoArestas_; }

    float getLimiteInferior() { return limiteInferior; }
    void setLimiteInferior(float limiteInferior) { this->limiteInferior = limiteInferior; }

    float getLimiteSuperior() { return limiteSuperior; }
    void setLimiteSuperior(float limiteSuperior) { this->limiteSuperior = limiteSuperior; }
    
};

#endif