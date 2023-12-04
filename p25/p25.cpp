#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <queue>
#include <unordered_set>
// Introduce más librerías si son necesarias
using namespace std;

class tGrafo {
	int V;
	int A;
	vector<vector<pair<int, int>>>ady;// coste y valor
public:
	tGrafo(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w, int coste) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ coste,w });
		ady[w].push_back({ coste,v });

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

struct tValor {
	int cost;
	int V;
	tValor(int c=0, int v=0) :cost(c), V(v) {}
	bool operator <(tValor const& other) const{
		return this->cost> other.cost;
	}
	bool operator == (tValor const& other) const{
		return this->cost == other.cost && this->V == other.V;
	}

};


class tRecorrido {
	const int INF = INT_MAX;
	int origen;
	int destino;
	vector<int>dist;
	vector<int>num_ant;
	bool relajar(const int &orig, const int&dest,int const& coste){
		bool ans = false;
		if (dist[dest] > coste) {
			dist[dest] = coste;
			num_ant[dest] = num_ant[orig];
			ans = true;
		}
		else if (dist[dest] == coste) {
			num_ant[dest] += num_ant[orig];
		}
		if (dest == destino)// llego al destino no necesita volver a buscarlo
			ans = false;
		return ans;
	}

	void dijkstra(tGrafo const & g) {
		dist[origen] = 0;
		num_ant[origen] = 1;
		priority_queue<tValor>q;
		q.push({0,origen});
		tValor value;
		while (!q.empty()) {
			value = q.top();
			q.pop();
			for (pair<int,int>const & x : g.getAdy(value.V)) {
				if (relajar(value.V, x.second, x.first+value.cost)) {
					q.push({dist[x.second],x.second});
				}
			}
		}
	}

public:
	tRecorrido(tGrafo const &g):dist(g.getV(), INF),num_ant(g.getV(),0){}
	
	void recorrido(tGrafo const& g) {
		origen= 0;
		destino = g.getV() - 1;
		dijkstra(g);
	}

	int ans() {
		return num_ant[destino];
	}
};

bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	tGrafo g(entrada);
	int calles;
	cin >> calles;
	int a, b, coste;
	for (int i = 0; i < calles; i++) {
		cin >> a >> b >> coste;
		g.ponArista(a - 1, b - 1, coste);
	}
	tRecorrido r(g);
	r.recorrido(g);

	cout << r.ans() << "\n";

	return true;
}