const ll MOD = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll modExp(ll a, ll b) {
  ll res = 1;
  for (; b; a = (a * a) % MOD, b >>= 1)
    if (b & 1) res = (res * a) % MOD;
  return res;
}
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modExp(root, MOD >> s)};
		FOR(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
	}
	vi rev(n);
	FOR(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	FOR(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) F0R(j,k) {
			ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? MOD: 0);
			ai += (ai + z >= MOD ? z - MOD : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = modExp(n, MOD - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	F0R(i,n) out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
