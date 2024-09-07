//* Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
