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
struct sol {
    int menor;
    int mayor;
    int alt;
    bool valido;
};
sol arbolAVL(bintree<int>arbol) {
    if (arbol.empty()) 
        return {0,0,0,true };    
    else if (arbol.left().empty() && arbol.right().empty()) {
        return { arbol.root(),arbol.root() ,1,true };
    }
    else if (arbol.left().empty()) {
        sol der= arbolAVL(arbol.right());
        der.valido = der.valido&& arbol.root()<der.menor && der.alt++ < 2;
        der.menor = arbol.root();
        return der;
    }
    else if (arbol.right().empty()) {
        sol izq = arbolAVL(arbol.left());
        izq.valido = izq.valido &&izq.mayor<arbol.root() && izq.alt++ < 2;
        izq.mayor = arbol.root();
        return izq;
    }
    else {
        sol izq = arbolAVL(arbol.left());
        sol der = arbolAVL(arbol.right());
        sol ans = { izq.menor,der.mayor,max(izq.alt,der.alt) + 1,der.valido && izq.valido };
        ans.valido = ans.valido && izq.mayor < arbol.root() && arbol.root() < der.menor && abs(izq.alt - der.alt) < 2;
        return ans;
    }
}

// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> arbol = leerArbol(-1);

    sol ans = arbolAVL(arbol);
    string result = (ans.valido) ? "SI" : "NO";
    cout << result << endl;
}