#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
// Introduce más librerías si son necesarias
using namespace std;

/*
justificacion

explicacion del código
inicializamos la respuesta a la cantidad de agujero que hay en la manguera , que es una cota superior
si hay un punto en donde el primer agujero puede ser tapado con la misma cinta hasta el siguiente agujero reducimos el numero de parche y miramos si ese mismo parche puede tapar el siguiente agujero 

Demostración
suponiendo x voraz y optimo , sx y sy son secuencia de este resultado con tamaño el numero de parche y dos argumentos el primer agujero hasta el ultimo 

suponiendo que desde 0 hasta k-1 tiene el mismo valor:

sabemos que en k sx[k]=(i,a) y sy[k]=(i,b), ya que se tiene que tapar el agujero
tambien sabemos que b< a , ya que si es posible taparlo el voraz lo tapara 
entonces la diferencia entre a y b estaria en s[k+1]

con esto sabemos que siendo sx[k+1] = (c,d) y sy[k+1]= (e,f) , c > e y d <= f
si cambiamos la solucion optima a la de voraz , entonces tenemos un sy[k+1] = (c,f)
entonces f-c < f-e , lo que es una distancia valida.

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

int parches(vector<int>const & v,int longitud ) {
	int ans = v.size();
	int ini = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i] - v[ini] <= longitud) {
			ans--;
		}
		else {
			ini = i;
		}
	}
	return ans;
}


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	int long_parche;
	cin >> long_parche;
	vector<int>v(entrada);
	for (int& k : v) {
		cin >> k;
	}
	cout << parches(v, long_parche)<<"\n";

	return true;
}