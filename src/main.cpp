#include <iostream>
#include <fstream>
#include "grafo.h"
#include "guloso.h"
#include <cstring>
#include <strings.h>

using namespace std;

void leHandover(ifstream &arq_ent, Grafo *g, Guloso *algoritmo){
    long long num_nos;
    long long num_clusters;
    double lim_inf = 0;
    double lim_sup;

    float pesoNo;
    float pesoAresta;

    arq_ent >> num_nos;
    arq_ent >> num_clusters;
    arq_ent >> lim_sup;

    for (long long i = 0; i < num_nos; i++)
    {
        arq_ent >> pesoNo;
        g->addNo(i, pesoNo);
    }

    int numArestas = 0;
    for (long long i = 0; i < num_nos; i++)
    {
        for (long long j = 0; j < num_nos; j++)
        {
            arq_ent >> pesoAresta;
            if (pesoAresta != 0){
                numArestas ++;
                g->addAresta(i, j, pesoAresta);
            }
        }
    }
    algoritmo = new Guloso(num_clusters, lim_inf, lim_sup, num_nos, g);

}

void le(ifstream &arq_ent, Grafo *g, Guloso *algoritmo){
    long long num_nos;
    long long num_clusters;

    int id_origem;
    int id_dest;
    float pesoAresta;
    float pesoNo;

    string lixo;

    arq_ent >> num_nos;
    arq_ent >> num_clusters;
    arq_ent >> lixo;

    float* lim_inf = new float[num_clusters];
    float* lim_sup = new float[num_clusters];

    for (long long i = 0; i < num_clusters; i++)
    {        
        arq_ent >> lim_inf [i];
        arq_ent >> lim_sup [i];
    }

    arq_ent >> lixo;

    for (long long i = 0; i < num_nos; i++){
        arq_ent >> pesoNo;
        g->addNo(i, pesoNo);
    }

    int numArestas = 0;
    while(!arq_ent.eof()){
        arq_ent >> id_origem;
        arq_ent >> id_dest;
        arq_ent >> pesoAresta;
        numArestas ++;
        g->addAresta(id_origem, id_dest, pesoAresta);
    }

    algoritmo = new Guloso(num_clusters, lim_inf, lim_sup, num_nos, g);

    delete [] lim_inf, lim_sup;
}

void leArquivoEntrada(ifstream &arq_ent, string tipo_instancia, Grafo *g, Guloso *algoritmo){
    string s = "Handover";
    if (strcasecmp(tipo_instancia.c_str(), s.c_str()) == 0){
        leHandover(arq_ent, g, algoritmo);
    }
    else{
        le(arq_ent, g, algoritmo);
    }
}

int main(int argc, char **argv)
{
    Grafo *g = new Grafo(false);
    Guloso *algoritmo;
    ifstream arq_ent, arq_saida;
    arq_ent.open(argv[1], ios::in);
    if (arq_ent.is_open()){
        leArquivoEntrada(arq_ent, argv[3], g, algoritmo);
        arq_ent.close();
    }
    else{
        cout << "Erro ao abrir arquivo de entrada" << endl;
    }
}