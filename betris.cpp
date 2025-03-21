//------------------------------------------------------------------------------
// File:   betris.cpp
// Author: Javier Perez y Máximo Valenciano
// Date:   mayo 2022
// Coms:   Código fuente para el trabajo práctico de Programación II 2022
//------------------------------------------------------------------------------

#include "betris.hpp"
#include <ctime>
#include <thread>         
#include <chrono>

// Pre: true
// Post: ∀α ∊[0,tablero.nfils] & ∀ β ∊[0,tablero.ncols] tablero.matriz[α][β] =-1
void inicializarTablero(tpTablero &tablero) {
    for(int i=0; i< tablero.nfils;i++) {
        for(int j=0; j< tablero.ncols;j++) {
            tablero.matriz[i][j] = -1;
        }
    }
}

/*
*   Pre: 0<= i <= tablero.nfils && 0 <= j <= tablero.ncols && 0 <= #vEntrada
*   Post: Muestra la casilla actual tablero[i][j] con el color que corresponde en función de vEntrada
*/
bool mostrarTableroAux (const tpTablero & tablero, const int vEntrada[], int i, int j) {

    if (i == tablero.nfils ) {
        return false;//return vacío para slair de la función al temrinar (si funcioona bien quitalo)
    }

    else if (tablero.matriz[i][j] == -1) {//SIMPLIFICAR CON VARIABLE CÓDIGO COLOR DIRECTAMENTE EN EL COUT --> Hecho
        cout << "  " ;
    } else {
        int indice = tablero.matriz[i][j];
        int codigoColor=vEntrada[indice];
        int color;
        if (codigoColor == 0) {color = AZUL;} //azul
        else if (codigoColor == 1) {color = VERDE;} //verde
        else if (codigoColor == 2) {color = ROJO;}//rojo
        else if (codigoColor == 3) {color = CIAN;}//cian
        else {color = AMARILLO;}// amarillo
        
        cout << "\033[34;" << to_string(color) <<"m  " << "\033[0m"; 
    }


    if (j== tablero.ncols-1) {
        cout << endl;
        mostrarTableroAux(tablero,vEntrada,i+1,0);
    } else {
        mostrarTableroAux(tablero,vEntrada,i,j+1);
    } 
    return true;

}

// Pre: vEntrada contiene los números de las piezas que entran y tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero, const int vEntrada[]) {
    /*
    *   cojo tablero.matriz y compruebo [i][j]
    *   miro si es -1 pa ponerle un espacio
    *   si es otro número, me voy al vEntrada de lo que haya en [i][j]
    *   cojo lo que haya en vEntrada de lo anterior 
    *   miro el numero de pieza con lo que haya en vEntrada[tablero.matriz[i][j]]]
    *   pongo color en esa celda con eso
    *   llamo a función auxiliar recursiva que inlcuya indices i y j
    */
   mostrarTableroAux (tablero, vEntrada, 0, 0);
   cout << endl;

}

/*
*  Pre:  0<= i <= tablero.nfils && 0 <= j <= tablero.ncols && 0<= pieza.color <=4
*  Post: compruebaPieza(tablero,fila,col,pieza) = m && m= ∃ (α,β). tablero.matriz[α][β]== -1 ∀ tpPieza
*/
bool compruebaPieza (tpTablero &tablero, int fila, int col, tpPieza pieza){
    int filaux,colaux;

    for (int i =0; i<TAMPIEZA; i++) {//cojo las 4 duplas de cada pieza

        filaux=fila + pieza.forma[i][0]; //sumo la col de la x de la dupla a fila (hacia la dcha)
        colaux=col + pieza.forma[i][1];  //resto la fila de la y de la dupla (para comprobar por arriba)

        if ( (filaux < 0) || (colaux < 0) || (filaux>= tablero.nfils) || (colaux>=tablero.ncols) || (tablero.matriz[filaux][colaux] != -1) ) {
            return false;
        }
    }
    
    return true;
}


