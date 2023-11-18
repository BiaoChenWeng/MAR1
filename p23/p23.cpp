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
	vector<vector<pair<int, int>>>ady;// coste y valor
public:
	tGrafo(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w, int coste) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ coste,w});
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

class puentes {
	vector<bool>visit;

	pair<bool, int> bfs(tGrafo const & g) {
		priority_queue<pair<int,int>,vector<pair<int, int>>,greater<>>q;
		q.push({ 0,0 });
		int visitados= 0;
		pair <int, int>aux;
		int coste = 0;
		while (visitados<visit.size() &&!q.empty()) {
			aux = q.top();
			q.pop();
			if (!visit[aux.second]) {
				coste += aux.first;
				visitados++;
				visit[aux.second] = true;
				for (auto x : g.getAdy(aux.second)) {
					if (!visit[x.second]) {
						q.push(x);
					}
				}
			}
		}
		return { visitados == visit.size() , coste };
	}

public:

	puentes(tGrafo const & g) :visit(g.getV(),false){

	}
	pair<bool, int>coste_minimo(tGrafo const & g) {
		
		if (g.getV() > g.getA()+1) {
			return { false,0 };
		}
		return bfs(g);
		

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
	int a, b, coste;
	for (int i = 0; i < k; i++) {
		cin >> a >> b >> coste;
		g.ponArista(a - 1, b - 1, coste);
	}
	puentes p(g);
	pair<bool, int>ans = p.coste_minimo(g);
	if (ans.first) {
		cout << ans.second << "\n";
	}
	else {
		cout << "No hay puentes suficientes\n";
	}


	return true;
}
