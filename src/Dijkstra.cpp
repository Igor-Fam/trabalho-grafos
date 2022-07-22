#include "Dijkstra.h"
#include "Grafo.h"
#include "no.h"
#include <iostream>
#include <limits.h>
#include <list>
#include <math.h>

using namespace std;
Dijkstra::Dijkstra() {}
Dijkstra::~Dijkstra() {}

list<int> Dijkstra::caminhoMinimo(Grafo *g, int noI, int noAlvo)
{

    No *ver = g->procurarNo(noAlvo);
    if (ver->getGrauEntrada() == 0)
    {
        cout << endl
             << "Nao existe caminho entre o vertice" << noI << "e o vertice" << noAlvo << endl;
        return caminho;
    }

    int *dist = new int[g->getOrdem()];
    int *ant = new int[g->getOrdem()];

    for (auto i = g->nosGrafo.begin(); i != g->nosGrafo.end(); i++)
    {

        No *aux = *i;
        abertos.push_back(aux);
        int id = aux->getId();
        dist[id] = INFINITY;
        ant[id] = -1;
    }

    dist[noI] = 0;

    for (int j = 0; j < (g->getOrdem() - 1); j++)
    {
        No *no1 = menorDist(dist);
        abertos.remove(no1);
         
        for (auto i = no1->ListAdj.begin(); i != no1->ListAdj.end(); i++)
        {
            Aresta *arestaAux = g->existeAresta(no1->getId(), *i);
            if (dist[*i] > (dist[no1->getId()] + arestaAux->getPeso()))
            {                                                         // custo de no2 maior que a soma da dist de no1 mais o peso da aresta
                dist[*i] = dist[no1->getId()] + arestaAux->getPeso(); // atualiza custo de no2
                ant[*i] = no1->getId();                               // indica o predecessor
            }
        }
    }

    if (dist[noAlvo] < INFINITY)
    {                                  // se houve caminho encontrado
        criaCaminho(noAlvo, ant, noI); // cria lista do menor caminho encontrado
        cout << endl
             << "Custo do caminho minimo: " << dist[noAlvo] << endl;
    }
    else // nao foi encontrado caminho entre os vertices
        cout << endl
             << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    delete dist; // free memory
    delete ant;  // free memory
    return caminho;
}

No *Dijkstra::menorDist(int dist[])
{
    No *id;
    int menor = INFINITY;
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
