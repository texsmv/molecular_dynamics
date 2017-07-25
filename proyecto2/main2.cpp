#include <iostream>
#include "controlador2.h"


int main(int argc, char const *argv[]) {

	
	srand(time(NULL));
	float tiempoRefresco = 0.005;
	float alto = 500;
	float ancho = 700;
	
	Controlador controlador(alto, ancho,  tiempoRefresco);
	controlador.set_numero_moleculas(1000);
	controlador.crear_moleculas();

	while (true)
	{
	   	controlador.update();
	}

  	return 0;

  	
}
