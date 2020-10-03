#pragma once

#include<iostream>
using namespace std;

class CPunto {
public:
    double x, y, z;
    CPunto() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    CPunto(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    friend istream& operator>>(istream& is, CPunto& punto) {
        is >> punto.x >> punto.y >> punto.z;
        return is;
    }

    bool operator==(CPunto& p) {
        return x == p.x && y == p.y && z == p.z;
    }

    CPunto operator+(CPunto& p2) {
        CPunto p;
        p.x = x + p2.x; p.y = y + p2.y; p.z = z + p2.z;
        return p;
    }

    CPunto operator-(CPunto& p2) {
        CPunto p;
        p.x = x - p2.x; p.y = y - p2.y; p.z = z - p2.z;
        return p;
    }

    CPunto operator*(CPunto& p2) {
        CPunto p;
        p.x = x * p2.x; p.y = y * p2.y; p.z = z * p2.z;
        return p;
    }

    CPunto& operator=(const CPunto& p) {
        this->x = p.x; this->y = p.y; this->z = p.z;
        return *this;
    }

    void print() {
        cout << '<' << x << ',' << y << ',' << z << '>' << endl;
    }

   
};