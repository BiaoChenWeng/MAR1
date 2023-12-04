#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<limits.h>
// Introduce más librerías si son necesarias
using namespace std;
//struct tEnlace {
//	int v;
//	int w;
//	int coste;
//	
//	tEnlace(int v,int w ,int c):v(v),w(w),coste(c){}
//
//	int desde()const{
//		return v;
//	}
//	int hasta()const{
//		return w;
//	}
//};

class tGrafoDir {
	int V;
	int A;
	vector<vector<pair<int, int>>>ady;// valor y coste
public:
	tGrafoDir(int v = 0) :V(v), A(0), ady(v) {}

	void ponArista(int v, int w, int coste) {
		if (v < 0 || v >= V || w < 0 || w >= V)
			throw std::domain_error("Vertice inexistente");
		++A;
		ady[v].push_back({ w,coste });

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
	int pos;
	int coste;
	tValor(int p, int c) :pos(p), coste(c) {

	}
	bool operator>(tValor const& other)const {
		return this->coste < other.coste;
	}
	bool operator== (tValor const& other)const {
		return this->coste == other.coste && this->pos == other.pos;
	}
	
};

class tPagina {
	vector<int>ant;
	vector<int>dist;
	int dest;
public:
	tPagina(vector<int>const &t):ant(t.size(),-1),dist(t.size(),INT_MAX),dest(0) {
	}
	void dj(vector<int>const& t, tGrafoDir const& g) {
		dest = t.size() - 1;
		ant[0] = 0;
		dist[0] = t[0];
		priority_queue<tValor, vector<tValor>, greater<tValor>>q;
		q.push({ 0,dist[0] });
		tValor value = { 0,0 };
		while (!q.empty()) {
			value = q.top();
			q.pop();
			for (auto x : g.getAdy(value.pos)) {
				if (dist[x.first] > dist[value.pos] + x.second + t[x.first]) {
					dist[x.first] = dist[value.pos] + x.second + t[x.first];
					ant[x.first] = value.pos;
					q.push({ x.first,dist[x.first] });
				}
			}

		}
	}
	bool posible() {
		return dist[dest] != INT_MAX;
	}
	int ans() {
		return dist[dest];
	}

};


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;
	vector<int>tiempo(entrada);
	for (int& k : tiempo)
		cin >> k;
	int k;
	int a, b, c;
	cin >> k;
	tGrafoDir g(entrada);
	for (int i = 0; i < k; i++) {
		cin >> a >> b >> c;
		g.ponArista(a-1, b-1, c);
	}
	tPagina p(tiempo);
	p.dj(tiempo,g);
	if (p.posible()) {
		cout <<p.ans() <<"\n";
	}
	else {
		cout << "IMPOSIBLE\n";
	}
	return true;
}
