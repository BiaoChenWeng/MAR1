#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
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


class calculador {

    using tPair = pair<int,int>;
    int maximo;
    int num_op;
    int casos(int val,int opcion) {
        switch (opcion)
        {
        case 0:
            return (val + 1) % maximo;
        case 1:
            return (val * 2) % maximo;
        case 2: 
            return (val / 3);
        }
    }

    int bfs(int orig,int fin) {
        if (orig == fin)
            return 0;
        queue<int>q;
        int v,op;
        v = orig;
        vector<int>visit(maximo, -1);
        visit[orig] = 0;
        q.push(orig);
        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (int i = 0; i < num_op; i++) {
                op = casos(v, i);
                if (visit[op] == -1) {
                    visit[op] = visit[v]+1;
                    if (op == fin)
                        return visit[op];
                    q.push(op);
                }
            }
        }
        
        return visit[fin];
    }
public:
    calculador():maximo(10000),num_op(3){}
    int paso_hasta(int orig, int fin) {
        return bfs(orig, fin);
    }
};

bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!std::cin)  // fin de la entrada
        return false;
    int obje;
    cin >> obje;
    calculador c;
    cout <<c.paso_hasta(entrada, obje)<<"\n";

    return true;
}

