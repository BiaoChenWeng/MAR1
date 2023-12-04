#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<limits.h>
#include "IndexPQ.h"
// Introduce más librerías si son necesarias
using namespace std;

struct tArista {
	int ini;
	int fin;
	int coste;
	tArista(int d,int h, int c) :ini(d),fin(h), coste(c) {

	}
	bool operator>(tArista const& other)const {
		return this->coste < other.coste;
	}
	bool operator<(tArista const &other)const {
		return this->coste > other.coste;
	}
	bool operator== (tArista const& other)const {
		return coste == other.coste && ini == other.ini && fin == other.fin;
	}
	int getDesde()const {
		return ini;
	}
	int getHasta()const {
		return fin;
	}
};

class tGrafoDir {
	int V;
	int A;
	vector<vector<tArista>>ady;// valor y coste
public:
	tGrafoDir(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(tArista a) {
		int v = a.ini;
		int w = a.fin;
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back(a);

	}
	vector<tArista> const& getAdy(int v) const {
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
	tGrafoDir inverso() const {
		tGrafoDir inv(V);
		for (int v = 0; v < V; ++v) {
			for (auto  x: ady[v]) {
				inv.ponArista({x.fin,x.ini,x.coste});
			}
		}
		return inv;
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

class tRecorrido{
	vector<int>ant_ida;
	vector<int>dist_ida;//ida
	vector<int>dist_reg;//regreso
	vector<int>ant_reg;
	int orig ;
	
	bool relajar(tArista const &a,vector<int>const & dist)const {
		int v = a.ini;
		int w = a.fin;
		int c = a.coste;
		
		return dist[w]>dist[v]+c;
	}
	

	void Dijkstra(int orig,tGrafoDir const & g, vector<int> & dist,vector<int>&ant) {
		IndexPQ<int>q(g.getV());
		dist[orig] = 0;
		ant[orig] = 0;
		q.update(orig, 0);
		while (!q.empty()) {
			auto t = q.top();
			q.pop();
			for (tArista const& x : g.getAdy(t.elem)) {
				if (relajar(x, dist)) {
					dist[x.fin] = dist[x.ini] + x.coste;
					ant[x.fin] = x.ini;
					q.update(x.fin, dist[x.fin]);
				}
			}

		}

	}
public:
	tRecorrido(tGrafoDir const& g,int tam,int o):ant_ida(tam,-1),dist_ida(tam,INT_MAX), dist_reg(tam,INT_MAX),ant_reg(tam,-1),orig(o){
		Dijkstra(orig, g, dist_ida, ant_ida);
		
		Dijkstra(orig, g.inverso(), dist_reg, ant_reg);

	}
	
	bool hayCaminoEntre(int i) const{
		return dist_ida[i] != INT_MAX && dist_reg[i] != INT_MAX;
	}
	int coste(int i ) const{
		return dist_ida[i] + dist_reg[i];
	}
	
};




bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	tGrafoDir g(entrada);
	int k;
	int a, b, c;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> a >> b >> c;
		g.ponArista({a-1,b-1,c});
	}
	int orig,dest;
	cin >> orig >> k;
	int total=0;
	bool ans = true;
	tRecorrido r(g,g.getV(),orig-1);
	for (int i = 0; i < k; i++) {
		cin >> dest;
		dest--;
		ans = ans && r.hayCaminoEntre(dest);
		if (ans) {
			total += r.coste(dest);
		}
	}
	if (!ans) {
		cout << "Imposible\n";
	}
	else {
		cout << total << "\n";
	}
	return true;
}
