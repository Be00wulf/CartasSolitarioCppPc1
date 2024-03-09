#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <iostream>


template <class T>
class DoublyLinkedList {
    
    public:
        DoublyLinkedList();
        void addFirst(T value);
        void addLast(T value);
        void add(int index, T value);
        T getFirst();
        T getLast();
        T get(int index);
        int indexOf(T value);
        void removeFirst();
        void removeLast();
        void removeIndex(int index);
        void removeValue(T value);
        bool isEmpty();
        void clear();
        int size();
        
    private:
        Node<T>* header;
        Node<T>* end;
        bool isEmptyList();
        bool isArrayOutOfBounds(int index);
        void remove(Node<T>* node);
};

//constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
    this->header = NULL;
    this->end = NULL;
}

//addFirst          AGREGANDO UN NUEVO NODO AL INICIO DE LA LISTA
template <typename T>
void DoublyLinkedList<T>::addFirst(T value){        
    Node<T>* node = new Node<T>(value);         //creando nodo
    if(this->isEmpty()){                        
        this->header = node;                    //asignar header y end a una lista vacia
        this->end = node;
    }
    else{
        node->setNext(this->header);            //cuando la lista no esta vacia se agrega el nuevo noodo al principio de la lista
        this->header->setPrevious(node);        //asignamos el siguiente del nuevo nodo al header actual
        this->header = node;                    //actualizando header para apuntar al nuevo nodo
    }
} 

//addLast       AGREGANDO NODO AL FINAL DE UNA LISTA
template <typename T>
void DoublyLinkedList<T>::addLast(T value){
    Node<T>* node = new Node<T>(value);         //creando nodo
    if(this->isEmpty()){                        //lista vacia
        header = node;                          //con la lista vacia asignamos el header y el end al nuevo nodo
        end = node;
    }
    else{                                   //en caso no este vacia se agrega el nodo al final de la lista
        node->setPrevious(this->end);       //el nodo previo al nuevo nodo como el end actual
        this->end->setNext(node);           //establecemos el siguiente del end actual hacia el nuevo nodo
        end = node;                         //actualizamos el end para que apunte al nuevo nodo
    }
} 

//add           INSERTAMOS NUEVO NODO EN EL INDICE DE LA LISTA QUE RECIBE COMO PARAMETRO
template <typename T>
void DoublyLinkedList<T>::add(int index, T value){
    if(index == this->size()){              //revisar si el indice es igual a la longitud de la lista
        this->addLast(value);               //Si es así, insertar el nuevo elemento justo después del último elemento de la lista
    }
    else{       //si la lista no esta vacia y el indice esta dento de los limites
        if(!this->isEmptyList()){
            if(!this->isArrayOutOfBounds(index)){
                int actualIndex = 0;                //inicializamos 
                for(Node<T>* actualNode = this->header; actualNode != NULL; actualNode = actualNode->getNext()){        //iteramos sobre los nodos de la lista
                    if(actualIndex == index){               //debemos verificar si el indice actual = indice donde se desea insertar
                        if(actualNode == this->header){     
                            this->addFirst(value);              //si el nodo actual = header llamamos al metodo
                            break;
                        }
                        else{       //lista vacia y el indice esta dento de los limites
                            Node<T>* newNode = new Node<T>(value);              //creamos nodo con el valor recibido como parametro
                            actualNode->getPrevious()->setNext(newNode);        //Establecer el siguiente del nodo previo al nuevo nodo
                            newNode->setPrevious(actualNode->getPrevious());    //Establecer el previo del nuevo nodo al previo del nodo actual
                            newNode->setNext(actualNode);                       //Establecer el siguiente del nuevo nodo al nodo actual
                            actualNode->setPrevious(newNode);                   //Establecer el previo del nodo actual al nodo nuevo
                            break;
                        }
                    }
                    actualIndex++;
                }
            }
        }
    }
}

