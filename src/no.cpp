#include <iostream>
#include <set>
#include <unordered_map>
#include "no.h"

using namespace std;

No::No(int id, float peso){
    this->id = id;
    this->peso = peso;
    this->primeiraAresta = nullptr;
    this->proxNo = nullptr;
    this->grau = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
}

bool No::noExiste(int id){
    if(this->id != id && this->proxNo == nullptr)
        return false;
    if(this->id == id)
        return true;
    return proxNo->noExiste(id);
}

bool No::addAresta(int id1, int id2, float peso){
    if(this->id == id1){
        if(primeiraAresta == nullptr){
            Aresta* newAresta = new Aresta(id2, peso);
            primeiraAresta = newAresta;
            return true;
        } else if(primeiraAresta->id == id2){
            //cout << "Aresta ja existente!" << endl;
            return false;
        } else if(id2 < primeiraAresta->id){
            Aresta* temp = new Aresta(id2, peso);
            temp->proxAresta = primeiraAresta;
            primeiraAresta = temp;
            return true;
        } else {
            primeiraAresta->addAresta(id2, peso);
            return true;
        }
    } else {
        if(proxNo == nullptr){
            cout << "No " << id1 << " nao existe!";
            return false;
        }
        return proxNo->addAresta(id1, id2, peso);
    }
    
}

No* No::addNo(int id, float peso){
    if(proxNo == nullptr){
        No* newNo = new No(id, peso);
        proxNo = newNo;
        return newNo;
    } else if(proxNo->id == id){
        //cout << "No ja existente!" << endl;
        return nullptr;
    } else if(id < proxNo->id){
        No* newNo = new No(id, peso);
        newNo->proxNo = proxNo;
        proxNo = newNo;
        return newNo;
    } else {
        return proxNo->addNo(id, peso);
    }
}

void No::printArestas(){
    cout << id;
    if(primeiraAresta == nullptr){
        cout << " -|| ";
    }
    else {
        cout << " -> ";
        primeiraAresta->printList();
    }
    cout << endl;
    if(proxNo == nullptr)
        cout << " -||" << endl;
    else
        proxNo->printArestas();
}

void No::fechoTransitivoDireto(set<int>* ftd, Grafo* g){
    ftd->insert(this->id);
    if(primeiraAresta != nullptr){
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

bool No::fechoTransitivoIndireto(int id, Grafo* g, set<int>* fti, set<int>* nosVisitados){
    //cout << "     No " << this->id << ": " << endl;
    nosVisitados->insert(this->id);
    if(primeiraAresta != nullptr){
        if (primeiraAresta->fechoTransitivoIndireto(id, g, fti, nosVisitados)){
            fti->insert(this->id);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}