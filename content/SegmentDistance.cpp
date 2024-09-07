// Point-Segment Distance
// Returns the shortest distance between point p and the line segment from point s to e.
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

// Segment-Segment distance
double TwoSegMinDist(P A,P B,P C,P D)
{
    return min(min(segDist(A,B,C),segDist(A,B,D)),
               min(segDist(C,D,A),segDist(C,D,B)));
}
