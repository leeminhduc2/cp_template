// 1-indexed hash table
struct hashTable {
private:
    static constexpr int MOD = 1e9+ 7;
    static constexpr int BASE = 311;
public:
    int n;
    vector <int> h,pwr;
    hashTable(string s) {
        int n = s.size();
        h.resize(n+1,0);
        pwr.resize(n+1,1);
        for (int i = 1;i <=n;i++) {
            pwr[i] = (1ll * pwr[i-1] * BASE) % MOD;
            h[i] = (1ll * h[i-1] * BASE + s[i-1]) % MOD;
        }
    }
    int query(int l,int r) {
        return (h[r] - (int) ((1ll * h[l-1] * pwr[r-l+1]) % MOD) + MOD) % MOD;  
    }
};