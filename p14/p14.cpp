#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
// Introduce más librerías si son necesarias
using namespace std;
void resuelveCaso();




int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

int grupo_mayor(Grafo const& g) {
	int n = g.V();
	if (n < 2) {
		return n;
	}
	int ans = 1;
	queue<int>q;
	unordered_set<int>personas;
	for (int i = 0; i <n; i++) {
		personas.insert(i);
	}
	int size;
	int persona;
	int lider_grupo;
	unordered_map<int, unordered_set<int>>red;
	while (!personas.empty()) {
		lider_grupo= *personas.begin();
		q.push(lider_grupo);// metemos un random
		red[lider_grupo].insert(lider_grupo);// el mismo esta en su red de amigo
		personas.erase(lider_grupo);
		while (!q.empty()) {
			persona = q.front();
			q.pop();
			auto& it = g.ady(persona);
			for (const int& x : it) {
				if (personas.count(x) > 0) {
					//aun no esta en ninguna red o sido contabilizado
					q.push(x);
					red[lider_grupo].insert(x);
					personas.erase(x);
				}
			}
		}
		if (ans < red[lider_grupo].size()) {
			ans = red[lider_grupo].size();
		}

	}
	return ans;

}



void resuelveCaso() {
	Grafo g(cin, 1);
	int ans = grupo_mayor(g);
	cout << ans << "\n";
}
