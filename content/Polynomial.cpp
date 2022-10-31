constexpr int maxn = 262144;
constexpr int mod = 998244353;

using i64 = long long;
using poly_t = int[maxn];
using poly = int *const;

//Find f^{-1} mod x^n.
void polyinv(const poly &h, const int n, poly &f) {
  /* f = 1 / h = f_0 (2 - f_0 h) */
  static poly_t inv_t;
  std::fill(f, f + n + n, 0);
  f[0] = fpow(h[0], mod - 2);
  for (int t = 2; t <= n; t <<= 1) {
    const int t2 = t << 1;
    std::copy(h, h + t, inv_t);
    std::fill(inv_t + t, inv_t + t2, 0);

    DFT(f, t2);
    DFT(inv_t, t2);
    for (int i = 0; i != t2; ++i)
      f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
    IDFT(f, t2);

    std::fill(f + t, f + t2, 0);
  }
}

//Find h(x) such that h^2(x) = f(x) mod x^{deg}.
inline void sqrt(int deg, int *f, int *h) {
  if (deg == 1) {
    h[0] = 1;
    return;
  }
  sqrt(deg + 1 >> 1, f, h);
  int len = 1;
  while (len < deg * 2) {  // doubling
    len *= 2;
  }
  fill(g, g + len, 0);
  inv(deg, h, g);
  copy(f, f + deg, t);
  fill(t + deg, t + len, 0);
  NTT(t, len, 1);
  NTT(g, len, 1);
  NTT(h, len, 1);
  for (int i = 0; i < len; i++) {
    h[i] = (long long)1 * inv2 *
           ((long long)1 * h[i] % mod + (long long)1 * g[i] * t[i] % mod) % mod;
  }
  NTT(h, len, -1);
  fill(h + deg, h + len, 0);
}

/*This is Fast Walsh Transformation
Goal: Given A, B, compute C_i = \sum_{j ? k = i}A_jB_k
? is or, and, xor*/
void FWT(int *f,int pd){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=f[i+j],y=f[i+j+d];
                if(pd==0) f[i+j+d]=(x+y)%p; // or
                if(pd==1) f[i+j]=(x+y)%p; // and
                if(pd==2) f[i+j]=(x+y)%p,f[i+j+d]=(x-y+p)%p; //xor
            }
}
void IFWT(int *f,int pd){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=f[i+j],y=f[i+j+d];
                if(pd==0) f[i+j+d]=(y-x+p)%p; //OR
                if(pd==1) f[i+j]=(x-y+p)%p;; // AND
                if(pd==2) f[i+j]=1ll*(x+y)*inv%p,f[i+j+d]=1ll*(x-y+p)*inv%p; //XOR
            }
}

void solve_or()
{
    memcpy(a,A,sizeof a);
    memcpy(b,B,sizeof b);
    FWT(a,0);FWT(b,0);
    for(int i=0;i<n;i++)
        a[i]=1ll*a[i]*b[i]%p;
    IFWT(a,0);
}
