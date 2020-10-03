#pragma once

#include"CNode.h"
#include<stralign.h>
#include <fstream>
#include <string>
#include<sstream>
#include"Visualizador.h"

class COctree {
public:
    vector<CPunto> conjuntoPuntos;
    CNode* root = NULL;
    double capacidadTotal;


    COctree(double capacidad) {
        ifstream dataFileXYZ;
        ifstream ArchivoXYZ("rabbit.obj");
        CPunto maxBound, minBound;

        if (ArchivoXYZ.fail())
            cout << "No hay archivos de puntos" << endl;

        else {
            string punto_string;
            CPunto tmp;
            int i = 0;
            while (!ArchivoXYZ.eof()) {
                getline(ArchivoXYZ, punto_string);
                stringstream ss(punto_string);
                ss >> tmp;
                ActualizarMaximo(maxBound, tmp);
                ActualizarMinimo(minBound, tmp);
                //cout << tmp.x << " " << tmp.y << " " << tmp.z << endl;
                //Poner los Puntos a la raiz
                conjuntoPuntos.push_back(tmp);
                ++i;
            }
            ArchivoXYZ.close();

            CPunto p111 = CPunto(1, 1, 1);
            minBound = minBound - p111;
            maxBound = maxBound + p111;
            root = new CNode(int(conjuntoPuntos.size()), minBound, maxBound - minBound);
            capacidadTotal = capacidad;
            //Construcción del Árbol
            BuildTree();
        }
    }
          
   
    bool insert(CPunto a_point) {
        CNode** poct;
        int pind = 0;
        if (!find(a_point, poct, pind)) {
            while (!(*poct)->isInStopCriterion(capacidadTotal)) {
                split(poct);
                for (auto& child : (*poct)->hijos) {
                    if (child->isInside(a_point)) {
                        poct = &child;
                        break;
                    }
                }
            }
            (*poct)->content.push_back(new CPunto(a_point.x, a_point.y, a_point.z));
            if ((*poct)->color != BLACK) {
                (*poct)->color = BLACK;
                poct = &(*poct)->parent;
                recall(*poct);
            }
            return true;
        }
        return false;
    }

    void prepararOpenGL() {
        CNode* reader = root;
        read(reader);
    }

    void BuildTree() {
        for (auto& point : conjuntoPuntos) {
            insert(point);
        }
    }

    bool find(CPunto a_point, CNode**& poct, int& pind) {
        poct = &root;
        if (*poct && !(*poct)->isInside(a_point)) return false;
        while ((*poct)->color == GRAY) {
            for (auto& child : (*poct)->hijos){
                if (child && child->isInside(a_point)) {
                    poct = &child;
                    break;
                }
            }
        }
        if ((*poct)->color == BLACK) {
            for (auto& p : (*poct)->content) {
                if (*p == a_point)
                    return true;
                ++pind;
            }
        }
        return false;
    }
    
    void split(CNode**& poct) {
        (*poct)->color = GRAY;
        int childVolume = (*poct)->volume / 8, i = 0;
        
        //perimetro,size,padre
        CPunto X = CPunto((*poct)->chSize.x, 0, 0);
        CPunto Y = CPunto(0 ,(*poct)->chSize.y, 0);
        CPunto Z = CPunto(0, 0, (*poct)->chSize.z);

        (*poct)->hijos[0] = new CNode(childVolume,(*poct)->boundfp, X + Y + Z, (*poct));
        (*poct)->hijos[1] = new CNode(childVolume,(*poct)->boundfp + Y, X + Y + Z, (*poct));
        (*poct)->hijos[2] = new CNode(childVolume,(*poct)->boundfp + Z, X + Y + Z, (*poct));
        (*poct)->hijos[3] = new CNode(childVolume,(*poct)->boundfp + Y + Z, X + Y + Z, (*poct));
        (*poct)->hijos[4] = new CNode(childVolume,(*poct)->boundfp + X, X + Y + Z, (*poct));
        (*poct)->hijos[5] = new CNode(childVolume,(*poct)->boundfp + X + Y, X + Y + Z, (*poct));
        (*poct)->hijos[6] = new CNode(childVolume,(*poct)->boundfp + X + Z, X + Y + Z, (*poct));
        (*poct)->hijos[7] = new CNode(childVolume,(*poct)->boundfp + X + Y + Z, X + Y + Z, (*poct));
    }

    void recall(CNode* parnt, COLOR status = BLACK) {
        while (parnt) {
         
            for (auto& child : parnt->hijos) if (child->color != status) return;

            for (auto& child : parnt->hijos) {
                parnt->content.insert(parnt->content.end(), child->content.begin(), child->content.end());
                child->content.clear();
                delete child;
                child = NULL;
            }
            parnt->color = status;
            parnt = parnt->parent;
        }
    }
    void read(CNode* reader) {
        if (reader->color == BLACK) {
            DrawableOctant oct(reader->boundfp, reader->boundsp);
            octants.push_back(oct);
            return;
        }

        for (auto& child : reader->hijos) {
            if (child && child->color == GRAY) {
                DrawableOctant oct(reader->boundfp, reader->boundsp);
                octants.push_back(oct);
                read(child);
            }
        }
    }

    void ActualizarMaximo(CPunto& M, CPunto& X) {
        M.x = (M.x < X.x) ? X.x : M.x;
        M.y = (M.y < X.y) ? X.y : M.y;
        M.z = (M.z < X.z) ? X.z : M.z;
    }
    void ActualizarMinimo(CPunto& M, CPunto& X) {
        M.x = (M.x > X.x) ? X.x : M.x;
        M.y = (M.y > X.y) ? X.y : M.y;
        M.z = (M.z > X.z) ? X.z : M.z;
    }
};