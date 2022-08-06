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
    static int limiteInferior;
    static int limiteSuperior;
public:
    Cluster(){}
    Cluster(int noInicial_, Grafo* g);

    float getPesoVertices() const { return pesoVertices; }
    void setPesoVertices(float pesoVertices_) { pesoVertices = pesoVertices_; }

    float getPesoArestas() const { return pesoArestas; }
    void setPesoArestas(float pesoArestas_) { pesoArestas = pesoArestas_; }

    static float getLimiteInferior() { return Cluster::limiteInferior; }
    static void setLimiteInferior(float limiteInferior) { Cluster::limiteInferior = limiteInferior; }

    static float getLimiteSuperior() { return Cluster::limiteSuperior; }
    static void setLimiteSuperior(float limiteSuperior) { Cluster::limiteSuperior = limiteSuperior; }
    
};

#endif