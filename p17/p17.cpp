#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include <queue>
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

class red {
    using tPair = pair<int, int>;
    int bfs(Grafo const& g, int nodo, int dist) {
        vector<bool>visit(g.V(), false);
        int tam = g.V()-1;
        visit[nodo] = true;
        queue<tPair>q;
        q.push({nodo,0});
        tPair val;
        while (tam != 0 && !q.empty()) {
            val = q.front();
            q.pop();
            if (val.second<dist) {
                for (const int& x : g.ady(val.first)) {
                    if (!visit[x]) {
                        tam--;
                        visit[x] = true;
                        q.push({ x,val.second + 1 });
                    }
                }
            }
        }
        return tam;
    }

public:
    red(){}

    int inaccesible(Grafo const & g, int nodo, int dist) {
        return bfs(g,nodo,dist);
    }

};



bool resuelveCaso() {
    Grafo g(cin,1);
    if (!std::cin)  // fin de la entrada
        return false;
    int i,nodo, dist;
    cin >> i;
    red r;

    for (; i > 0; i--) {
        cin >> nodo>> dist;
        cout << r.inaccesible(g, nodo - 1, dist)<<"\n";
    }
    cout << "---\n";

    return true;
}

