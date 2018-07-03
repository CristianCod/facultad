/*
 * ABB.h
 *
 *  Created on: 26 jun. 2018
 *      Author: cristian
 */

#ifndef SRC_ABB_H_
#define SRC_ABB_H_

#include <iostream>
template <class T>
class ABB
{
private:
  struct nodo
  {
	  T info;
	  struct nodo *izq;
	  struct nodo *der;
	  struct nodo *padre;
  };

  nodo *raiz;
  int elementos;

 public:
/*post: crea arbol*/
 	 ABB()
 	 {
      this->raiz=NULL;
      this->elementos=0;
 	 }
/*pre: arbol creado y un elemento agregado, sino devuelve basura.
 * post: muestra el primer elemento insertado*/
 	 T verRaiz (){
 		 return this->raiz->info;
 	 }
/*pre: dato T sin modificar
 * post: devuelve si existe*/

 	 bool existe(const T& clave){
 		nodo * iterar=this->raiz;
 	 	while(iterar!=NULL&&
 	 			iterar->info!=clave){
 	 		if(clave < iterar->info){
 	 			iterar=iterar->izq;
 	 		}
 	 		else{
 	 			iterar=iterar->der;
 	 		}
 	 	}
 	 	return iterar!=NULL;
 	 }

/*pre: dato tipo T, elemento no debe exixtir en el arbol
 * post: agrega elemento*/
 	 void agregar(T dato){
			altaElemento(this->raiz, dato, NULL);

 	 }


 	 /*pre: arbol creado y con elementos
 	  * post: recorre el arbol y muestra valores*/
 	 void verArbolInOrden(){
 		 if(this->raiz==NULL){
 			 throw std::string("NO hay elementos en el arbol");
 		 }
 		 else{
 			 verInOrden(this->raiz);
 		 }
 	 }
 	 /*post: devuelve cant de elementos*/
 	 int tamanio()
 	 {
 		 return elementos;
 	 }
 	 /*post: devuelve si el arbol tiene una unica hoja vacia*/

 	 bool vacio()
 	 {
 		 return this->raiz==0;
 	 }
 	/*pre: dato valido y existente, arbol creado
 	 * post: realiza baja del elemento*/
 	 void remover(T dato){
 		 if(this->raiz==NULL){
 	 		 throw std::string("El arbol esta vacio. ");
 	 	 }
 	 	 else{
 	 		 if(dato<this->raiz->info){
 	 			 remover(this->raiz->izq, dato);
 	 		 }else{
 	 			 remover(this->raiz->der, dato);
 	 		 }
 	 	 }
 	 }
 	 void remover(nodo*& arbol, T dato){
 		if(arbol==NULL){
 		 	std::cout<<"El elemento no existe. "<<std::endl;
 		return;}
 		else{
 			 if(dato<arbol->info){
 				 remover(arbol->izq, dato);
 			 }else if(dato>arbol->info){
 				 remover(arbol->der, dato);
 			 }
 			 else{
 				 eliminar(arbol, dato);
 			 }
 		}
 	 }
 	 void eliminar(nodo*aEliminar, T dato){
 		 if(aEliminar->der!=NULL&&aEliminar->izq!=NULL){
 			 nodo* mayorMenores=this->buscarMayorMenores(aEliminar->izq);
 			 aEliminar->info=mayorMenores->info;
 			 eliminar(mayorMenores, dato);
 		 }
 		 else if(aEliminar->izq!=NULL){
 			 cambiarNodo(aEliminar,aEliminar->izq);
 			 quitarNodo(aEliminar);
 		 }
 		 else if(aEliminar->der!=NULL){
 			 cambiarNodo(aEliminar,aEliminar->der);
 			 quitarNodo(aEliminar);
 		 }
 		 else {

 			 cambiarNodo(aEliminar, NULL);
 			 quitarNodo(aEliminar);
 		 }
 	 }
 	 void quitarNodo(nodo* nodo){
 		 nodo->der=NULL;

 		 nodo->izq=NULL;
 		 delete nodo;
 	 }

