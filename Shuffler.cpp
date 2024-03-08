#include "Shuffler.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include <iostream>

Shuffler::Shuffler(){}

/*
 * Metodo encargado de revolver las cartas.
 * Recibe como parametro un lista doblemente enlazada, la cual contiene las cartas en un orden especifico.
 *  1. Recorre la lista desde el inicio hasta el final de la mima. 
 *  2. Obtiene un numero aleatorio entre 0 y 51 y lo almacena en la variable randomNum.
 *  3. Obtiene la carta de la lista almacenada en el indice i y la almacena en la variable card.
 *  4. Remueve la carta almacenada en el indice i.
 *  5. Insertar la carta almacenada en la variable card en el indice de la lista determinado por la variable randomNum.
 */  
void Shuffler::shuffleCards(DoublyLinkedList<Card*>* cards){
    srand((unsigned)time(NULL)); 
    for(int i = 0; i < cards->size() - 4; i++){
        this->randomNum = rand()%51+0;
        card = cards->get(i);
        cards->removeIndex(i);
        cards->add(randomNum, card);
    }
    this->distributeQueues(cards);
    this->distributeStacks(cards);
}

/*
 * Metodo encargado de insertar dentro de la lista doblemente enlazada queques dos colas.
 * En la  primera cola se insertan 24 cartas y por ultimo se inserta la cola dentro la lista doblemente enlazada.
 * La segunda cola se encuentra vacia y se inserta dentro de la lista doblemente enlazada.
 */
 
void Shuffler::distributeQueues(DoublyLinkedList<Card*>* cards){
    for(int i = 0; i < 24; i++){
        queue->add(cards->getFirst());
            cards->removeFirst();
    }    
}

/*
 * Metodo encargado de insertar dentro de las listas doblemente enlazadas principalStacks y secondaryStacks 7 y 4 pilas respectivamente.
 *  1. Crea 7 pilas, una en cada iteracion, dentro de cada pila inserta una cantidad j de cartas, cantidad que depende del valor actual del 
 *     contador i (se insertaran i cartas en cada iteracion). La carta que es insertada en la pila es removida de la lista. Finalmente inserta
 *     la pila dentro de la lista principalStacks.
 *  2. Crea 4 pilas, una en cada iteracion, dentro de cada pila inserta la ultima carta contenida dentro de la lista cards en cada iteracion.
 *     La carta que es insertada en la pila es removida de la lista. Finalmente inserta dentro de la lista secondaryStacks la pila recien creada.
 * 
 */
void Shuffler::distributeStacks(DoublyLinkedList<Card*>* cards){            
    //Creacion e insercion de las pilas principales.
    for(int i = 1; i < 8; i++){
        Stack<Card*>* stack = new Stack<Card*>;
        for(int j = 0; j < i; j++){
            stack->push(cards->getFirst());
            cards->removeFirst();
            if(j == 0){
                stack->peek()->setHide(false);
            }
        }
        principalStacks->add(i-1, stack);
    }
    //Creacion e insercion de las pilas secundarias.
    for(int i = 0; i < 4; i++){
        Stack<Card*>* stack = new Stack<Card*>;
        stack->push(cards->getLast());
        cards->removeLast();
        secondaryStacks->addFirst(stack);
    }
}

DoublyLinkedList<Stack<Card*>*>* Shuffler::getPrincipalStacks(){
    return this->principalStacks;
}

DoublyLinkedList<Stack<Card*>*>* Shuffler::getSecondaryStacks(){
    return this->secondaryStacks;
}

Queue<Card*>* Shuffler::getQueue(){
    return this->queue;
}
 