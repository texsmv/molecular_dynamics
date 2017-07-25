#include "molecula.h"
#include <vector>
#include <math.h>

int numero_random(int a, int b){
  return a + rand()%(b - a);
}

float distancia(float x1, float y1, float x2, float y2){
	
	return sqrt(fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2));
}

double pi = 3.14159265359;

using namespace sf;

class Controlador
{
public:
	Controlador(){}
	Controlador(float alto, float ancho, float te,RenderWindow* wi){
		this->ancho = ancho;
		this->alto = alto;	
		this->tiempoEmpleado = te;	
		window = wi;
	}
	~Controlador(){}

	bool b_update = true;
	float tiempoEmpleado;
	float alto;
	float ancho;
	float e = 40.3;
	float o = 3.33;
	float a_gravedad = 0.5;
	RenderWindow* window;
	Event* evento;	
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
			molecula* mol = new molecula(numero_random(0, ancho), numero_random(0, alto), 2 , 0.0001, window);
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

	void dibujar_moleculas(){
		for(auto mol : moleculas){
			mol->dibujar();
		}
	}

	void update_fuerza_moleculas(){
		for(auto mol : moleculas){
			mol->set_fuerza_y(a_gravedad * mol->get_masa());
			mol->set_fuerza_x(0);
		}
	}

	void update_velocidad_moleculas(){

		float utotal = 0;

		for(auto mol : moleculas){
			mol->set_aceleracion_x(mol->get_fuerza_x() / mol->get_masa());
			mol->set_aceleracion_y(mol->get_fuerza_y() / mol->get_masa());
			mol->set_velocidad_x(mol->get_velocidad_x() + mol->get_aceleracion_x() * tiempo_frame());
			mol->set_velocidad_y(mol->get_velocidad_y() + mol->get_aceleracion_y() * tiempo_frame());
			//cout<<mol->get_velocidad_y()<<endl; //<<" "<<mol->get_aceleracion_y()<<" "<<mol->get_fuerza_y()<<endl;
			
			float vxx = mol->get_velocidad_x();
			float vyy = mol->get_velocidad_y();
			float u = 0.5 * mol->get_masa()*(vxx*vxx + vyy * vyy); 
			utotal+=u;

			//cout << "u " << u << " " << vxx << " " << vyy  << "m" << mol->get_masa() << endl;
		}

		cout << "UTOTAL: "<<utotal << endl;

	}

	void update(){

		if (b_update){
			colisiones_moleculas();
			colisiones_caja();
			//update_fuerza_moleculas(); //Gravedad
			//leonard_jones_moleculas();
			update_velocidad_moleculas();
			mover_moleculas();
			dibujar_moleculas();
			
		}
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
				}
			}
		}
	}

	void leonard_jones_moleculas(){
		vector<vector<bool>> b_lennard(n, vector<bool>(n, false));
		for(int i = 0; i < n; i++){
			if(!b_update)
				break;
			for(int j = 0; j < n; j++){
				if(!b_lennard[i][j] && i != j){
		
					b_lennard[i][j] = true;
					b_lennard[j][i] = true;
					//cout<<"-"<<endl;
					
					//cout<<i<<" "<<j<<endl;
					float r = distancia(moleculas[i]->get_x(), moleculas[i]->get_y(), moleculas[j]->get_x(), moleculas[j]->get_y());
					r *= 1.3;
					/*
					cout<<moleculas[i]->get_x()<<endl;
					cout<<moleculas[i]->get_y()<<endl;
					cout<<moleculas[j]->get_x()<<endl;
					cout<<moleculas[j]->get_y()<<endl;
					*/
					r *= 2;
					if (r == 0){
						r = 0.00000000001;
						continue;
					}
					//cout<<"r "<<r<<endl;
					float f = f_potencial_leonard_jones(e, o, r);
					
					float p = (moleculas[i]->get_x() - moleculas[j]->get_x());
					float q = (moleculas[i]->get_y() - moleculas[j]->get_y());
					if (p == 0)
						p =0.0000000001;
					if (q == 0)
						q =0.0000000001;
					/*
					cout<<p<<endl;
					cout<<q<<endl;
					*/
					if(q == 0){
						q = 0.0000000000001;
					}
					//cout<<p/q<<endl;
					float a = asin(sin(p / q));
					

					moleculas[i]->set_fuerza_y(moleculas[i]->get_fuerza_y() + f * sin(a) *  tiempo_frame());
					moleculas[i]->set_fuerza_x(moleculas[i]->get_fuerza_x() + f * cos(a) *  tiempo_frame());
					moleculas[j]->set_fuerza_y(moleculas[j]->get_fuerza_y() - f * sin(a) *  tiempo_frame());
					moleculas[j]->set_fuerza_x(moleculas[j]->get_fuerza_x() - f * cos(a) *  tiempo_frame());
					//scout<<"df "<<f<<endl;
					if (f>10)
						cout<<"f: "<<f<<endl;
					/*
					cout<<"fy "<<moleculas[j]->get_fuerza_y()<<endl;
					cout<<"fx "<<moleculas[j]->get_fuerza_x()<<endl;
					cout<<"a "<<a * 180 / pi<<endl;
					cout<<"sin a "<<sin(a) <<endl;
					cout<<"df "<<f<<endl;
					*/
					if(isnan(a) || isnan(f) || isnan(sin(a) || isnan(moleculas[j]->get_x())) || isnan(moleculas[i]->get_x()) || isnan(moleculas[i]->get_y()) || isnan(moleculas[j]->get_y()) || isnan(moleculas[j]->get_fuerza_y()) 
						|| isinf(moleculas[i]->get_fuerza_y()) || isinf(moleculas[j]->get_fuerza_y()) || isinf(moleculas[i]->get_fuerza_x()) || isinf(moleculas[j]->get_fuerza_x())){
						b_update = false;
						break;
					}

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
  		      

		return;        
	}

	bool verificar_colision_moleculas(molecula* mol1,  molecula* mol2){
		if (distancia(mol1->get_x(), mol1->get_y(), mol2->get_x(), mol2->get_y()) < mol1->get_radio() + mol2->get_radio() - 0.1){
			
			return true;
		}
		return false;
	}

	float f_potencial_leonard_jones(float e, float o, float r){
		
		return -24 * e * (2 * ( pow(o, 12) / pow(r, 13)) - ( pow(o, 6) / pow(r, 7)) ) ;
	}

	float tiempo_frame(){
		return tiempoEmpleado;
	}

};