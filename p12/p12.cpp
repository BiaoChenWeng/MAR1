#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>



// Introduce más librerías si son necesarias
using namespace std;
using lli =long long int;
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

class carniceria {
private:
	priority_queue<int,vector<int>,greater<int>>mayor;// 1 2 3
	priority_queue<int,vector<int>,less<int>>menor;// 3 2 1

public:
	carniceria(){}
	int size() const {
		return mayor.size() + menor.size();
	}
	bool empty() const {
		return menor.empty() && mayor.empty() ;
	}
	void push(int value) {
		if (menor.empty()) {
			menor.push(value);
		}
		else {
			int mediana = menor.top();
			if (mediana < value) {
				mayor.push(value);
				if (mayor.size() > menor.size()) {
					menor.push(mayor.top());
					mayor.pop();
				}
			}
			else {
				menor.push(value);
				if (menor.size() - mayor.size() > 1) {
					mayor.push(menor.top());
					menor.pop();
				}
			}

		}

	}
	void pop_mediana() {
		if (!empty()) {
			menor.pop();
			if (menor.size() < mayor.size()) {
				menor.push(mayor.top());
				mayor.pop();
			}
		}

	}
	int mediana() {
		if (this->empty())
			return -1;
		return menor.top();
	}

};



bool resuelveCaso() {
	int entrada;
	cin >> entrada;
	if (!cin)
		return false;
	int val;
	carniceria c;
	for (int i = 0; i < entrada; i++) {
		cin >> val;
		if (val == 0) {
			if (c.empty()) {
				cout << "ECSA ";
			}
			else {
				cout << c.mediana()<<" ";
				c.pop_mediana();
			}
		}
		else {
			c.push(val);
		}
	}
	cout << "\n";
	return true;
}