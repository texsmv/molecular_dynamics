#include "molecula2.h"
#include <vector>
#include <math.h>


int numero_random(int a, int b){
  return a + rand()%(b - a);
}

float distancia(float x1, float y1, float x2, float y2){
	
	return sqrt(fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2));
}

double pi = 3.14159265359;


class Controlador
{
public:
	Controlador(){}
	Controlador(float alto, float ancho, float te){
		this->ancho = ancho;
		this->alto = alto;	
		this->tiempoEmpleado = te;	
	}

	~Controlador(){}

	bool b_update = true;
	float tiempoEmpleado;
	float alto;
	float ancho;
	float e = 40.3;
	float o = 3.33;
	float a_gravedad = 0.5;

	vector<molecula*> moleculas;
	
	int n; //Numero de moleculas

	void set_numero_moleculas(int n){
		this-> n = n;
	}

	int get_numero_moleculas(){
		return n;
	}

	void crear_moleculas(){
		for(int i = 0; i < this->n; i++){
			molecula* mol = new molecula(numero_random(0, ancho), numero_random(0, alto), 2 , 0.0001);
			mol->set_velocidad_x(numero_random(-150, 150));
			mol->set_velocidad_y(numero_random(-150, 150));
			//mol->set_velocidad_x(100);
			//mol->set_velocidad_y(0);
		
			moleculas.push_back(mol);
		}
	}

	void colisiones_caja(){
		for(auto mol : moleculas){
			
			if (mol->get_x() - mol->get_radio() < 0){
	            mol->set_x(mol->get_radio());
	            mol->set_velocidad_x(-mol->get_velocidad_x() * 1);
	        }
	        else if(mol->get_x() + mol->get_radio() > ancho){
				mol->set_x(ancho - mol->get_radio());
	            mol->set_velocidad_x(-mol->get_velocidad_x() * 1);	
	        }
	        if (mol->get_y() - mol->get_radio() < 0) {
	        	mol->set_y(mol->get_radio());
	        	mol->set_velocidad_y(-mol->get_velocidad_y() * 1 );
	        }
	        else if(mol->get_y() + mol->get_radio() > alto){
	        	//Choque Piso
	        	mol->set_y(alto - mol->get_radio());
	        	mol->set_velocidad_y(- mol->get_velocidad_y() * 1  );
	        }
		}

	}

	void mover_moleculas(){
		for(auto mol : moleculas){
			mol->set_x(mol->get_x() + mol->get_velocidad_x() * tiempo_frame());
			mol->set_y(mol->get_y() + mol->get_velocidad_y() * tiempo_frame());
		}
	}

	float cont_i = 0;
	void update(){

			//cout <<  cont_i  << ",";

			colisiones_moleculas();
			colisiones_caja();
			mover_moleculas();

			cont_i++;						
		
	}

	void colisiones_moleculas(){
		vector<vector<bool>> b_colision(n, vector<bool>(n, false));

		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i!= j)
					if(!b_colision[i][j])
						if(verificar_colision_moleculas(moleculas[i], moleculas[j])){
							b_colision[i][j] = true;
							b_colision[j][i] = true;
							colision_moleculas(moleculas[i], moleculas[j]);
							//cout << "coli";
							//cout << this->cont_i << " " << j <<  endl;
							
							if(i>100 && i <=105)  cout << this->cont_i <<","<< i << ","<<moleculas[i]->get_x() << "," <<  moleculas[i]->get_y()<<endl;
							if(j>100 && j <=105)  cout << this->cont_i <<","<< i  <<  ","<<moleculas[j]->get_x() << "," <<  moleculas[i]->get_y()<<endl;
						}
			}
		}
	}


	void colision_moleculas(molecula* mol1, molecula* mol2){
		double m1, m2, R, x1, y1, x2, y2, vx1, vy1, vx2, vy2;

		if(x1 == x2)
			cout<<"x"<<endl;
		if(y1 == y2)
			cout<<"y"<<endl;
		x1 	= mol1->get_x();
		y1 	= mol1->get_y();
		vx1 = mol1->get_velocidad_x();
        vy1 = mol1->get_velocidad_y();
        m1  = mol1->get_masa();

        x2 	= mol2->get_x();
		y2 	= mol2->get_y();
        vx2 = mol2->get_velocidad_x();
        vy2 = mol2->get_velocidad_y();
        m2  = mol2->get_masa();
        
        R = 1;

        double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;



        m21=m2/m1;
		x21=x2-x1;
		y21=y2-y1;
		vx21=vx2-vx1;
		vy21=vy2-vy1;

		vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
		vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;

		
		if ( (vx21*x21 + vy21*y21) >= 0) return;


		fy21=1.0E-12*fabs(y21);
		if ( fabs(x21)<fy21 ) {
		           if (x21<0) { sign=-1; } else { sign=1;}
		           x21=fy21*sign;
		}

		
		a=y21/x21;
		dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
		vx2=vx2+dvx2;
		vy2=vy2+a*dvx2;
		vx1=vx1-m21*dvx2;
		vy1=vy1-a*m21*dvx2;

		
		vx1=(vx1-vx_cm)*R + vx_cm;
		vy1=(vy1-vy_cm)*R + vy_cm;
		vx2=(vx2-vx_cm)*R + vx_cm;
		vy2=(vy2-vy_cm)*R + vy_cm;

		mol1->set_velocidad_x(vx1);
		mol1->set_velocidad_y(vy1);

		mol2->set_velocidad_x(vx2);
		mol2->set_velocidad_y(vy2);



	}

	bool verificar_colision_moleculas(molecula* mol1,  molecula* mol2){
		if (distancia(mol1->get_x(), mol1->get_y(), mol2->get_x(), mol2->get_y()) < mol1->get_radio() + mol2->get_radio() - 0.1){
			
			return true;
		}
		return false;
	}

	float tiempo_frame(){
		return tiempoEmpleado;
	}

};