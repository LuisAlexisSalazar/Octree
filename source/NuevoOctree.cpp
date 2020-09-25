#include "COctree.h"
#include<fstream>
#include<string>
#include<sstream>

vector<int>PuntosLimites(6, 0);

void ActualizarMaximo(int x,int y,int z) {
    if (PuntosLimites[3] < x)
        PuntosLimites[3] = x;

    if (PuntosLimites[4] < y)
        PuntosLimites[4] = y;

    if (PuntosLimites[5] < z)
        PuntosLimites[5] = z;
}

void ActualizarMinimos(int x, int y, int z) {
    if (PuntosLimites[0] > x)
        PuntosLimites[0] = x;

    if (PuntosLimites[1] > y)
        PuntosLimites[1] = y;

    if (PuntosLimites[2] > z)
        PuntosLimites[2] = z;
}


int main()
{
    ifstream inFile("rabbit.obj");

    vector<CPunto<int> > PuntosOficiales;
    stringstream ss;
    string point_str;
    CPunto<double> tmp;

    CPunto<int> Punto;

    while (getline(inFile, point_str)) {
        stringstream ss(point_str);
        ss >> tmp;

        Punto.x = tmp.x * 10000;
        Punto.y = tmp.y * 10000;
        Punto.z = tmp.z * 10000;

        //Actualizar Minimo
        ActualizarMinimos(Punto.x, Punto.y, Punto.z);
        //Actualizar Maximo
        ActualizarMaximo(Punto.x, Punto.y, Punto.z);

        PuntosOficiales.push_back(Punto);
    }

    cout << "Dominio: " << endl;
    for (int i = 0; i < 6; i++)
        cout << PuntosLimites[i]<< endl;

    COctree<int> Octree(PuntosLimites[0], PuntosLimites[1], PuntosLimites[2], PuntosLimites[3], PuntosLimites[4], PuntosLimites[5]);

    for (int i = 0; i < PuntosOficiales.size(); i++)
        Octree.insert(PuntosOficiales[i].x,PuntosOficiales[i].y,PuntosOficiales[i].z);
    
    //Ejemplo de Busqueda y eliminación
    int x, y, z;

    x = 32362;
    y = -8371;
    z = 76232;


    cout << "Buscando Punto " << x << " " << y << " "<< z<<endl;
    if (Octree.findPunto(x, y, z))
        cout << "   Punto Encontrado" << endl;
    else
        cout << "   Punto no encontrado"<<endl;

    cout << endl;
    cout << "Removiendo Punto " << x << " " << y << " " << z << endl;
    Octree.remove(x, y, z);
    cout << endl;

    cout << "Bucando Punto" << x << " " << y << " " << z << endl;
    if (Octree.findPunto(x, y, z))
        cout << "   Punto Encontrado" << endl;
    else
        cout << "   Punto no encontrado" << endl;
    return 0;
    
}

