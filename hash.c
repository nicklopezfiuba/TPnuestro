#include "hash.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPAC 1000  //Capacidad

// Para guardar la clave y dato en cada Nodo, creo que podemos diseniar un struct mas (Nodo_hash)
// Segun tengo graficado en la carpeta hay que guardar ambos, esta es una duda a preguntar
// maniana.
//     void* dato;
//     char* key;

typedef struct hash_interno{
    lista_t* lista;
}hash_interno_t;


struct hash{
    hash_interno_t* datos;                       
    hash_destruir_dato_t* funcion_destruir;
    size_t elementos;                            // Elementos del Hash
};


/* Crea el hash
 */
hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;

    hash->datos = malloc(sizeof(hash_interno_t) * CAPAC);
    if(!hash->datos){
        free(hash);
        return NULL;
    }

    hash->elementos = 0;
    hash->funcion_destruir = &destruir_dato;
    return hash;
}



/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato){
}



/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura hash fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *hash_borrar(hash_t *hash, const char *clave){
}




/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada
 */
void* hash_obtener(const hash_t *hash, const char *clave){
}



/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada
 */
bool hash_pertenece(const hash_t *hash, const char *clave){

}



/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada
 */
size_t hash_cantidad(const hash_t *hash){
    return hash->elementos;

}



/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida
 */
void hash_destruir(hash_t *hash){

}
