/**
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
	 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
	 * The input vector is set to an optimal $x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
	 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
	 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
	 * vd b = {1,1,-4}, c = {-1,-1}, x;
	 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM \cdot \#pivots), where a pivot may be e.g. an edge relaxation. O(2^N) in the general case.
 * Source: KACTL, Stanford
	* https://cs.stanford.edu/group/acm/SLPC/notebook.pdf
	* https://www.utdallas.edu/~scniu/OPRE-6201/documents/LP06-Simplex-Tableau.pdf (good example)
	* http://www.columbia.edu/~cs2035/courses/ieor3608.F05/bigm1.pdf
  * verification: https://open.kattis.com/contests/ecna19open/problems/cheeseifyouplease
 * ICPC WF16I, solves 200 systems of size up to 100 in 450ms
 */

typedef vector<vd> vvd;
const ld eps = 1e-8, inf = 1/.0;

#define ltj(X) if (s == -1 || make_pair(X[j],N[j]) < make_pair(X[s],N[s])) s=j

struct LPSolver {
	int m, n; // # contraints, # variables
	vi N, B;
	vvd D;
	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			F0R(i,m) F0R(j,n) D[i][j] = A[i][j]; 
			F0R(i,m) { 
				B[i] = n+i, D[i][n] = -1, D[i][n+1] = b[i]; 
				// B[i]: add basic variable for each constraint, convert ineqs to eqs
				// D[i][n]: artificial variable for testing feasibility
			}
			F0R(j,n) { 
				N[j] = j; // non-basic variables, all zero
				D[m][j] = -c[j]; // minimize -c^T x
			} 
			N[n] = -1; D[m+1][n] = 1; 
		}

	void pivot(int r, int s) { // r = row, c = column
		ld *a = D[r].data(), inv = 1/a[s]; 
		F0R(i,m+2) if (i != r && abs(D[i][s]) > eps) {
			ld *b = D[i].data(), binv = b[s]*inv;
			F0R(j,n+2) b[j] -= a[j]*binv; // make column corresponding to s all zeroes
			b[s] = a[s]*binv; // swap N[s] with B[r]
		}
		// equation corresponding to r scaled so x_r coefficient equals 1
		F0R(j,n+2) if (j != s) D[r][j] *= inv; 
		F0R(i,m+2) if (i != r) D[i][s] *= -inv; 
		D[r][s] = inv; swap(B[r], N[s]); // swap basic w/ non-basic
	}
	bool simplex(int phase) {
		int x = m+phase-1;
		while (1) {
			int s = -1; F0R(j,n+1) if (N[j] != -phase) ltj(D[x]); // find most negative col for nonbasic variable
			if (D[x][s] >= -eps) return true; // can't get better sol by increasing non-basic variable, terminate
			int r = -1;
			F0R(i,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || mp(D[i][n+1] / D[i][s], B[i])
							 < mp(D[r][n+1] / D[r][s], B[r])) r = i; 
				// find smallest positive ratio, aka max we can increase nonbasic variable
			}
			if (r == -1) return false; // increase N[s] infinitely -> unbounded
			pivot(r,s);
		}
	}

	ld solve(vd &x) {
		int r = 0; FOR(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) { // x=0 not feasible, run simplex to find smth feasible 
			pivot(r, n); // N[n] = -1 is artificial variable, initially set to smth large
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf; 
			// D[m+1][n+1] is max possible value of the negation of 
			// artificial variable, optimal value should be zero 
			// if exists feasible solution
			F0R(i,m) if (B[i] == -1) { // ?
				int s = 0; FOR(j,1,n+1) ltj(D[i]);
				pivot(i,s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		F0R(i,m) if (B[i] < n) x[B[i]] = D[i][n+1]; 
		return ok ? D[m][n+1] : inf;
	}
};
