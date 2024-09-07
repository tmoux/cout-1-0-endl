// This algorithm concerns efficient evaluation of sum of number theoric functions like phi or mu.
// We know that using Eulerian sieve, we can only archieve O(n) time complexity.
// What we are doing is to archieve O(n^{2/3}) time complexity.
// The example program shows how to evaluate sum of phi and sum of mu efficiently.
// For smaller n (n less than (N^{2/3}), we use calculate them as usual.
// For larger n, use getphi
// phi_cheat is a lookup table for getphi(n) that has been computed for "large" n
ll getphi(ll n)
{
  if (n <= m) return phi[n];
  if (phi_cheat.find(n) != phi_cheat.end()) return phi_cheat[n];
  ll ans = (ll)n*(n + 1) / 2; //this is \sum_{i = 1}^n \sum_{d | n} \phi(d)
  //when getting mu, ans = 1
  ll last;
  for (ll i = 2;i <= n;i = last + 1)
  {
    last = n / (n / i);
    ans -= (last-i+1)*getphi(n / i);
  }
  phi_cheat[n] = ans;
  return ans;
}
