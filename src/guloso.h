#ifndef GULOSO_H
#define GULOSO_H

#include "cluster.h"
#include "aresta.h"
#include "grafo.h"
#include <chrono>

using relogio_t = std::chrono::high_resolution_clock;
using tempo_t  = relogio_t::time_point;
using namespace std;

class Guloso
{
private:
    Grafo* g;
    Aresta* candidatos;
    Cluster** clusters;
    float valorSolucao;
    float tempo;
    int numArestas;
    int numClusters;
    int numVert;
    int *vertCont;
    void preencheClusters(int *clusterVertice, int numeroVertices, int *idsInvalidos, int idInvalidoCont, string nomeArquivo, tempo_t start);
    void salvaResultado(string nomeArquivo);
    double getQualidadeSolucao();
    bool verificaSolucaoViavel(int numeroVertices);
public:
    Guloso(int numeroClusters, float limiteInferior, float limiteSuperior, int numeroVertices, Grafo *g, int numArestas, string nomeArquivo);
    Guloso(int numeroClusters, float limiteInferior [], float limiteSuperior [], int numeroVertices, Grafo *g, int numArestas, string nomeArquivo);
};

#endif