//getFirst              DEVOLVIENDO VALOR DEL NODO AL FRENTE DE LA LISTA
template <typename T>
T DoublyLinkedList<T>::getFirst(){
    if(!this->isEmptyList()){                   //si la lista no esta vacia
        return this->header->getValue();        //retornamos el valor almacenado en el primer nodo, referenciado por el header 
    }
    return NULL;
}

//getLast                   DEVUELVE EL VALOR DEL NODO AL FINAL DE LA LISTA
template <typename T>
T DoublyLinkedList<T>::getLast(){
    if(!this->isEmptyList()){                   //si l alista no esta vacia
        return this->end->getValue();           //devuelve el valor almacenado en el ultimo nodo, referenciado por end
    }
    return NULL;
}

//get           DEVUELVE EL VALOR CONTENIDO DEL NODO DONDE EL INDICE SE RECIBE COMO PARAMETRO
template <typename T>
T DoublyLinkedList<T>::get(int index){
    if(!this->isEmptyList()){                       //cuando la lista no este vacia 
        if(!this->isArrayOutOfBounds(index)){       //verificamos si el indice esta dentro de los limites de la lista
            int actualIndex = 0;                    //inicializamos
            for(Node<T>* node = this->header; node != NULL; node = node->getNext()){    //Recorrer la lista para encontrar el nodo en el índice especificado
                if(index == actualIndex){           // si el índice actual coincide con el índice especificado
                    return node->getValue();        //evuelve el valor contenido en el nodo actual
                }
                actualIndex++;      //si no  hya coincidecias avanzar al siguiente nodo y aumentar el índice actual en 1
            }
        }      
    }
    return NULL;
}

//indexOf           OBTIENE EL INDICE DEL NODO CUYO VALOR SEA IGUAL AL QUE SE RECIBE COMO PARAMETRO
template <typename T>
int DoublyLinkedList<T>::indexOf(T value){
    if(!this->isEmptyList()){                   //si la lista esta vacia
        int index = 0;                  //inicializamos
        for(Node<T>* node = this->header; node != NULL; node = node->getNext()){    //recorremos la lista desde el header hasta el uultimo nodo
            if(node->getValue() == value){      //si coincide el valor, se devuelve el indice actual
                return index;                   
            }
            index++;        //si no hay coincidencias, avanzar al siguiente nodo y aumentar el índice en 1
        }
    }
    return -1;          //Si no se encuentra ningún nodo con el valor buscado, se devuelve -1
}    

//removeFirst                   ELIMINANDO PRIMER NODO DE LA LISTA
template <typename T>
void DoublyLinkedList<T>::removeFirst(){
    if(!this->isEmptyList()){                   //que lista no esté vacía
        Node<T>* node = this->header;           //Crear un nuevo nodo que apunta al header
        if(this->header == this->end){          //ver si el header y el end apuntan al mismo nodo
            this->header = NULL;                //Si el header y el end son iguales, establecer ambos a NULL
            this->end = NULL;
        }
        else{
            this->header = node->getNext();         //Si no, mover el header al siguiente nodo y establecer el previo del siguiente nodo a NULL
            node->getNext()->setPrevious(NULL);
        }
        delete node;
    }
} 

//removeLast                ELIMINANDO EL ULTIMO NODO DE LA LISTA
template <typename T>
void DoublyLinkedList<T>::removeLast(){
    if(!this->isEmptyList()){           //Validar que la lista no esté vacía
        Node<T>* node = this->end;      // Crear un nuevo nodo que apunta al end
        if(this->header == this->end){  //Comprobar si el header y el end apuntan al mismo nodo
            this->header = NULL;        //Si el header y el end son iguales, establecer ambos a NULL
            this->end = NULL;           //Si el header y el end son iguales, establecer ambos a NUL
        }
        else{
            this->end = node->getPrevious();        //Si no, mover el end al nodo previo y establecer el siguiente del nodo previo a NULL
            node->getPrevious()->setNext(NULL);
        }
        delete node;        //Eliminar el nodo actual
    }
} 

