#include "guloso.h"
#include "cluster.h"
#include <iostream>

using namespace std;

Guloso::Guloso(int numeroClusters, float limiteInferior, float limiteSuperior){
    clusters = new Cluster[numeroClusters];
    Cluster::setLimiteInferior(limiteInferior);
    Cluster::setLimiteSuperior(limiteSuperior);
}