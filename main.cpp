#include <iostream>
#include "controlador.h"






int main(int argc, char const *argv[]) {

	
	srand(time(NULL));
	cout<<asin(sin(0.5 * 180 / pi)) <<endl;
	cout<<sin(asin(0.5)) <<endl;
	float alto , ancho;
	alto = 500;
	ancho = 700;
	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(ancho, alto), "Proyecto Moleculas");

	Controlador controlador(alto, ancho,  window);
	controlador.set_numero_moleculas(60);
	controlador.crear_moleculas();

	int cont = 0;

	while (window->isOpen())
	{
	    sf::Event event;
	    

	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) )
	            window->close();
	    }
	   

	    window->clear();		
	    controlador.update();
        window->display();
        
        cont++;

	}


	

  	return 0;

  	
}
