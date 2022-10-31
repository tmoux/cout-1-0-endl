/*Class1 : Interval DP: f_{l,r} = min_{k=l}^{r-1} f_{l,k}+f_{k+1,r} + w(l,r)
weights w(l,r) satisfying the following inequality:
(1) For any l <= l' <= r' <= r, we have w(l',r') <= w(l,r).
(2) (The important one): For any l1 <= l2 <= r1 <= r2, we have
w(l1,r1) + w(l2,r2) <= w(l1,r2) + w(l2,r1).
*/

for (int len = 2; len <= n; ++len)  // Enumerate Interval Length
  for (int l = 1, r = len; r <= n; ++l, ++r) {
    // Enumerate Intervals of Length Len
    f[l][r] = INF;
    for (int k = m[l][r - 1]; k <= m[l + 1][r]; ++k)
      if (f[l][r] > f[l][k] + f[k + 1][r] + w(l, r)) {
        f[l][r] = f[l][k] + f[k + 1][r] + w(l, r);  //Update DP
        m[l][r] = k;  // Update Decision Point
      }
  }

/*Class2: 2D DP, f_{i,j} = min_{k <= j}{f_{i-1,k}} + w(k,j)
Where 1 <= i <= n, 1 <= j <= m
*/
int n;
long long C(int i, int j);
vector<long long> dp_before(n), dp_cur(n);
// compute dp_cur[l], ... dp_cur[r] (inclusive)
//Call compute for each possible i.
void compute(int l, int r, int optl, int optr) {
  if (l > r) return;
  int mid = (l + r) >> 1;
  pair<long long, int> best = {INF, -1};
  for (int k = optl; k <= min(mid, optr); k++) {
    best = min(best, {dp_before[k] + C(k, mid), k});
  }
  dp_cur[mid] = best.first;
  int opt = best.second;
  compute(l, mid - 1, optl, opt);
  compute(mid + 1, r, opt, optr);
}
