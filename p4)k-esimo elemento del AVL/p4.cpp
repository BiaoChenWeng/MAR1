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

/*
cosas añadida a TreeSet 
    metodos kesimo y kesimoBusqueda
    contructor añadido el int tam_i , hijos que hay en la izq 
    modificado void reequilibraDer(Link& a)  , se activa cuando se ha añadido un elemento a la izq , por lo que sumamos a los que le han crecido por la izq
    modificado las dos rotaciones para modificar tam_i dependiendo del caso
*/

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
    cin >> entrada;
    for (int i = 0; i < entrada; i++) {
        cin >> value;
        pair <bool,int>ans = s.kesimo(value);
        if (ans.first)cout << ans.second;
        else cout << "??";
        cout << endl;
    }
    cout <<"---" << endl;
    return true;
}
