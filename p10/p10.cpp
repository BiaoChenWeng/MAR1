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

vector<lli> tiempo_vuelo(priority_queue<lli>&cinco, priority_queue<lli>& uno,int drones) {
    vector<lli>result;
    int i = 0;
    lli u;
    lli c;
    vector<pair<bool,lli>>almacen(drones);// si es true va en cinco
    int num_drones = 0;
    int count;
    while (!cinco.empty() && !uno.empty()) {
        
        num_drones = min(cinco.size(), uno.size());
        num_drones = min(num_drones, drones);
        count = 0;
        result.push_back(0);
        for (int j = 0; j < num_drones; j++) {
            c = cinco.top();
            u = uno.top();
            cinco.pop();
            uno.pop();
            if (u > c) {
                result[i] += c;
                almacen[count++] = {false,u-c};
            }
            else if (u < c) {
                result[i] += u;
                almacen[count++] = {true,c-u};
            }
            else {
                result[i] += u;
            }
        }
        for (int j = 0; j < count;j++) {
            if (almacen[j].first) {
                cinco.push(almacen[j].second);
            }
            else {
                uno.push(almacen[j].second);
            }
        }
        i++;
    }


    return result;
}


bool resuelveCaso() {
    
    int entrada;
    cin >> entrada;
    if (!cin)  // fin de la entrada
        return false;
    int pila_b, pila_a;
    cin >> pila_a >> pila_b;
    priority_queue<lli>cinco;
    priority_queue<lli>uno;
    lli val;
    for (int i = 0; i < pila_a; i++) {
        cin >> val;
        cinco.push(val);
    }
    for (int i = 0; i < pila_b; i++) {
        cin >> val;
        uno.push(val);
    }
    vector<lli>v= tiempo_vuelo(cinco,uno,entrada);
    for (const lli& k : v)
        cout << k << " ";
    cout << endl;
    return true;
}

