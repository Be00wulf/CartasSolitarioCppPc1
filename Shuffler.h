#ifndef SHUFFLER_H
#define SHUFFLER_H
#include <string>
#include "Card.h"
#include "Stack.h"
#include "Queue.h"
#include "DoublyLinkedList.h"
using namespace std;

class Shuffler {
    
    public:
        Shuffler();
        void shuffleCards(DoublyLinkedList<Card*>* cards);
        void distributeQueues(DoublyLinkedList<Card*>* cards);
        void distributeStacks(DoublyLinkedList<Card*>* cards);
        Queue<Card*>* getQueue();
        DoublyLinkedList<Stack<Card*>*>* getPrincipalStacks();
        DoublyLinkedList<Stack<Card*>*>* getSecondaryStacks();

    private:
        Card* card;
        int randomNum;
        DoublyLinkedList<Stack<Card*>*>* principalStacks = new DoublyLinkedList<Stack<Card*>*>;
        DoublyLinkedList<Stack<Card*>*>* secondaryStacks = new DoublyLinkedList<Stack<Card*>*>;
        Queue<Card*>* queue = new Queue<Card*>;
};
#endif /* SHUFFLER_H */