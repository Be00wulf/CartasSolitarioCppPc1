#include "MovementDriver.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

MovementDriver::MovementDriver() {
}

/*
 * Metodo encargado del movimiento entre la cola y la pila de 26 cartas.
 */
void MovementDriver::moveQueue(Queue<Card*>* queue, Stack<Card*>* stack){
    if(!queue->isEmpty()){
        stack->push(queue->remove());
        stack->peek()->setHide(false);      
    }
    else{
        while(!stack->isEmpty()){
            stack->peek()->setHide(true);
            auxiliarStack->push(stack->pop());
        } 
        while(!auxiliarStack->isEmpty()){
            queue->add(auxiliarStack->pop());
        }
    }
}

/*
 * Metodo encargado del movimiento de cartas entre las 7 pilas principales.
 */
bool MovementDriver::movePrincipalCards(DoublyLinkedList<Stack<Card*>*>* principalStacks,int selectedColumn, int targetColumn){
    if(selectedColumn > 7 || selectedColumn < 1 || targetColumn > 7 || targetColumn < 1){
        std::cout<<"La columna indicada se encuentra fuera de los limites\n";
        this->print = false;
    }
    else{   
        //Obtener las pilas en las cuales se desea mover.
        this->selectedStack = principalStacks->get(selectedColumn-1);
        this->targetStack = principalStacks->get(targetColumn-1);        
        
        //Reordenar las pilas para poder realizar acciones sobre ellas.
        while(!this->selectedStack->isEmpty()){
            this->auxiliarStack1->push(this->selectedStack->pop());
        }
        while(!this->targetStack->isEmpty()){
            this->auxiliarStack2->push(this->targetStack->pop());
        }
        
        //Validar si alguna de las pilas se encuentra vacia.
        if(auxiliarStack1->isEmpty()){
            std::cout<<"No existe ninguna carta en la columna seleccionada\n";
            print = false;
        }
        else if(auxiliarStack2->isEmpty()){
            if(auxiliarStack1->peek()->getValue() == "K"){
                this->moveCard(0);
            }
            else{
                std::cout<<"No se permite insertar la carta seleccionada. Solamente K\n";
                print = false;
            }
        }
        else{
            //Validar que no sean cartas del mismo color.
            if(auxiliarStack1->peek()->getColor() == auxiliarStack2->peek()->getColor()){
                std::cout<<"No se permite colocar dos cartas del mismo color seguidas en esta seccion\n";
                print = false;
            }
            else{
            //Validar el orden de las cartas
                if(auxiliarStack2->peek()->getValue() == "K"){
                    if(auxiliarStack1->peek()->getValue() == "Q"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "Q"){
                    if(auxiliarStack1->peek()->getValue() == "J"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "J"){
                    if(auxiliarStack1->peek()->getValue() == "10"){
                        this->moveCard(0);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "2"){
                    if(auxiliarStack1->peek()->getValue() == "A"){
                        this->moveCard(0); 
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack2->peek()->getValue() == "A"){
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }

                else{
                    if(auxiliarStack1->peek()->getValue() == "A" || auxiliarStack1->peek()->getValue() == "K" || auxiliarStack1->peek()->getValue() == "Q" || auxiliarStack1->peek()->getValue() == "J"){
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                    else{
                        if(stoi(auxiliarStack2->peek()->getValue()) == (stoi(auxiliarStack1->peek()->getValue())+1)){
                           this->moveCard(0);
                        }
                        else{
                            std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                            print = false;
                        }
                    }
                }   
            } 
        }
        //Reestablecer las pilas a su estado original    
        while(!this->auxiliarStack1->isEmpty()){
            this->selectedStack->push(this->auxiliarStack1->pop());
        }
        while(!this->auxiliarStack2->isEmpty()){
            this->targetStack->push(this->auxiliarStack2->pop());
        }    
    }
    return print;
}

/*Metodo encargado de mover de las 7 pilas principales a alguna de las pilas secundarias.
 */
bool MovementDriver::moveToSecondaryStack(DoublyLinkedList<Stack<Card*>*>* principalStacks, DoublyLinkedList<Stack<Card*>*>* secondaryStacks, int selectedColumn){
    
    //Obtener la pila en la cual se desea mover.
    this->selectedStack = principalStacks->get(selectedColumn-1);
    
    //Reordena la pila para poder realizar acciones sobre ella.
    while(!this->selectedStack->isEmpty()){
        this->auxiliarStack3->push(this->selectedStack->pop());
    }
    
    //Validar la pila se encuentra vacia.
        if(auxiliarStack3->isEmpty()){
            std::cout<<"No existe ninguna carta en la columna seleccionada\n";
            print = false;
        }
        else{
            //Establecer a que pila se debe insertar la carta seleccionada.
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
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }
            }      

            else if(auxiliarStack4->peek()->getValue() == "A"){
                if(auxiliarStack3->peek()->getValue() == "2"){
                    this->moveCard(1);
                }
                else{
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }
            }
            
            else if(auxiliarStack4->peek()->getValue() == "10"){
                if(auxiliarStack3->peek()->getValue() == "J"){
                    this->moveCard(1);
                }
                else{
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }
            }

            else if(auxiliarStack4->peek()->getValue() == "J"){
                if(auxiliarStack3->peek()->getValue() == "Q"){
                    this->moveCard(1); 
                }
                else{
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }
            }
            
            else if(auxiliarStack4->peek()->getValue() == "Q"){
               if(auxiliarStack3->peek()->getValue() == "K"){
                   this->moveCard(1); 
               }
               else{
                   std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                   print = false;
               }
           }
            
            else if(auxiliarStack4->peek()->getValue() == "K"){
                std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                print = false;
            }

            else{
                if(auxiliarStack3->peek()->getValue() == "A" || auxiliarStack3->peek()->getValue() == "K" || auxiliarStack3->peek()->getValue() == "Q" || auxiliarStack3->peek()->getValue() == "J"){
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }
                else{
                    if(stoi(auxiliarStack4->peek()->getValue()) == (stoi(auxiliarStack3->peek()->getValue())-1)){
                       this->moveCard(1);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }
            } 
        }
    
    //Reestablecer la pila a su estado original    
    while(!this->auxiliarStack3->isEmpty()){
        this->selectedStack->push(this->auxiliarStack3->pop());
    }
    
    
   // auxiliarStack1->clear();
    //auxiliarStack2->clear();
    return print;
}

/*
 * Metodo encargado de mover de la cola a una de las 7 pilas pricipales.
 */
bool MovementDriver::moveToPrincipalStack(Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* principalStacks, int targetColumn){
    if(targetColumn > 7 || targetColumn < 1){
        std::cout<<"La columna indicada se encuentra fuera de los limites\n";
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
            std::cout<<"No existe ninguna carta en la cola actualmente\n";
            print = false;
        }
        else if(auxiliarStack6->isEmpty()){
            if(auxiliarStack5->peek()->getValue() == "K"){
                this->moveCard(2);
            }
            else{
                std::cout<<"No se permite insertar la carta seleccionada. Solamente K\n";
                print = false;
            }
        }
        else{
            //Validar que no sean cartas del mismo color.
            if(auxiliarStack5->peek()->getColor() == auxiliarStack6->peek()->getColor()){
                std::cout<<"No se permite colocar dos cartas del mismo color seguidas en esta seccion\n";
                print = false;
            }
            else{
            //Validar el orden de las cartas
                if(auxiliarStack6->peek()->getValue() == "K"){
                    if(auxiliarStack5->peek()->getValue() == "Q"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "Q"){
                    if(auxiliarStack5->peek()->getValue() == "J"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "J"){
                    if(auxiliarStack5->peek()->getValue() == "10"){
                        this->moveCard(2);
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "2"){
                    if(auxiliarStack5->peek()->getValue() == "A"){
                        this->moveCard(2); 
                    }
                    else{
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                }

                else if(auxiliarStack6->peek()->getValue() == "A"){
                    std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                    print = false;
                }

                else{
                    if(auxiliarStack5->peek()->getValue() == "A" || auxiliarStack5->peek()->getValue() == "K" || auxiliarStack5->peek()->getValue() == "Q" || auxiliarStack5->peek()->getValue() == "J"){
                        std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                        print = false;
                    }
                    else{
                        if(stoi(auxiliarStack6->peek()->getValue()) == (stoi(auxiliarStack5->peek()->getValue())+1)){
                           this->moveCard(2);
                        }
                        else{
                            std::cout<<"No se puede mover la carta, no se cumple con el orden establecido.\n";
                            print = false;
                        }
                    }
                }   
            } 
        }
        //Reestablecer las pilas a su estado original    
        while(!this->auxiliarStack6->isEmpty()){
            this->targetStack->push(this->auxiliarStack6->pop());
        }
        
    }
    return print;
}

/*
 * Metodo encargadp de realizar el movimiento de una carta entre dos pilas.
 */
void MovementDriver::moveCard(int type){
    if(type == 0){
        auxiliarStack2->push(auxiliarStack1->pop());
        if(!auxiliarStack1->isEmpty()){
            auxiliarStack1->peek()->setHide(false);
        }
    }
    else if(type == 1){
        auxiliarStack4->push(auxiliarStack3->pop());
        if(!auxiliarStack3->isEmpty()){
            auxiliarStack3->peek()->setHide(false);
        }
    }
    else{
        auxiliarStack6->push(auxiliarStack5->pop());
        if(!auxiliarStack5->isEmpty()){
            auxiliarStack5->peek()->setHide(false);
        }
    }
    this->print = true;
}
