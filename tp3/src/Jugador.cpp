/*
 * Jugador.cpp
 *
 *  Created on: 08/06/2018
 *      Author: gerard
 */

#include "Jugador.h"
#include "Terreno.h"
#include <fstream>
#include<iostream>
#include <string>


Jugador::Jugador(ui dificultad){
	this->terrenos=new Lista<Terreno**>;
	this->posicionTerrenoEnJuego=0;
	this->finTurno=false;
	this->tamanio.filas = 0;
	this->tamanio.culumnas = 0;
	this->cantTerrenos=0;
	this->terrenoEnJuego = NULL;
	this->aSembrar=NULL;
	//this->mercado=NULL;
	this->dificultad=dificultad;
	cargarDificJugador(dificultad);
	//his->mercado=new Mercado(cultivos);

}

/*********************************/
void Jugador::apuntarTerreno(){
	this->terrenoEnJuego = this->terrenos->obtener(1);
}

void Jugador::cargarDificJugador(ui dificultad){
	ui N,M;
	if(dificultad==1){
		N=5, M=5;
	}else if(dificultad==2){
		N=6, M=7;
	}else if(dificultad==3){
		N=7, M=9;
	}
	agregarTerreno(N+1,M+1);
	this->almacen=new Almacen(2*(N+M));
	this->estado.creditos=2*N*M;
	this->estado.cantAgua = 0;
	this->estado.turnosRestantes=2*N*M;
	this->tamanio.filas = N+1;
	this->tamanio.culumnas = M+1;
	this->estado.AguaMAX = N*M;
	apuntarTerreno();

}


ui Jugador::opcionValida(ui min, ui max){
	ui opcion;
	std::cout<<"Ingrese una opcion: "<<std::endl;
	std::cin>>opcion;
	if(opcion>max|| opcion<min){
		opcionValida(min, max);
	}
	return opcion;
}




void Jugador::comprarCapacAlmacen(){
	//porsu faltan metodos de comprobacion
	ui capac;
	std::cout<<"Ingrese la capacidad a agregar: "<<std::endl;
	cin>>capac;
	//Multiplicar costo por dificultad
	ui costo=capac*this->dificultad*this->cantTerrenos;
	if(hayCreditos(costo)){
		this->almacen->extenderCapacidad(capac);
		this->estado.creditos-=costo;
		std::cout<<"Se extendio el almacen en "<<capac<<std::endl;
	}else{
		std::cout<<"No hay creditos suficientes "<<std::endl;
	}
}

/*Metodo a practicar uso en todas las compras*/

bool Jugador::hayCreditos(ui costoCompra){
	ui comparacion=this->estado.creditos;
	return (comparacion-costoCompra)>=0;
}

void Jugador::venderCosecha(){
	ui opcionCosecha;
	this->almacen->mostrarCosechas();
	std::cout<<"ELIJA COSECHA A VENDER "<<endl;
	opcionCosecha=this->opcionValida(1, this->almacen->numCosechas());
	ui costo=this->almacen->enviarCosecha(opcionCosecha);
	if(hayCreditos(costo)){
		this->estado.creditos-=costo;
		ui ganancia=this->almacen->transaccion(opcionCosecha);
		this->almacen->descontarCosecha(opcionCosecha);
		this->estado.creditos+=ganancia;
		std::cout<<"Obtuvo "<<ganancia<<" creditos."<<std::endl;
	}
	else{
		std::cout<<"*** NO POSEE CREDITOS SUFICIENTES **"<<endl;
	}
}


/* Comprar Terreno */
void Jugador::comprarTerreno(){
	ui costo = ((this->tamanio.filas) * (this->tamanio.culumnas))/2;
	if (hayCreditos(costo)){
		this->agregarTerreno(this->tamanio.filas,this->tamanio.culumnas);
		this->estado.creditos -= costo;
		std::cout<<"** COMPRO EL TERRENO CON EXITO **"<<endl;
	}
	else{
		std::cout<<"** NO CUENTA CON SUFICIENTES CREDITOS PARA COMPRAR UN TERRENO **"<<endl;
	}
	cout<<endl;
}

