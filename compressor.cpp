template<class T>
void compress(vector<T> &a) {
    vector<T> tmp = a;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()),tmp.end());
    int cnt = 0;
    for (int i=0;i<(int) a.size(); i++) {
        a[i] = lower_bound(tmp.begin(),tmp.end(),a[i]) - tmp.begin();
    }
}