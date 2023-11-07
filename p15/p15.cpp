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
const std::vector<pair<int, int>> m = { {1, 0}, { -1,0 }, { 0,1 }, { 0,-1 } };

pair<int,int> trozo_mayor(const vector<vector<char>>& mapa, unordered_map<int, unordered_set<int>>& posiciones) {
    queue<pair<int,int>>q;
    pair<int, int> ans = {0,0};
    int count;
    pair<int,int>pos;
    int op;
    while (!posiciones.empty() ) {
        auto it = posiciones.begin();
        q.push({it->first,*it->second.begin()});
        if (it->second.size() == 1) {
            posiciones.erase(it);
        }
        else {
            it->second.erase(q.front().second);
        }
        count = 1;
        while (!q.empty()) {
            pos= q.front();            
            q.pop();
            for (int i = 0; i < m.size(); i++) {
                auto it = posiciones.find(pos.first + m[i].first);
                if (it!= posiciones.end()) {
                    if (it->second.erase(pos.second + m[i].second)==1) {
                        count++;
                        q.push({pos.first+m[i].first,pos.second+m[i].second});
                        if (it->second.empty())
                            posiciones.erase(it);
                    }
                    
                }
            }
        }
        ans.second = max(ans.second, count);
        ans.first++;
    }
    return ans;

}


bool resuelveCaso() {
    int entrada;
    cin >> entrada;
    if (!std::cin)  // fin de la entrada
        return false;
    int col;
    cin >> col;
    char val;
    unordered_map<int, unordered_set<int>>s;
    vector<vector<char>>v(entrada, vector<char>(col));
    for (int i = 0; i < entrada; i++) {
        for (int j = 0; j < col; j++) {
            cin >> val;
            v[i][j]=val;
            if (val == '#')
                s[i].insert(j);
        }
    }

    pair<int,int>ans = trozo_mayor(v, s);
    cout <<ans.first<<" "<<ans.second << "\n";
    return true;
}

