#include "Printer.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

Printer::Printer(){}

void Printer::print(Queue<Card*>* queue, Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* principalStacks, DoublyLinkedList<Stack<Card*>*>* secondaryStacks){
    this->printQueuesAndSecondaryStacks(queue, stack, secondaryStacks);
    this->printPrincipalStacks(principalStacks);
    for(int i = 0; i < 7; i++){
        switch(i){
            case 0:
                stack = stack1;
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
        while(!auxiliarStack->isEmpty()){
            stack->push(auxiliarStack->pop());
        }  
    }
}

void Printer::printPrincipalStacks(DoublyLinkedList<Stack<Card*>*>* principalStacks){
    string image;
    int row = 1;
    stack1 = principalStacks->get(0);
    stack2 = principalStacks->get(1);
    stack3 = principalStacks->get(2);
    stack4 = principalStacks->get(3);
    stack5 = principalStacks->get(4);
    stack6 = principalStacks->get(5);
    stack7 = principalStacks->get(6);

    while(!stack1->isEmpty() || !stack2->isEmpty() || !stack3->isEmpty() || !stack4->isEmpty() || !stack5->isEmpty() || !stack6->isEmpty() || !stack7->isEmpty()){ 
       for(int i = 1; i < 6; i++){  
            for(int j = 0; j < 7; j++){
                switch(j){
                    case 0:
                        stack = stack1;
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
                         
                if(!stack->isEmpty()){
                    if(stack->peek()->isHide()){
                        image = image + "   " + this->createImage(i, 0, "-"); //3 mas -        0 espacios entre cartas
                    }
                 
                    else{
                        card = stack->peek();       
                        image = image + " " + this->createImage(i, card->getType(), card->getValue());  // 1* espacio dela pared inicio
                    }   
                    if(i == 5){
                        card = stack->pop();
                        auxiliarStack->push(card);
                    }
                }
                else{
                    image = image + "         ";   //9 espacios adentro de la carta
                }
            }
            //VALOR R           
            if(i == 1){    
                image = image + " " + std::to_string(row) +  "\n"; //2      ->1     espacio entre la carta y la columna de numeros final
                row++;
            }
            else{      
               image = image + "\n";
            }     
        }         
    }
    std::cout<<image;

}

//  printQueuesAndSecondaryStacks           IMPRIMIENDO LAS COLAS
void Printer::printQueuesAndSecondaryStacks(Queue<Card*>* queue, Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* secondaryStacks){
    string img = "    1       2         3       4         5        6       7   \n";    //de 2 a 3 se agregaron 2 espacios      de 4-5 3espacios 
    for(int i = 1; i < 6; i++){     //iterando en filas 5s
        //Colas 3312
        for(int j = 0; j < 2; j++){         //iterando en las dos colas
            
            if(j == 0){                     //primera cola
                if(queue->isEmpty()){       //cola vacia
                    //3312
                    Card* card = new Card(" ", 0, " ", true);       //creando carta vacia
                    this->card = card;                              //asignando la carta creada como la carta actual
                }

                else{                               //      si la cola no esta vacia
                    if(queue->peek()->isHide()){    //si la carta sobre la cola esta oculta
                        //3312
                        Card* card = new Card("-", 0, " ", true);   //creamos carta oculta
                        this->card = card;                          //asignamos la carta creada como la carta actual
                    }
                    else{       //si la carta en la cima de la cola no está oculta
                        card = queue->peek();                 //obtenemos la carta en la cima de la cola     
                        //cant cards     
                        
                    }  
                }
            }

            //3312
            else{       // si es la segunda cola
                if(stack->isEmpty()){       //pila vacia
                    Card* card = new Card(" ", 0, " ", true);       //creando cola vacia
                    this->card = card;                              //la carta creada es la carta actual
                }
                else{               //si la pila no esta vacia
                    if(stack->peek()->isHide()){                        //teniendo oculta la carta en la cima de la pila
                        Card* card = new Card("-", 0, " ", true);       //creamos carta oculta
                        this->card = card;                              //la carta creada sera la actual
                    }
                    else{           //si la carta en la cima de la pila no esta oculta
                        card = stack->peek();   //obtenemos la carta en la cima de la pila
                    }
                }
            }
            //3312      [2*]espacios dentro  tenia[1]    SEPARACION DE LA PARED INICIAL
            img = img + " " + this->createImage(i, card->getType(), card->getValue());      //agregamos la primera cola de cartas al tablero
        }
        //3312
        img = img + "              ";      //separando colas de pilas 7->14
        
        //Pilas secundarias PILAS
        for(int j = 0; j < secondaryStacks->size(); j++){           
            card = secondaryStacks->get(j)->peek();             //obteniendo la carta de la cima de la pila secundaria actual
            //3312
            img = img + " " + this->createImage(i, card->getType(), card->getValue());      //agregamos las pilas de cartas al tablero TIENEN[1]   PASA A [4]
        }

        if(i == 1){                                     //agregando el indicador de las filas 0
            img = img + "  0\n";
        }
        else{
//           //img = img;
            //3312
            img = img + "\n";               //agregando salto de linea
        }

    }
    std::cout<<img;
}

//createImage           VISUALIZANDO LA CARTA
string Printer::createImage(int part, int type, string value){
    string img;
    switch (type){
        case 0:
            this->type = "  ";
            //this->color = "\x1B[30m";
            this->color = " ";      //para los ocultos ?
        break;
        
        case 1:
            this->type = "<3";
            //this->color = "\x1B[31m";
            this->color = "R";
        break;

        case 2:
            this->type = "<>";
            //this->color = "\x1B[31m";
            this->color = "R";
        break;

        case 3:
            this->type = "E3";
            //this->color = "\x1B[30m";
            this->color = "N";
        break;

        case 4:
            this->type = "!!";
            //this->color = "\x1B[30m";
            this->color = "N";
        break;
    }

    //impresion carta
    switch(part){

        case 0:
            img = "["+this->type +  color + "   ]"+ endColor;;  
            //img = color + "["+this->type+"   ]" + endColor;           //P2
            //img = color + "["+this->type+  value   + color +            "   ]" + endColor;        //P1
        break;

        case 1:
            if(value.compare("10") == 0 || value.compare("<3") == 0 || value.compare("<>") == 0 || value.compare("E3") == 0 ||value.compare("!!") == 0){
                img = "["+ value +  color  + this->type + "]"+ endColor;;
                //img = color + "["+ value + " " + this->type + "]" + endColor;
            }
            else{
                img = "["+ value +  color  + this->type + "]"+ endColor;;
                // img = color + "["+ value + " " + this->type + "]" + endColor;
            }
        break;

    }//end switch(part)
    
    return img;
}   