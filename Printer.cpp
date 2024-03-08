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
                        image = image + " " + this->createImage(i, 0, "-");
                    }
                    else{
                        card = stack->peek();
                        image = image + " " + this->createImage(i, card->getType(), card->getValue());
                    }
                    if(i == 5){
                        card = stack->pop();
                        auxiliarStack->push(card);
                    }
                }
                else{
                    image = image + "        ";
                }
            }
           
            if(i == 4){
                image = image + "  " + std::to_string(row) +  "\n";
                row++;
            }
            else{
               image = image + "\n";
            }     
        }         
    }
    std::cout<<image <<"\n\n";
}

/*
 * Metodo encargado de la impresion de las colas.
 * 1. Realiza 5 iteraciones, en cada iteracion concatena al string image un segmento de las cartas que se estan
 *    construyendo. 
 * 2. Por cada cola valida si se encuentra vacia o contiene elementos, si se encuentra vacia crea una objeto carta 
 *    cuyos atributos son vacios, de lo contrario asigna a la variable card el valor obtenido de la cima de la pila.
 * 3. Concatena segmentos al string image mediante el llamado al metodo createImage, enviandole como parametros los 
 *    valores de la carta y el numero de iteracion i. Depues de cada iteracion i inserta un salto de linea en el string.
 * 4. Por cada pila asigna el el valor obtenido de la cima de la misma a la variable carta y llama al metodo createImage
 *    enviandole como parametros los valores de la carta.
 * 5. Concatena los strings recibidos por el metodo createImage en la variable image.
 * 6. Por ultimo imprime el string image.
 */
void Printer::printQueuesAndSecondaryStacks(Queue<Card*>* queue, Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* secondaryStacks){
    string img = "    1       2      3       4       5       6       7   \n";
    for(int i = 1; i < 6; i++){
        //Colas.
        for(int j = 0; j < 2; j++){
            
            if(j == 0){
                if(queue->isEmpty()){
                    Card* card = new Card(" ", 0, " ", true);
                    this->card = card;
                }
                else{
                    if(queue->peek()->isHide()){
                        Card* card = new Card("-", 0, " ", true);
                        this->card = card;
                    }
                    else{
                        card = queue->peek();
                    }  
                }
            }
            else{
                if(stack->isEmpty()){
                    Card* card = new Card(" ", 0, " ", true);
                    this->card = card;
                }
                else{
                    if(stack->peek()->isHide()){
                        Card* card = new Card("-", 0, " ", true);
                        this->card = card;
                    }
                    else{
                        card = stack->peek();
                    }
                }
            }
            img = img + " " + this->createImage(i, card->getType(), card->getValue());
        }
        img = img + "       ";
        
        
        //Pilas secundarias.
        for(int j = 0; j < secondaryStacks->size(); j++){
            card = secondaryStacks->get(j)->peek();
            img = img + " " + this->createImage(i, card->getType(), card->getValue());
        }
        if(i == 4){
            img = img + "  0\n";
        }
        else{
            img = img + "\n";
        }
    }
    std::cout<<img <<"\n \n";
}

string Printer::createImage(int part, int type, string value){
    string img;
    switch (type){
        case 0:
            this->type = "  ";
            this->color = "\x1B[30m";
        break;
        case 1:
            this->type = "<3";
            this->color = "\x1B[31m";
        break;
        case 2:
            this->type = "<>";
            this->color = "\x1B[31m";
        break;
        case 3:
            this->type = "E3";
            this->color = "\x1B[30m";
        break;
        case 4:
            this->type = "!!";
            this->color = "\x1B[30m";
        break;
    }
    switch(part){
        case 1:
            img = color + " _____ " + endColor;
        break;
        case 2:
            img = color + "|"+this->type+"   |" + endColor;
        break;
        case 3:
            img = color + "|     |" + endColor;
        break;
        case 4:
            if(value.compare("10") == 0 || value.compare("<3") == 0 || value.compare("<>") == 0 || value.compare("E3") == 0 ||value.compare("!!") == 0){
                img = color + "| "+value+"  |" + endColor;
            }
            else{
                img = color + "|  "+value+"  |" + endColor;
            }
        break;
        case 5:
            img = color + "|_____|" + endColor;
        break;
            
    }
    return img;
}   