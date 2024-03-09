#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"
template <class T>
class Queue{
    
    public:
        Queue();
        void add(T value);
        T remove();
        T peek();
        bool isEmpty();
        void clear();
    
    private:
        Node<T>* header;
        Node<T>* end;
        bool isEmptyQueue();
};
//templates

template <typename T>
Queue<T>::Queue(){
    this->header = NULL;
    this->end = NULL;
}

//add       INSERTAR ELEMENTO AL FINAL DE LA COLA
template <typename T>   
void Queue<T>::add(T value){        
    Node<T>* node = new Node<T>(value);     //se crea un nuevo nodo con el valor recibido como parámetro.
    if(this->isEmpty()){                    //si la cola esta vacia
        this->header = node;                //se asigna el nodo recién creado como el header de la cola.
    }
    else{                                   //si la cola no esta vacia
        end->setNext(node);                 //se establece el siguiente del nodo apuntado por "end" hacia el nodo recién creado
    }
    this->end = node;                       //Se actualiza el puntero de end para que apunte al nuevo nodo, ahora es el último elemento en la cola
}

//remove            QUITAR ELEMENTO DE LA CIMA DE LA COLA
template <typename T>
T Queue<T>::remove(){                       
    if(!this->isEmptyQueue()){                  //si la cola no esta vacia
        Node<T>* node = this->header;           //creamos un nuevo nodo que apunta hacia el header actual
        header = node->getNext();               //establecemos el header al siguiente del nodo actual
        T value = node->getValue();             //almacenamos el valor contenido dentro del nodo actual
        delete node;                            //eliminamos el nodo actual
        return value;                           //retornamos el valor almacenado
    }
    return NULL;
}

//peek                  TOMA Y DEVUELVE EL VALOR DE LA CIMA DE LA COLA
template <typename T>
T Queue<T>::peek() {                                           
    if(!this->isEmptyQueue()){          //si la cola no esta vacia    
        return header->getValue();      //devuelve el valor contenido dentro del nodo apuntado por header
    }
    return NULL;
}

// isEmpty                  REVISAMOS SI LA COLA ESTA VACIA
template <typename T>
bool Queue<T>::isEmpty(){
    return this->header == NULL;        //true si el puntero header apunta a NULL -> la cola está vacía
}

//clear                 VACIANDO LA COLA
template <typename T>
void Queue<T>::clear(){
    Node<T>* node;                      //declaramos un puntero a nodo para almacenar temporalmente cada nodo que se eliminará
    while(!this->isEmpty()){            //iterando hasta que la cola este vacia
        node = this->header;            //asignamos el puntero actual del header al puntero del nodo temporal
        header = header->getNext();     //actualizamos header para que apunte al siguiente nodo en la cola
        delete node;                    //borrando nodo almacenado en el nodo temporal
    }
}

//isEmptyQueue                      VERIFICANDO COLA VACIA Y ALERTANDO CON EXCEPCION
template <typename T>
bool Queue<T>::isEmptyQueue(){
    if(this->isEmpty()){                                                //verificando si la cola esta vacia
        std::string msg = "ADVERTENCIA: LA COLA ESTA VACIA";            //alerta si la cola esta vacia
        throw msg;                                                      //EXCEPCION CON ALERTA
    }
    return false;                                                       //LA COLA NO ESTAVACIA
}


#endif /* QUEUE_H */