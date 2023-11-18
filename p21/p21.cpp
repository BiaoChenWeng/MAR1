#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Introduce más librerías si son necesarias
using namespace std;

bool resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("datos.out");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

const std::vector<pair<int, int>> mov = { {1, 0}, { -1,0 }, { 0,1 }, { 0,-1 },{1,1},{-1,1},{1,-1},{-1,-1} };


class tManchas {
	vector<vector<bool>>visit;
	vector<vector<pair<int, int>>>ant;
	vector<vector<int>>tamano;
	int num_max;

	bool permitido(int x, int y) {
		return x >= 0 && x < visit.size() && y >= 0 && y < visit[0].size();
	}

	int dfs(const vector<string>& m, int x, int y) {
		int tam = 1;
		visit[x][y] = true;
		for (auto mv : mov) {
			mv.first += x;
			mv.second += y;
			if (permitido(mv.first, mv.second) && m[mv.first][mv.second] == '#' && !visit[mv.first][mv.second]) {
				ant[mv.first][mv.second] = ant[x][y];
				tam += dfs(m, mv.first, mv.second);

			}
		}

		return tam;
	}
	pair<int, int> buscar(pair<int,int>v) {
		if (ant[v.first][v.second] != v) 
			ant[v.first][v.second] = buscar(ant[v.first][v.second]);
		return ant[v.first][v.second];
	}

	void unir(pair<int, int>a, pair<int, int>b) {
		pair<int, int>i = buscar(a);
		pair<int, int>j = buscar(b);
		if (i == j)return;
		if (tamano[i.first][i.second] > tamano[j.first][j.second]) {
			tamano[i.first][i.second] += tamano[j.first][j.second];
			ant[j.first][j.second] = i;
		}
		else {
			tamano[j.first][j.second] += tamano[i.first][i.second];
			ant[i.first][i.second] = j;
		}
	
	}

public:
	tManchas(const vector<string>& m) :num_max(0), visit(m.size(), vector<bool>(m[0].size(), false)), tamano(m.size(), vector<int>(m[0].size(), 1)),ant(m.size(),vector<pair<int,int>>(m[0].size())) {}

	int getMax() {
		return this->num_max;
	}
	void iniciar(const vector<string>& m) {
		int tam;
		for (int i = 0; i < m.size(); i++) 
			for (int j = 0; j < m[i].size(); j++) 
				if (m[i][j] == '#' && !visit[i][j]) {
					ant[i][j] = { i,j };
					tam = dfs(m, i, j);
					num_max = max(tam, num_max);
					tamano[i][j] = tam;
				}
	}

	void actualizar(int x,int y ) {
		if (visit[x][y])
			return;
		visit[x][y] = true;
		ant[x][y] = { x,y };
		tamano[x][y] = 1;
		for (pair<int,int> mv: mov) {
			mv.first += x;
			mv.second += y;
			if (permitido(mv.first, mv.second) && visit[mv.first][mv.second] ) {
				unir(mv, { x,y });
			}
		}
		pair<int,int>p= buscar({ x,y });
		num_max = max(num_max, tamano[p.first][p.second]);
	}
};


bool resuelveCaso() {
	int n, m;
	cin >> n >> m;

	if (!cin)
		return false;
	string row;
	getline(cin, row);
	
	vector<string>mapa(n);
	for (string& x : mapa) {
		getline(cin, x);
	}
	int k;
	cin >> k;
	int x, y;
	tManchas mancha(mapa);
	mancha.iniciar(mapa);
	cout << mancha.getMax() ;
	for (int i = 0; i < k; i++) {
		cin >> x >> y;
		mancha.actualizar(x - 1, y - 1);
		cout << " " << mancha.getMax();
	}
	cout << "\n";

	return true;
}