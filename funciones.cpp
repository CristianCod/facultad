/*
 * sembrar.cpp
 *
 *  Created on: 17 abr. 2018
 *      Author: cristian
 */
#include "funciones.h"
#include <string>
#include <iostream>

#include <cstdlib>
using namespace std;


int mostrarOpciones(){
    int opcion;
	cout<<"1- Sembrar parcela: "<<endl;
	cout<<"2- Regar parcela: "<<endl;
	cout<<"3- Cosechar Parcela: "<<endl;
	cout<<"4- Comprar Semillas: "<<endl;
	cout<<"5- Mostrar Tablero: "<<endl;
	cout<<"6- Pasar turno(no se puede revertir): "<<endl;
	cout<<"7-Salir del juego..."<<endl;
	cout<<"Seleccione una opcion: "<<endl;
	cin>>opcion;
	//cout<<"_____________________________________"<<endl;

	if (opcion>7){
		opcion=0;
		cout<<"Ingreso una opcion Incorrecta...\n";
		cout<<"\n";
	}
    return opcion;
}


void valoresIniciales(estadoJugador *jugador, semillas *TipoA,semillas *TipoB
		,semillas *TipoC){
	(*jugador).creditos=50;
	(*jugador).unidadesDeRiego=0;
	(*jugador).turnosRestantes=10;
	jugador->cantidadSemillasA=0;
	jugador->cantidadSemillasB=0;
	jugador->cantidadSemillasC=0;
	(*TipoA).precio=1;
	(*TipoA).turnosCosecha=2;
	(*TipoA).cantidad=0;
	(*TipoA).tipoCaracter=(char)65;
	(*TipoA).rentabilidad=10;
	(*TipoA).turnosRecuperacion=1;
	(*TipoB).precio=3;
	(*TipoB).turnosCosecha=4;
	(*TipoB).cantidad=0;
	(*TipoB).tipoCaracter=(char)66;
	(*TipoB).rentabilidad=30;
	(*TipoB).turnosRecuperacion=2;
	(*TipoC).precio=2;
	(*TipoC).turnosCosecha=1;
	(*TipoC).cantidad=0;
	(*TipoC).tipoCaracter=(char)67;
	(*TipoC).rentabilidad=5;
	(*TipoC).turnosRecuperacion=0;

}
void crearTablero(Parcela **parcelas){
	 for(int i=0;i<=4;i++){
    	parcelas[i]=new Parcela[4];
	    }

	 for(int i=0;i<5;i++){
	   	for(int j=0;j<5;j++){
    		//cout<<"\nIngrese estado: ";
    		//cin>>(*(*(parcelas+i)+j));
    		//cin>>((*(*(parcelas+i)+j)).estadoParcela);
    		parcelas[i][j].estadoParcela=64;
    		/*
    		((*(*(parcelas+i)+j)).cosechar)=false;
    		((*(*(parcelas+i)+j)).estaPodrida)=false;
    		((*(*(parcelas+i)+j)).estaSeca)=false;
    		((*(*(parcelas+i)+j)).estaSembrada)=false;
    		((*(*(parcelas+i)+j)).necesitaRecuperacion)=NULL;
    		((*(*(parcelas+i)+j)).recuperacion)=10000;
    		((*(*(parcelas+i)+j)).regada)=NULL;
    		((*(*(parcelas+i)+j)).tipoSiembra)=64;
*/
	    	}
	    }
}

void tirarDados(estadoJugador *jugador){
    int numero;
	cout<<"Presione una tecla para tirar los dados \n";
    cin>>numero;
	unsigned short int unidadesRiego= 1+rand()%6;
	unidadesRiego=5*unidadesRiego;
	((*jugador).unidadesDeRiego)+=(unidadesRiego);

	if(((*jugador).unidadesDeRiego)>=25){
		cout<<"El tanque se llenó.\n";
		((*jugador).unidadesDeRiego)=25;

	}
	else{
		cout<<"Obtuvo "<<unidadesRiego<<" unidades de riego\n";
	}

}
void mostrarTablero(Parcela **parcelas, estadoJugador *jugador){
	cout<<"\nBienvenido a granjeros!!!"<<endl;

	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			//cout<<(*(*(parcelas+i)+j));
			cout<<"||\t"<<(parcelas[i][j].estadoParcela)<<"\t";
		}
		cout<<"||";
		cout<<"\n";
	}
