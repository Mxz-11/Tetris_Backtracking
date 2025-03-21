//------------------------------------------------------------------------------
// File:   mainB.cpp
// Author: Javier Perez y Máximo Valenciano
// Date:   mayo 2022
// Coms:   Código fuente para el trabajo práctico de Programación II 2022
//------------------------------------------------------------------------------

#include "betris.hpp"
#include <iostream>
using namespace std;

int main (int numArg, char* args[]) { //nombreProg nfils ncols objetivo retardo N1 N2 N3 N4 N5 N6 N7 N8.... -1
    int filas = stoi(args[1]);        //empieza en 1 porque el 0 es el nombre del ejectutable
    int cols = stoi(args[2]);
    int objetivo = stoi(args[3]);
    int retardo = stoi(args[4]); // retardo en milisegundos
    int numPiezas=numArg-5;     //numero de componentes = numero de numeros detrás de los 5 primeros parámetros (incluye el -1 y el nombre del ejecutable)
    int vEntrada[numPiezas];    //Creamos el vector con el numero de piezas que tenemos
    int vSalida[numPiezas];     //Creamos el vector de salida que albergará el número de columna en el que se ha situado cada pieza.

    for (int i = 0; i < numPiezas; i++) {
        vEntrada[i] = stoi(args[5+i]);
    }
    

    //Creamos el tablero
    tpTablero tablero;
    tablero.ncols = cols;
    tablero.nfils = filas;

    //si objetivo > nfils nunca se puede cumplir, ni siquera ejecutamos el programa
    if (objetivo > filas) {
        mostrarTablero(tablero,vEntrada); 
        return 1;
    }
    //inicializamos el tablero
    inicializarTablero(tablero);
    mostrarTablero(tablero,vEntrada);



    //ejecutamos backtracking para buscar solución
    int piezasColocadas = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

    //sacamos por pantalla datos de solución (piezas colocadas, vector salida)
    cout << "Entrada (números de piezas) : " ;
    for(int i=0; i< (numArg-5); i++) {
        cout << vEntrada[i] << " " ;
    }
    cout << endl;

    cout << "Numero de piezas colocadas: " << piezasColocadas << endl;

    cout << "Salida (números de columnas): ";

    if(piezasColocadas >= 0 ) {
        for (int i = 0; i < piezasColocadas; i++) {
            cout << vSalida[i] << " ";
        }
    }
    cout << endl;

}
