#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;
using namespace sf;

double pi = 3.14159265359;


class ball{
private:
    float x;
    float y;
    float diametar;
    sf::RenderWindow* wi;
    
    double xSpeed;
    double ySpeed;
public:
    float m;
    ball(float x, float y, float diameter, float m,sf::RenderWindow* wi ) {
        this->x = x;
        this->y = y;
        this->m = m;
        this-> wi = wi;
        this->diametar = diameter;
        
    }

    void draw() {
        
        //Ellipse2D.Double circle = new Ellipse2D.Double(getX() - getDiametar() / 2, getY() - getDiametar() / 2, getDiametar(), getDiametar());
        
        sf::CircleShape circle;
        circle.setRadius(getDiametar()/2.);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(1);
        circle.setPosition(getX() - getDiametar() / 2, getY() - getDiametar() / 2);
        wi->draw(circle);
    }

    void move() {
        setX((float) (getX() + getxSpeed()));

        if (getX() - getDiametar() / 2 < 0) {
            setX(getDiametar() / 2);
            setxSpeed(-getxSpeed());
        } else if (getX() + getDiametar() / 2 > 390) {
            setxSpeed(-getxSpeed());
        }

        setY((float) (getY() + getySpeed()));

        if (getY() - getDiametar() / 2 < 0) {
            setySpeed(-getySpeed());
        } else if (getY() + getDiametar() / 2 > 360) {
            setY(360 - getDiametar() / 2);
            setySpeed(-getySpeed());
        }
    }

    /**
     * @return the xSpeed
     */
    double getxSpeed() {
        return xSpeed;
    }

    /**
     * @param xSpeed the xSpeed to set
     */
    void setxSpeed(double xSpeed) {
        this->xSpeed = xSpeed;
    }

    /**
     * @return the ySpeed
     */
    double getySpeed() {
        return ySpeed;
    }

    /**
     * @param ySpeed the ySpeed to set
     */
    void setySpeed(double ySpeed) {
        this->ySpeed = ySpeed;
    }

    /**
     * @return the x
     */
    float getX() {
        return x;
    }

    /**
     * @param x the x to set
     */
    void setX(float x) {
        this->x = x;
    }

    /**
     * @return the y
     */
    float getY() {
        return y;
    }

    /**
     * @param y the y to set
     */
    void setY(float y) {
        this->y = y;
    }

    /**
     * @return the diametar
     */
    float getDiametar() {
        return diametar;
    }

    /**
     * @param diameter
     */
    void setDiametar(float diameter) {
        this->diametar = diameter;
    }
};

void collision2Ds(double m1, double m2, double R,
                 double x1, double y1, double x2, double y2,
                 double& vx1, double& vy1, double& vx2, double& vy2)     {

       double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;


       m21=m2/m1;
       x21=x2-x1;
       y21=y2-y1;
       vx21=vx2-vx1;
       vy21=vy2-vy1;

       vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
       vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;


//     *** return old velocities if balls are not approaching ***
       if ( (vx21*x21 + vy21*y21) >= 0) return;


//     *** I have inserted the following statements to avoid a zero divide;
//         (for single precision calculations,
//          1.0E-12 should be replaced by a larger value). **************

       fy21=1.0E-12*fabs(y21);
       if ( fabs(x21)<fy21 ) {
                   if (x21<0) { sign=-1; } else { sign=1;}
                   x21=fy21*sign;
        }

//     ***  update velocities ***
       a=y21/x21;
       dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
       vx2=vx2+dvx2;
       vy2=vy2+a*dvx2;
       vx1=vx1-m21*dvx2;
       vy1=vy1-a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;

       return;
}

void checkCollision(ball& b1, ball& b2, double& deltaX, double& deltaY, double& distance) {

      deltaX = fabs(b1.getX() - b2.getX());
      deltaY = fabs(b1.getY() - b2.getY());
      distance = deltaX * deltaX + deltaY * deltaY;
      
      if (distance < (b1.getDiametar() / 2 + b2.getDiametar() / 2) * (b1.getDiametar() / 2 + b2.getDiametar() / 2)) {
          /*
          double newxSpeed1 = (b1.getxSpeed() * (4 - 7) + (2 * 7 * b2.getxSpeed())) / 11;

          double newxSpeed2 = (b2.getxSpeed() * (7 - 4) + (2 * 4 * b1.getxSpeed())) / 11;

          double newySpeed1 = (b1.getySpeed() * (4 - 7) + (2 * 7 * b2.getySpeed())) / 11;

          double newySpeed2 = (b2.getySpeed() * (7 - 4) + (2 * 4 * b1.getySpeed())) / 11;

          b2.setxSpeed(newxSpeed2);
          b2.setySpeed(newySpeed2);
          b1.setxSpeed(newxSpeed1);
          

          b1.setySpeed(newySpeed1);
        */
        double vx1, vy1, vx2, vy2;
        vx1= b1.getxSpeed();
        vy1= b1.getySpeed();
        vx2= b2.getxSpeed();
        vy2= b2.getySpeed();
        collision2Ds(b1.m, b2.m, 1.0, b1.getX() , b1.getY(),b2.getX(), b2.getY(), vx1, vy1, vx2, vy2);
        b1.setxSpeed(vx1);
        b1.setySpeed(vy1);
        b2.setxSpeed(vx2);
        b2.setySpeed(vy2);

      }
  }











