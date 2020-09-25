#pragma once
#include"CNode.h"

template<typename T>
class COctree
{
public:
	CNode<T>* Root;


	COctree() {
		Root = new CNode<T>();
	}

	//Definir dominio total a mi root
	COctree(T x1, T y1, T z1, T x2, T y2, T z2) {
		Root = new CNode<T>(x1, y1, z1, x2, y2, z2);
	}

	
	void insert(T x, T y, T z) {
		if (findPunto(x, y, z))
			cout << "No se aceptan repeticiones" << endl;
		
		else
			Root->Insertar(x, y, z);
	}


	bool findPunto(T x, T y, T z) {
		CPunto<T>* PuntoBuscar;
		CNode<T>* NodoBuscar;
		return Root->Find(x, y, z, PuntoBuscar, NodoBuscar);
	}

	void remove(T x, T y, T z) {
		Root->Eliminar(x, y, z);
	}
	
	void printPunto(T x, T y, T z) {
		CPunto<T>* Punto = NULL;
		if (findPunto(x, y, z, Punto))
			cout << Punto->x << "-" << Punto->y << "-" << Punto->z << endl;
		else
			cout << "No existe el punto" << endl;
	}

	
	bool isNodoNulo(CNode<T>* a) {
		if (a->Punto->x == -1 && a->Punto->y == -1 && a->Punto->z == -1)
			return true;
		return false;
	}

};

