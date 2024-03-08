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
int targetRow;
int targetColumn;


int main(){
    //Creamos todas las cartas y las mandamos a barajear.
    cards = creator.createCards();
    shuffler.shuffleCards(cards);
    delete cards;
    
    //Obtenemos las cartas organizadas dentro de sus respectivas estructuras.
    queue = shuffler.getQueue();
    principalStacks = shuffler.getPrincipalStacks();
    secondaryStacks = shuffler.getSecondaryStacks();
       
    //Enviamos a imprimir la configuracion inicial.
    printer.print(queue, stack, principalStacks, secondaryStacks);

    try{
        //Ingresamos al menu del juego.
        while(option != 5){
            cout<< "\nSOLITARIO" <<endl;
            cout<< "1. Sacar carta de la cola." <<endl;
            cout<< "2. Mover carta de la cola al tablero principal." <<endl;
            cout<< "3. Mover Carta en el tablero principal." <<endl;  
            cout<< "4. Mover carta del tablero principal a la pila." <<endl;
            cout<< "5.Salir del Juego." <<endl;
            cout<< "Seleccione una opcion" <<endl;
            cin >> option;
            switch(option){
                case 1:
                    movementDriver.moveQueue(queue, stack);
                    printer.print(queue, stack, principalStacks, secondaryStacks);
                break;
                case 2:
                    cout<<"Ingrese la columna destino: ";
                    cin >> targetColumn; 
                    if(movementDriver.moveToPrincipalStack(stack, principalStacks, targetColumn)){
                        printer.print(queue, stack, principalStacks, secondaryStacks);
                    }
                break;
                case 3:
                    cout<<"Ingrese la columna origen: ";
                    cin >> selectedColumn;  
                    cout<<"Ingrese la columna destino: ";
                    cin >> targetColumn; 
                    cout<<endl;
                    if(movementDriver.movePrincipalCards(principalStacks, selectedColumn, targetColumn)){
                        printer.print(queue, stack, principalStacks, secondaryStacks);
                    }
                break;
                case 4:
                    cout<<"Ingrese la columna origen: ";
                    cin >> selectedColumn;  
                    if(movementDriver.moveToSecondaryStack(principalStacks, secondaryStacks, selectedColumn)){
                         printer.print(queue, stack, principalStacks, secondaryStacks);
                    }     
                break;
                case 5:
                    cout<<"-------------------Terminando el Juego-------------------" <<endl;
                break;
                default:
                    printer.print(queue, stack, principalStacks, secondaryStacks);
                    cout<<"La opcion seleccionada no es valida" <<endl;
                break;     
            }
        }
    }
    catch(string e){
        cout<<e<<endl;
    }
    return 0;
}