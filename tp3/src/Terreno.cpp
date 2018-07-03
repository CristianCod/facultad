
#include "Terreno.h"
Terreno::Terreno() {
	this->Sembrada=false;
	this->Seca=false;
	this->regada=false;
	this->parcelaPodrida=false;
	this->seCosecho=false;
	this->enRecuperacion=false;
	this->Parcela.tipo = '#';
	this->Parcela.numeroDeRiegos = 0;
	this->Parcela.recuperacion = 0;
	this->Parcela.rentabilidad = 0;
	this->Parcela.tiempoHastaCosecha = 0;
	this->Parcela.tiempoTrasSiembra = 0;
	this->ESTADO = vacia;
}

char Terreno::mostrarTipo(){
	return this->Parcela.tipo;
}

bool Terreno::disponible(){
	bool disponible=false;
	if(this->ESTADO==sembrada){
		disponible=true;
	}
	return disponible;
}

bool Terreno::estaVacia(){
	return ((!this->Sembrada) && (!this->parcelaPodrida));
}

bool Terreno::listaCosechar(){
	return this->ESTADO==cosechar;
}
void Terreno::cambiarACosechado(){
	this->Parcela.rentabilidad  = 0;
	this->Parcela.tiempoHastaCosecha = 0;
	this->ESTADO = reposo;
	this->Parcela.numeroDeRiegos = 0;
	this->Parcela.tiempoTrasSiembra=0;
	this->seCosecho = true;
	this->Sembrada=false;
	this->regada=false;
	this->Parcela.tipo = '*';
}

void Terreno::actualizarParcelas(){
	if(this->ESTADO==sembrada){
		if(!this->regada){
			this->ESTADO=seca;
			this->Parcela.tipo='S';
			this->enRecuperacion=true;
		}else{
			this->Parcela.tiempoTrasSiembra++;
			this->regada=false;
			if(this->Parcela.tiempoHastaCosecha==this->Parcela.tiempoTrasSiembra){
				this->Parcela.siembra=this->Parcela.tipo;
				this->Parcela.tipo='C';
				this->ESTADO=cosechar;
			}
		}
	}
	else if(this->ESTADO==podrida||this->ESTADO==seca
			||this->ESTADO==reposo){
		this->Parcela.recuperacion--;
		if(this->Parcela.recuperacion==0){
			this->ESTADO=vacia;
			this->Sembrada=false;
			this->parcelaPodrida=false;
			this->Seca=false;
			this->enRecuperacion=false;
			this->Parcela.tipo='#';
		}
	}else if(this->ESTADO==cosechar){
		if(!this->seCosecho){
			this->ESTADO=podrida;
			this->Parcela.tipo = 'P';
			this->Parcela.tiempoHastaCosecha = 0;
			this->Parcela.numeroDeRiegos = 0;
			this->Parcela.tiempoTrasSiembra=0;
			this->Parcela.riegoPorTurno=0;
			this->parcelaPodrida = true;
		}
		else{
			this->ESTADO=reposo;
			this->Parcela.tipo='R';
		}
	}
}

char Terreno::mostrarCultivo(){
	return this->Parcela.siembra;
}

/********* quitar ccomentARIOS*/

ui Terreno::obtenerRentabilidad(){
	return this->Parcela.rentabilidad;
}

void Terreno::aumentarNumeroDeRiegos(){
	this->Parcela.numeroDeRiegos++;
	this->regada=true;
}


void Terreno::cambiarEstadoDeParcelaSembrada(Semilla * aSembrar){
	this->Parcela.rentabilidad = aSembrar->ganancia();
	this->Parcela.recuperacion = aSembrar->turnosRecuperacion();
	this->Parcela.tiempoHastaCosecha = aSembrar->turnosCosecha();
	this->Parcela.riegoPorTurno=aSembrar->cantidadAguaTurno();
	this->Sembrada = true;
	this->ESTADO = sembrada;
	this->Parcela.numeroDeRiegos = 0;
	this->Parcela.tipo=aSembrar->obtenerTipo();
}
ui Terreno::riegoNecesario(){

	return this->Parcela.riegoPorTurno;
}

