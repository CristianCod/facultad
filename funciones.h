/*
 * funciones.h
 *
 *  Created on: 17 abr. 2018
 *      Author: cristian
 */

#ifndef SRC_FUNCIONES_H_
#define SRC_FUNCIONES_H_

struct estadoJugador{
	int creditos;
	int cantidadSemillasA;
	int cantidadSemillasB;
	int cantidadSemillasC;
	int unidadesDeRiego;
	int turnosRestantes;

};

struct Parcela{
	char estadoParcela;//El valor que se muestra en tablero
	bool estaSembrada;
	char tipoSiembra;//para verificar que semilla fue sembrada
	bool estaSeca;
	bool estaPodrida;
	bool cosechar;
	int recuperacion;
	int turnosCosecha;
	bool regada;
	bool estaCosechada;
	bool necesitaRecuperacion;

};

struct semillas{
	int precio;
	int cantidad;
	int turnosCosecha;
	char tipoCaracter;
	int rentabilidad;
	int turnosRecuperacion;
//Mostrar cantidad
};




void valoresIniciales(estadoJugador *jugador, semillas *TipoA,semillas *TipoB
		,semillas *TipoC);
void valoresIniciales(estadoJugador *jugador, semillas *TipoA,semillas *TipoB, semillas *TipoC);
void tirarDados(estadoJugador *jugador);
void crearTablero(Parcela **parcelas);
bool verificarEstadoCosecha(int fila,int  columna, Parcela **parcelas);
void rutinaSembrar(int fila, int columna, estadoJugador *jugador,
		Parcela **parcelas,semillas *tipoA, semillas *tipoB,
		semillas *tipoC, char tipoSemilla);
int mostrarOpciones();
bool menu(Parcela**parcelas,estadoJugador *jugador,semillas *tipoA, semillas*tipoB,
		semillas *tipoC);
void mostrarInfoSemillas(semillas *semillaTipoA, semillas *semillaTipoB,
		semillas *semillaTipoC);
bool verificoCantSemillas(char tipoSemilla, estadoJugador *jugador);
char elegirSemilla();
char comprobarTipoSemilla(char semillaElegida);
void mostrarInfoSemillas(semillas *semillaTipoA, semillas *semillaTipoB,
		semillas *semillaTipoC);
bool verificarParcelaSecaVacia(int fila, int columna, Parcela **parcelas);
bool verificoSiembra(Parcela **parcelas,int  fila, int columna);
void rutinaRegar(Parcela**parcelas, estadoJugador *jugador, int fila, int columna);
bool verificoCosechaParcela(Parcela **parcelas,int fila, int columna);
void actualizarCosecha(Parcela **parcelas, int fila, int columna);
void rentabilidad(int fila,int columna, Parcela **parcelas,semillas *tipoA,
		semillas *tipoB, semillas *tipoC,estadoJugador *jugador);
void comprarSemillas(semillas *tipoA,semillas *tipoB,semillas *tipoC,
		estadoJugador *jugador);
void contarTurnos(estadoJugador *jugador);
bool seguirJuego(estadoJugador *jugador);
void agregarCosechadas(Parcela **parcelas);
void recuperarParcelasCosechadas(Parcela**parcelas);
void borrarHeap(semillas *TipoA, semillas *TipoB, semillas *TipoC,estadoJugador *jugador, Parcela **parcelas);
void buscoParcelas(Parcela **parcelas, int fila, int columna);
void recuperarParcelaSecAnterior(Parcela **parcelas,int fila, int columna);
void agregarParcelaSeca(Parcela **parcelas);
void mostrarTablero(Parcela**parcelas, estadoJugador *jugador);



#endif /* SRC_FUNCIONES_H_ */
