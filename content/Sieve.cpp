vi primes, leastFac;
void compPrimes(int N) {
  leastFac.resize(N, 0);
  leastFac[0] = 1; leastFac[1] = 1;
  FOR(i, 2, N) {
    if (leastFac[i] == 0) {
      primes.pb(i);
      leastFac[i] = i;
    }
    for (int j = 0; j < sz(primes) && i*primes[j] < N && primes[j] <= leastFac[i]; j++) {
      leastFac[i*primes[j]] = primes[j];
    }
  }
}
