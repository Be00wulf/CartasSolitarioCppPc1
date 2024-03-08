#include "CardCreator.h"
#include <string>

CardCreator::CardCreator() {        //Cvacio inicializando
}

 //Metodo encargado de crear todas las cartas, devuelve puntero de cards
DoublyLinkedList<Card*>* CardCreator::createCards(){    //puntero a una lista doblemente enlazada que contiene cartas. Esta lista se crea dentro de la función.
    actualColor = colors[0];        //ctual en rojo, el primer color en el arreglo 
    for(int i = 1; i < 5; i++){   //recorriendo los tipos de cartas 
        if(i == 3){     //para el tercer indice de tipo cambia el color 
            actualColor = colors[1];
        }
        for(int j = 0; j < 13; j++){    //recorre los valores de las cartas 0-12
            Card* card = new Card(values[j], i, actualColor, true); //creando carta dentro de la lista doblemente enlazada cards v c sV
            cards->addFirst(card);  //agregando al inicio de la DOUBLY LINKED LIST
        }
    }
    
    actualColor = colors[0];        //1. establece el color actual en rojo (colors[0]).
    for(int i = 1; i < 5; i++){      //2. Itera por cada una de los tipos i: <3 <> E3 !!
        if(i == 3){                 //3. Si llega a la tercera iteracion (i=3) cambia el color actual a rojo (colors[1]).
            actualColor = colors[1];
        }
        Card* card = new Card(valuesT[i-1], i, actualColor, false); //nueva carta
        cards->addLast(card);   //la carta recien creada agregada al final de la doubly linked list 
    }
    return this->cards;
}
