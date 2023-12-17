#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<algorithm>

// Introduce más librerías si son necesarias
using namespace std;

/*
explicacion
O(nlogn) sort 
ordenamos las casas por su lado west 
si existe una casa , inicializamos la respuesta a 1 tunel como minimo , mientras que la casa
este dentro de los limites de la distancia más alejada de puede usar el tunel.

Demostracion 
Reduccion de diferencia 

Suponemos que tenemos un array de [0..n] siendo este la distancia que va desde la primera casa hasta el lado más oeste del ultimo 
si en la posicion k es 0 es que no hay tunel en caso contrario tiene un tunel 

Suponiendo x: voraz y:optimo , siendo sx y sy secuencia validas y con el mismo numero de tuneles . 

Si desde 0 hasta k-1 son iguales tenemos el siguiente caso :
1 sx[k]=1 y sy[k]=0 este caso no es posible porque el voraz siempre pone el tunel en la distancia más alejada posible 

2 sx[k]=0 y sy[k]=1 en este caso tenemos un sx[m]= 1 , siendo m > k , sabemos que en sy[k+1..m] no puede haber ningun 1 , en caso contrario dejaria de ser optima porque la voraz tiene un mejor coste  
entonces podemos cambiar el valor de sy[k] y sy[m] a la misma que el voraz debido no cambia el resultado final 


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



struct tCasa {
	int ini;
	int fin;
	tCasa(int i=0 ,int f=0):ini(i),fin(f) {

	}

	bool operator<(tCasa const & other) {
		if (ini != other.ini) {
			return ini < other.ini;
		}
		return fin < other.fin;
	}

};

int tuneles(vector<tCasa>&v ) {
	if (v.empty())
		return 0;
	sort(v.begin(), v.end());
	int ans=1;
	int ini = 0;
	
	for (int i = 1; i < v.size(); i++) {
		if (v[ini].fin <= v[i].ini) {
			ans++;
			ini = i;
		}
		if (v[ini].fin >v[i].fin) {
			ini = i;
		}
	}

	return ans;
}

bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada==0)
		return false;
	vector<tCasa>v;
	int a, f;
	for (int i = 0; i < entrada;i++) {
		cin >> a >> f;
		v.push_back({ a,f });
	}
	cout << tuneles(v)<<"\n";

	return true;
}