struct eratosthenes_sieve
{
    vector <bool> isprime;
    int n;
    eratosthenes_sieve(int n): n(n){
        isprime.resize(n+1,1);
        isprime[0]=isprime[1]=0;
        for( int i=2;i*i<=n;++i)
            if (isprime[i])
                for (int j=i*i;j<=n;j+=i) isprime[j]=0;
    }
};