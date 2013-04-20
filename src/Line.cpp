#include "../include/Line.h"

Line::Line(Point i, Point f)
{
    //ctor
    this -> i = i;
    this -> f = f;


}

Line::Line()
{

}

Line::~Line()
{
    //dtor
}

void Line::exchangePoints(){

    Point temp;

    temp = i;
    i = f;
    f = temp;

}

void Line::drawLine()
{

    float e,ax,ay,temp;
    GLint s1,s2,intercambio,g,x,y;

	/** Operaciones**/
	x=i.getX();
	y=i.getY();
	ax=std::abs(f.getX()-x);
	ay=std::abs(f.getY()-y);
	s1=signo(f.getX()-y);
	s2=signo(f.getY()-y);

	if(ay>ax){

		temp=ax;
		ax=ay;
		ay=temp;
		intercambio=1;

	}
	else
		intercambio=0;

	/** condición de paro **/
	e=2*ay-ax;

    for(g=0;g<=ax;g++)
    {
        //printf("(%i , %i)\n",e,x,y);
        i.drawPoint();
        if(e>=0){
            if (intercambio==1)
                i.moveX(s1);

            else
                i.moveY(s2);
                 //y=y+s2;
            e=e-(2*ax);

        }
        else{
            if (intercambio==1)
                i.moveY(s2);
                //y=y+s2;

            else
                i.moveX(s1);
                //x=x+s1;

            e=e+2*ay;

        }

	}

}

int Line::signo(int num)
{

    if(num<0)return -1;
    if(num>0) return 1;
    return 0;
}
