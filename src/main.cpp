#include <iostream>
#include <unordered_map>
#include "grafo.h"

using namespace std;

int main()
{
    Grafo* g = new Grafo();
    while(true){
        cout << "Digite n para adicionar um no, a para adicionar uma aresta e g para verificar grau de um no" << endl;
        char option;
        cin >> option;
        if(option == 'n'){
            cout << "Digite o id do no" << endl;
            int id;
            cin >> id;
            g->addNo(id);
        }
        if(option == 'a'){
            cout << "Digite o id do primeiro no" << endl;
            int id1;
            cin >> id1;
            cout << "Digite o id do segundo no" << endl;
            int id2;
            cin >> id2;
            g->addAresta(id1, id2, false);
        }
        if(option == 'g'){
            cout << "Digite o id do no" << endl;
            int id;
            cin >> id;
            g->printGrau(id);
        }
        g->printGrafo();
    }

    return 0;
}