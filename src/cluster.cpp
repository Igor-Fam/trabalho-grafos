#include "cluster.h"
#include "grafo.h"
#include <iostream>

using namespace std;

Cluster::Cluster(int noInicial_, Grafo* g){
    noInicial = g->getNo(noInicial_);
}