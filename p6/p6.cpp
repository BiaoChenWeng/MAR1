#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>



// Introduce más librerías si son necesarias
using namespace std;
using lli =long long int;
bool resuelveCaso();
struct tUsuario {
	int id;
	int num_peticion;
	int period;
	tUsuario(int i = 0, int per = 0, int pet = 1) :id(i), num_peticion(pet), period(per) { }
	bool operator < (const tUsuario& other) const {	
		lli a=this->period*this->num_peticion;
		lli b = other.period * other.num_peticion;
		if (a!=b) {
			return a>b;
		}
		return this->id > other.id;
	}
	bool operator==(const tUsuario& other)const {
		return this->id == other.id && this->num_peticion == other.num_peticion && this->period == other.period;
	}
	bool operator<= (const tUsuario& b)const {
		return *this < b || *this == b;
	}
	bool operator>(const tUsuario& other)const {
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

void k_petition(int k, priority_queue<tUsuario>& q) {	
	for (int i = 0; i < k; i++) {
		auto &u = q.top();
		cout << u.id << "\n";
		
		q.push({ u.id,u.period,u.num_peticion + 1 });
		q.pop();
	}
}


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada == 0)
		return false;
	priority_queue<tUsuario>q;
	int id;
	int period;
	for (int i = 0; i < entrada; i++) {
		cin >> id >> period;
		q.push({ id,period,1 });
	}
	int k;
	cin >> k;
	k_petition(k, q);
	cout << "---\n" ;
	return true;
}