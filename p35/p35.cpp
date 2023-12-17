#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
// Introduce más librerías si son necesarias
using namespace std;

/*
Explicacion 
Coge la pila del mayor voltaje y lo junta con el menor, si es valido entonces lo pone junto y avanza ambos punteros.
Si no avanza a la siguiente pila con menor voltaje y repite el proceso

Justificacion 
Suponiendo que la solucion son pares de pilas ordenado por su carga , con (n,1) .. (n-1,2) si todas las parejas desde n hasta 1 son validas.
tenemos x:voraz y:optima 

Siendo sx sy secuencia de una solucion 

si desde 0 hasta k-1 son identico en k tenemos un sx[k]=(a,b) sy[k]=(a,c) siendo a>b y a>c tambien sabemos que b<c 

ya que estan ordenado por mayor podemos asegurar que si la pila a es usada entonces tiene que estar en la posicion k_decimo si es el k_decimo mayor 

casos : en la optima
1	b es descartada: si b es descartada porque no existe  otra pila aparte de a que pueda combinarlo , entonces descartamos c y colocamos b
2	b es usada en otra parte , entonces existe en la optima
	caso 1 : (b,m) caso imposible porque si b >m entonces en la voraz lo hubiera usado antes entre 0-(k-1)
	caso 2 : (n,b) sabiendo que c > b entonces n +c > n+b y si n +b es valido entonces n+c tambien lo es 

*/

void resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::ofstream out("datos.out");
	//auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
	int a;
	cin >> a;
	for (int i = 0; i < a; i++)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}



void resuelveCaso() {
	
	int entrada;
	int bateria;
	cin >> entrada >> bateria;
	vector<int>v(entrada);
	for (int& k : v)
		cin >> k;
	sort(v.begin(), v.end());
	int ans = 0;
	int i=0;
	int j=v.size()-1;
	while (i < j) {
		if (v[i] + v[j] >= bateria) {
			ans++;
			j--;
		}
		i++;
	}
	cout << ans << "\n";

}