#include <iostream>
#include <fstream>
#include <vector>
#include "IndexPQ.h"
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


struct tPair {
    int prioridad;
    int llegada;
    tPair(int p=0,int l=0):prioridad(p), llegada(l) { }
    void operator +=(tPair const& other) {
        this->prioridad += other.prioridad;
        
    }
    bool operator >(tPair const& other)const {
        if (this->prioridad != other.prioridad) {
            return this->prioridad > other.prioridad;
        }
        return this->llegada > other.llegada;
    }
};


bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!cin) {
        return false;
    }
    IndexPQ<string,tPair> q;
    string command;
    string value;
    int num;
    vector<IndexPQ<string,tPair>::Par>v(3);
    for (int i = 0; i < entrada; i++) {
        cin >> command;
        if (command == "TC") {
            
            int s = min(q.size(), 3);
            
            for (int i = 0; i < s;i++) {
                v[i] = q.top();
                q.pop();
            }
            for (int i = 0; i < s; i++) {
                cout << i + 1 << " " << v[i].elem << endl;
                q.update(v[i].elem, v[i].prioridad);
            }
        }
        else {
            cin >>value>> num;
            if (command == "C") {
                q.updateAdd(value, { num,i });
            }
            else {
                q.updateAdd(value, { -num,i });
            }
            
        }
    }
    cout << "---\n";


    return true;
}

