#pragma once


#include "CPunto.h"
#include<vector>



//Regiones de las particiones
//superior delantera izquierda
const int SDI = 0;
//superior delantera derecha
const int SDD = 1;
//inferior delantera derecha
const int IDD = 2;
//inferior delantera izquierda
const int IDI = 3;

//superior trazero izquierda
const int STI = 4;
//superior trazero derecha
const int STD = 5;
//inferior trazero derecha
const int ITD = 6;
//inferior trazero izquierda
const int ITI = 7;


template<typename T>
class CNode
{

public:
	//Superior Izqueirdo Delantero y Inferior Trazero derecho
	vector<CPunto<T>*> Dominio;

    //Proximamente
	//vector<CPunto<T>*>ArrayPuntos;
	CPunto<T>* Punto;

	vector<CNode<T>*>Hijos;

    //Declara nodo vacio (P => -1 -1 -1)
	CNode<T>() {
		Punto = new CPunto<T>();
	}


    // Declarar un nodo Punto (P=> x y z)
	CNode(T x, T y, T z) {
		Punto = new CPunto<T>(x, y, z);
	}


    //Definir el Dominio en el Nodo
    CNode(T x1, T y1, T z1, T x2, T y2, T z2) {

        if (x2 < x1 || y2 < y1 || z2 < z1)
            return;
        Punto = NULL;

        CPunto<T>* top_left_front = new CPunto<T>(x1, y1, z1);
        CPunto<T>* bottom_right_back = new CPunto<T>(x2, y2, z2);

        Dominio.push_back(top_left_front);
        Dominio.push_back(bottom_right_back);

        Hijos.assign(8, NULL);

        for (int i = 0; i < 8; ++i)
            Hijos[i] = new CNode<T>();
    }

	//Determinar Posición (Segmento de los 8 hijos)
    int determinarPosicion(T x, T y, T z, T midx, T midy, T midz) {
        if (x <= midx) {
            if (y <= midy) {
                if (z <= midz)
                    return SDI;
                else
                    return STI;
            }
            else {
                if (z <= midz)
                    return IDI;
                else
                    return ITI;
            }
        }
        else {
            if (y <= midy) {
                if (z <= midz)
                    return SDD;
                else
                    return STD;
            }
            else {
                if (z <= midz)
                    return IDD;
                else
                    return ITD;
            }
        }
    }


	
	//Insertar Punto
    void Insertar(T x, T y, T z) {

        if (x < Dominio[0]->x || x > Dominio[1]->x || y < Dominio[0]->y ||
            y > Dominio[1]->y || z < Dominio[0]->z || z > Dominio[1]->z)
            return;

        T midx = (Dominio[0]->x + Dominio[1]->x) / 2;
        T midy = (Dominio[0]->y + Dominio[1]->y) / 2;
        T midz = (Dominio[0]->z + Dominio[1]->z) / 2;

        int pos = -1;

        pos = determinarPosicion(x, y, z, midx, midy, midz);

        //Si es un Nodo Region
        if (Hijos[pos]->Punto == NULL) {
            Hijos[pos]->Insertar(x, y, z);
            return;
        }
        // Si es Nodo Vacio
        else if (Hijos[pos]->Punto->x == -1) {
            //cout << pos << " ";
            delete Hijos[pos];
            Hijos[pos] = new CNode<T>(x, y, z);
            return;
        }

        else
        {
            int x_ = Hijos[pos]->Punto->x,
                y_ = Hijos[pos]->Punto->y,
                z_ = Hijos[pos]->Punto->z;
            delete Hijos[pos];

            Hijos[pos] = NULL;
            if (pos == SDI) {
                Hijos[pos] = new CNode<T>(Dominio[0]->x, Dominio[0]->y, Dominio[0]->z,
                    midx, midy, midz);
            }
            else if (pos == SDD) {
                Hijos[pos] = new CNode<T>(midx + 1, Dominio[0]->y, Dominio[0]->z, Dominio[1]->x, midy, midz);
            }
            else if (pos == IDD) {
                Hijos[pos] = new CNode<T>(midx + 1, midy + 1, Dominio[0]->z,
                    Dominio[1]->x, Dominio[1]->y, midz);
            }
            else if (pos == IDI) {
                Hijos[pos] = new CNode<T>(Dominio[0]->x, midy + 1, Dominio[0]->z,
                    midx, Dominio[1]->y, midz);
            }
            else if (pos == STI) {
                Hijos[pos] = new CNode<T>(Dominio[0]->x, Dominio[0]->y, midz + 1,
                    midx, midy, Dominio[1]->z);
            }
            else if (pos == STD) {
                Hijos[pos] = new CNode<T>(midx + 1, Dominio[0]->y, midz + 1,
                    Dominio[1]->x, midy, Dominio[1]->z);
            }
            else if (pos == ITD) {
                Hijos[pos] = new CNode<T>(midx + 1, midy + 1, midz + 1,
                    Dominio[1]->x, Dominio[1]->y, Dominio[1]->z);
            }
            else if (pos == ITI) {
                Hijos[pos] = new CNode<T>(Dominio[0]->x, midy + 1, midz + 1,
                    midx, Dominio[1]->y, Dominio[1]->z);
            }
            Hijos[pos]->Insertar(x_, y_, z_);
            Hijos[pos]->Insertar(x, y, z);
        }
    }

    //bool Find(T x, T y, T z, CPunto<T>*& PuntoBuscar) {
    bool Find(T x, T y, T z, CPunto<T>*& PuntoBuscar, CNode<T>*& NodoBuscar) {
        if (x < Dominio[0]->x || x > Dominio[1]->x || y < Dominio[0]->y ||
            y > Dominio[1]->y || z < Dominio[0]->z || z > Dominio[1]->z)
            return 0;


        T midx = (Dominio[0]->x + Dominio[1]->x) / 2;
        T midy = (Dominio[0]->y + Dominio[1]->y) / 2;
        T midz = (Dominio[0]->z + Dominio[1]->z) / 2;

        int pos = -1;

        pos = determinarPosicion(x, y, z, midx, midy, midz);

        // Si es Nodo Region
        if (Hijos[pos]->Punto == NULL) {
            return Hijos[pos]->Find(x, y, z, PuntoBuscar, NodoBuscar);
        }

        //Si es Nodo vacio
        else if (Hijos[pos]->Punto->x == -1) {
            return 0;
        }
        else {
            if (x == Hijos[pos]->Punto->x && y == Hijos[pos]->Punto->y
                && z == Hijos[pos]->Punto->z) {
                NodoBuscar = Hijos[pos];
                 PuntoBuscar= Hijos[pos]->Punto;
                return 1;
            }
        }
        Punto = NULL;
        return 0;
    }

    
    void Eliminar(T x, T y, T z) {
        CPunto<T>* PuntoEliminar;
        CNode<T>* NodoBuscar;

        if (Find(x,y,z,PuntoEliminar,NodoBuscar))
        {
            //Eliminar el punto y Nodo porque solo almacena un punto
            delete PuntoEliminar;
            //Nodo vacio pero con dominio
            NodoBuscar->Punto = new CPunto<T>();
        }
        else
            cout << "No se pudo eliminar porque el elemento no se encuentra" << endl;
    }

};