void Jugador::venderTerreno(){
	ui posicion = 0;
	//ui numeroTerreno;
	ui costo = (((this->tamanio.filas) * (this->tamanio.culumnas))/2) - this->tamanio.culumnas;
	if(this->cantTerrenos > 1){
		while (posicion < 1 || posicion > this->cantTerrenos){
			std::cout<<"Tiene "<<this->cantTerrenos<<" terrenos. Cual desea vender."<<endl;
			std::cin>> posicion;
			//numeroTerreno=this->terrenoValido();
			this->terrenos->remover(posicion);
			this->estado.creditos -= costo;
		}
	}
	else{
		std::cout<<"** NO PUEDE VENDER UN TERRENO SI SOLO TIENE 1 **"<<endl;
	}
	apuntarTerreno();
	cout<<endl;
}

void Jugador::mostrarMenuCompras(){
	std::cout<<"1- COMPRAR TERRENO "<<std::endl;
	std::cout<<"2- VENDER TERRENO"<<std::endl;
	std::cout<<"3  VENDER COSECHA"<<std::endl;
	std::cout<<"4- COMPRAR ESPACIO DE ALMACEN "<<std::endl;
	std::cout<<"5- VOLVER AL MENU ANTERIOR "<<std::endl;
}

void Jugador::comprar(){
	bool seguirComprando=true;
	do{
		mostrarMenuCompras();
		ui opcion=opcionValida(1,5);
	switch(opcion){
	case 1:
		comprarTerreno();
			break;
	case 2:
		venderTerreno();
			break;
	case 3:
		venderCosecha();
		   break;
	case 4:
		comprarCapacAlmacen();
		break;
	case 5:
		seguirComprando=false;
		break;
	}
	}while(seguirComprando);

}

bool Jugador::noFinalizado(){
	return this->finTurno;
}

/***************** AGREGO TERRENO *******************/
void Jugador::agregarTerreno(ui fil, ui col){

	Terreno ** terreno = new Terreno*[fil];
	for( ui i = 1 ; i< fil; i++ ){
		//// VERIFICAR++++++++++++++++++++++++eergfrgege
	    terreno[i] = new Terreno[col];
	}
	this->terrenos->agregar(terreno);
	this->cantTerrenos+=1;
}

void Jugador::obtenerTerrenoEnJuego(ui posicionTerreno){
	this->terrenoEnJuego=this->terrenos->obtener(posicionTerreno);
}
ui Jugador::terrenoValido(){
	ui posTerreno = 0;
	while((posTerreno > this->cantTerrenos) || (posTerreno < 1)){
		std::cout<<"Tiene "<<this->cantTerrenos<<" terrenos. "<<std::endl;
		std::cout<<"A que terreno desea cambiar: "<<std::endl;
		std::cin>> posTerreno;
	}
	return posTerreno;
}

ui Jugador::filaColValido(ui maxFilCol){
	ui posicion;
	char pos;
	std::cin>>pos;
	if(!isdigit(pos)|| pos>(char)maxFilCol+'0'||pos<(char)1+'0'){
		std::cout<<"Ingrese una cantidad valida... "<<std::endl;
		filaColValido(maxFilCol);
		}
	else{
		posicion=(ui)pos-'0';
	}
	return posicion;
}


void Jugador::sembrarTerreno(Semilla * elegida){
	this->aSembrar = elegida;
	std::cout<<"Numero de Fila: ";
	ui fil=this->filaColValido(this->tamanio.filas);
	std::cout<<"Numero de Columna: ";
	ui col=this->filaColValido(this->tamanio.culumnas);

	if (this->terrenoEnJuego[fil][col].estaVacia()){
		this->terrenoEnJuego[fil][col].cambiarEstadoDeParcelaSembrada(this->aSembrar);
		this->estado.creditos-=this->aSembrar->precio();
		std::cout<<"******** SEMBRO CORRECTAMENTE *********"<<std::endl;
	}
	else{
		std::cout <<"***** LA PARCELA SE ENCUENTRA SEMBRADA O EN REPOSO *****"<<std::endl;
	}
}