/*
	cout<<"La letra S indica que una parcela se secó por no regarse a tiempo."
			"(No se podra sembrar por un turno )"<<endl;
	cout<<"Las letras A,B,C indican el tipo de cultivo que se sembro."<<endl;
	cout<<"El estado # indica que la parsela se puede cosechar."
			"El estado es * si se perdio la cosecha "<<endl;
*/
	cout<<"____________________________________________________________________________"<<endl;
	cout<<"Tiene "<<jugador->creditos<<" creditos disponibles.\n";
	cout<<"Tiene "<<jugador->unidadesDeRiego<< " unidades de agua para regar sus cultivos.\n";
	cout<<"Le quedan "<<jugador->turnosRestantes<<" turnos restantes\n";
	cout<<"\n";
	cout<<"Tiene "<<jugador->cantidadSemillasA<<" semillas tipo A para cosechar.\n";
	cout<<"Tiene "<<jugador->cantidadSemillasB<<" semillas tipo B para cosechar.\n";
	cout<<"Tiene "<<jugador->cantidadSemillasC<<" semillas tipo C para cosechar.\n";
	cout<<"____________________________________________________________________________"<<endl;

}
void elegirParcela(int *direccionParcela){
    int fila, columna;
	cout<<"Ingrese la posicion de la parcela(solo fila):"<<endl;
	cin>>fila;
	fila=(fila-1);
	cout<<"Ingrese la posicion de la parcela(solo columna):"<<endl;
	cin>>columna;
	columna=(columna-1);

	*(direccionParcela)=fila;
	*(direccionParcela+1)=columna;


	while((fila>5)||(columna>5)){
		cout<<"Ingrese la posicion de la parcela(solo fila):"<<endl;
		cin>>fila;
		fila=(fila-1);
		cout<<"Ingrese la posicion de la parcela(solo columna):"<<endl;
		cin>>columna;
		columna=(columna-1);

		*(direccionParcela)=fila;
		*(direccionParcela+1)=columna;

	}
}
////////////////////sembrar////////////////////////////////////////////////////////////////////////

bool verificarEstadoCosecha(int fila,int  columna, Parcela **parcelas){
	bool puedeUsarse;
	if((*(*(parcelas+fila)+columna)).necesitaRecuperacion==false){
		puedeUsarse=true;
	}else{
		puedeUsarse=false;
	}
	return puedeUsarse;
}
void cambiarEstadoParcela(int fila, int columna, Parcela **parcelas, char tipoSemillaMostrar){
	(*(*(parcelas+fila)+columna)).estadoParcela=tipoSemillaMostrar;
	cout<<"Se cambio el estado de la parcela correctamente.\n";
}
void agregarDatosParcela(Parcela **parcelas, int fila, int columna,
		char tipoSemilla){
	(*(*(parcelas+fila)+columna)).tipoSiembra=tipoSemilla;

	(*(*(parcelas+fila)+columna)).estaSembrada=true;
	//(*(*(parcelas+fila)+columna)).cosechar=false;
}
void agregarTurnosCosecha(Parcela **parcelas, int fila, int columna){
	switch(    ((*(*(parcelas+fila)+columna)).tipoSiembra)   ){
	case ((char)65):
			{
		((*(*(parcelas+fila)+columna)).turnosCosecha)=2;
			}break;
	case ((char)66):
			{
		((*(*(parcelas+fila)+columna)).turnosCosecha)=4;
			}break;
	case ((char)67):
			{
		((*(*(parcelas+fila)+columna)).turnosCosecha)=1;
			}break;
	}
}

void actualizarSemillas(estadoJugador *jugador, char tipoSemilla,
		semillas *tipoA, semillas *tipoB, semillas *tipoC){
	if(tipoSemilla==((*tipoA).tipoCaracter)){
		((*jugador).cantidadSemillasA)-=1;
	}
	else if(tipoSemilla==((*tipoB).tipoCaracter)){
		((*jugador).cantidadSemillasB)-=1;
	}
	else if(tipoSemilla==((*tipoC).tipoCaracter)){
		((*jugador).cantidadSemillasC)-=1;
	}
}
void mostrarInfoSemillas(semillas *semillaTipoA, semillas *semillaTipoB,
		semillas *semillaTipoC){
	cout<<"_______________________________________________________________________________\n";
	cout<<"a- tipo a "<<"La cosecha necesita "<<(*semillaTipoA).turnosCosecha<<" turnos"<<endl;
	cout<<"b- tipo b "<<"La cosecha necesita "<<(*semillaTipoB).turnosCosecha<<" turnos"<<endl;
	cout<<"c- tipo c "<<"La cosecha necesita "<<(*semillaTipoC).turnosCosecha<<" turnos"<<endl;
	cout<<"_______________________________________________________________________________"<<endl;

}

