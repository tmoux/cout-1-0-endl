//The notations from here might be different
//Find the symmetric point of point p about line p1p2
Point SymPoint(Point p,Line l)
{
    Point result;
    double a=l.p2.x-l.p1.x;
    double b=l.p2.y-l.p1.y;
    double t=((p.x-l.p1.x)*a+(p.y-l.p1.y)*b)/(a*a+b*b);
    result.x=2*l.p1.x+2*a*t-p.x;
    result.y=2*l.p1.y+2*b*t-p.y;
    return result;
}
