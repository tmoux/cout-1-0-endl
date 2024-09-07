//volumn of polyhedron, with face outwards
template<class V, class L>
double signed_poly_volume(const V& p, const L& trilist) {
	double v = 0;
	trav(i, trilist) v += p[i.a].cross(p[i.b]).dot(p[i.c]);
	return v / 6;
}