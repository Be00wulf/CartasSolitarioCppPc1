#include "Card.h"
#include <string>
using namespace std;

Card::Card(){}

Card::Card(string value, int type, string color, bool hide){
    this->value = value;
    this->type = type;
    this->color = color;
    this->hide = hide;
}

void Card::setValue(string value){
    this->value = value;
}

void Card::setType(int type){
    this->type = type;
}

void Card::setColor(string color){
    this->color = color;
}

void Card::setHide(bool hide){
    this->hide = hide;
}

string Card::getValue(){
    return this->value;
}

int Card::getType(){
    return this->type;
}

string Card::getColor(){
    return this->color;
}

bool Card::isHide(){
    return this->hide;
}

Card::~Card(){
    
}