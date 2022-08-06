#ifndef GULOSO_H
#define GULOSO_H

#include "cluster.h"
#include "aresta.h"
#include "grafo.h"

using namespace std;

class Guloso
{
private:
    Grafo* g;
    Aresta* candidatos;
    Cluster** clusters;
    float valorSolucao;
    float tempo;
public:
    Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g);
};

#endif