void Jugador::regarTerreno(){
	std::cout<<"Numero de Fila: ";
	ui fil=this->filaColValido(this->tamanio.filas);
	std::cout<<"Numero de Columna: ";
	ui col=this->filaColValido(this->tamanio.culumnas);

	if (this->terrenoEnJuego[fil][col].disponible()&&this->estado.cantAgua>0){
		this->estado.cantAgua-=this->terrenoEnJuego[fil][col].riegoNecesario();
		this->terrenoEnJuego[fil][col].aumentarNumeroDeRiegos();
		std::cout<<"***** REGO CORRECTAMENTE *****"<<endl;
		std::cout<<"* LE QUEDAN "<<this->estado.cantAgua<<" UNIDADES DE RIEGO *"<<endl;
	}
	else{
		std::cout <<"***** INTENTA REGAR DONDE NO HAY NADA SEMBRADO*****"<<std::endl;
	}
}
void Jugador::cosecharTerreno(){
	std::cout<<"Numero de Fila: ";
	ui fil=this->filaColValido(this->tamanio.filas);
	std::cout<<"Numero de Columna: ";
	ui col=this->filaColValido(this->tamanio.culumnas);

	if(this->terrenoEnJuego[fil][col].listaCosechar()){
		//this->estado.creditos += this->terrenoEnJuego[fil][col].obtenerRentabilidad();
		if(this->almacen->hayEspacio()){
		this->almacen->agregarCosecha(this->terrenoEnJuego[fil][col].mostrarCultivo());
		this->terrenoEnJuego[fil][col].cambiarACosechado();
		std::cout<<"** COSECHO CORRECTAMENTE Y SU COSECHA FUE GUARDADA EN EL ALMACEN **"<<endl;
		}
		else{
			std::cout<<"NO HAY ESPACIO EN ALMACEN, DEBE COMPRARLO."<<std::endl;
		}
	}
	else{
		std::cout <<"***** NO SE PUEDE COSECHAR AÚN *****"<<std::endl;
	}
}

Terreno**Jugador::obtenerTerreno(){
	return this->terrenoEnJuego;
}

void Jugador::finalizarTurno(){
	this->finTurno=true;
}

void Jugador::renovarTurno(){
	this->finTurno = false;
}

/******************** MUESTRA EL TERRENO ******************************/
Terreno** Jugador::obtenerTerrenoEnTurno(){

	return this->terrenoEnJuego;
}

void Jugador::mostrarTerreno(){
	ui fila = this->tamanio.filas;
	ui columna = this->tamanio.culumnas;

	std::cout<<"\tBienvenido a granjeros. "<<endl;

	for(ui i = 1;i < fila;i++){
		std::cout<<"     "<<i;
		for(ui j = 1;j < columna;j++){
		std::cout<<"| "<<this->terrenoEnJuego[i][j].mostrarTipo()<<"| ";
		}

		std::cout<<endl;
	}
	std::cout<<endl;
}
/************** hasta aca********************************/
void Jugador::actualizar(){
	ui fila = this->tamanio.filas;
	ui columna = this->tamanio.culumnas;
	for (ui i= 1; i< fila;i++){
		for (ui j=1; j< columna;j++){
			this->terrenoEnJuego[i][j].actualizarParcelas();
		}
	}
}

void Jugador::terrenosSembrados(){
	this->terrenos->iniciarCursor();
	while(this->terrenos->avanzarCursor()){
		this->terrenoEnJuego = this->terrenos->obtenerCursor();
		this->actualizar();
	}
}

void Jugador::restarCredito(int cant){
	this->estado.creditos -= cant;
}

ui Jugador::totalDeCredito(){
	return this->estado.creditos;
}

ui Jugador::totalDeAgua(){
	return this->estado.cantAgua;
}

ui Jugador::numeroDeTerrenos(){
	return this->cantTerrenos;
}

void Jugador::agregarAgua(ui agua){
	if (agua > this->estado.AguaMAX){
		agua = this->estado.AguaMAX;
	}
	this->estado.cantAgua = agua;
}

void Jugador::procesoDeAlmacen(Lista<Semilla*>* semillas){
	this->almacen->procesarSemillas(semillas);
}

void Jugador::mostrarAlmacen(){
	this->almacen->mostrarCosechas();
}

Jugador::~Jugador() {
	this->almacen->~Almacen();

	this->terrenos->iniciarCursor();
	while(this->terrenos->avanzarCursor()){
		Terreno **terreno=terrenos->obtenerCursor();
		for(ui i=1;i<this->tamanio.filas;i++){
			delete[] terreno[i];
		}
		delete[] terreno;

	}
	delete this->almacen;
	this->terrenos->~Lista();

}



