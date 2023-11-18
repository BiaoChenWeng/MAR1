#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>


// Introduce más librerías si son necesarias
using namespace std;

class tGrafo {
	int V;
	int A;
	vector<vector<pair<int, int>>>ady;// valor y coste
public:
	tGrafo(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w, int coste) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ w,coste });
		ady[w].push_back({ v,coste });

	}
	vector<pair<int, int>> const& getAdy(int v) const {
		if (v < 0 || v >= V)
			throw std::domain_error("Vertice inexistente");
		return ady[v];
	}
	int getA()const {
		return A;
	}
	int getV()const {
		return V;
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

class tCamino {
	//vector<bool>visit;

	/*void dfs(const tGrafo & g,int v,const int & dest, int const & tam, bool & fin) {
		visit[v] = true;
		for (pair<int,int>const &x : g.getAdy(v)) {
			if (!visit[x.first] && x.second >= tam) {
				if (x.first == dest) {
					fin = true;
					break;
				}
				else {
					dfs(g, x.first, dest, tam, fin);
				}

			}
		}

		visit[v] = false;
	}*/
	bool bfs(const tGrafo& g, int orig, const int& dest, int const& tam) {
		vector<bool>visit(g.getV(), false);
		queue<int>q;
		q.push(orig);
		visit[orig] = true;
		int v;
		while (!visit[dest] && !q.empty()) {
			v = q.front();
			q.pop();
			for (auto x : g.getAdy(v)) {
				if (!visit[x.first] && x.second >= tam) {
					visit[x.first] = true;
					if (x.first == dest)
						break;
					q.push(x.first);
				}
			}
		}


		return visit[dest];
	}
public:
	tCamino(){}
	//tCamino(tGrafo const& g) :visit(g.getV(), false){}
	bool pasa(tGrafo const& g,int orig,int dest,int tam) {
		
		return bfs(g, orig, dest, tam);
	}
};


bool resuelveCaso() {
	int entrada;
	cin >> entrada;

	if (!cin)
		return false;
	tGrafo g(entrada);

	int k;
	cin >> k;
	int orig, dest, ancho;
	for (int i = 0; i < k; i++) {
		cin >> orig >> dest >> ancho;
		g.ponArista(orig-1, dest-1, ancho);
	}


	tCamino c;
	cin >> k;
	string ans;
	for (int i = 0; i < k; i++) {
		cin >> orig >> dest >> ancho;
		ans = (c.pasa(g, orig-1, dest-1, ancho)) ? "SI\n" :"NO\n";
		cout << ans;
	}



	return true;
}
