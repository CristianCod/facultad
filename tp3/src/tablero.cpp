#include "tablero.h"

#include <string>
#include <sstream>


Tablero :: Tablero ()
{    parcelaVacia.ReadFromFile("parcelaVacia.bmp");
	cultivoAParaCosechar.ReadFromFile("cultivoAParaCosechar.bmp");
	cultivoBParaCosechar.ReadFromFile("cultivoBParaCosechar.bmp");
	cultivoCParaCosechar.ReadFromFile("cultivoCParaCosechar.bmp");
	//cultivoAEnCrecimiento.ReadFromFile("cultivoAEnCrecimiento.bmp");
	//cultivoBEnCrecimiento.ReadFromFile("cultivoBEnCrecimiento.bmp");
	//cultivoCEnCrecimiento.ReadFromFile("cultivoCEnCrecimiento.bmp");
	cultivoPodrido.ReadFromFile("cultivoPodrido.bmp");
	cultivoSeco.ReadFromFile("cultivoSeco.bmp");
	ceroTurnos.ReadFromFile("ceroTurnos.bmp");
	unTurno.ReadFromFile("unTurno.bmp");
	dosTurnos.ReadFromFile("dosTurnos.bmp");
	tresTurnos.ReadFromFile("tresTurnos.bmp");
	cuatroTurnos.ReadFromFile("cuatroTurnos.bmp");
	parcelaEnRecuperacion.ReadFromFile("parcelaEnRecuperacion.bmp");
}

void Tablero::crearTablero(ui filas, ui columnas)
{
    tableroSalida.SetSize(columnas*60, filas*60);
    tableroSalida.SetBitDepth(PROFUNDIDAD);
    RGBApixel color;
    for (ui i = 0; i < columnas*60; i++)
    {   for (ui j = 0; j < filas*60; j++)
        {
            color.Green = 0;
            color.Blue  = 0;
            color.Red   = 0;
            tableroSalida.SetPixel(i, j, color);
        }
    }
}

/*PRE: Recibe datos del jugador actual y un string con el pie de la ruta que se necesita para la salida de las imagenes de los tableros.
  POST: Devuelve el nombre completo y armado de la ruta necesaria.*/

  /* NOTA DE CORRECCION: ESTA FUNCION ES AUXILIAR, NO ES DEL TDA EN CONCRETO, POR ESO NO ESTA EN EL .H
                         LO QUE HACE ESTA FUNCION ES RECIBIR EL OBJETO JUGADOR Y EXTRAER NUMERO DE JUGADOR
                         Y NUMERO DE TURNO ACTUAL. CON ESTE PROCEDIMIENTO ARMO LA RUTA DE SALIDA DE LAS
                         IMAGENES CON NUMERO DE JUGADOR Y TURNO.

                         EJ: TE QUEDARIA " JUGADOR1TURNO3tableroTurnosHastaCosecharse.bmp"

                         */
char* rutaImagenesSalida (Jugador* JUGADOR, std::string rutas)
{
 ui  TURNO =  JUGADOR->verTurnos();
 ui  numJugador= 1;


std::string cadenaTurno ="";
std::string cadenaJugador ="";
cadenaTurno = static_cast<std::ostringstream*>(&(std::ostringstream()<<TURNO))->str();
cadenaJugador=static_cast<std::ostringstream*>(&(std::ostringstream()<<numJugador))->str();

std::string ruta ="Jugador"+cadenaJugador+"Turno"+ cadenaTurno+rutas;
char* nombreRuta;
nombreRuta=(char*)ruta.c_str();
return nombreRuta;
}

/* NOTA DE CORRECCION : ACA SE COMPARA CON LAS LETRAS S - PARCELA SECA, P - PARCELA PODRIDA, X - PARCELA EN RECUPERACION
                        O - PARCELA VACIA. A, B Y C ES PARA LOS CULTIVOS. */

void Tablero::actualizarTableroCultivosTurnoActual(Terreno** TERRENO, Jugador* JUGADOR)
{	char tipo;
	ui filas=JUGADOR->obtenerFilMax();
	ui columnas=JUGADOR->obtenerColMax();
	for (ui i = 1; i < columnas; i++) {
		for (ui j = 1; j < filas; j++) {
			tipo='#';
			switch (tipo) {

			case '#' : RangedPixelToPixelCopy(parcelaVacia,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 'S' : RangedPixelToPixelCopy(cultivoSeco,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 'P' : RangedPixelToPixelCopy(cultivoPodrido,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 'Z' : RangedPixelToPixelCopy(cultivoAParaCosechar,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 'B' : RangedPixelToPixelCopy(cultivoBParaCosechar,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 'C' : RangedPixelToPixelCopy(cultivoCParaCosechar,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 'R' : RangedPixelToPixelCopy(parcelaEnRecuperacion,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			}
			std::cout<<std::endl;
		}
	std::cout<<std::endl;

	}

std:: string ruta = "tableroCultivos.bmp";
tableroSalida.WriteToFile(rutaImagenesSalida( JUGADOR,ruta));
}



/* NOTA DE CORRECCION : ACA SE COMPARA CON EL NUMERO DE TURNOS HASTA QUE ESTE DISPONIBLE LA COSECHA */
/*
void Tablero::actualizarTableroTurnosHastaCosecharse(Terreno** TERRENO, Jugador* JUGADOR, ui filas, ui columnas)
{
	for (int i = 1; i < columnas; i++) {
		for (int j = 1; j < filas; j++) {
			switch (TERRENO[j][i].turnosHastaSerDesocupada) {
			case 0 : RangedPixelToPixelCopy(ceroTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 1 : RangedPixelToPixelCopy(unTurno,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 2 : RangedPixelToPixelCopy(dosTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 3 : RangedPixelToPixelCopy(tresTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 4 : RangedPixelToPixelCopy(cuatroTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
		}
	}
	}
std::string ruta = "tableroTurnosHastaCosecharse.bmp";
	tableroSalida.WriteToFile(rutaImagenesSalida(JUGADOR,ruta));
}

*/
/* NOTA DE CORRECCION : ACA SE COMPARA CON EL NUMERO DE TURNOS HASTA QUE ESTE DISPONIBLE LA COSECHA */
/*
void Tablero::actualizarTableroTurnosHastaDesocuparParcelas(Terreno** terreno,Jugador* jugador, ui filas, ui columnas)
{
	for (int i = 0; i < columnas; i++) {
		for (int j = 0; j < filas; j++) {
			switch (terreno[j][i].turnosHastaSerDesocupada) {
			case 0 : RangedPixelToPixelCopy(ceroTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 1 : RangedPixelToPixelCopy(unTurno,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
			case 2 : RangedPixelToPixelCopy(dosTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 3 : RangedPixelToPixelCopy(tresTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
            case 4 : RangedPixelToPixelCopy(cuatroTurnos,0,59,59,0,tableroSalida, i*59+1 , j*59 + 1);
				break;
		}
	}
}
std::string ruta = "tableroTurnosRecuperacion.bmp";
tableroSalida.WriteToFile(rutaImagenesSalida(jugador,ruta));
}
*/
