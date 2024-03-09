#include "MovementDriver.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

MovementDriver::MovementDriver() {
}

//COLA Y PILA de cartas comodin         [ - ] [  ]
void MovementDriver::moveQueue(Queue<Card*>* queue, Stack<Card*>* stack){
    if(!queue->isEmpty()){                  //si la cola no esta vacia
        stack->push(queue->remove());       //retira la carta de la cola
        stack->peek()->setHide(false);      //colocando en pila, la carta ya no esta oculta
    }
    else{
        while(!stack->isEmpty()){       //si la cola esta vacia
            stack->peek()->setHide(true);   //oculta cartas
            auxiliarStack->push(stack->pop());  //eliminamos carta de la cola, la colocamos en la auxiliar
        } 
        while(!auxiliarStack->isEmpty()){
            queue->add(auxiliarStack->pop());       //cuando se acaben cartas por voltear usamos add de Queue
        }
    }
}

//Movimineto entre las 7 double linked lists/pilas      restricciones-varias cartas-carta auxiliar
bool MovementDriver::movePrincipalCards(DoublyLinkedList<Stack<Card*>*>* principalStacks,int selectedColumn, int targetColumn, int amount){
    if(selectedColumn > 7 || selectedColumn < 1 || targetColumn > 7 || targetColumn < 1){
        std::cout<<"LA COLUMNA NO EXISTE\n";
        this->print = false;
    }
    
    else{   
        //Obtener las pilas en las cuales se desea mover
        this->selectedStack = principalStacks->get(selectedColumn-1);
        this->targetStack = principalStacks->get(targetColumn-1);
        Stack<Card*>* auxiliarMovementStack = new Stack<Card*>;
        Card* auxCard = NULL;
        
        //Reordenar las pilas para poder realizar acciones sobre ellas      [abc] [cba] [abc]
        while(!this->selectedStack->isEmpty()){
            auxiliarMovementStack->push(this->selectedStack->peek());
            this->auxiliarStack1->push(this->selectedStack->pop());
        }
        while(!this->targetStack->isEmpty()){
            this->auxiliarStack2->push(this->targetStack->pop());
        }

        auxCard = auxiliarMovementStack->pop();
        this->currentAmount = 1;
        while(!auxiliarMovementStack->isEmpty() && this->currentAmount < amount && !auxiliarMovementStack->peek()->isHide()) {
            auxCard = auxiliarMovementStack->pop();
            this->currentAmount++;
        }

        //revisando carta seleccionada
        cout << "CARTA AUXILIAR --------------------" <<endl;
        cout << auxCard->getValue() << endl;

        
        //Validar si alguna de las pilas se encuentra vacia
        if(auxiliarStack1->isEmpty()){
            std::cout<<"NO HAY CARTAS EN ESTA SELECCION\n";
            print = false;
        }  

        else if(auxiliarStack2->isEmpty()){                         //SOLO PODEMOS COLOCAR K EN ESPACIOS VACIOS
            if(auxCard->getValue() == "K"){
                this->moveCard(0);
            }
            else{
                std::cout<<"SOLO PODEMOS COLOCAR K EN ESTOS ESPACIOS VACIOS\n";
                print = false;
            }
        }

        else{
            //Validar que no sean cartas del mismo color
            if(auxCard->getColor() == auxiliarStack2->peek()->getColor()){
                std::cout<<"EN LISTAS NO PUEDEN SER COLOCADAS CARTAS CONSECUTIVAS DEL MISMO COLOR\n";
                print = false;
            }

            else{
            //Validar el orden de las cartas
                if(auxiliarStack2->peek()->getValue() == "K"){
                    if(auxCard->getValue() == "Q"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "Q"){
                    if(auxCard->getValue() == "J"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "J"){
                    if(auxCard->getValue() == "10"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "2"){
                    if(auxCard->getValue() == "A"){
                        this->moveCard(0); 
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "A"){
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }

                else{
                    //stoi: para convertir una cadena que representa un número en formato de texto (string) en su equivalente numérico en formato entero (int)
                    if(auxCard->getValue() == "A" || auxCard->getValue() == "K" || auxCard->getValue() == "Q" || auxCard->getValue() == "J"){
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                    else{
                        if(stoi(auxiliarStack2->peek()->getValue()) == (stoi(auxCard->getValue())+1)){
                           this->moveCard(0);
                        }
                        else{
                            std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                            print = false;
                        }
                    }
                }   
            } 
        }
        //Reestablecer las pilas a su estado original   COLA PILA 
        while(!this->auxiliarStack1->isEmpty()){
            this->selectedStack->push(this->auxiliarStack1->pop());
        }
        while(!this->auxiliarStack2->isEmpty()){
            this->targetStack->push(this->auxiliarStack2->pop());
        }    
    }
    return print;
}

//MOVIENDO DE LAS 7 PILAS (listas a 4 pilas)  ->   restricciones 
bool MovementDriver::moveToSecondaryStack(DoublyLinkedList<Stack<Card*>*>* principalStacks, DoublyLinkedList<Stack<Card*>*>* secondaryStacks, int selectedColumn){
    
    //Obtener la pila en la cual se desea mover
    this->selectedStack = principalStacks->get(selectedColumn-1);
    
    //Reordena la pila para poder accionar encima                   [abc]   [cba]   [abc]
    while(!this->selectedStack->isEmpty()){
        this->auxiliarStack3->push(this->selectedStack->pop());
    }
    
    //Validar pila vacia
        if(auxiliarStack3->isEmpty()){
            std::cout<<"NO HAY CARTAS EN ESTA SELECCION\n";
            print = false;
        }

        else{
            //Establecer a que pila se debe insertar la carta seleccionada
            for(int i = 0; i < 4; i++){
                if(auxiliarStack3->peek()->getType() == secondaryStacks->get(i)->peek()->getType()){
                    auxiliarStack4 = secondaryStacks->get(i);
                }
            }

            //Validar el orden de las cartas            
            if(auxiliarStack4->peek()->getValue() == "<3" || auxiliarStack4->peek()->getValue() == "<>" || auxiliarStack4->peek()->getValue() == "E3" || auxiliarStack4->peek()->getValue() == "!!"){
                if(auxiliarStack3->peek()->getValue() == "A"){
                    this->moveCard(1);
                }
                else{
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }
            }      

            else if(auxiliarStack4->peek()->getValue() == "A"){
                if(auxiliarStack3->peek()->getValue() == "2"){
                    this->moveCard(1);
                }
                else{
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }
            }
            
            else if(auxiliarStack4->peek()->getValue() == "10"){
                if(auxiliarStack3->peek()->getValue() == "J"){
                    this->moveCard(1);
                }
                else{
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }
            }

            else if(auxiliarStack4->peek()->getValue() == "J"){
                if(auxiliarStack3->peek()->getValue() == "Q"){
                    this->moveCard(1); 
                }
                else{
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }
            }
            
            else if(auxiliarStack4->peek()->getValue() == "Q"){
               if(auxiliarStack3->peek()->getValue() == "K"){
                   this->moveCard(1); 
               }
               else{
                   std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                   print = false;
               }
           }
            
            else if(auxiliarStack4->peek()->getValue() == "K"){
                std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                print = false;
            }

            else{
                if(auxiliarStack3->peek()->getValue() == "A" || auxiliarStack3->peek()->getValue() == "K" || auxiliarStack3->peek()->getValue() == "Q" || auxiliarStack3->peek()->getValue() == "J"){
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }
                else{
                    if(stoi(auxiliarStack4->peek()->getValue()) == (stoi(auxiliarStack3->peek()->getValue())-1)){
                       this->moveCard(1);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }
            } 
        }
    
    //restableciendo pila cuando acaben las cartas 
    while(!this->auxiliarStack3->isEmpty()){
        this->selectedStack->push(this->auxiliarStack3->pop());
    }
    
    return print;
}

//MOVIMIENTO DE COLA A 7 LISTAS (EN PILA)           restricciones  de la cola a las listas 
bool MovementDriver::moveToPrincipalStack(Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* principalStacks, int targetColumn){
    if(targetColumn > 7 || targetColumn < 1){
        std::cout<<"LA COLUMNA NO EXISTE\n";
        this->print = false;
    }
    else{
        //Obtener las pilas en las cuales se desea mover.
        this->auxiliarStack5 = stack;
        this->targetStack = principalStacks->get(targetColumn-1);  
        
        //Reordenar la pila para poder realizar acciones sobre ella.
        while(!this->targetStack->isEmpty()){
            this->auxiliarStack6->push(this->targetStack->pop());
        }
        
        //Validar si alguna de las pilas se encuentra vacia.
        if(auxiliarStack5->isEmpty()){
            std::cout<<"NO HAY CARTAS EN ESTA SELECCION\n";
            print = false;
        }
        else if(auxiliarStack6->isEmpty()){
            if(auxiliarStack5->peek()->getValue() == "K"){
                this->moveCard(2);
            }
            else{
                std::cout<<"SOLO PODEMOS COLOCAR K EN ESPACIOS VACIOS\n";
                print = false;
            }
        }
        else{
            //Validar que no sean cartas del mismo color.
            if(auxiliarStack5->peek()->getColor() == auxiliarStack6->peek()->getColor()){
                std::cout<<"EN LISTAS NO PUEDEN SER COLOCADAS CARTAS CONSECUTIVAS DEL MISMO COLOR\n";
                print = false;
            }

            else{
            //Validar el orden de las cartas
                if(auxiliarStack6->peek()->getValue() == "K"){
                    if(auxiliarStack5->peek()->getValue() == "Q"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "Q"){
                    if(auxiliarStack5->peek()->getValue() == "J"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "J"){
                    if(auxiliarStack5->peek()->getValue() == "10"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "2"){
                    if(auxiliarStack5->peek()->getValue() == "A"){
                        this->moveCard(2); 
                    }
                    else{
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "A"){
                    std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                    print = false;
                }

                else{
                    if(auxiliarStack5->peek()->getValue() == "A" || auxiliarStack5->peek()->getValue() == "K" || auxiliarStack5->peek()->getValue() == "Q" || auxiliarStack5->peek()->getValue() == "J"){
                        std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                        print = false;
                    }
                    else{
                        if(stoi(auxiliarStack6->peek()->getValue()) == (stoi(auxiliarStack5->peek()->getValue())+1)){
                           this->moveCard(2);
                        }
                        else{
                            std::cout<<"NO SE PUEDEN COLOCAR CARTAS EN ESTE ORDEN, RECUERDA K-Q-J-(10-2)-A\n";
                            print = false;
                        }
                    }
                }   
            } 
        }

        //restableciendo pila cuando acaben las cartas 
        while(!this->auxiliarStack6->isEmpty()){
            this->targetStack->push(this->auxiliarStack6->pop());
        }
        
    }
    return print;
}

//TIPO DE MOVIMIENTO ENTRE listas pilas     una o varias cartas-setHide    
void MovementDriver::moveCard(int type){        //type determina el tipo de movimiento que se realizara
    if(type == 0){                              //movimiento entre las primeras dos pilas (auxiliarStack1 y auxiliarStack2).
        int counter = 0;
        Stack<Card*>* auxiliarMovementStack = new Stack<Card*>;    //almacenando temporalmente las cartas que se moveran
        
        //moviendo de auxiliarStack1 a auxiliarMovementStack y luego de auxiliarMovementStack a auxiliarStack2
        while(!auxiliarStack1->isEmpty() && counter < this->currentAmount) {    //pila 1[abc]   pila2[cba]      pila3[abc]
            auxiliarMovementStack->push(auxiliarStack1->pop());
            counter++;
        }
        
        counter = 0;
        while(!auxiliarMovementStack->isEmpty() && counter < this->currentAmount) {
            auxiliarStack2->push(auxiliarMovementStack->pop());
            counter++;
        }
        
        if(!auxiliarStack1->isEmpty()){                 //si al mover aun hay cartas la ultima se muestr: [- ] -> [carta]
            auxiliarStack1->peek()->setHide(false);
        }
    }

    else if(type == 1){         //movimiento entre las pilas de 3 a 4: no hay limite en cant de cartas a mover
        auxiliarStack4->push(auxiliarStack3->pop());
        if(!auxiliarStack3->isEmpty()){             //verificar si despues del movimiento esta vacia y revelar carta superior si hay
            auxiliarStack3->peek()->setHide(false);
        }
    }

    else{                       //movimiento entre las pilas de 5 a 6
    //si auxiliarStack5 no está vacía después del movimiento, se revela la carta superior (peek) de auxiliarStack5 
    //estableciendo su estado de ocultamiento en false, como el type==1
        auxiliarStack6->push(auxiliarStack5->pop());
        if(!auxiliarStack5->isEmpty()){
            auxiliarStack5->peek()->setHide(false);
        }
    }
    this->print = true;     //para indicar que se ha realizado un movimiento
}
