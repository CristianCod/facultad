/*
 * Terreno.h
 *
 *  Created on: 26/05/2018
 *      Author: romero_gerard
 */

/*
 * Terreno.h
 *
 *  Created on: 13 may. 2018
 *      Author: cristian
 */


#ifndef TERRENO_H_
#define TERRENO_H_
#define VACIA (char) 35
typedef unsigned short int ui;
#include "Semilla.h"
enum Estado{vacia,sembrada,reposo, seca, podrida, cosechar};

struct InfoParcela{
	ui rentabilidad;
	/*turnos luego de secarse, podrirse o cosecharse*/
	ui recuperacion;
	/*turnos para la cosecha*/
	ui tiempoHastaCosecha;
	/*numero de riegos creciente por turno*/
	ui numeroDeRiegos;

	ui tiempoTrasSiembra;
	/*descuento de unidades de agua al regar por turno*/
	ui riegoPorTurno;
	/*el estado caracter que se muestra en tablero*/
	char tipo;
	/*tipo de cultivo*/
	char siembra;
};
class Terreno{

	private:
	/*Ubicar estos atributos en un struct Parcela, cambiar el constructor*/
			InfoParcela Parcela;
			Estado ESTADO;
			bool regada;
			bool Sembrada;
			bool parcelaPodrida;

			bool seCosecho;
			bool Seca;
			bool enRecuperacion;

	public:
			Terreno();
			char mostrarTipo();
			bool disponible();
			bool listaCosechar();
			char mostrarCultivo();


			ui riegoNecesario();

			ui obtenerRentabilidad();

			void aumentarNumeroDeRiegos();

			void cambiarACosechado();

			void cambiarEstadoDeParcelaSembrada(Semilla* aSembrar);
			/*
			 * post:Devuelve true si la parcela esta llena o
			 * 	   false en caso contrario.
			 */
			bool estaVacia();
			void actualizando();

			void actualizarParcelas();
			void mostrarTerreno(Terreno **terreno);


};

#endif /* TERRENO_H_ */
