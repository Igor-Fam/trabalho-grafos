#include <iostream>
#include <set>
#include <unordered_map>
#include "no.h"
#include "aresta.h"

using namespace std;

No::No(int id, int id_insercao, float peso)
{
    this->id = id;
    this->peso = peso;
    this->primeiraAresta = nullptr;
    this->proxNo = nullptr;
    this->grau = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->id_insercao = id_insercao;
}

bool No::noExiste(int id)
{
    if (this->id != id && this->proxNo == nullptr)
        return false;
    if (this->id == id)
        return true;
    return proxNo->noExiste(id);
}

bool No::addAresta(int id1, int id2, int arestas_inseridas, float peso)
{
    
    // cout << id1 << " " << id2 << " " << arestas_inseridas << endl;
    if (this->id == id1)
    {
        if (primeiraAresta == nullptr)
        {
            Aresta *newAresta = new Aresta(this->id,id2, peso);
            primeiraAresta = newAresta;
            primeiraAresta->setId_insercao(arestas_inseridas);
            return true;
        }
        else if (primeiraAresta->id == id2)
        {
            // cout << "Aresta ja existente!" << endl;
            return false;
        }
        else if (id2 < primeiraAresta->id)
        {
            Aresta *temp = new Aresta(id2, peso);
            temp->proxAresta = primeiraAresta;
            primeiraAresta = temp;
            primeiraAresta->setId_insercao(arestas_inseridas);
            return true;
        }
        else
        {
            primeiraAresta->addAresta(id2, arestas_inseridas, peso);
            return true;
        }
    }
    else
    {
        if (proxNo == nullptr)
        {
            cout << "No " << id1 << " nao existe!";
            return false;
        }
        return proxNo->addAresta(id1, id2, arestas_inseridas, peso);
    }
}

No *No::addNo(int id, int &vert_inseridos, float peso)
{
    if (proxNo == nullptr)
    {
        No *newNo = new No(id, vert_inseridos, peso);
        proxNo = newNo;
        vert_inseridos += 1;
        return newNo;
    }
    else if (proxNo->id == id)
    {
        // cout << "No ja existente!" << endl;
        return nullptr;
    }
    else if (id < proxNo->id)
    {
        No *newNo = new No(id, vert_inseridos, peso);
        newNo->proxNo = proxNo;
        proxNo = newNo;
        vert_inseridos += 1;
        return newNo;
    }
    else
    {
        return proxNo->addNo(id, vert_inseridos, peso);
    }
}

void No::printArestas()
{
    cout << "Vertice: " << id;
    if (primeiraAresta == nullptr)
    {
        cout << " -|| ";
    }
    else
    {
        cout << " -> Vertices adjacentes: ";
        primeiraAresta->printList();
    }
    cout << endl;
    if (proxNo == nullptr)
        cout << "Vertice: -||" << endl;
    else
        proxNo->printArestas();
}

void No::fechoTransitivoDireto(set<int> *ftd, Grafo *g)
{
    ftd->insert(this->id);
    if (primeiraAresta != nullptr)
    {
        primeiraAresta->fechoTransitivoDireto(ftd, g);
    }
}

// bool No::fechoTransitivoIndireto(int id, Grafo* g, set<int>* fti){
//     set<int>* nosVisitados = new set<int>;
//     nosVisitados->insert(this->id);
//     if(primeiraAresta != nullptr){
//         if (primeiraAresta->fechoTransitivoIndireto(id, g, fti, nosVisitados)){
//             fti->insert(this->id);
//             return true;
//         } else {
//             return false;
//         }
//     } else {
//         return false;
//     }

// }

bool No::fechoTransitivoIndireto(int id, Grafo *g, set<int> *fti, set<int> *nosVisitados)
{
    // cout << "     No " << this->id << ": " << endl;
    nosVisitados->insert(this->id);
    if (primeiraAresta != nullptr)
    {
        if (primeiraAresta->fechoTransitivoIndireto(id, g, fti, nosVisitados))
        {
            fti->insert(this->id);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void No::adicionaAdjacencia(int id_alvo)
{
    this->ListAdj.push_back(id_alvo);
}

Aresta* No::retornaArestas()
{
    
}

void No::PreencheDist(unsigned int dist[], int tam, Grafo* g)
{
    list<No*> abertos;
    for (auto k = g->nosGrafo.begin(); k != g->nosGrafo.end(); k++)
    {
        No* auxiliar = *k;
        abertos.push_back(auxiliar);
    }
    abertos.remove(this);
    for (auto i = this->ListAdj.begin(); i != this->ListAdj.end(); i++)
    {
        Aresta* ArestaAuxiliar = g->existeAresta(this->getId(), *i);
        if(ArestaAuxiliar != nullptr)
        {
            float pesoAresta = ArestaAuxiliar->getPeso();
            if(pesoAresta < dist[*i])
            {
                dist[*i] = pesoAresta;
            }
        }
    }
    
}