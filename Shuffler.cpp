#include "Shuffler.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include <iostream>

Shuffler::Shuffler(){}              //fisher yates-> pend

//shuffleCards              REVOLVIENDO LAS CARTAS              
void Shuffler::shuffleCards(DoublyLinkedList<Card*>* cards){
    srand((unsigned)time(NULL));                        //semilla para generar números aleatorios basada en el tiempo actual TETRIS     *POR PROCESO?
    for(int i = 0; i < cards->size() - 4; i++){         //lista de cartas [-4 para las catas vacias de pilas]
        this->randomNum = rand()%51+0;                  //random entre 0 y 51, almacenado en randomNum
        card = cards->get(i);                           //obtenemos carta de la lista y la almacenamos en cards
        cards->removeIndex(i);                          //removiendo carta de la lista
        cards->add(randomNum, card);                    //Inserta la carta de card en un índice aleatorio en la lista
    }
    this->distributeQueues(cards);                      //cartas a las colas
    this->distributeStacks(cards);                      //cartas a las listas
}

//distributeQueues                  INSERTANDO CARTAS EN LAS LISTAS, LOS SOBRANTES A UNA COLA, Y LUEGO ELIMINA DEL LISTADO DE CARTAS
void Shuffler::distributeQueues(DoublyLinkedList<Card*>* cards){
    for(int i = 0; i < 24; i++){
        queue->add(cards->getFirst());          //primera carta de la lista a la cola
            cards->removeFirst();               //remueve la primera carta de la lista de cartas
    }    
}

//distributeStacks                  INSERTANDO EN LISTAS 7 y 4 pilas
void Shuffler::distributeStacks(DoublyLinkedList<Card*>* cards){            
    //Creacion e insercion de las pilas principales.
    for(int i = 1; i < 8; i++){
        Stack<Card*>* stack = new Stack<Card*>;         //nueva pila
        for(int j = 0; j < i; j++){
            stack->push(cards->getFirst());             //agrega la primera carta de la lista de cartas a la pila
            cards->removeFirst();                       //remueve la primera carta de la lista de cartas
            if(j == 0){             
                stack->peek()->setHide(false);          //si es la primera carta en la pila debe mostrarse    
            }
        }
        principalStacks->add(i-1, stack);               //agrega la pila a la lista
    }
    //Creacion e insercion de las pilas secundarias, para 4 cartas vacias de un tipo
    for(int i = 0; i < 4; i++){
        Stack<Card*>* stack = new Stack<Card*>;         //nueva pila
        stack->push(cards->getLast());                  //agrega la ultima carta de la lista de cartas a la pila [las que no tienen valor]
        cards->removeLast();                            //quita la ultima carta, de la lista original de cartas
        secondaryStacks->addFirst(stack);               //se agrega la pila a la lista de pilas secundarias al principio
    }
}

//G
DoublyLinkedList<Stack<Card*>*>* Shuffler::getPrincipalStacks(){
    return this->principalStacks;
}

DoublyLinkedList<Stack<Card*>*>* Shuffler::getSecondaryStacks(){
    return this->secondaryStacks;
}

Queue<Card*>* Shuffler::getQueue(){
    return this->queue;
}
 