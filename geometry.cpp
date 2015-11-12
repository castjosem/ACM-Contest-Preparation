#include <iostream>
#include <math.h>
using namespace std;

class Point {
	public:
	double x, y;
	
	Point(double x1=0, double y1=0)
	{
		x=x1;
		y=y1;
	}
	
	Point & operator=(const Point &p)
	
	{
		x=p.x;
		y=p.y;
	}

	Point operator+(const Point &p)
	{
		return Point(x+p.x, y+p.y);
	}
			
	Point operator-(const Point &p)
	{
		return Point(x-p.x, y-p.y);
	}
	
	Point operator*(double s)
	{
		return Point(x*s, y*s);
	}
};
typedef Point Vector;

// Linea
// p1 y p2 no pueden ser iguales
class Line
{	
	public:
	Point p1;
	Point p2;
	
	Line(Point p3 , Point p4)
	{
		p1 = p3;
		p2 = p4;
	} 
};
typedef Line Segment;

// producto punto
double dot(Vector &v1, Vector &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// producto cruz // no es un vector
double cross(Vector &v1, Vector &v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

//Distance from a Point to the Origin
double distancePoint(Point &p)
{
	return sqrt(pow(p.x, 2) + pow(p.y,2 ));
}

//Distance from a Point to a Point
double distancePointPoint(Point& p1, Point& p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

//Distance from a Point to a Line 
double distancePointLine(Point& p, Line& l)
{
    Vector v1 = p - l.p1, v2 = l.p2 - l.p1;
    return fabs(cross(v1, v2)) / distancePoint(v2);
}

//Distance from a Point to a Segment 
double distancePointSegment(Point& p, Segment& s)
{
    Vector p1p = p - s.p1, p1p2 = s.p2 - s.p1;
    Vector p2p = p - s.p2, p2p1 = s.p1 - s.p2;
 
    double d1 = dot(p1p, p1p2), d2 = dot(p2p, p2p1);
 
    if (d1 <= 0)    
//      return distance(p, p1);
        return distancePoint(p1p);
    else if (d2 <= 0)
//      return distance(p, p2);
        return distancePoint(p2p);
    else
		return distancePointLine(p, s);
}

double distanceSegmentLine(Segment& s, Line& l)
{
    Vector v = l.p2 - l.p1;
    Vector v1 = s.p1 - l.p1, v2 = s.p2 - l.p1;
    double c1 = cross(v, v1), c2 = cross(v, v2);
 
    if (c1 > 0 && c2 > 0 || c1 < 0 && c2 < 0)
        return min( distancePointLine(s.p1, l), distancePointLine(s.p2, l));
    else
        return 0.0;
}

// solamente devuelve true si los 2 segmentos no son paralelos y se intersectan
// no se sabe si se intersectan cuando los 2 segmentos son paralelos, por lo tanto siempre devuelve false
bool intersectSegmentSegment(Segment& s1, Segment& s2)
{
    Vector v1 = s2.p1 - s1.p1, v2 = s1.p2 - s2.p1;
    Vector v3 = s2.p2 - s1.p2, v4 = s1.p1 - s2.p2;
    
    double c1 = cross(v1, v2), c2 = cross(v2, v3);
    double c3 = cross(v3, v4), c4 = cross(v4, v1);
    
    return (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0)
        || (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0);
}
 
double distanceSegmentSegment(Segment& s1, Segment& s2)
{
    if (intersectSegmentSegment(s1, s2)) 
        return 0.0;
    else   
        return  min (distancePointSegment(s1.p1, s2),
				min (distancePointSegment(s1.p2, s2),
				min (distancePointSegment(s2.p1, s1),
                     distancePointSegment(s2.p2, s1))));
}


 
double distanceLineLine(Line& l1, Line& l2)
{
    Vector v1 = l1.p2 - l1.p1, v2 = l2.p2 - l2.p1;
 
    if (cross(v1, v2) == 0)
        return distancePointLine(l1.p1, l2); 
    else
        return 0.0;
}

Point INF(1e9, 1e9);
 
 /*
Point intersectionLineLine(Point& p1, Point& p2, Point& p3, Point& p4)
{
    Point p12 = p2 - p1, p13 = p3 - p1, p34 = p4 - p3;
    double c1 = cross(p12, p34), c2 = cross(p13, p34);
 
    if (c1 == 0)
        if (c2 == 0)
            return INF; // ????
        else
            return INF; // ????????
    else
        return p1 + (p12 * (c2 / c1));
}
*/

Point intersectionLineLine(Line &l1, Line &l2)
{
    Vector v12 = l1.p2 - l1.p1,
	       v13 = l2.p1 - l1.p1,
		   v34 = l2.p2 - l2.p1;
    double c1 = cross(v12, v34), c2 = cross(v13, v34);
 
    if (c1 == 0)
        if (c2 == 0)
            return INF; // solapar - una encima de la otra //infinitos puntos de interseccion
        else
            return INF; // paralelo
    else
        return l1.p1 + (v12 * (c2 / c1)); // Si hay interseccion
}

Point intersectionSegmentSegment(Segment &s1,Segment &s2)
{
    Vector v12 = s1.p2 - s1.p1,
	       v13 = s2.p1 - s1.p1,
		   v34 = s2.p2 - s2.p1;
    double c1 = cross(v12, v34), c2 = cross(v13, v34);
    Vector v31 = s1.p1 - s2.p1;
    double c3 = cross(v34, v12), c4 = cross(v31, v12);
 
    if (c1 < 0) c1 = -c1, c2 = -c2; // ???????,????
    if (c3 < 0) c3 = -c3, c4 = -c4;
 
    if (c1 == 0)
        if (c2 == 0)
            return INF; // 2 lineas en parelelo // no se sabe si se intersecta o no
        else
            return INF; // paralelo y no intersecta
    else
        if (c2 >= 0 && c2 <= c1 && c4 >= 0 && c4 <= c3)
            return s1.p1 + (v12 * (c2 / c1));
        else
            return INF; // no paralelo y no intersecta
}



	
int main()
{

	Point p(0,0), p1(3,0), p2(-3,4);
	
	Vector v1 = p1 - p, v2 = p2 - p;
	double l1 = distancePoint(v1), l2 = distancePoint(v2);
    cout << "cos(a):" << dot(v1, v2) / l1 / l2 <<endl;
    cout << "sin(a):" << cross(v1, v2) / l1 / l2 <<endl;
    cout << "a:" << acos(dot(v1, v2) / l1 / l2) <<endl; //en radian	// [0, pi]
    cout << "a:" << asin(cross(v1, v2) / l1 / l2) <<endl; //en radian	// [-pi/2, pi/2]
    cout << endl;
    
    Point punto(3,4);
    
    
    Segment segment1(Point(0,2),Point(1,1));
    Segment segment2(Point(0,0),Point(1,0));
    Line linea(Point(-500,0),Point(500,0));
    Line linea1(Point(300,1),Point(300,-1));
    
	
	cout << "LINEA:" <<distancePointSegment(punto, linea)<<endl;
	
	
	Point ppp=intersectionSegmentSegment(linea, linea1);
	cout << "LINEA:" <<ppp.x<<" "<<ppp.y<<endl;

	system("PAUSE");
	return 0;
}
