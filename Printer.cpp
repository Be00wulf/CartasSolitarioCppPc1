#include "Printer.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

Printer::Printer(){}

//impresion del tablero completo.  pasando las referencias a la cola, la pila y la lista doblemente enlazada de pilas secundarias
void Printer::print(Queue<Card*>* queue, Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* principalStacks, DoublyLinkedList<Stack<Card*>*>* secondaryStacks){
    this->printQueuesAndSecondaryStacks(queue, stack, secondaryStacks);     //imprimiendo colas y pilas secundarias al inicio
    this->printPrincipalStacks(principalStacks);        //imprimiendo liastas principales

    for(int i = 0; i < 7; i++){                     //recorremos las listas
        switch(i){
            case 0:                  //asigna la pila principal correspondiente y auxiliar a las variables stack y auxiliarStack
                stack = stack1;
                auxiliarStack = auxiliarStack1;         //para los movimientos
            break;                                      //actualiza el estado de las pilas principales al transferir 
            case 1:                                     //cualquier carta de las pilas auxiliares de vuelta a las pilas principales
                stack = stack2;
                auxiliarStack = auxiliarStack2;
            break;
            case 2:
                stack = stack3;
                auxiliarStack = auxiliarStack3;
            break;
            case 3:
                stack = stack4;
                auxiliarStack = auxiliarStack4;
            break;
            case 4:
                stack = stack5;
                auxiliarStack = auxiliarStack5;
            break;
            case 5:
                stack = stack6;
                auxiliarStack = auxiliarStack6;
            break;
            case 6:
                stack = stack7;
                auxiliarStack = auxiliarStack7;
            break;
        }
        while(!auxiliarStack->isEmpty()){
            stack->push(auxiliarStack->pop());
        }  
    }
}

//7 liastas
void Printer::printPrincipalStacks(DoublyLinkedList<Stack<Card*>*>* principalStacks){   //doubly linked lists de stacks
    string image = "";      //tablero
    int row = 1;            //para recorrer las filas
    stack1 = principalStacks->get(0);
    stack2 = principalStacks->get(1);
    stack3 = principalStacks->get(2);
    stack4 = principalStacks->get(3);
    stack5 = principalStacks->get(4);
    stack6 = principalStacks->get(5);
    stack7 = principalStacks->get(6);

    //mientras hayan cartas en las listas principales
    while(!stack1->isEmpty() || !stack2->isEmpty() || !stack3->isEmpty() || !stack4->isEmpty() || !stack5->isEmpty() || !stack6->isEmpty() || !stack7->isEmpty()){ 
       for(int i = 1; i < 6; i++){              //recorriendo la carta                  
            for(int j = 0; j < 7; j++){         //recorrie las 7 columnas de las listas
                switch(j){
                    case 0:
                        stack = stack1;                             //creamos stacks y sus auxiliares
                        auxiliarStack = auxiliarStack1;
                    break;
                    case 1:
                        stack = stack2;
                        auxiliarStack = auxiliarStack2;
                    break;
                    case 2:
                        stack = stack3;
                        auxiliarStack = auxiliarStack3;
                    break;
                    case 3:
                        stack = stack4;
                        auxiliarStack = auxiliarStack4;
                    break;
                    case 4:
                        stack = stack5;
                        auxiliarStack = auxiliarStack5;
                    break;
                    case 5:
                        stack = stack6;
                        auxiliarStack = auxiliarStack6;
                    break;
                    case 6:
                        stack = stack7;
                        auxiliarStack = auxiliarStack7;
                    break;
                }
                         
                if(!stack->isEmpty()){                  //pila vacia
                    if(stack->peek()->isHide()){        //si la carta en la cima de la pila esta oculta
                        image = image + "  " + this->createImage(i, 0, "-"); //3 mas -        0 espacios entre cartas  ->4->6->2    
                    }       //agregamos espacio "-" simbolizando la carta oculta
                 
                    else{                           //si la carta no esta oculta
                        card = stack->peek();       //obtenemos la carta y luego mostramos sus valores
                        image = image + " " + this->createImage(i, card->getType(), card->getValue());  // 1* espacio dela pared inicio
                    }   
                    if(i == 5){                         //en el final de la carta
                        card = stack->pop();            //extraemos la carta en la parte superior de la pila 
                        auxiliarStack->push(card);      //se coloca en una pila aux para revisar movimientos del juego
                    }
                }
                else{
                    image = image + "        ";   //9 espacios adentro de la carta     ->8 y
                }
            }
            //VALOR R           
            if(i == 1){        //pos 1 dentro de la carta, luego imprimimos sus cartasel y numero de la fila
                image = image + "  " + std::to_string(row) +  "\n"; //2      ->1  ->2   espacio entre la carta y la columna de numeros final
                row++;
            }
            else{       
               image = image + "\n";            // fila de cartas y salto de linea
            }     
        }         
    }
    std::cout<<image ;      //3312          representacion completa de las cartas en el tablero

}

