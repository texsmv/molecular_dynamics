#include <iostream>
#include "controlador.h"






int main(int argc, char const *argv[]) {

	
	srand(time(NULL));

	float alto , ancho, tiempoRefresco;
	alto = 500;
	ancho = 700;
	tiempoRefresco = 0.005;

	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(ancho, alto), "Proyecto Moleculas");

	Controlador controlador(alto, ancho,  tiempoRefresco, window);
	controlador.set_numero_moleculas(1);
	controlador.crear_moleculas();

	Clock clockM;


	while (window->isOpen())
	{
	    sf::Event event;
	    

	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) )
	            window->close();
	    }
	   

	    Time te = clockM.getElapsedTime();  

        if(te.asSeconds() > tiempoRefresco ){
        	window->clear();	

	    	controlador.update();

	   
	    	clockM.restart();
        	window->display();
		}


	}

  	return 0;

  	
}
