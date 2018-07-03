//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string>
#include <fstream>
#include "Juego.h"
typedef unsigned short int ui;
#include <stdlib.h>
#include "ABB.h"
#include "EasyBMP.h"


void leer(string rutaEntrada){
	std::ifstream entrada;
	entrada.open(rutaEntrada.c_str());

	while (! entrada.eof()) {
		char tipo;
		int costo;
		int tiempoCosecha;
		int rentabilidad;
		int tiempoRecup;
		int aguaTurno;

		entrada >> tipo;
		if (! entrada.eof()) {
			entrada >> costo;
			entrada >> tiempoCosecha;
			entrada >> rentabilidad;
			entrada >> tiempoRecup;
			entrada >> aguaTurno;

			std::cout << tipo << " | " << costo << " | " << tiempoCosecha <<"|"<< rentabilidad<<"|"<<tiempoRecup<<"|"<<aguaTurno << endl;
		}
	}

		/* cierra el archivo, liberando el recurso */
	entrada.close();
}
int main() {
	ABB <int> arbol;
	arbol.agregar(5);
	arbol.agregar(2);
	arbol.agregar(8);
	arbol.agregar(9);
	arbol.agregar(10);
	arbol.agregar(7);
	std::cout<<"existe "<<arbol.existe(8)<<std::endl;
	std::cout<<"existe "<<arbol.existe(2)<<std::endl;
	//arbol.remover(2);
	std::cout<<"existe "<<arbol.existe(2)<<std::endl;
	std::cout<<"existe "<<arbol.existe(5)<<std::endl;

	std::cout<<"existe "<<arbol.existe(7)<<std::endl;

	arbol.verArbolInOrden();


	/*
	ui fil=5;
	ui col=5;

Tablero tablero;
Jugador *jugador=new Jugador(1);
Terreno **terreno1=new Terreno*[jugador->obtenerFilMax()];
for( ui i = 1 ; i< col; i++ ){
		//// VERIFICAR++++++++++++++++++++++++eergfrgege
	    terreno1[i] = new Terreno[jugador->obtenerColMax()];
	}

tablero.crearTablero(fil,col);
tablero.actualizarTableroCultivosTurnoActual(terreno1,jugador);

*/
/*

	Juego granjeros;
	granjeros.elegirDificultad();
	ui cantidadValida=granjeros.cantidadJugadores();
	granjeros.agregarJugadores(cantidadValida);
	while(!granjeros.finJuego()){
		granjeros.comenzarTurno();
	}
	granjeros.~Juego();
	*/
	return 0;
}
