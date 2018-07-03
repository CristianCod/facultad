/*
 * Almacen.cpp
 *
 *  Created on: 13/06/2018
 *      Author: gerard
 */
#include "Almacen.h"
#include<fstream>

Almacen::Almacen(ui tamanio){
	this->espacioDiscponible = tamanio;
	this->estaVacio = true;
	this->cosechas = new Lista<Cosecha*>;
	this->Destinos=new Lista<Destino*>;
	this->cantDestinos=0;
	cargarDestinos();
}

void Almacen::cargarDestinos(){
	std::string rutaEntrada = "Datos/destinos.txt";
	std::ifstream entrada;
	entrada.open(rutaEntrada.c_str());
	while (! entrada.eof()) {
		std::string nombre;
		float distancia;
		ui precio;
		char tipo;
		entrada>>nombre;
		if (! entrada.eof()) {
			Destino* destino = new Destino();
			entrada>> distancia;
			entrada>> precio;
			entrada>> tipo;
			destino->cargar(nombre,distancia,precio,tipo);
			this->Destinos->agregar(destino);
			this->cantDestinos+=1;
		}
	}
}

ui Almacen::numCosechas(){
	return this->cosechas->contarElementos();
}
void Almacen::mostrarDestinos(){
	ui i = 1;
	std::cout<<"******************************************************************"<<std::endl;
	std::cout<<"*************** LOS DESTINOS A DONDE PUEDE ENVIAR SON ************"<<std::endl;
	std::cout<<"******************************************************************"<<std::endl;
	this->Destinos->iniciarCursor();
	while (this->Destinos->avanzarCursor()){
		Destino* destino =  this->Destinos->obtenerCursor();
		std::cout<<i<<"|"<<destino->obtenerDestino()<<"|"<<
				destino->obtenerPrecio()<<"|"<<destino->obtenerTipo()<<"|"<<std::endl;
		i+=1;
	}
}
ui Almacen::numDestinos(){
	return this->cantDestinos;
}
ui Almacen::destinoElegido(ui opcion){
	Destino* destino= this->Destinos->obtener(opcion);
	ui cobro = destino->obtenerPrecio();
	return cobro;
}
/* ******** ACA ESTA LA DUDA TIENE O NO QE HABER UNA GANANCIA POR ENVIAR ************/
ui Almacen::transaccion(ui pos){
	Cosecha* cosecha = this->cosechas->obtener(pos);
	return cosecha->rentabilidad;
}

void Almacen::procesarSemillas(Lista<Semilla*>* semillas){
	semillas->iniciarCursor();
	while(semillas->avanzarCursor()){
		Semilla* semilla = semillas->obtenerCursor();
		Cosecha* cosecha = new Cosecha;
		cosecha->tipo = semilla->obtenerTipo();
		cosecha->cantidad = 0;
		cosecha->costo = semilla->precio();
		cosecha->rentabilidad = semilla->ganancia();
		this->cosechas->agregar(cosecha);
	}
}

ui Almacen::mostrarTamanio(){
	return this->espacioDiscponible;
}
void Almacen::descontarCosecha(ui posCosecha){
	this->cosechas->obtener(posCosecha)->cantidad-=1;
}
ui Almacen::verificarDestino(ui posCosecha){

	ui opcionDestino=this->opcionValida(this->numDestinos());
	if(!destinoValido(posCosecha, opcionDestino)){
			std::cout<<"No coincide el destino a enviar. "<<std::endl;
			opcionDestino=this->opcionValida(this->numDestinos());
	}
	return opcionDestino;

}
ui Almacen::enviarCosecha(ui posCosecha){
	ui opcionDestino;
	ui cobro;
	if(this->hayCosecha(posCosecha)){
		std::cout<<"A DONDE DESEA VENDER SU COSECHA."<<
				"CADA DESTINO TIENE UN TIPO DE COSECHA Y COSTOS DIFERENTES : "<<endl;
		this->mostrarDestinos();
		opcionDestino=this->verificarDestino(posCosecha);
		cobro = this->destinoElegido(opcionDestino);
	}else{
		cobro=0;
		throw std:: string("No hay cosecha de ese tipo.");
	}
	return cobro;

}
bool Almacen::destinoValido(ui posCos, ui opcDes){
	Cosecha *cosecha=this->cosechas->obtener(posCos);
	Destino *destino=this->Destinos->obtener(opcDes);
return cosecha->tipo==destino->obtenerTipo();
}
ui Almacen::opcionValida(ui max){
	ui opcion;
	std::cout<<"INgrese una opcion:"<<std::endl;
	std::cin>>opcion;
	if(opcion<1||opcion>max){
		opcionValida(max);
	}
	return opcion;
}
bool Almacen::hayCosecha(ui posCosecha){
	Cosecha*cosecha=this->cosechas->obtener(posCosecha);
	return cosecha->cantidad>0;
}
bool Almacen::hayEspacio(){
	return (this->espacioDiscponible)>0;
}
void Almacen::extenderCapacidad(ui tamanio){
	this->espacioDiscponible += tamanio;
}

void Almacen::agregarCosecha(char tipo){
	this->estaVacio = false;
	this->cosechas->iniciarCursor();
	while(this->cosechas->avanzarCursor()){
		Cosecha* cosecha = this->cosechas->obtenerCursor();
		agregarATipo(cosecha,tipo);
		this->espacioDiscponible-=1;
	}
}

void Almacen::agregarATipo(Cosecha* cosecha, char tipo){
	if (cosecha->tipo == tipo){
		cosecha->cantidad += 1;
	}
}

void Almacen::mostrarCosechas(){
	ui opcion=1;
	std::cout<<"********* SUS COSECHAS GUARDADAS SON ********"<<std::endl;
	std::cout<<"|TIPO DE COSECHA | CANTIDAD"<<endl;
	this->cosechas->iniciarCursor();
	while (this->cosechas->avanzarCursor()){
		Cosecha* cosecha = this->cosechas->obtenerCursor();
		std::cout<<opcion<<"|  "<<cosecha->tipo<<"  |   "<<cosecha->cantidad<<std::endl;
		opcion+=1;
	}
}

bool Almacen::coincideCosechaDestino(ui posCosecha,ui posDestino){
	Cosecha* cosecha = this->cosechas->obtener(posCosecha);
	Destino* destino = this->Destinos->obtener(posDestino);
	return (cosecha->tipo == destino->obtenerTipo());
}

Almacen::~Almacen(){
	this->cosechas->iniciarCursor();
	while(this->cosechas->avanzarCursor()){
		Cosecha*cosecha= this->cosechas->obtenerCursor();
	delete cosecha;
	}
	this->cosechas->~Lista();
	this->Destinos->iniciarCursor();
	while(this->Destinos->avanzarCursor()){
			delete this->Destinos->obtenerCursor();
	}
	this->Destinos->~Lista();
}




