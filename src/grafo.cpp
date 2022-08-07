#include "grafo.h"
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

bool Grafo::noExiste(int id){
    return primeiroNo->noExiste(id);
}

No* Grafo::auxAddNo(int id, float peso){
    if(primeiroNo == nullptr){
        No* newNo = new No(id, peso);
        primeiroNo = newNo;
        return primeiroNo;
    } else if(primeiroNo->id == id){
        // cout << "No ja existente!" << endl;
        return nullptr;
    } else if(id < primeiroNo->id){
        No* newNo = new No(id, peso);
        newNo->proxNo = primeiroNo;
        primeiroNo = newNo;
        return primeiroNo;
    } else {
        return primeiroNo->addNo(id, peso);
    }
}

void Grafo::addNo(int id, float peso){
    No* n = auxAddNo(id, peso);
    if(n != nullptr)
        mapa[id] = n;
}

void Grafo::addAresta(int id1, int id2, float peso){
    if(!(this->direcionado)){
        if(auxAddAresta(id1, id2, peso)){
            mapa.at(id1)->addGrau();
        }
        if(auxAddAresta(id2, id1, peso)){
            mapa.at(id2)->addGrau();
        }
    } else {
        auxAddAresta(id1, id2, peso);
        mapa.at(id1)->addGrauSaida();
        mapa.at(id2)->addGrauEntrada();
    }
        
}

bool Grafo::auxAddAresta(int id1, int id2, float peso){
    if(noExiste(id2))
        return primeiroNo->addAresta(id1, id2, peso);
    else
        cout << "No " << id2 << " nao existe!" << endl;
    return false;
}

void Grafo::printGrafo(){
    cout << endl;
    if(primeiroNo == nullptr)
        cout << "Grafo vazio!" << endl;
    else
        primeiroNo->printArestas();
}

void Grafo::printGrau(int id){
    cout << mapa.at(id)->getGrau() << endl << endl;
}

void Grafo::fechoTransitivoDireto(int id){
    if(!this->direcionado){
        cout << "Grafo nao direcionado nao possui fecho transitivo direto!" << endl;
        return;
    }
    set<int>* ftd = new set<int>;
    No * n = mapa[id];
    n->fechoTransitivoDireto(ftd, this);
    cout << "Fecho transitivo direto: " << endl;
    for(int x : *ftd){
        cout << x << " ";
    }
    cout << endl;

    delete ftd;
}

void Grafo::fechoTransitivoIndireto(int id){
    if(!this->direcionado){
        cout << "Grafo nao direcionado nao possui fecho transitivo indireto!" << endl;
        return;
    }
    set<int>* fti = new set<int>;
    set<int>* nosVisitados = new set<int>;
    for(auto it : mapa){
        *nosVisitados = {};
        //cout << endl << "* No " << it.first << ": " << endl;
        it.second->fechoTransitivoIndireto(id, this, fti, nosVisitados);
    }
    cout << "Fecho transitivo indireto: " << endl;
    for(int x : *fti){
        cout << x << " ";
    }
    cout << endl;

    delete fti, nosVisitados;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ordena um vetor de aresta com base no peso dessas
void Grafo::QuickSort(Aresta arestas[], int p, int q)
{
    if (p < q)
    {
        int j = particionamento(arestas, p, q);
        QuickSort(arestas, p, j - 1);
        QuickSort(arestas, j + 1, q);
    }
}

int Grafo::particionamento(Aresta arestas[], int p, int q)
{
    int i = p - 1, j = q;
    float v = arestas[q].peso;

    while (1)
    {
        while (arestas[++i].peso > v);
        while (v > arestas[--j].peso)
        {
            if (j == p)
                break;
        }
        if (i >= j)
            break;
        troca(&arestas[i], &arestas[j]);
    }

    troca(&arestas[i], &arestas[q]);

    return i;
}

void Grafo::troca(Aresta *a, Aresta *b)
{
    Aresta aux = *a;
    *a = *b;
    *b = aux;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aresta* Grafo::getArestas(int numArestas){
    Aresta *arestas = new Aresta[numArestas];
    int cont = 0;
    cout << numArestas << endl;
    for (No *v1 = primeiroNo; v1 != NULL; v1 = v1->proxNo)
    {
        Aresta *a = v1->primeiraAresta;
        while (a != NULL)
        {
            a->id_origem = v1->id;
            if (a->id_origem < a->id){
                //arestas[cont] = new Aresta(a->id_origem, a->id, a->peso);
                arestas[cont] = *a;
                cont++;
            }
            a = a->proxAresta;
        }
    }
    
    /*
    for (int b = 0; b < numArestas; b++){
        cout << (arestas[b]).id_origem << " " << arestas[b].id << " " << arestas[b].peso << endl;
    }
    */
    
    QuickSort(arestas, 0, cont - 1);

    /*
    for (int b = 0; b < numArestas; b++){
        cout << (arestas[b]).id_origem << " " << arestas[b].id << " " << arestas[b].peso << endl;
    }
    */

    return arestas;
}
