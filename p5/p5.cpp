#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>



// Introduce más librerías si son necesarias
using namespace std;

bool resuelveCaso();


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
using lli = long long int;
lli sumar_minimo(priority_queue<lli, vector<lli>, greater<>>& q) {
	lli val1;
	lli val2;
	lli ans = 0;
	while (q.size() >= 2) {
		val1 = q.top();
		q.pop();
		val2 = q.top();
		q.pop();
		ans += val1 + val2;
		q.push(val1 + val2);
	}
	return ans;
}


bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (entrada == 0)
		return false;
	priority_queue<lli, vector<lli>, greater<>>q;
	int v;
	for (int i = 0; i < entrada; i++) {
		cin >> v;
		q.push(v);
	}
	lli ans = sumar_minimo(q);
	cout << ans << endl;
	return true;
}
