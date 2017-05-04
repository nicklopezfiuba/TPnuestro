

struct hash_iter{
    lista_iter_t* iterador_lista_actual;
    hash_t* hash_;
    size_t indice;
    size_t iterados;
};

// Crea iterador
hash_iter_t* hash_iter_crear(const hash_t *hash);
    hash_iter_t* iterador = malloc(sizeof(hash_iter_t));
    if(!iterador)   return NULL;

    if(hash->elementos == 0){

        iterador->iterador_lista_actual = lista_iter_crear(hash->tabla[hash->capacidad - 1]);
    }
    else{
        int i = 0;
        while(lista_esta_vacia(hash->tabla[i])){
            i++;
        }
        iterador->iterador_lista_actual = lista_iter_crear(hash->tabla[i]);

    }
    iterador->hash_ = hash;
    iterador->indice = i;
    iterador->iterados = 1;
    return iterador;
}

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter){
    if(hash_iter_al_final(iter))    return false;

    if(lista_iter_avanzar(iter->iterador_lista_actual)){
        if(lista_iter_al_final(iter->iterador_lista_actual)){   // Se "Salta" a la lista siguiente
            int i = iter->indice;
            i = i + 1;
            while(i < iter->hash_->capacidad && lista_esta_vacia(iter->hash_->tabla[i])){
                i++;
            }
            if(i < iter->hash_->capacidad){
                lista_iter_destruir(iter->iterador_lista_actual);
                iter->iterador_lista_actual = lista_iter_crear(iter->hash_->tabla[i]);
                iter->indice = i;
            }
        }
        iter->iterados = iter->iterados + 1;
        return true;
    }
    return false;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char* hash_iter_ver_actual(const hash_iter_t *iter){
    return (lista_iter_ver_actual(iter->iterador_lista_actual))->clave;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter){
    if(iter->iterados > iter->hash_->elementos) return true;
    return false;
}


// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter){
    lista_iter_destruir(iter->iterador_lista_actual);
    free(iter);
}
