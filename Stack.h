#ifndef STACK_H
#define STACK_H
#include "Node.h"

template <class T> 
class Stack {

    public:
        Stack();
        void push(T value);
        T pop();
        T peek();
        bool isEmpty();
        void clear();
        
    private:
        Node<T>* top;
        bool isEmptyStack();
};

//CASO : TEMPLATES
template <typename T>
Stack<T>::Stack(){
    this->top = NULL;
}

//push              APILAR EN LA CIMA DE LA PILA
template <typename T>                           
void Stack<T>::push(T value){               //nuevo nodo con valor recibido como parametro
    Node<T>* node = new Node<T>(value);     //estableciendo el siguiente del nuevo nodo como el nodo apuntado por top
    node->setNext(top);                     //actualiza top para apuntar a un nuevo nodo, convirtiendolo en el nuevo nodo superior de la pila
    top = node;
}

//pop                           DESAPILAR DE LA CIMA DE LA PILA
template <typename T>
T Stack<T>::pop(){
    if(!this->isEmptyStack()){              //para pila vacia
        Node<T>* node = this->top;          //nuevo nodo apuntando al nodo en la cima de la pila
        top = node->getNext();              //top al siguiente del nodo actual, eliminando asi el nodo superior de la pila
        T value = node->getValue();         //almacena el valor contenido dentro del nodo actual
        delete node;                        //eliminando nodo actual pa liberar memoria
        return value;                       //retornando valor almacenado
    }
    return NULL;
}

//peek                      OBTENER Y DEVOLVER EL VALOR CONTENIDO EN LA CIMA DE LA PILA
template <typename T>
T Stack<T>::peek(){
    if(!this->isEmptyStack()){          //pia vacia
        return this->top->getValue();       //valor dentro del nodo que es apuntado por top
    }
    return NULL;
}

//isEmpty                                   PILA VACIA
template <typename T>
bool Stack<T>::isEmpty(){
    return top == NULL;                 //si top apunta a null, la pila esta vacia
}

//clear                     VACIANDO PILA
template <typename T>
void Stack<T>::clear(){
    Node<T>* node;                  //puntero node T
    while(!this->isEmpty()){        //mientras la pila no este vacia
        node = this->top;           //node al puntero top
        top = top->getNext();       //moviendo el puntero top al siguiente nodo
        delete node;                //liberando memoria del nodo actual
    } 
}

//isEmptyStack                      EXCEPCION SI LA PILA ESTA VACIA
template <typename T>
bool Stack<T>::isEmptyStack(){
    if(this->isEmpty()){                                            //si la pila esta vacia
        std::string msg = "ADVERTENCIA: LA PILA ESTA VACIA";        //advertencia
        throw msg;                                                  //excepcion con la advertencia
    }
    return false;
}


#endif /* STACK_H */