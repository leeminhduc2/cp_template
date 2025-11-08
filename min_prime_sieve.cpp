struct min_prime_sieve
{
    vector <int> minPrime;
    int n;
    min_prime_sieve(int n): n(n){
        minPrime.resize(n+1,0);
        
        for( int i=2;i<=n;++i)
            if (minPrime[i] == 0) {
                minPrime[i] = i;
                for (long long j=1ll*i*i;j<=n;j+=i) if (minPrime[j] == 0) minPrime[j] = i;
            }
    }
    bool is_prime(int i) {
        assert(i <= n);
        return (minPrime[i] == i);
    }
    int min_prime(int i) {
        assert(i <=n);
        return minPrime[i];
    }
};