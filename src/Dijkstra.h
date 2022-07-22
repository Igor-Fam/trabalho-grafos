#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "grafo.h"
#include "no.h"
#include <list>

class Dijkstra {
private:
    list<int> caminho;
    list<No*> abertos;
    No* menorDist(int dist[]); // busca vertice aberto com menor custo salvo
    void criaCaminho(int no, int ant[], int noI); // Busca nos predecessores para fazer o caminho
    
public:
    Dijkstra();
    ~Dijkstra();
    list<int> caminhoMinimo(Grafo *g, int noI, int noAlvo); //base do algoritimo
    
};
  
#endif //DIJKSTRA_H_INCLUDED