#include "CardCreator.h"
#include <string>

CardCreator::CardCreator() {
}

/*
 * Metodo encargado de crear todas las cartas.
 * 1. Establece el color actual en rojo (colors[0]).
 * 2. Itera por cada una de los tipos (i):
 *       1. Corazones
 *       2. Rombos
 *       3. Treboles
 *       4. Espadas
 * 3. Si llega a la tercera iteracion (i=3) cambia el color actual a rojo (colors[1]).
 * 4. Itera por cada uno de los valores contenidos dentro del arreglo values (j);
 * 5. Crea una nueva carta con el valor indicado por el arreglo values en el indice j, el tipo indicado por el arreglo types en el indice i, el color indicado por 
 *    actual color, la imagen creada mediante la llamada al metodo createImage, y el parametro hide igual a true.
 * 6. Guarda la carta dentro de la lista doblemente enlazada cards.  
 * 7. Realiza un proceso similar para crear 4 cartas, cuyos valores estan dados por el arreglo valuesT.
*/
DoublyLinkedList<Card*>* CardCreator::createCards(){
    actualColor = colors[0];
    for(int i = 1; i < 5; i++){
        if(i == 3){
            actualColor = colors[1];
        }
        for(int j = 0; j < 13; j++){
            Card* card = new Card(values[j], i, actualColor, true);
            cards->addFirst(card); 
        }
    }
    
    actualColor = colors[0];
    for(int i = 1; i < 5; i++){
        if(i == 3){
            actualColor = colors[1];
        }
        Card* card = new Card(valuesT[i-1], i, actualColor, false);
        cards->addLast(card); 
    }
    return this->cards;
}
