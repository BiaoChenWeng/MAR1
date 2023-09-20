#include <iostream>
#include <fstream>
#include <vector>
#include "TreeSet_AVL.h"

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



bool resuelveCaso() {

    int entrada;
    cin >> entrada;
    if (entrada ==0)
        return false;
    Set<int>s;
    int value;
    for (int i = 0; i < entrada; i++) {
        cin >> value;
        s.insert(value);
    }
    int k1, k2;
    cin >> k1 >> k2;
    vector<int>v;
    s.buscarEntre(k1, k2, v);
    for (const int &k : v) {
        cout << k<<" ";
    }
    cout << endl;

    return true;
}
