#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "EasyBMP.h"
#include "Jugador.h"

#define PROFUNDIDAD 24
class Tablero
{
private:

    BMP tableroSalida;
    BMP parcelaVacia;
	BMP cultivoAParaCosechar;
	BMP cultivoAEnCrecimiento;
	BMP cultivoBParaCosechar;
	BMP cultivoBEnCrecimiento;
	BMP cultivoCParaCosechar;
	BMP cultivoCEnCrecimiento;
	BMP cultivoPodrido;
	BMP cultivoSeco;
	BMP ceroTurnos;
	BMP unTurno;
	BMP dosTurnos;
	BMP tresTurnos;
	BMP cuatroTurnos;
	BMP parcelaEnRecuperacion;


    public:

        /* pre: No existe tablero bmp.
           post: Abre las imagenes bmp a utilizarse. */

        Tablero ();

        /* PRE: Recibe numero de filas y columnas del terreno. Recibe datos del terreno.
        POST: Analiza el contenido de cultivos del terreno y lo vuelca en una imagen .bmp.
        */
        /* NOTA PARA CORRECCION : ACA EN DATOS DE TERRENO IRIA EL OBJETO TERRENO, SE NECESITA
                                  SABER QUE CULTIVO HAY EN CADA PARCELA. EN EL SWITCH COMPARA
                                  EL CONTENIDO DE LA PARCELA CON LAS OPCIONES POSIBLE PARA
                                  SABER QUE IMAGEN IMPRIMIR.
                                  EN DATOS JUGADOR IRIA EL OBJETO JUGADOR, SE NECESITA SABER
                                  QUE NUMERO DE JUGADOR ES Y EN QUE TURNO DE PARTIDA SE ENCUENTRA.
                                  ESTO ES PARA QUE CADA VEZ QUE IMPRIMA UNA IMAGEN LA RUTA INDIQUE
                                  EL NUMERO DE JUGADOR Y EL TURNO EN EL QUE ESTA.*/

        void actualizarTableroCultivosTurnoActual(Terreno** TERRENO, Jugador* jugador);

        void quepasa(Jugador *jugador);
        /* PRE: Recibe numero de filas y columnas del terreno. Recibe datos del terreno.
        POST: Analiza el estado de turnos de la parcela para ver cuantos falta hasta que este lista para cosechar
              y lo vuelca en una imagen .bmp.
        */

        /* NOTA PARA CORRECCION : ACA EN DATOS DE TERRENO IRIA EL OBJETO TERRENO, SE NECESITA
                                  SABER QUE CANTIDAD DE TURNOS FALTAN HASTA QUE SE PUEDA COSECHAR HAY EN CADA PARCELA.
                                  EN EL SWITCH COMPARA EL CONTENIDO DE LOS TURNOS DE LA PARCELA CON LAS OPCIONES POSIBLE PARA
                                  SABER QUE IMAGEN IMPRIMIR.

                                  EN DATOS JUGADOR IRIA EL OBJETO JUGADOR, SE NECESITA SABER
                                  QUE NUMERO DE JUGADOR ES Y EN QUE TURNO DE PARTIDA SE ENCUENTRA.
                                  ESTO ES PARA QUE CADA VEZ QUE IMPRIMA UNA IMAGEN LA RUTA INDIQUE
                                  EL NUMERO DE JUGADOR Y EL TURNO EN EL QUE ESTA.*/



  //      void actualizarTableroTurnosHastaCosecharse(Terreno** TERRENO,Jugador* JUGADOR, ui filas, ui columnas);

          /* PRE: Recibe numero de filas y columnas del terreno. Recibe datos del terreno. Recibe datos del jugador.
             POST: Analiza el estado de turnos de recuperacion de la parcela y lo vuelca en una imagen .bmp.
        */

        /* NOTA PARA CORRECCION : ACA EN DATOS DE TERRENO IRIA EL OBJETO TERRENO, SE NECESITA
                                  SABER QUE CANTIDAD DE TURNOS FALTAN PARA QUE SE RECUPERE LA PARCELA.
                                  EN EL SWITCH COMPARA EL CONTENIDO DE LOS TURNOS DE LA PARCELA CON LAS OPCIONES
                                  POSIBLE PARA SABER QUE IMAGEN IMPRIMIR.

                                  EN DATOS JUGADOR IRIA EL OBJETO JUGADOR, SE NECESITA SABER
                                  QUE NUMERO DE JUGADOR ES Y EN QUE TURNO DE PARTIDA SE ENCUENTRA.
                                  ESTO ES PARA QUE CADA VEZ QUE IMPRIMA UNA IMAGEN LA RUTA INDIQUE
                                  EL NUMERO DE JUGADOR Y EL TURNO EN EL QUE ESTA.*/



//        void actualizarTableroTurnosHastaDesocuparParcelas(Terreno** TERRENO,Jugador* jugador,ui filas, ui columnas);

        /* PRE: Recibe numero de fila y columnas elegidos por el jugador y arma una imagen tablero base.
           POST: Crea una imagen tablero base para usarse despues para  armar los tableros con parcelas y datos.*/

        void crearTablero(ui filas, ui columnas);



};



#endif // TABLERO_H_INCLUDED