//  printQueuesAndSecondaryStacks           punteros a los objetos  IMPRIMIENDO LAS COLAS PILAS SECUNDARIAS
void Printer::printQueuesAndSecondaryStacks(Queue<Card*>* queue, Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* secondaryStacks){
    string img = "    1       2       3       4       5        6       7   \n";     //ENCABEZADO      
    for(int i = 1; i < 6; i++){     //iterando en filas 5 superiores
        //Colas 3312
        for(int j = 0; j < 2; j++){         //iterando en las dos colas
            
            if(j == 0){                     //primera cola
                if(queue->isEmpty()){       //cola vacia
                    //3312
                    Card* card = new Card(" ", 0, " ", true);       //creando carta vacia
                    this->card = card;                              //asignando la carta creada como la carta actual
                }

                else{                               //      si la cola no esta vacia`
                    if(queue->peek()->isHide()){    //si la carta sobre la cola esta oculta
                        //3312
                        Card* card = new Card("-", 0, " ", true);   //creamos nueva carta oculta para mostrarla en oculto
                        this->card = card;                          //asignamos la carta creada como la carta actual
                    }
                    else{       //si la carta en la cima de la cola no esta oculta
                        card = queue->peek();                 //obtenemos la carta en la cima de la cola      
                        
                    }  
                }
            }

            //3312->y
            else{       // si es la segunda cola
                if(stack->isEmpty()){       //pila vacia
                    Card* card = new Card(" ", 0, " ", true);       //creando cola vacia
                    this->card = card;                              //la carta creada es la carta actual
                }
                else{               //si la pila no esta vacia
                    if(stack->peek()->isHide()){                        //si esta oculta la carta en la cima de la pila
                        Card* card = new Card("-", 0, " ", true);       //creamos carta oculta
                        this->card = card;                              //la carta creada sera la actual
                    }
                    else{           //si la carta en la cima de la pila no esta oculta
                        card = stack->peek();   //obtenemos la carta en la cima de la pila
                    }
                }
            }
            //3312->y   1   [2*]  ->1    SEPARACION DE LA PARED INICIAL 
            img = img + " " + this->createImage(i, card->getType(), card->getValue());      //agregamos la primera cola de cartas al tablero   
        }
        //3312->y
        img = img + "          ";      //separando colas de pilas 7->14*->12->10*
        
//
        for(int j = 0; j < secondaryStacks->size(); j++){           
            card = secondaryStacks->get(j)->peek();             //obteniendo la carta de la cima de la pila secundaria actual
            //3312 espacio entre cartas de las pilas ->y
            img = img  + " " + this->createImage(i, card->getType(), card->getValue());      //agregamos las pilas de cartas al tablero    1*
        }

        if(i == 1){                                     //agregando el indicador de las filas pos s0
            img = img + "  0\n";
        }
        else{
//           //img = img;
            //3312
            img = img + " \n";               //agregando salto de linea         +_
        }

    }
    std::cout<<img;             //imprimiendo la seccion de colas y pilas 
}

//createImage           VISUALIZANDO LA CARTA
string Printer::createImage(int part, int type, string value){
    string img;
    switch (type){
        case 0:
            this->type = "  ";
            this->color = " ";      //para los ocultos 
        break;
        
        case 1:
            this->type = "<3";
            this->color = "R";
        break;

        case 2:
            this->type = "<>";
            this->color = "R";
        break;

        case 3:
            this->type = "E3";
            this->color = "N";
        break;

        case 4:
            this->type = "!!";
            this->color = "N";
        break;
    }

    //impresion carta
    switch(part){

        case 0:
            img = "["+this->type +  color + "   ]"+ endColor;;  
        break;

        case 1:
            if(value.compare("10") == 0 || value.compare("<3") == 0 || value.compare("<>") == 0 || value.compare("E3") == 0 ||value.compare("!!") == 0){
                img = "["+ value +  color  + this->type + "]"+ endColor;;
            }
            else{
                img = "["+ value +  color  + this->type + "]"+ endColor;;
            }
        break;

    }//end switch(part)
    
    return img;
}   