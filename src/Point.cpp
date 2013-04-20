#include "../include/Point.h"

Point::Point(GLint x, GLint y)
{
    //ctor
    this->x = x;
    this->y = y;
}

Point::Point()
{
    //ctor
    this->x = 0;
    this->y = 0;
}

Point::~Point()
{
    //dtor
}

GLint Point::getX(){
    return x;
}

GLint Point::getY(){
    return y;
}

void Point::setX(GLint x){
    this->x = x;
}

void Point::setY(GLint y){
    this->y = y;
}

void Point::drawPoint(){

    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();

}

void Point::moveX(int x){
    this->x+=x;
}
void Point::moveY(int y){
    this->y+=y;
}

bool Point::operator > (Point p2){
    if(this->x > p2.x)
        return true;
    return false;
}

void Point::operator = (Point p2){
    this->x = p2.x;
    this->y = p2.y;
}

bool Point::operator == (Point p2){
    if(this->x == p2.x && this->y == p2.y)
        return true;
    return false;
}
