#include "funciones.h"






int main(int argc, char const *argv[]) {



	sf::RenderWindow *window=new sf::RenderWindow(sf::VideoMode(700, 700), "SFML works!");




	sf::Event ev;
	

	ball b1(50, 80, 30, 3,window);	
    bool going = true;

    
    ball b2(50, 80, 70, 10,window);
    double deltaX;
    double deltaY;
    double distance;

    
    b1.setX(50);
    b1.setY(80);
    b1.setxSpeed(0.1);
    b1.setySpeed(0.1);

    
    b2.setX(150);
    b2.setY(80);
    b2.setxSpeed(0.04);
    b2.setySpeed(0.02);



	while (window->isOpen())
	{
	    sf::Event event;
	    

	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) )
	            window->close();
	    }
	    
	    b1.move();
        b2.move();

        checkCollision(b1, b2, deltaX, deltaY, distance);

	    window->clear();
		b1.draw();
        b2.draw();	    
        window->display();

	}


	

  	return 0;

  	
}
