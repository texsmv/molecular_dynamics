#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;
using namespace sf;

double pi = 3.14159265359;






class Molecula : public CircleShape{
public:
  Molecula(double x, double y, double r, double m, RenderWindow* wi){
    posicion.x = x;
    posicion.y = y;
    this->r = r;
    this->m = m;
    this->setRadius(r);    
    this->setOutlineThickness(1);
    this->setPosition(posicion);
    this->wi = wi;

  }
  Molecula(){}
  ~Molecula(){}
  void dibujar(){
    wi->draw(*this);
    sf::CircleShape circle;
    circle.setRadius(1);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1);
    circle.setPosition(this->getCenter());
    wi->draw(circle);
  }

  void update_position(){
    this->setPosition(posicion);
  }

  void set_velocidad(Vector2f vel){
    velocidad = vel;
  }

  void update(){    
    update_position();
    posicion = getPosition();
  }

  void mover(){
    posicion += velocidad;
  }

  Vector2f getCenter(){
    return Vector2f(posicion.x + r, posicion.y + r);
  }

  double x, y, r, m;
  Vector2f velocidad;
  Vector2f posicion;
  sf::RenderWindow* wi;
};







double to_degrees(double x){
  return x * pi / 180;
}

double to_radians(double x){
  return x * 180 / pi;
}

void impacto(double u1, double u2, double a1, double a2, double m1, double m2, double e, double& v1, double& v2, double& b1, double& b2){
  
  double F1 = e * (u1 * cos(a1) - u2 * cos(a2));    
  double F2 = m1 * u1 * cos(a1) + m2 * u2 *cos(a2);  
  double h1 = u1 * sin(a1);  
  double h2 = u2 * sin(a2);
  double V1 = F1 *m1;
  V1 = V1 + F2;
  V1 = V1 / (m1 + m2);
  b2 = atan(h2 / V1);  
  v2 = h2 / sin(b2);
  double V2 = F1 * -m2;
  V2 = V2 + F2;
  V2 = V2 / (m1 + m2);
  b1 = atan(h1 / V2);  
  v1 = h1 / sin(b1);
  


}


double angle_vector(Vector2f u, Vector2f v){
  double val = (u.x * v.x + u.y * v.y) / (sqrt(pow(u.x,2) + pow(u.y, 2)) * sqrt(pow(v.x,2) + pow(v.y, 2)));  
  val = acos(val);
  //val = to_radians(val);
  return val;
}





double angle_pairs(pair<double, double> u, pair<double, double> v){
  double val = (u.first * v.first + u.second * v.second) / (sqrt(pow(u.first,2) + pow(u.second, 2)) * sqrt(pow(v.first,2) + pow(v.second, 2)));  
  val = acos(val);  
  //val = to_radians(val);
  return val;
}

double angle_x_axis(Vector2f v){
  Vector2f u(1, 0);
  double val = (u.x * v.x + u.y * v.y) / (sqrt(pow(u.x,2) + pow(u.y, 2)) * sqrt(pow(v.x,2) + pow(v.y, 2)));  
  val = acos(val);  
  if(v.y < 0){
    val = to_degrees(180) + val;
  }
  return val;
}



double distance_vector(Vector2f u, Vector2f v){
  return sqrt(pow((u.x - v.x),2 ) + pow((u.y - v.y),2 ));
}


double modulo_vector(Vector2f v){
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}


double complemento(double x){
  x = to_radians(x);
  x = 360 - x;
  x = to_degrees(x);
  return x;
}

double min(double x,double y){
  if (x > y)
    return y;
  return x;
}