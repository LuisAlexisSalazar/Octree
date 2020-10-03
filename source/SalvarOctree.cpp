
#include <iostream>
#include"Visualizador.h"
#include"COctree.h"


int main(int argc, char** argv)
{
    COctree tree(1.0);

    //Pasar los perimetros 
    tree.prepararOpenGL();
    runOPENGL(argc, argv);

    return 0;
}

