#include <iostream>
#include <fstream>
#include <vector>
#include "bintree_eda.h"
// Introduce más librerías si son necesarias
using namespace std;
void resuelveCaso();




int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
using tPair = pair<int, bool>;
tPair resulevaCaso(bintree<char>arbol) {
    if (arbol.empty()) 
        return { 0,true };    
    else {
        tPair izq = resulevaCaso(arbol.left());
        tPair der = resulevaCaso(arbol.right());
        tPair ans = { max(izq.first, der.first) + 1,izq.second && der.second && (abs(izq.first - der.first) <= 1) };
        return ans;
    }
}

// configuración, y escribiendo la respuesta
void resuelveCaso() {
    string result = (resulevaCaso(leerArbol('.')).second) ? "SI\n" : ("NO\n");
    cout <<  result;
}