//removeIndex               ELIMINANDO NODO EN FUNCION DEL INDICE QUE SE RECIBE COMO PARAMETRO
template <typename T>
void DoublyLinkedList<T>::removeIndex(int index){
    if(!this->isEmptyList()){                       //Verificar que la lista no esté vacía
        if(!this->isArrayOutOfBounds(index)){           //Verificar que el índice esté dentro de los límites de la lista
            int actualIndex = 0;
            for(Node<T>* node = this->header; node != NULL; node = node->getNext()){    //Recorrer la lista desde el header
                if(actualIndex == index){       //Si el índice actual coincide con el índice del nodo que se desea eliminar
                    this->remove(node);         //para eliminar el nodo actual
                    break;
                }   
            actualIndex++;          // Incrementar el índice actual
            }
        }
    }
}


//isEmpty               VERIFICAR SI UNA LISTA ESTA VACIA
template <typename T>
bool DoublyLinkedList<T>::isEmpty(){        //Verificar si tanto el header como el end apuntan a NULL
    return this->header == NULL && end == NULL;
}

//clear                     ELIMINANDO TODOS LOS NODOS DE LA LISTA
template <typename T>
void DoublyLinkedList<T>::clear(){
    if(!this->isEmpty()){        //Verificar si la lista no está vacía
        int length = this->size();      //Obtener la longitud de la lista
        for(int i =0; i < length; i++){     //Iterar sobre la lista y eliminar cada nodo llamando al método removeFirst()
            this->removeFirst();    
        }
    }
}

//size          OBTIENE Y RETORNA LA LONGITUD DE LA LISTA
template<typename T>
int DoublyLinkedList<T>::size(){        //Verificar si la lista está vacía
    if(this->isEmpty()){                //retornar 0
        return 0;
    }
    else{                               //Si la lista no está vacía, inicializar el contador de tamaño en 1
        int size = 1;
        for(Node<T>* node = this->header; node != end; node = node->getNext()){         //Iterar sobre la lista desde el header hasta el end y contar los nodos
            size++;         // Incrementar el tamaño por cada nodo encontrado
        }
        return size;        //Retornar el tamaño calculado
    }
}

// /isEmptyList             LISTA VACIA ENVIANDO EXCEPCION
template <typename T>
bool DoublyLinkedList<T>::isEmptyList(){           // Verificar si la lista está vacía utilizando el método isEmpty()
    if(this->isEmpty()){
        std::string msg = "La lista se encuentra vacia";
        throw msg;          //lanzar una excepción
    }
    return false;    
}

/*
 * Metodo encargado de validar si el indice se encuentra dentro de los limites. De no ser asi lanza una excepcion.
 * De lo contrario devuelve un valor false;
 */
template <typename T>
bool DoublyLinkedList<T>::isArrayOutOfBounds(int index){
    if(index >= this->size() || index < 0){
        std::string msg = "El indice se encuentra fuera de los limites";
        throw  msg;
    }   
    return false;       
}

//remove                ELIMINANDO EL NODO QUE RECIBE COMO PARAMETRO
template <typename T>
void DoublyLinkedList<T>::remove(Node<T>* node){
    if(node == this->header){           //Verificar si el nodo recibido es apuntado por el header
        this->removeFirst();            //Si es así, llamar al método removeFirst() para eliminar el primer nodo
    }
    else if(node == this->end){         //Verificar si el nodo recibido es apuntado por el end
        this->removeLast();             //Si es así, llamar al método removeLast() para eliminar el último nodo
    }
    else{       //Si no es el primer ni el último nodo, realizar los siguientes pasos
        node->getPrevious()->setNext(node->getNext());              // Establecer el siguiente del nodo previo al siguiente del nodo a eliminar
        node->getNext()->setPrevious(node->getPrevious());          // Establecer el previo del nodo siguiente al previo del nodo a eliminar
        delete node;    // Eliminar el nodo
    }
}


#endif /* DOUBLYLINKEDLIST_H */