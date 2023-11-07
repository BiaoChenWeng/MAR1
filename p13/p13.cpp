#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
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



bool arboles_libre(const Grafo & g) {
    int vertices = g.V();
    unordered_set<int>s;
    for (int i = 1; i < vertices; i++) {
        s.insert(i);
    }
    queue<int>q;
    q.push(0);
    unordered_map<int,int>m;
    int v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        auto &  it = g.ady(v);
        for (int const& x : it) {
            if (s.count(x) > 0) {
                q.push(x);
                s.erase(x);
     
                if (!m.insert({ x,v }).second) {
                    return false;
                }
            }
            else {
                // verifico si es el padre 
                if (m[v] != x) {
                    return false;
                }
            }
        }
    }
    return s.empty();
}

bool resuelveCaso() {
    Grafo g(cin );
    if (!cin) {
        return false;
    }

    string ans = (arboles_libre(g)) ? "SI\n" : "NO\n";
    cout << ans;

    return true;
}