char elegirSemilla(){
	char semillaElegida=64;
	char tipoSemilla;

	cout<<"Que tipo de semilla va a sembrar? \n";
	cin>>semillaElegida;
	if(toupper(semillaElegida)==(char)65){
		tipoSemilla=65;
	   }
	else if(toupper(semillaElegida)==(char)66){
		tipoSemilla=66;
	    }
    else if(toupper(semillaElegida)==(char)67){
    	tipoSemilla=67;
	    }

    return tipoSemilla;
}



void recuperacionParcela(Parcela**parcelas, int fila, int columna, semillas *tipoA, semillas *tipoB, semillas *tipoC){
	if(  (*(*(parcelas+fila)+columna)).tipoSiembra==((*(tipoA)).tipoCaracter) ){

		((*(*(parcelas+fila)+columna)).recuperacion)=((*(tipoA)).turnosRecuperacion);

	}else if((*(*(parcelas+fila)+columna)).tipoSiembra==((*(tipoB)).tipoCaracter)){
		((*(*(parcelas+fila)+columna)).recuperacion)=((*(tipoA)).turnosRecuperacion);


	}else if((*(*(parcelas+fila)+columna)).tipoSiembra==((*(tipoC)).tipoCaracter)){
		((*(*(parcelas+fila)+columna)).recuperacion)=((*(tipoA)).turnosRecuperacion);

	}

}



bool verificoCantSemillas(char tipoSemilla, estadoJugador *jugador){
	bool haySemilla;

	if ((((*jugador).cantidadSemillasA)==0)&&(toupper(tipoSemilla)==(char)65)){
        haySemilla=false;
		cout<<"Le faltan semillas tipo 'a', comprelas en el menú \n";

		}
	else if((((*jugador).cantidadSemillasB)==0)&&(toupper(tipoSemilla)==(char)66)){
		haySemilla=false;
		cout<<"Le faltan semillas tipo 'b', comprelas en el menú \n";

		}
	else if((((*jugador).cantidadSemillasC)==0)&&(toupper(tipoSemilla)==(char)67)){
		haySemilla=false;
		cout<<"Le faltan semillas tipo 'c', comprelas en el menú \n";
		}
	else {
		haySemilla=true;
	}
	cout<<"\n";

	return haySemilla;
}
bool verificarParcelaSecaVacia(int fila, int columna, Parcela **parcelas){
	bool noSecayNoVacia=NULL;
	if (  !((*(*(parcelas+fila)+columna)).estaSeca)   ){
		if(   !((*(*(parcelas+fila)+columna)).estaSembrada)      ){
			noSecayNoVacia=true;
		}
		else{
			cout<<"La parcela elegida esta sembrada. "<<endl;
			noSecayNoVacia=false;
		}
	}else{
		cout<<"La parcela elegida esta seca. Espere un turno. "<<endl;
		noSecayNoVacia=false;
	}
	return noSecayNoVacia;
}



