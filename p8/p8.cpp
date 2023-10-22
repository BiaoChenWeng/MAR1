#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>



// Introduce más librerías si son necesarias
using namespace std;
using lli = long long int;
bool resuelveCaso();
struct tCajas {
	lli tiempo_tarda;
	int num_caja;

	tCajas(lli tiempo = 0, int num = -1) :tiempo_tarda(tiempo), num_caja(num) {}
	bool operator <(tCajas const& other)const {
		if (this->tiempo_tarda != other.tiempo_tarda)
			return this->tiempo_tarda > other.tiempo_tarda;
		return this->num_caja > other.num_caja;
	}
	bool operator==(tCajas const& other)const {
		return this->num_caja == other.num_caja && this->tiempo_tarda == other.tiempo_tarda;
	}
	bool operator <=(tCajas const& other)const {
		return *this < other || *this == other;
	}
	bool operator >(tCajas const& other)const {
		return !(*this <= other);
	}
};

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

int caja_designado(priority_queue<tCajas>& q, queue<int>& cola) {	
	vector<lli>tiempo_caja(q.size(),0);
	int num_caja;
	while (!cola.empty()) { 
		num_caja= q.top().num_caja;
		tiempo_caja[num_caja] += cola.front();
		q.push({tiempo_caja[num_caja],num_caja});
		cola.pop();
		q.pop();
	}
	return q.top().num_caja+1;
}
bool resuelveCaso() {
	int caja;
	int cliente;
	cin >> caja >> cliente;
	if (caja == 0 && cliente == 0)
		return false;
	queue<int>clientes;
	int val;
	priority_queue<tCajas>q;
	
	for (int i = 0; i < caja; i++) {
		q.push({0,i});
	}
	for (int i = 0; i < cliente; i++) {
		cin >> val;
		clientes.push(val);
	}
	int ans = caja_designado(q, clientes);
	cout << ans << endl;

	return true;
}

