#include <iostream>
#include <fstream>
#include <vector>


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

class tSumidero {
	bool es_sumidero=true;
	int sumidero = 0;
public:
	tSumidero(vector<vector<bool>> const & g) {
		sumidero = 0;
		int n = g.size();
		for (int i = 1; i < n; i++) {
			if (g[sumidero][i]) {
				sumidero = i;
			}
		}
		for (int i = 0; i < n && es_sumidero; i++) {
			if (i == sumidero)
				continue;
			es_sumidero = !g[sumidero][i] && g[i][sumidero];
		}

	}
	pair<bool, int>ans() const{
		return{ es_sumidero,sumidero };
	}

};


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	vector<vector<bool>>grafo(entrada,vector<bool>(entrada,false));
	int k;
	cin >> k;
	int a, b;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		grafo[a][b] = true;

	}
	tSumidero s(grafo);
	auto ans = s.ans();
	if (ans.first) {
		cout << "SI " << ans.second<<"\n";
	}
	else {
		cout << "NO\n";
	}
	return true;
}
