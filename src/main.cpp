#include <iostream>
#include "common/graph.h"

using namespace std;

int main()
{
    Graph* g = new Graph();
    while(true){
        cout << "Digite n para adicionar um no ou a para adicionar uma aresta" << endl;
        char option;
        cin >> option;
        if(option == 'n'){
            cout << "Digite o id do no" << endl;
            int id;
            cin >> id;
            g->addNode(id);
        }
        if(option == 'a'){
            cout << "Digite o id do primeiro no" << endl;
            int id1;
            cin >> id1;
            cout << "Digite o id do segundo no" << endl;
            int id2;
            cin >> id2;
            g->addEdge(id1, id2);
        }
        g->printGraph();
    }

    return 0;
}