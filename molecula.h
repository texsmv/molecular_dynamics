#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


class molecula{
private:
    float x;
    float y;
    float m;    
    float radio;
    sf::RenderWindow* window;
    sf::CircleShape circle;
    float velocidad_x;
    float velocidad_y;
    float aceleracion_x = 0;
    float aceleracion_y = 0;
    float fuerza_x = 0;
    float fuerza_y = 0;
public:
    
    molecula(float x, float y, float radio, float m,sf::RenderWindow* window ) {
        this->x = x;
        this->y = y;
        this->m = m;
        this-> window = window;
        this->radio = radio;        
        circle.setRadius(get_radio());
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(1);
        
    }

    void dibujar() {      
        
        
        circle.setPosition(get_x() - get_radio(), get_y() - get_radio());
        window->draw(circle);
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

    float get_aceleracion_x() {
        return aceleracion_x;
    }

    float get_aceleracion_y() {
        return aceleracion_y;
    }

    float get_fuerza_x(){
        return fuerza_x;
    }

    float get_fuerza_y(){
        return fuerza_y;
    }

    void set_fuerza_x(float fuerza_x){
        this->fuerza_x = fuerza_x;
    }

    void set_fuerza_y(float fuerza_y){
        this->fuerza_y = fuerza_y;
    }


    void set_aceleracion_x(float aceleracion_x){
        this->aceleracion_x = aceleracion_x;
    }

    void set_aceleracion_y(float aceleracion_y){
        this->aceleracion_y = aceleracion_y;
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
