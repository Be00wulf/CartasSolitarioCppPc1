#include <memory>

#include "Card.h"
#include "CardCreator.h"
#include "Shuffler.h"
#include "Queue.h"
#include "Printer.h"
#include "MovementDriver.h"
using namespace std;
/*
 * 
 */
CardCreator creator;
Shuffler shuffler;
Printer printer;
MovementDriver movementDriver;
DoublyLinkedList<Card*>* cards = new DoublyLinkedList<Card*>;
Queue<Card*>* queue;
Stack<Card*>* stack = new Stack<Card*>;
DoublyLinkedList<Stack<Card*>*>* principalStacks;
DoublyLinkedList<Stack<Card*>*>* secondaryStacks;
bool endGame = false;
int option;
int selectedRow;
int selectedColumn;
int amount;
int targetRow;
int targetColumn;


int main(){
    //Creamos y barajamos cartas
    cards = creator.createCards();
    shuffler.shuffleCards(cards);
    delete cards;
    
    //colocar cartas en las estructuras
    queue = shuffler.getQueue();
    principalStacks = shuffler.getPrincipalStacks();
    secondaryStacks = shuffler.getSecondaryStacks();
       
    //CONFIGURACION INICIAL
    printer.print(queue, stack, principalStacks, secondaryStacks);

    try{
        //MENU
        while(option != 5){
            cout<< "\nOPCIONES:" <<endl;
            cout<< "1. Voltear una carta de la cola de cartas comodin." <<endl;
            cout<< "2. Sacar una carta de la cola y colocarla en el tablero principal." <<endl;
            cout<< "3. Mover una carta entre las listas del tablero principal." <<endl;  
            cout<< "4. Mover una carta del tablero principal a una pila." <<endl;
            cout<< "5. Salir" <<endl;
            cout<< "Seleccione una opcion" <<endl;
            cin >> option;

            switch(option){
                case 1: //VOLTEANDO CARTA DE LA COLA
                    movementDriver.moveQueue(queue, stack);
                    printer.print(queue, stack, principalStacks, secondaryStacks);
                break;

                case 2: //CARTA DE COLA AL TABLERO
                    cout<<"Ingrese la columna destino: ";
                    cin >> targetColumn; 
                    if(movementDriver.moveToPrincipalStack(stack, principalStacks, targetColumn)){
                        printer.print(queue, stack, principalStacks, secondaryStacks);
                    }
                break;

                case 3: //CARTA ENTRE LAS LISTAS 
                    cout<<"Ingrese la columna origen: ";
                    cin >> selectedColumn;  
                    cout<<"Ingrese la columna destino: ";
                    cin >> targetColumn;
                    cout << "Ingrese la cantidad de cartas: ";
                    cin >> amount; 
                    cout<<endl;
                    if(movementDriver.movePrincipalCards(principalStacks, selectedColumn, targetColumn, amount)){
                        printer.print(queue, stack, principalStacks, secondaryStacks);
                    }
                break;
                
                case 4:     //DE LISTAS A PILA
                    cout<<"Ingrese la columna origen: ";
                    cin >> selectedColumn;  
                    if(movementDriver.moveToSecondaryStack(principalStacks, secondaryStacks, selectedColumn)){
                         printer.print(queue, stack, principalStacks, secondaryStacks);
                    }     
                break;

                case 5: //SALIR
                    cout<<"FIN DE LA PARTIDA" <<endl;
                break;

                default:
                    printer.print(queue, stack, principalStacks, secondaryStacks);
                    cout<<"Seleccione una opcion dentro de los valores del manu" <<endl;
                break;     
            }
        }
    }
    catch(string e){
        cout<<e<<endl;
    }
    return 0;
}