#include <iostream>

using namespace std;


class molecula{
private:
    float x;
    float y;
    float m;    
    
    float radio;

    float velocidad_x;
    float velocidad_y;

public:
    
    molecula(float x, float y, float radio, float m) {

        this->x = x;
        this->y = y;
        this->m = m;

        this->radio = radio;        

    }

  
    float get_velocidad_x() {
        return velocidad_x;
    }

    
    void set_velocidad_x(float velocidad_x) {
        this->velocidad_x = velocidad_x;
    }

    float get_velocidad_y() {
        return velocidad_y;
    }

    

    void set_velocidad_y(float velocidad_y) {
        this->velocidad_y = velocidad_y;
    }


    float get_x() {
        return x;
    }


    void set_x(float x) {
        this->x = x;
    }


    float get_y() {
        return y;
    }


    void set_y(float y) {
        this->y = y;
    }

    float get_masa(){
        return m;
    }

    
    float get_radio(){
        return radio;
    }

    float set_radio(float radio){
        this-> radio = radio;
    }


    
};
