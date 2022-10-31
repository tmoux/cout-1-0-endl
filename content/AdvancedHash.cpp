ll base1[MX], base2[MX];
int base;
ll b1Inv, b2Inv;

ll baseExp(ll power, ll prime) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = baseExp(power / 2, prime); cur = cur * cur; cur = cur % prime;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % prime;
            return cur;
        }
    }

struct hsh  {
    ll p1, p2;

    ll val1, val2;
    vl val1s, val2s;
    vl nums;


    hsh() {
        p1 = 1000000007;
        p2 = 1000000009;
        val1 = 0;
        val2 = 0;
        val1s.pb(0); val2s.pb(0);
    }


    hsh(string S) {
        p1 = 1000000007;
        p2 = 1000000009;
        val1 = 0;
        val2 = 0;

        val1s.pb(0); val2s.pb(0);
        F0R(i, sz(S)) {
            push_back(S[i] - 'a' + 1);
        }

    }

    void push_back(ll v) {
        v++;
        val1 *= base;
        val1 += v;
        val1 %= p1;
        val2 *= base;
        val2 += v;
        val2 %= p2;

		val1s.pb(val1);
		val2s.pb(val2);
        nums.pb(v);
    }

    void pop_back() {
        //warning: the extent to which this has been tested is limited lol
        ll v = nums[sz(nums)-1]; nums.pop_back();
        val1s.pop_back(); val2s.pop_back();
        val1 += p1 - v; val1 *= b1Inv;
        val1 %= p1;
        val2 += p2 - v; val2 *= b2Inv; val2 %= p2;
    }

    ll get(int L, int R) {
        ll A = (val1s[R+1] - (val1s[L] * base1[R-L+1]) % p1 + p1) % p1;
        ll B = (val2s[R+1] - (val2s[L] * base2[R-L+1]) % p2 + p2) % p2;
        return A * p2 + B;
    }
};

void prepHash() {
    base = uniform_int_distribution<int>(1000, MOD-2)(rng);

    base1[0] = 1; base2[0] = 1;
    b1Inv = baseExp(1000000005, 1000000007);
    b2Inv = baseExp(1000000007, 1000000009);
    FOR(i, 1, MX) {
        base1[i] = (base1[i-1] * base) % 1000000007; 
        base2[i] = (base2[i-1] * base) % 1000000009; 
    }
}
