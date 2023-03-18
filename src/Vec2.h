#ifndef _VEC2_H_
#define _VEC2_H_

struct Vec2			// un struct suffit ici (mais une classe irait aussi)
{
	int x,y;
	
	Vec2(int _x, int _y);
	
	static void testRegression() const;
}

Vec2 operator+(Vec2, vec2);
Vec2 operator-(Vec2, vec2);
bool operator==(Vec2 , Vec2 );

#endif