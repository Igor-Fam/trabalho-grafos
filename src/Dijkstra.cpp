#include "Dijkstra.h"
#include "Grafo.h"
#include "no.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <math.h>

using namespace std;
Dijkstra::Dijkstra(Grafo* g) {
    for (int i = 0; i < g->getOrdem()-1; i++)
        {
            dist[i] = INT_MAX/2;
        }
}
Dijkstra::~Dijkstra() {}

list<int> Dijkstra::caminhoMinimo(Grafo *g, int noI, int noAlvo)
{
    No* noInicial = g->procurarNo(noI);
    noInicial->PreencheDist(this->dist, g->getOrdem(), g);
    No* proximoCaminho = menorDist(dist);
    caminho.push_back(proximoCaminho->getId());
    if(noI == noAlvo)
    {
        return this->caminho;
    }
    caminhoMinimo(g, proximoCaminho->getId(), noAlvo);

}

No *Dijkstra::menorDist(unsigned int dist[])
{
    No *id;
    int menor = INT_MAX/2;
    for (auto i = abertos.begin(); i != abertos.end(); i++)
    {

        No *aux = *i;
        if (dist[aux->getId()] < menor)
        {
            menor = dist[aux->getId()];
            id = aux;
        }
    }
    return id;
}

void Dijkstra::criaCaminho(int noA, int ant[], int noI)
{
    if (noA != noI)
    {
        caminho.push_front(noA);
        int aux = ant[noA];
        criaCaminho(aux, ant, noI);
    }
    else
        caminho.push_front(noI);
}
