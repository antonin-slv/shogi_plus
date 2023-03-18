#ifndef _VEC2_H_
#define _VEC2_H_

class Vec2			// un struct suffit ici (mais une classe irait aussi)
{	public : 
		int x,y;
		
		Vec2(int _x=0, int _y=0);
		

		Vec2 operator+=(Vec2);

};

Vec2 operator+(Vec2, Vec2);
Vec2 operator-(Vec2, Vec2);
bool operator==(Vec2 , Vec2 );
bool operator!=(Vec2 , Vec2 );


#endif