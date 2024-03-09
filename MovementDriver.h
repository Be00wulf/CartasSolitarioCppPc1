#ifndef MOVEMENTDRIVER_H
#define MOVEMENTDRIVER_H
#include "Card.h"
#include "Queue.h"
#include "Stack.h"
#include "DoublyLinkedList.h"

class MovementDriver {
public:
    MovementDriver();
    void moveQueue(Queue<Card*>* queue, Stack<Card*>* stack);
    bool movePrincipalCards(DoublyLinkedList<Stack<Card*>*>* principalStacks, int selectedColumn, int targetColumn, int amount);
    bool moveToSecondaryStack(DoublyLinkedList<Stack<Card*>*>* principalStacks, DoublyLinkedList<Stack<Card*>*>* secondaryStacks, int selectedColumn);
    bool moveToPrincipalStack(Stack<Card*>* stack, DoublyLinkedList<Stack<Card*>*>* principalStacks, int targetColumn);

private:
    void moveCard(int type);
    int currentAmount;
    bool print;
    Stack<Card*>* auxiliarStack = new Stack<Card*>;
    Stack<Card*>* auxiliarStack1 = new Stack<Card*>;
    Stack<Card*>* auxiliarStack2 = new Stack<Card*>;
    Stack<Card*>* auxiliarStack3 = new Stack<Card*>;
    Stack<Card*>* auxiliarStack4 = new Stack<Card*>;
    Stack<Card*>* auxiliarStack5 = new Stack<Card*>;
    Stack<Card*>* auxiliarStack6 = new Stack<Card*>;
    Stack<Card*>* selectedStack = new Stack<Card*>;
    Stack<Card*>* targetStack = new Stack<Card*>;

};

#endif /* MOVEMENTDRIVER_H */