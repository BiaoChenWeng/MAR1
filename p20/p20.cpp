#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>

// Introduce más librerías si son necesarias
using namespace std;

class diGrafo {
    vector<vector<int>>grafo;
    int V;
    int A;
public:
    diGrafo(int v = 0) :A(0), V(v), grafo(v) {}
    void pon_arista(int ini, int fin) {
        grafo[ini].push_back(fin);

    }
    int getV() const {
        return V;
    }
    int getA() const {
        return A;
    }
    vector<int>const& getAdy(int i) const {
        return grafo[i];
    }
};
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

class juego {
    vector<bool>visit;
    int min_mov;
    void bfs(diGrafo const& g,int caras) {
        queue<pair<int,int>>q;// pos y nivel
        q.push({0,0});
        pair<int, int>value;
        visit[0] = true;
        int k;
        int n = g.getV();// tamaño del tablero 
        while (!q.empty() && min_mov==-1) {
            value = q.front();
            q.pop();
            k = min(n - 1, value.first + caras);
            for (int x = value.first+1; x <= k; x++) {
                if (x==n-1) {
                    this->min_mov = value.second + 1;
                }
                else if (!visit[x]) {
                    visit[x] = true;
                    if(g.getAdy(x).empty())
                        q.push({ x,value.second + 1 });
                    else {// escalera o serpiente
                        for (int const& ady : g.getAdy(x)) {
                            if (!visit[ady]) {
                                q.push({ ady,value.second + 1 });
                                visit[ady] = true;
                            }
                        }
                    }
                }
            }
        }


    }
public:
    juego(diGrafo const & g):min_mov(-1),visit(g.getV(),false){}

    void jugar(diGrafo const & g,int k) {
        bfs(g,k);
    }
    int getMin() {
        return this->min_mov;
    }
};

bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    int k, s, e;
    cin >> k >> s >> e;
    if (entrada==0 && k == 0 && s==0 && e==0)
        return false;

    diGrafo g(entrada*entrada);
    s += e;
    int a, b;
    for (int i = 0; i < s; i++) {
        cin >> a>>b;
        g.pon_arista(a-1, b-1);
    }
    juego j(g);
    j.jugar(g,k);
    cout << j.getMin()<<"\n";

    return true;
}
