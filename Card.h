#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card {
    public:
        Card();
        Card(string value, int type, string color, bool hide);
        void setValue(string value);
        void setType(int type);
        void setColor(string color);
        void setHide(bool hide);
        string getValue();
        int getType();
        string getColor();
        bool isHide();
        ~Card();  //destructor, garantizando que no hayan perdidas de memoria o fugas de recursos cuando se destruyan objetos de Cartas
    
    private:
        string value;
        int type;
        string color;
        bool hide;
};
//CASO: TEMPLATES


#endif /* CARD_H */