#include "Floyd.h"
#include "no.h"
#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <limits.h>
#include <math.h>

Floyd::Floyd(){}
Floyd::~Floyd(){}

void Floyd::caminhoMinimo(Grafo *g,int noI,int noAlvo){
    No* ver = g->procurarNo(noAlvo);
    if(ver->getGrauEntrada() == 0)
    cout << endl << "Nao existe caminho entre o verice " << noI << "e o vertice " << noAlvo << endl;

    int n = g->getOrdem();
    int **F; //alocando matriz de custos
    F = new int *[n];
    for(int i = 0; i<n; i++)
    F[i] = new int[n];

    for(int i=0;i<n;i++){
        for(int j = 0; j<n;j++){
            if(i==j)
            F[i][j] = 0;
            else
            F[i][j] = INFINITY;
        }
    }
for(auto i = g->nosGrafo.begin(); i != g->nosGrafo.end(); i++){
    No* auxI = *i;
    for(auto j = auxI->ListAdj.begin(); j != auxI->ListAdj.end();j++){
        No* auxJ = g->procurarNo(*j);
        Aresta* arestaAux = g->existeAresta(auxI->getId(),auxJ->getId());
        F[auxI->getId()][auxJ->getId()] = arestaAux->getPeso();
        
    }
}
    int ant, dep, soma, teste; // variaveis para auxiliar
    for(int k=0;k<n;k++){
        for(auto i = g->nosGrafo.begin(); i != g->nosGrafo.end(); i++){
            No *auxI = *i; 
            ant = auxI->getId(); // ant recebe i
            for(auto j = g->nosGrafo.begin(); j != g->nosGrafo.end(); j++){
                No *auxJ = *j;
                dep = auxJ->getId(); // dep recebe j
                if(ant != dep){ // se i != j, foi inicializado com 0
                    soma = F[ant][k] + F[k][dep]; 
                    teste = F[ant][dep]; // valor atual
                    if(soma < teste) // se a soma for menor que valor atual
                        F[ant][dep] = soma; // F[i][j] recebe soma
                }
            }
        }  
}
    if(F[noI][noAlvo] < INFINITY) // Se encontrou caminho entre os vertices inicial e alvo
        cout << endl << "Custo do caminho minimo: " << F[noI][noAlvo] << endl;
    else
        cout << endl << "Nao existe caminho entre o vertice " << noI << " e o vertice " << noAlvo << endl;
    
    delete F; // free memory
}