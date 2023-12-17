#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<algorithm>
// Introduce m�s librer�as si son necesarias
using namespace std;

/*
justificacion 

Ordenamos los enemigos y aliados por su poder de ataque 
con lo mas fuertes antes , miramos si lo se puede vencer al mas fuerte enemigo con nuestra fuerza
si se puede ganamos una batalla ,pasamos al siguiente ejercito con la siguiente fuerza mayor,
en caso contrario enviamos a lo m�s d�biles a pelear con lo m�s fuerte , ya que en caso de que el equipo m�s d�bil puede vencer al enemigo m�s d�bil , entonces el equipo m�s fuerte tambi�n lo puede

Demostraci�n 
Reducci�n de diferencia 
x = voraz y= �ptimo , 

suponiendo que los enemigos est�n siempre ordenado por el m�s fuerte al principio
y sx , sy es la secuencia de valores de fuerza aliada con el que pelea 

suponiendo que son iguales hasta un cierto i , los valores sx[i]!= sy[i]
siendo j la posicion de beta tenemos los siguientes casos

caso 1 :sx[i] y sy[i] ganan ambos , entonces se puede cambiar , ya que sabemos que sx[i]>sy[i] , entonces sx[i] , puede ganar al enemigo en la posicion sx[j]
caso 2 : ambos pierden , podemos cambiarlo ya que no modifica el resultado final del ejercicio 

caso 3 : sx[i] pierde y sy[i] gana , este caso es imposible porque salen primero los aliados m�s fuertes si ganan , si ha perdido es porque no existe un beta tal que pueda ganar en la posicion i 

caso 4 : sx[i] gana y sy[i] pierde tenemos dos casos 
	sx[j] gana y sy[j] pierde , este caso es imposible porque significa que se puede mejorar la solucion optima
	sx[j] pierde y sy[j] gana , sabemos que sx[j] con el valor de sx[i] gana , vemos si sx[j] puede ganar en sx[i] , si gana la solucion optima dejaria de ser optima , si pierde se equilibra la victoria y derrotas





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
	vector<int>enemigo(entrada);
	vector<int>aliados(entrada);
	for (int& k : enemigo)
		cin >> k;
	for (int& k : aliados) 
		cin >> k;
	
	
	sort(enemigo.begin(), enemigo.end());
	sort(aliados.begin(), aliados.end());
	int ans = 0;
	int i = entrada - 1;
	int j = entrada - 1;
	while (i >= 0) {
		if (aliados[j] >= enemigo[i]) {
			j--; i--;
			ans++;
		}
		else {
			i--;
		}
	}
	
	cout << ans << "\n";
	return true;
}