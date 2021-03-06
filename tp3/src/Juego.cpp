
#include "Juego.h"
#include<iostream>
#include<fstream>


Juego::Juego() {
	this->jugadores=new Lista<Jugador*>;
	this->semillas = new Lista<Semilla*>;
	this->cantJugadores = 0;
	this->turnosJuego=0;
	this->potenciador = 0;
	this->juegoTerminado = false;
	this->jugadorActual=NULL;
	this->posJugadorEnJugadores=1;
	this->dificultad = 0;
	//this->tablero=new Tablero;
	agregarSemillas();

}


void Juego::agregarJugadores(ui cantidad){
	for(ui i=1; i<=cantidad; i++){
		Jugador *jugador=new Jugador(this->dificultad);
		this->jugadores->agregar(jugador);
		this->cantJugadores ++;
	}
	semillasAlAlmacendelJugador();
}

void Juego::semillasAlAlmacendelJugador(){
	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		Jugador* jugador = this->jugadores->obtenerCursor();
		jugador->procesoDeAlmacen(this->semillas);
	}
}

/***************************************************/
void Juego::asignar(){
	ui N,M;
	switch(this->dificultad){
	case 1: N = 3, M = 2;
		    break;
	case 2: N = 4, M = 3;
			break;
	case 3: N = 5, M = 4;
			break;
	}
	this->turnosJuego =2*N*M;
}

void Juego::elegirDificultad(){
	ui dificultad;
	std::cout<<"Ingrese una dificultad para los jugador/es(solo numeros): "<<std::endl;
	std::cout<<"1-Facil"<<std::endl;
	std::cout<<"2-Normal"<<std::endl;
	std::cout<<"3-Dificil"<<std::endl;
	std::cout<<"Ingrese una opcion: ";
	std::cin>>dificultad;
	if(dificultad>3||dificultad==0){
		elegirDificultad();
	}
	this->dificultad = dificultad;
	asignar();
}
/***************************************************/

Jugador* Juego::obtenerJugador(){
	return this->jugadorActual;
}

void Juego::contarTurnos(){

	this->turnosJuego--;
}

bool Juego::finJuego(){
		if(this->turnosJuego == 0){
			this->juegoTerminado = true;
		}
		return this->juegoTerminado;
	}


void Juego::comenzarTurno(){

	this->jugadores->iniciarCursor();
	while(this->jugadores->avanzarCursor()){
		this->jugadorActual=this->jugadores->obtenerCursor();
		this->potenciador = tirarDados();
		this->jugadorActual->agregarAgua(potenciador*5);
		Jugar();
	}
	contarTurnos();

}

void Juego::Jugar(){
	while(!(this->jugadorActual->noFinalizado())){
		mostrarOpciones();
	}
	this->jugadorActual->renovarTurno();
}

ui Juego::opcionValida(){
	ui opcion;
	std::cout <<"Opcion: ";
	std::cin>> opcion;
	if (opcion <= 0 || opcion > 7){
		opcionValida();
	}
	return opcion;

}

ui Juego::posicionDeJugador(){
	if (this->jugadores->contarElementos() < this->posJugadorEnJugadores){
		this->posJugadorEnJugadores = 1;
	}
	return this->posJugadorEnJugadores;
}

void  Juego::menu(){
	std::cout<<"HAY "<<this->cantJugadores<<" JUGADORES JUGANDO. "<<std::endl;
	std::cout<<"El jugador "<<posicionDeJugador()
			<<" esta jugando. "<<" Tiene "<<this->jugadorActual->totalDeCredito()<<" monedas."<<std::endl;

	std::cout<<"Tiene "<< this->turnosJuego<<" turnos."<<endl;
	std::cout<<"Tiro dados y obtuvo: "<<this->potenciador<<endl;
	std::cout<<"Tiene "<<this->jugadorActual->totalDeAgua()<<" unidades de riego."<<endl;
	std::cout<<"******* MENU *******"<<std::endl;
	std::cout<<"1)SEMBRAR."<<std::endl;
	std::cout<<"2)REGAR."<<std::endl;
	std::cout<<"3)COSECHAR."<<std::endl;
	std::cout<<"4)MERCADO."<<std::endl;
	std::cout<<"5)MOSTRAR ALMACEN."<<std::endl;
	std::cout<<"6)CAMBIAR TERRENO EN JUEGO."<<std::endl;
	std::cout<<"7)MOSTRAR TERRENO EN JUEGO."<<std::endl;
	std::cout<<"8)PASAR TURNO."<<std::endl;
}

