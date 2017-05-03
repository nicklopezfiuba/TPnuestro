#include "hash.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define CAPAC 1000  // deberia ser numero primo para que el hash distribuya mejor segun martin.
#define CAPACIDAD 53  // Me parece mejor que empiece de menor tamaño e ir redimensionando si se necesita mas,
                      // sino tenia que guardar 3000 datos antes de redimensionar

                      //Las documentaciones de las funciones ya estan en el .h

//ESTRUCTURAS DE DATOS

typedef struct nodo{
  void* dato;
  char* clave;
}hash_nodo_t;

struct hash{
    void* tabla;
    hash_destruir_dato_t* funcion_destruir;
    size_t elementos;
    size_t capacidad;
};

//PRIMITIVAS nodo

hash_nodo_t* hash_nodo_crear(char* clave, void* dato){
  hash_nodo_t* nodo = malloc(sizeof(hash_nodo_t));
  if(!nodo) return NULL;

  nodo->clave = strdup(clave);      //para que el usuario no pueda modificar el contenido de su puntero y romper el hash
  nodo->dato = dato;

  return nodo;
}
void hash_nodo_destruir(hash_nodo_t* nodo, hash_destruir_dato_t destruir_dato){
  destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}
void hash_nodo_reemplazar_dato(hash_nodo_t* nodo, void* dato, hash_destruir_dato_t destruir_dato){
  destruir_dato(nodo->dato);
  nodo->dato = dato;
}

//FUNCION HASHING

int hash_func(char* clave, int capacidad){
    char* claveIter = clave;
    int suma = 0;                       //suma de los valores numericos de los caracteres de la clave
    while(*claveIter != '\0'){
      suma += (int)*claveIter;
      claveIter++;                      //avanza puntero
    }
    return suma % capacidad;
}

//FUNCIONES AUXILIARES



//Busca una clave dentro de una lista y devuelve un iterador posicionado en el nodo que posee esa clave,
//o devuelve NULL si no se encontro la clave.
lista_iter_t* lista_buscar_clave(lista_t* lista, char* clave){
  lista_iter_t* listaIter = lista_iter_crear(lista);

  hash_nodo_t* nodoActual = lista_iter_ver_actual(listaIter);
  while(!lista_iter_al_final(listaIter) && strcmp(nodoActual->clave, clave)){
    lista_iter_avanzar(listaIter);
    nodoActual = lista_iter_ver_actual(listaIter);
  }
  if(lista_iter_al_final(listaIter)){
    lista_iter_destruir(listaIter);
    return NULL;
  }
  return listaIter;
}
lista_iter_t* hash_buscar_clave(hash_t* hash, char* clave){
  int pos = hash_func(clave, hash->capacidad);
  return lista_buscar_clave(hash->tabla[pos], clave);
}

//PRIMITIVAS HASH

hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;

    hash->tabla = malloc(sizeof(lista_t) * CAPACIDAD);  //En casa agrego a la carpeta la implementacion de la lista
    if(!hash->tabla){
        free(hash);
        return NULL;
    }
    for (size_t i = 0; i < CAPACIDAD; i++) {
      tabla[i] = lista_crear();
      if(!tabla[i]){
        for (size_t j = 0; j < i; j++) {
          lista_destruir(tabla[j]);
        }
        free(hash->tabla);
        free(hash);
        return NULL;    //que te parece esta parte? me parece que me complique de mas
      }
    }

    hash->elementos = 0;
    hash->funcion_destruir = &destruir_dato;
    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){ //FALTA REDIMENSIONADO
    lista_iter_t* iterEnNodoEncontrado = hash_buscar_clave(hash, clave);  //si se te ocurre otro nombre descriptivo no tan largo metelo
    if(iterEnNodoEncontrado){
      hash_nodo_reemplazar_dato(lista_iter_ver_actual(iterEnNodoEncontrado), dato, hash->destruir_dato);
      lista_iter_destruir(iterEnNodoEncontrado);
    }else{
      hash_nodo_t* nodo = hash_nodo_crear(clave, dato);
      if(!nodo) return false;
      lista_insertar_primero(hash->tabla[hash_func(clave, hash->capacidad)], nodo);
    }
    return true;
}
void *hash_borrar(hash_t *hash, const char *clave){

}
void* hash_obtener(const hash_t *hash, const char *clave){
  lista_iter_t* iterEnNodoEncontrado = hash_buscar_clave(hash, clave);
  if(iterEnNodoEncontrado){
    hash_nodo_t* nodo = lista_iter_ver_actual(iterEnNodoEncontrado);
    lista_iter_destruir(iterEnNodoEncontrado);
    return nodo->dato;
  }
  return NULL;
}
bool hash_pertenece(const hash_t *hash, const char *clave){
  lista_iter_t* iterEnNodoEncontrado = hash_buscar_clave(hash, clave);
  if(iterEnNodoEncontrado){
    lista_iter_destruir(iterEnNodoEncontrado);
    return true;
  }
  return false;
}
size_t hash_cantidad(const hash_t *hash){
    return hash->elementos;
}
void hash_destruir(hash_t *hash){
  
}
