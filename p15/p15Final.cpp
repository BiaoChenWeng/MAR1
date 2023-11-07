#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include<unordered_map>
#include <queue>
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
const std::vector<pair<int, int>> mov = { {1, 0}, { -1,0 }, { 0,1 }, { 0,-1 } };

class tManchas {
    vector<vector<bool>>visit;
    int num_manchas;
    int num_max;

    bool permitido(int x, int y) {
        return x >= 0 && x < visit.size() && y >= 0 && y < visit[0].size();
    }

    int dfs(const vector<vector<char>>& m,int x ,int y) {
        int tam = 1;
        visit[x][y] = true;
        for (auto mv : mov) {
            mv.first += x;
            mv.second += y;
            if (permitido(mv.first, mv.second) && m[mv.first][mv.second] == '#' && !visit[mv.first][mv.second])
                tam += dfs(m, mv.first, mv.second);
        }

        return tam;
    }
public:
    tManchas(const vector<vector<char>>& m):num_max(0),num_manchas(0), visit(m.size(), vector<bool>(m[0].size(), false)) {}
    int getManchas() {
        return this->num_manchas;
    }
    int getMax() {
        return this->num_max;
    }
    void solucion(const vector<vector<char>>&m) {
        int tam;
        for (int i = 0; i < m.size(); i++) {
            for (int j = 0; j < m[i].size(); j++) {
                if (m[i][j] == '#' && !visit[i][j]) {
                    tam = dfs(m, i, j);
                    this->num_manchas++;
                    this->num_max = max(num_max, tam);
                }
                
            }
        }
    }
};

bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!std::cin)  // fin de la entrada
        return false;
    int col;
    cin >> col;
    char val;
    vector<vector<char>>v(entrada, vector<char>(col));
    for (int i = 0; i < entrada; i++) {
        for (int j = 0; j < col; j++) {
            cin >> val;
            v[i][j] = val;
        }
    }
    tManchas m(v);
    m.solucion(v);
    cout << m.getManchas()<< " " << m.getMax()<< "\n";
    return true;
}

