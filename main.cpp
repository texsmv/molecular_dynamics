#include "funciones.h"



int main(int argc, char const *argv[]) {
	
  	double u1, u2, m1, m2, a1, a2, e1;
  	u1 = 10;
  	u2 = 10;
	m1 = 2;
	m2 = 3;
	a1 = to_degrees(0);
	a2 = to_degrees(180);
	e1 = 1;

	double v1, v2, b1, b2;

	impacto(u1, u2, a1, a2, m1, m2, e1, v1, v2, b1, b2);
	cout<<v1<<endl;
	cout<<v2<<endl;
	cout<<to_radians(b1)<<endl;
	cout<<to_radians(b2)<<endl;

	

	/*
	

	sf::RenderWindow *window=new sf::RenderWindow(sf::VideoMode(700, 700), "SFML works!");
	



	sf::Event ev;
	sf::Event* e=&ev;

	Molecula m1(100, 40, 30, 2, window);
	Molecula m2(80, 140, 30, 2, window);

	m1.set_velocidad(Vector2f(0, 0.01));
	m2.set_velocidad(Vector2f(0, -0.01));


	

	while (window->isOpen())
	{
	    sf::Event event;
	    sf::Event* evento=&event;

	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed || ( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) )
	            window->close();
	    }
	    m1.mover();
	    m2.mover();
	    if(distance_vector(m1.getCenter(), m2.getCenter()) < m1.r + m2.r){
	    	cout<<"impacto"<<endl;
	    	double u1, u2, ma1, ma2, a1, a2, e1;
	    	double v1, v2, b1, b2;
	    	e1 = 1;
	    	u1 = modulo_vector(m1.velocidad);
	    	u2 = modulo_vector(m2.velocidad);
	    	ma1 = m1.m;
	    	ma2 = m2.m;
	    	a1 = angle_vector(m1.velocidad, m2.getCenter() - m1.getCenter());
	    	a2 = angle_vector(m2.velocidad, m2.getCenter() - m1.getCenter());
	    	//a1 = angle_x_axis(m2.getCenter() - m1.getCenter()) - angle_x_axis(m1.velocidad);
	    	
	    	//a2 = angle_x_axis(m2.getCenter() - m1.getCenter()) + angle_x_axis(m2.velocidad);
	    	
	    	
	    	//a1 = complemento(a1);
	    	//a2 = complemento(a2);
	    	
	    	cout<<"m1 :"<<ma1<<endl;
	    	cout<<"m2 :"<<ma2<<endl;
	    	cout<<"u1 :"<<u1<<endl;
	    	cout<<"u2 :"<<u2<<endl;
	    	cout<<"a1 :"<<to_radians(a1)<<endl;
	    	cout<<"a2 :"<<to_radians(a2)<<endl;
	    	
	    	impacto(u1, u2, a1, a2, ma1, ma2, e1, v1, v2, b1, b2);
	    	cout<<"impacto"<<endl;
	    	cout<<"v1 :"<<v1<<endl;
	    	cout<<"v2 :"<<v2<<endl;
	    	cout<<"b1 :"<<to_radians(b1)<<endl;
	    	cout<<"b2 :"<<to_radians(b2)<<endl;
	    	

	    	
	    	//b1 = angle_x_axis(m2.getCenter() - m1.getCenter()) + b1;
	    	//b2 = angle_x_axis(m1.getCenter() - m2.getCenter()) + b2;
	    	b1 = angle_x_axis(m1.getCenter() - m2.getCenter()) + b1;
	    	b2 = angle_x_axis(m1.getCenter() - m2.getCenter()) + b2;
	    	cout<<to_radians(b1)<<endl;
	    	cout<<to_radians(b2)<<endl;
	    	
	    	m1.set_velocidad(Vector2f(v1*sin(b1), v1*cos(b1)));
	    	m2.set_velocidad(Vector2f(v2*sin(b2), v2*cos(b2)));
	    	m1.posicion = m1.getPosition();
	    	m2.posicion = m2.getPosition();
	    	m1.mover();
	    	m2.mover();
	    	m1.update();
		    m2.update();

	    }
	    else{
	    	
	    	double u1, u2, ma1, ma2, a1, a2, e1;
	    	double v1, v2, b1, b2;
	    	e1 = 1;
	    	u1 = modulo_vector(m1.velocidad);
	    	u2 = modulo_vector(m2.velocidad);
	    	ma1 = m1.m;
	    	ma2 = m2.m;
	    	a1 = angle_vector(m1.velocidad, m2.getCenter() - m1.getCenter());
	    	a2 = angle_vector(m2.velocidad, m1.getCenter() - m2.getCenter());
	    	impacto(u1, u2, a1, a2, ma1, ma2, e1, v1, v2, b1, b2);


	    	cout<<to_radians(b1)<<endl;
	    	cout<<to_radians(b2)<<endl;
	    	//b1 = angle_x_axis(m2.getCenter() - m1.getCenter()) + b1;
	    	//b2 = angle_x_axis(m1.getCenter() - m2.getCenter()) + b2;
	    	b1 = angle_x_axis(m1.velocidad) + b1;
	    	b2 = angle_x_axis(m2.velocidad) + b2;
	    	cout<<to_radians(b1)<<endl;
	    	cout<<to_radians(b2)<<endl;
		    m1.update();
		    m2.update();
		    cout<<"----------"<<endl;
	    	
	    }
	    window->clear();
	    m1.dibujar();        
	    m2.dibujar();
        window->display();
	    
	}
	
	
	*/	
	
  	return 0;
}
