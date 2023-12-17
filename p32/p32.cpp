#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<algorithm>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;


/*
Explicacion tenemos una series de horas y queremos el maximo numero de pelicula , ordenamos el vector con la hora de inicio al principio 
si le da tiempo de terminar la pelicula k-1 para ver la k el numero de pelicula aumenta, si no le da tiempo elige entre las dos el que acabe antes.

Justificacion suponiendo que la solucion este ordenado 

Suponiendo que x: voraz y: optimo sea sx y sy 
*/


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



struct tPeli {
	int ini;
	int fin;

	tPeli(int i=0, int f=0):ini(i),fin(f) {
	}
	bool operator<(tPeli const & other)const {
		if (ini != other.ini)
			return ini < other.ini;
		return fin < other.fin;
	}
};

inline istream& operator >>(istream& in, tPeli & p) {
	int hora;
	int min;
	char espacio;
	int fin;
	in >> hora >> espacio >> min>>fin;
	int ini = hora * 60 + min;
	p = tPeli(ini, fin+ini+10);
	return in;
}

int max_peli(vector<tPeli>&v) {
	if (v.empty())
		return 0;
	int ans = 1;
	int actual = 0;
	
	for (int i = 1; i < v.size();i++) {
		
		if (v[actual].fin <= v[i].ini) {// a terminado la pelicula y no hay problema
			ans++;
			actual = i;
		}
		else {
			// escoger que pelicula ver
			if (v[actual].fin > v[i].fin) {// si uno termina antes vemos ese
				actual = i;
			}
		}
	}
	return ans;
}

bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;
	
	vector<tPeli>v;

	tPeli k;
	for (int i = 0; i < entrada;i++) {
		cin >> k;
		v.push_back(k);
	}

	sort(v.begin(), v.end());

	cout << max_peli(v) << "\n";

	return true;
}