//
//  IndexPQ.h
//
//  Implementaci�n de colas con prioridad mediante mont�culos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2019  Alberto Verdejo
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

// T es el tipo de las prioridades
// Comparator dice cu�ndo un valor de tipo T es m�s prioritario que otro
template <typename V = std::string, typename T = int, typename Comparator = std::greater<T>>
class IndexPQ {
public:
	// registro para las parejas < elem, prioridad >
	struct Par {
		V elem;
		T prioridad;
		
		
	};

private:
	// vector que contiene los datos (pares < elem, prio >)
	std::vector<Par> array;     // primer elemento en la posici�n 1

	// vector que contiene las posiciones en array de los elementos
	//std::vector<int> posiciones;   // un 0 indica que el elemento no est�
	std::unordered_map<V, int>posiciones;
	/* Objeto funci�n que sabe comparar prioridades.
	 antes(a,b) es cierto si a es m�s prioritario que b */
	Comparator antes;

public:
	IndexPQ(Comparator c = Comparator()) : array(1),  antes(c) {}

	IndexPQ(IndexPQ<V, T, Comparator> const&) = default;

	IndexPQ<V, T, Comparator>& operator=(IndexPQ<V, T, Comparator> const&) = default;

	~IndexPQ() = default;

	// e debe ser uno de los posibles elementos
	void push(V e, T const& p) {
		auto it = posiciones.find(e);
		if (it != posiciones.end())
			throw std::invalid_argument("No se pueden insertar elementos repetidos.");
		else {
			array.push_back({ e, p});
			posiciones[e] = size();
			flotar(size());
		}
	}

	void update(V e, T const& p) {
		auto it = posiciones.find(e);

		if (it == posiciones.end()) // el elemento e se inserta por primera vez
			push(e, p);
		else {
			int i = it->second;
			array[i].prioridad = p;
			if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
				flotar(i);
			else // puede hacer falta hundir a e
				hundir(i);
		}
	}

	int size() const {
		return int(array.size()) - 1;
	}

	bool empty() const {
		return size() == 0;
	}

	Par const& top() const {
		if (size() == 0)
			throw std::domain_error("No se puede consultar el primero de una cola vacia");
		else return array[1];
	}
	
	void updateAdd(V e, T p) {

		auto it = posiciones.find(e);
		if (it != posiciones.end()) {
			p += array[it->second].prioridad;
		}

		update(e, p);


	}
	void pop() {
		if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vac�a.");
		else {
			
			posiciones.erase(array[1].elem); // para indicar que no est�
			if (size() > 1) {
				array[1] = std::move(array.back());
				posiciones[array[1].elem] = 1;
				array.pop_back();
				hundir(1);
			}
			else
				array.pop_back();
		}
	}

	void printf() {
		for (Par x : array) {
			std::cout<<"(" << x.elem << " " << x.prioridad << ")\n";
		}
		std::cout << "\n";
	}

private:

	void flotar(int i) {
		Par parmov = std::move(array[i]);
		int hueco = i;
		while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad)) {
			array[hueco] = std::move(array[hueco / 2]); posiciones[array[hueco].elem] = hueco;
			hueco /= 2;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

	void hundir(int i) {
		Par parmov = std::move(array[i]);
		int hueco = i;
		int hijo = 2 * hueco; // hijo izquierdo, si existe
		while (hijo <= size()) {
			// cambiar al hijo derecho de i si existe y va antes que el izquierdo
			if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
				++hijo;
			// flotar el hijo si va antes que el elemento hundi�ndose
			if (antes(array[hijo].prioridad, parmov.prioridad)) {
				array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
				hueco = hijo; hijo = 2 * hueco;
			}
			else break;
		}
		array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
	}

};

#endif /* INDEXPQ_H_ */
