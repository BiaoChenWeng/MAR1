#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
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

class arboles_libres {

	vector<bool>visit;
	vector<int>ant;
	bool ciclico;

	void dfs(Grafo const& g, int v) {
		visit[v] = true;
		for (const int& x : g.ady(v)) {
			if (!visit[x]) {
				ant[x] = v;
				dfs(g, x);
			}
			else if (ant[v]!= x) {
				ciclico = true;
				return;
			}
		}
	}

public:
	arboles_libres(const Grafo& g) :visit(g.V(), false), ant(g.V(), -1), ciclico(false) {}
	bool es_conexo() {
		for (bool x : visit) {
			if (!x)
				return false;
		}
		return true;
	}
	bool es_ciclico() {
		return this->ciclico;
	}
	bool arboles_libre(const Grafo& g) {
		ant[0] = 0;
		dfs(g, 0);

		return es_conexo() && !es_ciclico();
	}


};

bool resuelveCaso() {
	Grafo g(cin);
	if (!cin) {
		return false;
	}
	arboles_libres a(g);
	string ans = (a.arboles_libre(g)) ? "SI\n" : "NO\n";
	cout << ans;

	return true;
}