/********************************** AGREGE ***********************************/
void Juego::mostrarSemillas(){
	ui i = 1;
	std::cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;
	std::cout<<"----------------------------------------------- TABLA DE SEMILLAS --------------------------------------------"<<endl;
	std::cout<<"--------------------------------------------------------------------------------------------------------------"<<endl;

	this->semillas->iniciarCursor();
	while (this->semillas->avanzarCursor()){
		Semilla* semilla = this->semillas->obtenerCursor();
		std::cout<<i<<")|Semilla: "<<semilla->obtenerTipo()<<" |Costo:  "<<semilla->precio()<<" |Turnos hasta Cosecha: "<<
			     semilla->turnosCosecha()<<" |Rentabilidad: "<<semilla->ganancia()<<
				 " |Tiempo Recuperacion: "<<semilla->turnosRecuperacion()<<
				 " |Agua necesaria: "<<semilla->cantidadAguaTurno()<<" | "<<endl;
		i++;
	}
}/*
void Juego::mostrarTablero(){
	Jugador* jugador=this->jugadorActual;
	this->tablero->actualizarTableroCultivosTurnoActual(this->jugadorActual->obtenerTerrenoEnTurno(), jugador);

}*/
void Juego::mostrarOpciones(){
	this->jugadorActual->mostrarTerreno();
	//his->mostrarTablero();

	menu();
	ui opcionMenu = this->opcionValida(1,8);

	switch(opcionMenu){
	case 1:{
		this->jugadorActual->sembrarTerreno(this->elegirCultivo());
		}break;
	case 2:
		this->jugadorActual->regarTerreno();
		break;
	case 3:
		this->jugadorActual->cosecharTerreno();
		break;
	case 4:
		this->jugadorActual->comprar();
		break;
	case 5:
		this->jugadorActual->mostrarAlmacen();
		break;
	case 6:{
		if(this->jugadorActual->numeroDeTerrenos() > 1){
			this->jugadorActual->obtenerTerrenoEnJuego(this->jugadorActual->terrenoValido());
		 }
		 else{
			 std::cout<<"** SOLO POSEE UN TERRENO **"<<endl;
		 }
		 std::cout<<endl;
		}break;
	case 7:
		mostrarOpciones();
		break;
	case 8:{
		this->posJugadorEnJugadores++;

		this->revisarEstados();
		this->jugadorActual->finalizarTurno();
		break;
		}
	}
}

ui Juego::obtenerTurnos(){
	return this->turnosJuego;
}

void Juego::revisarEstados(){
	this->jugadorActual->terrenosSembrados();
}

void Juego::agregarSemillas(){
	std::string rutaEntrada = "Datos/cultivos.txt";
	std::ifstream entrada;
	entrada.open(rutaEntrada.c_str());
	while (! entrada.eof()) {

		ui costo;
		ui tiempoCosecha;
		ui rentabilidad;
		ui tiempoRecup;
		ui aguaTurno;
		char tipo;

		entrada >> tipo;
		if (! entrada.eof()) {
			Semilla* semilla = new Semilla();
			entrada >> costo;
			entrada >> tiempoCosecha;
			entrada >> rentabilidad;
			entrada >> tiempoRecup;
			entrada >> aguaTurno;
			semilla->iniciar(tipo,costo,tiempoCosecha,rentabilidad,tiempoRecup,aguaTurno);
			this->semillas->agregar(semilla);
		}
	}
}

ui Juego::tirarDados(){
	ui potenciador= (1 + rand() % 6) ;
	return potenciador;
}
ui Juego::cantidadJugadores(){
	char cant;
	ui cantidad;
	std::cout<<"Ingrese la cantidad de jugadores: "<<std::endl;
	std::cin>>cant;
	if(!isdigit(cant)|| cant>'4'|| cant<'0'){
		std::cout<<"Ingrese una cantidad valida... "<<std::endl;
		cantidadJugadores();
	}
	else{
		cantidad=(ui)cant-'0';
	}
	return cantidad;
}
Semilla* Juego::elegirCultivo(){
	Semilla* semilla;
	mostrarSemillas();
	int cantidadSemillas = this->semillas->contarElementos();
	ui posCultivo=opcionValida(1,cantidadSemillas);
	semilla = this->semillas->obtener(posCultivo);
	return semilla;
}
ui Juego::opcionValida(ui min, ui max){
	ui opcion;
	char opc;
	std::cout <<"Opcion: ";
	std::cin>> opc;
	if (!isdigit(opc) || opc < (char)min+'0' || opc > (char)max+'0'){
		std::cout<<"Ingrese una opcion valida: "<<std::endl;
		opcionValida(min, max);
	}
	else{
		opcion=(ui)opc-'0';
	}
	return opcion;
}

Juego::~Juego() {
	this->jugadores->iniciarCursor();

	while(this->jugadores->avanzarCursor()){
		Jugador *jugador=this->jugadores->obtenerCursor();
		jugador->~Jugador();
		delete jugador;
		}
	this->jugadores->~Lista();

	semillas->iniciarCursor();

	while(this->semillas->avanzarCursor()){
		delete this->semillas->obtenerCursor();
		}
	this->semillas->~Lista();
	//delete this;
}
