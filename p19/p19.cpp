#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>

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

class ordenar_tareas {
    vector<bool>visit;
    stack<int>sol;
    vector<bool>apilado;
    bool ciclo;
    void dfs(diGrafo const & g,int v) {
        
        apilado[v]=visit[v] = true;
        
        for (const int& x : g.getAdy(v)) {
            if(ciclo){
                return;
            }
            else if (!visit[x]) {
                dfs(g, x);
            }  
            else if(apilado[x]) {
                ciclo = true;
            }
        }
        apilado[v] = false;
        sol.push(v);
    }
public:
    ordenar_tareas():ciclo(false){}
    ordenar_tareas(diGrafo const & g): ciclo(false), visit(g.getV(), false) ,apilado(g.getV(),false){}

    stack<int>& resolver(diGrafo const & g) {
        int i = 0;
        for (int i = 0; i < g.getV() && !ciclo; i++) {
            if (!visit[i]) {
                dfs(g, i);
            }
        }      
        return this->sol;
    }
    bool posible() {
        return !this->ciclo;
    }

};


bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!std::cin)  // fin de la entrada
        return false;
    diGrafo g(entrada);
    int arista;
    cin >> arista;
    int a, b;
    for (int i = 0; i < arista; i++) {
        cin >> a >> b;
        g.pon_arista(a-1, b-1);
    }
    ordenar_tareas o(g);
    auto it = o.resolver(g);
    
    if (!o.posible()) {
        cout << "Imposible\n";
    }
    else {
        while (!it.empty()) {
            cout << it.top()+1<<" ";
            it.pop();
        }
        cout << "\n";
    }
    return true;
}