 	 void cambiarNodo(nodo* arbol, nodo*nuevo){
 		 if(arbol->padre!=NULL){
 			 if(arbol->info==arbol->padre->izq->info){
 				 arbol->padre->izq=nuevo;
 			 }else if(arbol->info==arbol->padre->der->info){
 				 arbol->padre->der=nuevo;
 			 }
 			 nuevo->padre=arbol->padre;

 		 }
 		 else{
 			 this->raiz=NULL;
 		 }
 	 }
 	 ~ABB()
 	 {
 		 //destruir(raiz);
 	 }
 private:
 	 /*post: agrega elemento desde rutina altaElemento(T dato)*/
 	 void altaElemento( nodo * &arbol, T dato, nodo*padre){
 		 if(arbol==NULL){
 			 nodo *nuevaHoja=crearHoja(dato, padre);

 			 arbol=nuevaHoja;
 			 if(this->raiz==NULL){
 				 this->raiz=arbol;
 			 }
 			 this->elementos+=1;
 		 }
 		 else{
 			 T datoHoja=arbol->info;
 		 	 if(dato < datoHoja){
 			 altaElemento(arbol->izq, dato, arbol);
 		 	 }
 		 	 else if(dato > datoHoja){
 			 altaElemento(arbol->der, dato, arbol);
 		 	 }
 		 	 else{
 		 		 std::cout<<"Elemento existente. "<<std::endl;
 		 	 }
 		 }
 	 }
 	 /*post: recorre arbol desde rutina verArbolInOrden*/
	 void verInOrden( nodo *arbol){

 		 if(arbol==NULL){
 			 return;
 		 }
 		 else{
 			 verInOrden(arbol->izq);
 			 std::cout<<arbol->info<<std::endl;
 			 verInOrden(arbol->der);
 		 }
 	 }

	 /*pre: dato tipo T, arbol creado, metodo subrutina de altaElemento()
	  * post: crea hoja con un dato T*/
 	 nodo* crearHoja(T dato, nodo* arbol){
 		nodo* nuevaHoja=new nodo;
 		 nuevaHoja->info=dato;
 		 nuevaHoja->der=NULL;
 		 nuevaHoja->izq=NULL;
 		 nuevaHoja->padre=arbol;
 		 return nuevaHoja;
 	 }
 	 /*
 	 void eliminar(nodo* aEliminar, T dato){
 		 if(aEliminar->padre!=NULL){
			 nodo* padre=aEliminar->padre;
 			 ordenarHojas(padre, aEliminar, dato);
 		 }
 		 else{
 			 this->raiz=NULL;
 		 }
 	 }
 	 */
 	 /*
 	 void ordenarHojas(nodo* padre, nodo*aEliminar, T dato){
 		if(aEliminar->der==NULL&&aEliminar->izq==NULL){;
 		nodo* padre=aEliminar->padre;
 			if(padre->izq->info==dato){
 				padre->izq=NULL;
 			}
 		    else{
 		    	padre->der=NULL;
 		  	}
 		    delete aEliminar;
 		 }
 		 else if(aEliminar->der!=NULL||aEliminar->izq!=NULL){
 		 	 nodo*padre=aEliminar->padre;
 		 	if(padre->izq->info==dato&&aEliminar->der!=NULL){
 		 		padre->izq=aEliminar->der;
 		 	}
 		 	else if(padre->der->info==dato&&aEliminar->izq!=NULL){
 		 	 	padre->der=aEliminar->izq;
 		 	}
 		 }
 		 else if(aEliminar->der!=NULL&&aEliminar->izq!=NULL){
 		 	nodo* mayorMenores=buscarMayorMenores(aEliminar);
 		 	aEliminar->info=mayorMenores->info;
 		 	nodo*padre=mayorMenores->padre;
 		 	ordenarHojas(padre, mayorMenores, dato);
 		 }
 	 }
*/
 	 nodo * buscarMayorMenores(nodo* arbol){
 		 nodo* mayorMenor=arbol;
 		 mayorMenor=mayorMenor->der;
 		 while(mayorMenor!=NULL){
 			 mayorMenor=mayorMenor->der;
 		 }
 		 return mayorMenor;

 	 }
 	 /*
 	 void buscarElemento(nodo *&arbol, T dato){
 		 if(arbol==NULL){
 			 std::cout<<"El elemento no existe. "<<std::endl;
 			 return;}
 		 else{
 			 if(dato<arbol->info){
 				 buscarElemento(arbol->izq, dato);
 			 }else if(dato>arbol->info){
 				 buscarElemento(arbol->der, dato);
 			 }
 			 else{
 				 eliminar(arbol, dato);
 			 }
 		 }

 	 }
 	 */
};

#endif /* SRC_ABB_H_ */
