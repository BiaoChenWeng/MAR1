#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>



// Introduce más librerías si son necesarias
using namespace std;

bool resuelveCaso();
struct tPaciente {
	string nombre;
	int llegada;
	int gravedad;
	tPaciente() :nombre(""), llegada(0), gravedad(0) {}
	tPaciente(string n, int l, int g) :nombre(n), llegada(l), gravedad(g) {}
	bool operator <(const tPaciente& other)const {
		return (this->gravedad != other.gravedad) ? (this->gravedad < other.gravedad) : (this->llegada > other.llegada);

	}
	bool operator ==(const tPaciente& other)const {
		return (this->gravedad == other.gravedad) && this->llegada == other.llegada && this->nombre == other.nombre;
	}
	bool operator>(const tPaciente& other)const {
		return (this->gravedad != other.gravedad) ? (this->gravedad > other.gravedad) : (this->llegada < other.llegada);
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


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada == 0)
		return false;
	priority_queue<tPaciente>q;
	char orden;
	string nombre;
	int grave;

	for (int i = 0; i < entrada; i++) {
		cin >> orden;
		if (orden == 'I') {
			cin >> nombre >> grave;
			q.push({nombre,i,grave});
		}
		else {
			cout << q.top().nombre << endl;
			q.pop();
		}
	}


	cout << "---"<<endl;
	return true;
}