void rutinaSembrar(int fila, int columna, estadoJugador *jugador,
		Parcela **parcelas,semillas *tipoA, semillas *tipoB,
		semillas *tipoC, char tipoSemilla){

	cambiarEstadoParcela(fila, columna, parcelas, tipoSemilla);
	agregarDatosParcela(parcelas, fila, columna, tipoSemilla);
	agregarTurnosCosecha(parcelas, fila, columna);
	actualizarSemillas(jugador, tipoSemilla,tipoA,tipoB,tipoC );

}
////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////7////regar///////////////////////////////////////////////////////////
bool verificoSiembra(Parcela **parcelas,int  fila, int columna){
	bool estaSembrada=NULL;
	if ( (*(*(parcelas+fila)+columna)).estaSembrada  ){
		estaSembrada=true;
	}else{
		cout<<"La parcela no esta sembrada, elija otra."<<endl;
		estaSembrada=false;}
	return estaSembrada;
}
void rutinaRegar(Parcela**parcelas, estadoJugador *jugador, int fila, int columna){
	((*jugador).unidadesDeRiego)-=1;
	((*(*(parcelas+fila)+columna)).regada)=true;
	cout<<"Se rego la parcela correctamente"<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////

bool verificoCosechaParcela(Parcela **parcelas,int fila, int columna){
	bool sePuedeCosechar=NULL;
	if( ((*(*(parcelas+fila)+columna)).cosechar)==true   ){
		if(  ((*(*(parcelas+fila)+columna)).estaPodrida)==false ){
			sePuedeCosechar=true;
		}else{
			sePuedeCosechar=false;
			cout<<"La parcela esta Podrida, espere su recuperacion. "<<endl;
		}
	}else{
		sePuedeCosechar=false;
		cout<<"La parcela no esta lista para cosechar, espere los turnos indicados. "<<endl;
	}
	return sePuedeCosechar;
}
void actualizarCosecha(Parcela **parcelas, int fila, int columna){
	//(*(*(parcelas+fila)+columna)).estaPodrida=false;
	//(*(*(parcelas+fila)+columna)).estadoParcela=(char)64;
	(*(*(parcelas+fila)+columna)).estaSembrada=true;
	(*(*(parcelas+fila)+columna)).regada=true;
	(*(*(parcelas+fila)+columna)).necesitaRecuperacion=true;
	(*(*(parcelas+fila)+columna)).estaCosechada=true;
	(*(*(parcelas+fila)+columna)).cosechar=false;
}

void rentabilidad(int fila,int columna, Parcela **parcelas,semillas *tipoA,
		semillas *tipoB, semillas *tipoC,estadoJugador *jugador){
	if(  ((*(*(parcelas+fila)+columna)).tipoSiembra)== ((*tipoA).tipoCaracter) ){
		((*jugador).creditos)+=(*tipoA).rentabilidad;
		cout<<"Obtuvo más creditos!!!"<<endl;
	}else if(   ((*(*(parcelas+fila)+columna)).tipoSiembra)== ((*tipoB).tipoCaracter)   ){
		((*jugador).creditos)+=(*tipoB).rentabilidad;
		cout<<"Obtuvo más creditos!!!"<<endl;
	}
	else if (  ((*(*(parcelas+fila)+columna)).tipoSiembra)== ((*tipoC).tipoCaracter)  ){
		((*jugador).creditos)+=(*tipoC).rentabilidad;
		cout<<"Obtuvo más creditos!!!"<<endl;
	}
}
void comprarSemillas(semillas *tipoA,semillas *tipoB,semillas *tipoC,
		estadoJugador *jugador){
    int cantComprar;
    cout<<"a- tipo a "<<"La cosecha necesita "<<(*tipoA).turnosCosecha<<" turnos."<<"$"<<(*tipoA).precio;
    cout<<"\n"<<endl;
    cout<<"b- tipo b "<<"La cosecha necesita "<<(*tipoB).turnosCosecha<<" turnos."<<"$"<<(*tipoB).precio;
    cout<<"\n"<<endl;;
    cout<<"c- tipo c "<<"La cosecha necesita "<<(*tipoC).turnosCosecha<<" turnos."<<"$"<<(*tipoC).precio;
    cout<<"\n"<<endl;;
    //cout<<"Que tipo de semilla va a sembrar? \n";
    //cin>>semillaElegida;
    char semillaElegida=elegirSemilla();
	cout<<"¿Cuantas semillas quiere comprar?"<<endl;
	cin>>cantComprar;

	if (semillaElegida==((*tipoA).tipoCaracter)){
		(*jugador).cantidadSemillasA+=cantComprar;
		(((*jugador).creditos))-=((*tipoA).precio)*cantComprar;

	}
	else if(semillaElegida==((*tipoB).tipoCaracter)){
		(*jugador).cantidadSemillasB+=cantComprar;
		(((*jugador).creditos))-=((*tipoB).precio)*cantComprar;

	}
	else if(semillaElegida==((*tipoC).tipoCaracter)){
		(*jugador).cantidadSemillasC+=cantComprar;
		(((*jugador).creditos))-=((*tipoC).precio)*cantComprar;
	}

	cout<<"Se compro exitosamente...\n"<<endl;
}
void contarTurnos(estadoJugador *jugador){

((*jugador).turnosRestantes)=(((*jugador).turnosRestantes)-1);
	tirarDados(jugador);

}
bool seguirJuego(estadoJugador *jugador){
	bool comenzar;
	if(  (*(jugador)).turnosRestantes==0  ){
		comenzar=false;
		cout<<"Se quedo sin turnos"<<endl;
	}
	else if(((*(jugador)).turnosRestantes)>0){
		//(*(jugador)).turnosRestantes-=1;
		comenzar=true;


		}
	return comenzar;
	}
void agregarCosechadas(Parcela **parcelas){
	char listoParaCosechar=(char)42;
	for(int fila=0; fila<5;fila++){
		for(int columna=0; columna<5;columna++){

			if( (*(*(parcelas+fila)+columna)).estaSembrada
					&&(*(*(parcelas+fila)+columna)).regada){
				if(  (*(*(parcelas+fila)+columna)).turnosCosecha>0 ){
					(*(*(parcelas+fila)+columna)).turnosCosecha-=1;
				}
				else if( (*(*(parcelas+fila)+columna)).turnosCosecha==0){
					(*(*(parcelas+fila)+columna)).cosechar=true;
					(*(*(parcelas+fila)+columna)).estadoParcela=listoParaCosechar;
					(*(*(parcelas+fila)+columna)).estaPodrida=false;
				}
			}
		}
	}
}
void recuperarParcelasCosechadas(Parcela**parcelas){
	char listoSembrar=(char)64;
	for(int fila=0; fila<5;fila++){
			for(int columna=0; columna<5;columna++){
				if( (*(*(parcelas+fila)+columna)).necesitaRecuperacion){
					if ((*(*(parcelas+fila)+columna)).recuperacion>0){
						(*(*(parcelas+fila)+columna)).recuperacion-=1;
					}
					else if( (*(*(parcelas+fila)+columna)).recuperacion==0){
						(*(*(parcelas+fila)+columna)).estaSembrada=false;
						(*(*(parcelas+fila)+columna)).necesitaRecuperacion=false;
						(*(*(parcelas+fila)+columna)).regada=false;
						(*(*(parcelas+fila)+columna)).estaPodrida=false;
						(*(*(parcelas+fila)+columna)).estaCosechada=false;
						(*(*(parcelas+fila)+columna)).cosechar=false;
						(*(*(parcelas+fila)+columna)).estadoParcela=listoSembrar;

					}

				}

			}
	}
}
void recuperacionPodrida(int fila, int columna, Parcela**parcelas){
	 if((*(*(parcelas+fila)+columna)).tipoSiembra==(char)65){
		 (*(*(parcelas+fila)+columna)).recuperacion=1;
	 }else if( (*(*(parcelas+fila)+columna)).tipoSiembra==(char)66){
		 (*(*(parcelas+fila)+columna)).recuperacion=1;
	 }
	 else{
		 (*(*(parcelas+fila)+columna)).recuperacion=0;
	 }
}

void parcelasPodridas(Parcela**parcelas){
	char podrida=(char)35;
	for(int fila=0; fila<5;fila++){
			for(int columna=0; columna<5;columna++){
				if( (*(*(parcelas+fila)+columna)).cosechar&&
								!(*(*(parcelas+fila)+columna)).estaCosechada){
								(*(*(parcelas+fila)+columna)).estaPodrida=true;
								(*(*(parcelas+fila)+columna)).estadoParcela=podrida;
								(*(*(parcelas+fila)+columna)).necesitaRecuperacion=true;
								recuperacionPodrida(fila, columna, parcelas);
									}

			}
	}
}
//////////////////////////////parcelas secas/////////////////////////////////////////////////////////////

/*Si parcela no esta regada y esta sembrada, se seca cambiando icono
 *  correspondiente en tablero*/
void buscoParcelas(Parcela **parcelas, int fila, int columna){
	char iconoSeca=(char)83;//
	if( ((*(*(parcelas+fila)+columna)).estaSembrada)
	){
		if(  !((*(*(parcelas+fila)+columna)).regada)

		){	//La parcela se seca
			//cambiarEstadoParcela(fila, columna, parcelas, iconoSeca);
			(*(*(parcelas+fila)+columna)).estadoParcela=iconoSeca;
			(*(*(parcelas+fila)+columna)).estaSembrada=false;
			(*(*(parcelas+fila)+columna)).estaSeca=true;
		}
	}
}
/* Recupera una parcela que tenga el icono correspondiente en tablero y
 *  tenga valor bool estaSeca verdadero*/
void recuperarParcelaSecAnterior(Parcela **parcelas,int fila, int columna){
	char iconoDisponible=(char)64;
	if( ((*(*(parcelas+fila)+columna)).estaSeca)){
			if(  ((*(*(parcelas+fila)+columna)).estadoParcela)==(char)83  ){
				//La parcela se seca
				parcelas[fila][columna].estadoParcela=iconoDisponible;
				parcelas[fila][columna].estaSeca=false;
				parcelas[fila][columna].estaSembrada=false;//Con esta condicion no entraria en la busqueda de parcelas a secarse
				parcelas[fila][columna].estaPodrida=false;
			}
		}
}




/* Usa llamados a funciones anteriores para agregar y quitar parcelas secas*/
/* Recibe un struct doble puntero 'parcelas' del tipo parcela*/

void agregarParcelaSeca(Parcela **parcelas){
	for(int fila=0; fila<5;fila++){
		for(int columna=0; columna<5; columna++){
			recuperarParcelaSecAnterior(parcelas, fila, columna);
			buscoParcelas(parcelas, fila, columna);
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

void borrarHeap(semillas *TipoA, semillas *TipoB,semillas *TipoC,estadoJugador *jugador, Parcela **parcelas){
	delete TipoA;
	delete TipoB;
	delete TipoC;
	delete jugador;
	for(int i=0;i<=4;i++){
	   	delete[] parcelas[i];
		        }
    delete[] parcelas;
}


////////////////////////////////////////////////////////////////////////////////////////////////
bool menu(Parcela**parcelas,estadoJugador *jugador,semillas *tipoA, semillas*tipoB,
		semillas *tipoC){
		bool seguir=true;

		mostrarTablero(parcelas, jugador);
		int posicionParcela[1];
		int *posicionParcelaP=posicionParcela;
		int opcion=mostrarOpciones();

		switch(opcion){

		case 1:
		{	//sembrar
			elegirParcela(posicionParcelaP);
			int fila=*(posicionParcelaP);
			int columna=*(posicionParcelaP+1);
			mostrarInfoSemillas(tipoA, tipoB,tipoC);
			char tipoSemilla=elegirSemilla();
			bool haySemillas=verificoCantSemillas(tipoSemilla, jugador);
			bool noSecayVacia=verificarParcelaSecaVacia(fila, columna, parcelas);
			bool puedeUsarse=verificarEstadoCosecha(fila, columna, parcelas);
			if((haySemillas) &&(noSecayVacia) &&(puedeUsarse)){
				rutinaSembrar(fila,columna, jugador,parcelas,tipoA,tipoB, tipoC,tipoSemilla);
			}


		}break;

		case 2:
		{	//Regar
			elegirParcela(posicionParcelaP);
						int fila=*(posicionParcelaP);
						int columna=*(posicionParcelaP+1);
			bool estaSembrada= verificoSiembra(parcelas, fila, columna);
			if(estaSembrada){
				rutinaRegar(parcelas, jugador, fila, columna);
			}
		}break;

		case 3:{
			//Cosechar
			elegirParcela(posicionParcelaP);
			int fila=*(posicionParcelaP);
			int columna=*(posicionParcelaP+1);
	        bool cosecharNoPodrida= verificoCosechaParcela(parcelas, fila, columna);
	        if (cosecharNoPodrida ){
	        	rentabilidad(fila, columna, parcelas, tipoA,tipoB,tipoC, jugador);
	        	actualizarCosecha(parcelas, fila, columna);
	        	recuperacionParcela(parcelas, fila, columna,tipoA,tipoB,tipoC);
	        }}break;

		case 4:
		{		//Comprar Semillas
			comprarSemillas(tipoA, tipoB, tipoC,jugador);
		}break;

		case 5:
		{		//Mostrar Tablero
			mostrarTablero(parcelas, jugador);

		}break;

		case 6:
		{	//Pasar turno
			cout<<"Paso de turno.."<<endl;
			bool hayTurnos= seguirJuego(jugador);
			if(hayTurnos){
				agregarParcelaSeca(parcelas);
				parcelasPodridas(parcelas);
				agregarCosechadas(parcelas);
				recuperarParcelasCosechadas(parcelas);

				contarTurnos(jugador);
				//delete[] posicionParcela;

				}
			else{
				//delete[] posicionParcela;

				return seguir=false;
			}

		}break;

		case 7:{
			//salir
			cout<<"Se borro memo"<<endl;
			//delete[] posicionParcela;

			seguir=false;

		}break;
		case 0:
		{cout<<"Opcion Incorrecta..."<<endl;
		}break;
		cout<<"Se intento volver a borrr"<<endl;


		}//Fin switch


	return seguir;
}