/*
*   Pre: 0<= i <= tablero.nfils && 0 <= j <= tablero.ncols && 0<= pieza.color <=4 && 0 <= iter
*   Post: tablero.matriz[fila][col] es la parte superior izquierda de la pieza, y sus casillas adyacentes en función de la pieza quedan puestas
*         en tablero.matriz[][] con el valor de iter.
*/
void ponerPieza (tpTablero &tablero, int fila, int col, tpPieza pieza, int& iter) {
    int filaux,colaux;

    for (int i =0; i<TAMPIEZA; i++) {//cojo las 4 duplas de cada pieza

        filaux=fila + pieza.forma[i][0]; //sumo la col de la x de la dupla a fila (hacia la dcha)
        colaux=col + pieza.forma[i][1];  //resto la fila de la y de la dupla (para comprobar por arriba)

        tablero.matriz[filaux][colaux] = iter;
    }
}

/*
*   Pre: iter >= 0
*   Post: ∀ α,β. tablero.matriz[α][β] == iter. tablero.matriz[α][β]== -1
*/
void quitarPieza(tpTablero &tablero, int iter){//iter es el n de antes.

    for(int i=0; i<tablero.nfils;i++) {
        for (int j=0; j< tablero.ncols;j++) {
            if (tablero.matriz[i][j] == iter) {
                tablero.matriz[i][j] = -1;
            }
        }
    }

}

// Pre: tablero.nfils > 0 ∧ tablero.ncols > 0 ∧ filas > 0
// Post: filasLlenas(tablero, filas) = Num(α ∊ [0,nfils].β ∊ [0,ncols] tablero.matriz[α][β] != -1)

int numFilasLlenas(tpTablero tablero){
    int num=0;
    for(int i=0;i<tablero.nfils;i++) {
        bool llena= true;
        for (int j=0; j<tablero.ncols;j++) {
            if (tablero.matriz[i][j] == -1) {
                llena = false;
            }
        }
        if (llena) {
            num++;
        }
    }
    return num;
}




// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1

int buscaSolucion(tpTablero &tablero, const int vEntrada[], int vSalida[], const int objetivo, int n, const int retardo){

    //var locales
    tpPieza pieza;
    pieza = vPiezas[vEntrada[n]];
    int col = 0;
    int fil = vPiezas[vEntrada[n]].forma[3][0]; //cojo la 'y' máxima a la que baja la pieza, que está en forma[3][0] en todos los casos !!! (si no hiciera esto al comprobar en línea 0 muchas de las piezas me daría que no caben directamente y esto es falso)

    const int* obj= &objetivo;
    if (numFilasLlenas(tablero)==*obj){ //CASO BASE: ya hemos completado el objetivop: mostramos el tablero y hacemos return del numPiezas colocadas.
        mostrarTablero(tablero,vEntrada);
        std::this_thread::sleep_for (std::chrono::milliseconds(retardo));
        return n;
    }else if (vEntrada[n] == -1){//hemos llegado al final de vEntrada y != objetivo --> return numPiezas_colocadas
        quitarPieza(tablero,n-1);
        mostrarTablero(tablero,vEntrada);
        std::this_thread::sleep_for (std::chrono::milliseconds(retardo));
        return -1;
    }else{

        while (col < tablero.ncols) {
            int filaux= fil; //pongo en inicial para cada columna que compruebo

            while (filaux < tablero.nfils && compruebaPieza(tablero, filaux, col, pieza)) {
                filaux ++;
            }
            if (compruebaPieza(tablero,filaux-1,col, pieza)) { //es filaux - 1 porque al hacer el while me he pasado por 1 para salir del bucle

                ponerPieza(tablero,filaux-1,col,pieza,n);
                vSalida[n]=col;
                mostrarTablero(tablero,vEntrada);
                std::this_thread::sleep_for (std::chrono::milliseconds(retardo));
                int solParcial = buscaSolucion(tablero,vEntrada,vSalida,objetivo,n+1,retardo);

                if (solParcial != -1) {
                    return solParcial;
                }

            }

            col ++;
        }

        quitarPieza(tablero,n);
        quitarPieza(tablero,n-1);
        mostrarTablero(tablero,vEntrada);
        std::this_thread::sleep_for (std::chrono::milliseconds(retardo));
        return -1;

    }
    return -1;
}

