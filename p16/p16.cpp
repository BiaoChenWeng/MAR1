#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include "Grafo.h"
// Introduce más librerías si son necesarias
using namespace std;

bool resuelveCaso();
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

class noticias {
    vector<int>rumor;
    vector<int>ant;// este hace el trabajo de visit tmb
    void dfs(Grafo const & g,int v,int cabecera) {
        ant[v] = cabecera;// este es como poner visit=true 
        for (const int &x : g.ady(v)) {
            if (ant[x]==-1) {// no ha sido visitado
                rumor[cabecera]++;// aumentamos el contador 
                dfs(g, x, cabecera);
            }
        }
    }

public:
    noticias(){}
    noticias(Grafo const & g):ant(g.V(),-1),rumor(g.V(),1){}
    
    int esparcir_rumor(Grafo const & g, int i) {
        if (ant[i]==-1 ) 
            dfs(g, i, i);
        return rumor[ant[i]];
    }
};



bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!std::cin)  // fin de la entrada
        return false;
    int grupo;
    cin >> grupo;
    Grafo g(entrada);
    int j;
    int val;
    queue<int>q;
    
    for (int i = 0; i < grupo; i++) {
        cin >> j;
        for (; j > 0; j--) {
            cin >> val;
            q.push(val-1);
        }
        if (!q.empty()) {
            j = q.front();
            q.pop();
            while (!q.empty()) {
                g.ponArista(j, q.front());
                q.pop();
            }
        }
    }
    noticias n(g);
    for (int i = 0; i < g.V(); i++) {
        cout << n.esparcir_rumor(g, i)<<" ";
    }
    cout << "\n";
    return true;
}

