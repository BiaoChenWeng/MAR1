#include<queue>
#include <iostream>
#include <fstream>
#include <vector>
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
using lli = long long int;

struct tTareas {
    pair<bool, int>rep;// es o no tarea a repetir y el tiempo de repetir 
    lli start;
    lli end;
    tTareas(lli ini = 0, lli e = 0, pair<bool, int>r = { false, 0 }) :start(ini), end(e), rep(r) {}

    bool operator<(const tTareas& other)const {
        return this->start > other.start;
    }
};

bool conflicto_tarea(priority_queue<tTareas>& q, lli tiempo) {
    if (q.empty())
        return false;
    lli t = q.top().start;
    tTareas it;
    while (q.size() > 1 && t < tiempo) {
        it = q.top();
        q.pop();
        if (min(tiempo, it.end) > q.top().start) {
            return true;
        }
        if (it.rep.first) {
            it.start += it.rep.second;
            it.end += it.rep.second;
            q.push(it);
            it.end -= it.rep.second;// se resta para cambiar la hora mas tarde
        }
        t = it.end;

    }
    return false;
}


bool resuelveCaso() {
    int tarea_rep;
    int entrada;
    cin >> entrada;
    cin >> tarea_rep;
    //if (entrada == 0 && tarea_rep == 0)  // fin de la entrada // lo puse porque se puede ver entradas en udebug
    //    return false;
    if (!cin) {
        return false;
    }
    lli tiempo = 1000000;

    cin >> tiempo;
    priority_queue<tTareas>q;
    lli ini;
    lli fin;
    int rep;
    for (int i = 0; i < entrada; i++) {
        cin >> ini >> fin;
        q.push(tTareas(ini, fin));
    }
    for (int i = 0; i < tarea_rep; i++) {
        cin >> ini >> fin >> rep;
        q.push(tTareas(ini, fin, { true,rep }));
    }
    string ans = conflicto_tarea(q, tiempo) ? "SI" : "NO";
    cout << ans << endl;
    return true;
}

