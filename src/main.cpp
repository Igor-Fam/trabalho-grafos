#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
// #include "aresta.h"
// #include "no.h"
#include "grafo.h"

using namespace std;

void separaDadoArqEnt(string &str, int &parametro)
{
    int pos = str.find(' ');
    parametro = stoi(str.substr(0, pos));
    str.erase(0, pos + 1);
    return;
}

bool comparaStrings(const char *str1, const char *str2)
{
    if (strcmp(str1, str2) == 0)
        return true;
    return false;
}

int main(int argc, char **argv)
{

    bool dir, peso_aresta, peso_vertice;
    bool invalido;

    for (int i = 3; i <= 5; i++)
    {
        if (argv[i] != NULL)
        {
            bool parametro;
            if (comparaStrings(argv[i], "0"))
                parametro = false;
            else if (comparaStrings(argv[i], "1"))
                parametro = true;
            else
                invalido = true;
            if (!invalido && i == 3)
                dir = parametro;
            else if (!invalido && i == 4)
                peso_aresta = parametro;

            else if (!invalido && i == 5)
                if (peso_aresta && parametro)
                {
                    cout << "Não é possível atribuir peso às arestas e aos vértices simultaneamente" << endl;
                    exit(1);
                }
                else
                    peso_vertice = parametro;
        }
        if (argv[i] == NULL || invalido)
        {
            cout << "Argumento passado pela linha de comando inválido ou faltante" << endl;
            exit(1);
        }
    }

    // cout << boolalpha << "dir: " << dir << endl;
    Grafo *g = new Grafo(dir);
    g->setPesoAresta(peso_aresta);

    ifstream arq_ent;
    arq_ent.open(argv[1], ios::in);
    if (arq_ent.is_open())
    {
        string str;

        getline(arq_ent, str);

        int num_vert = stoi(str);
        g->setOrdem(num_vert);

        while (!arq_ent.eof())
        {
            getline(arq_ent, str);

            int id1, id2, p_a = 0 /*, p_v = 0*/;

            separaDadoArqEnt(str, id1);
            separaDadoArqEnt(str, id2);
            if (peso_aresta)
            {
                separaDadoArqEnt(str, p_a);
            }

            /*
            else if (peso_vertice)
            {
                separaDadoArqEnt(str, p_v);
            }
            */

            g->addNo(id1);
            g->addNo(id2);
            g->addAresta(id1, id2, p_a);
        }

        // g->printGrafo();

        arq_ent.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de entrada" << endl;
        exit(1);
    }

    // Link para download do graphviz: https://graphviz.org/download/
    // Após o download:
    // No terminal: dot -Tyourformat(png, pdf...) your file -o output
    // Ex: dot -Tpng arquivo.dot -o arquivo.png

    // 1o parametro: grafo
    // 2o parametro: nome do arquivo .dot
    // 3o parametro: nome do grafo
    g->escreveArquivoDot(g, "arquivo.dot", "G");

    /*
    ofstream arq_saida;
    arq_saida.open(argv[2], ios::out);
    if (arq_saida.is_open())
    {
        arq_saida.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de saída" << endl;
        exit(1);
    }
    */

    g->printGrafo();
    g->fechoTransitivoIndireto(1);

    // Kruskal
    int num_vert;
    cout << "Numero de Vertices: ";
    cin >> num_vert;

    int subConj_vertices[num_vert];

    for (int i = 0; i < num_vert; i++)
    {
        cout << "Vertice " << i << ": ";
        cin >> subConj_vertices[i];
    }

    g->arvoreMinimaKruskal(num_vert, subConj_vertices, argv[2]);

    // Grafo* g = new Grafo();
    //  while(true){
    //      cout << "Digite n para adicionar um no, a para adicionar uma aresta e g para verificar grau de um no" << endl;
    //      char option;
    //      cin >> option;
    //      if(option == 'n'){
    //          cout << "Digite o id do no" << endl;
    //          int id;
    //          cin >> id;
    //          g->addNo(id);
    //      }
    //      if(option == 'a'){
    //          cout << "Digite o id do primeiro no" << endl;
    //          int id1;
    //          cin >> id1;
    //          cout << "Digite o id do segundo no" << endl;
    //          int id2;
    //          cin >> id2;
    //          g->addAresta(id1, id2, false);
    //      }
    //      if(option == 'g'){
    //          cout << "Digite o id do no" << endl;
    //          int id;
    //          cin >> id;
    //          g->printGrau(id);
    //      }
    //      g->printGrafo();
    //  }

    return 0;
}