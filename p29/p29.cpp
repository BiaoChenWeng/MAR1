#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
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

class kruskal {
	int coste;
	vector<bool>visit;
	ConjuntosDisjuntos c;
public:
	kruskal(GrafoValorado<int> const & g) :coste(0),c(g.V()){
		
		priority_queue<Arista<int>,vector<Arista<int>>,greater<>>q;
		auto a = g.aristas();
		for (auto v : g.aristas()) {
			q.push(v);
		}
		
		int v, w;
		while (!q.empty()) {
			auto a  = q.top();
			q.pop();
			v = a.uno();
			w = a.otro(v);
			if (!c.unidos(v, w)){
				c.unir(v, w);
				coste = max(a.valor(),coste);
			}

		}

	}

	bool getPosible() {
		return c.num_cjtos() == 1;
	}
	int getAns() {
		return coste;
	}

};


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	int k;
	cin >> k;
	int a, b, c;
	GrafoValorado<int>g(entrada);
	for (int i = 0; i < k; i++) {
		cin >> a >> b >> c;
		g.ponArista({a-1,b-1,c});
	}

	kruskal sol(g);
	if (sol.getPosible()) {
		cout << sol.getAns() << "\n";
	}
	else {
		cout << "Imposible\n";
	}


	return true;
}