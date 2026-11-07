namespace FFT
{

    using cd = complex<long double>;

    void fft(vector<cd> &a, bool invert)
    {
        /// invert = true tương ứng với biến đổi ngược
        int n = a.size();
        if (n == 1)
            return;
        vector<cd> a0, a1;
        for (int i = 0; i < n / 2; i++)
        {
            a0.push_back(a[2 * i]);
            a1.push_back(a[2 * i + 1]);
        }
        fft(a0, invert);
        fft(a1, invert);
        cd w = 1, wn = polar(1.0L, acos(-1.0L) / n * (invert ? -2 : 2));
        /// polar(r, t) = r * exp(it) và acos(-1.0L) = pi
        /// thay wn = wn^-1 ở biến đổi ngược
        for (int i = 0; i < n / 2; i++)
        {
            a[i] = a0[i] + w * a1[i];
            a[i + n / 2] = a0[i] - w * a1[i];
            /// Ta sẽ chia 2 ở mỗi tầng đệ quy thay cho việc chia n ở cuối
            if (invert)
            {
                a[i] /= 2;
                a[i + n / 2] /= 2;
            }
            w *= wn;
        }
    }

    vector<int> conv(const vector<int> &a, const vector<int> &b)
    {
        if (a.empty() || b.empty())
            return {};
        int n = 1;
        while (n < int(a.size() + b.size()) - 1)
            n <<= 1;
        vector<cd> in(n), out(n);
        for (int i = 0; i < int(a.size()); i++)
            in[i].real(a[i]);
        for (int i = 0; i < int(b.size()); i++)
            in[i].imag(b[i]);
        fft(in, false);
        for (int i = 0; i < n; i++)
            in[i] *= in[i];
        for (int i = 0; i < n; i++)
        {
            /// (n - i) mod n
            int j = -i & (n - 1);
            out[i] = in[i] - conj(in[j]);
        }
        fft(out, true);
        vector<int> res(n);
        /// ở trên ta không chia cho 4i nên kết quả sẽ nằm trong phần ảo
        for (int i = 0; i < n; i++)
            res[i] = int(imag(out[i]) / 4 + 0.5);
        return res;
    }

    using ll = long long;

    vector<int> convMod(const vector<int> &a, const vector<int> &b, int M)
    {
        if (a.empty() || b.empty())
            return {};
        vector<int> res(a.size() + b.size() - 1);
        int B = 32 - __builtin_clz(res.size());
        int n = 1 << B, cut = sqrt(M);

        vector<cd> L(n), R(n), outs(n), outl(n);

        for (int i = 0; i < int(a.size()); i++)
            L[i] = cd(a[i] / cut, a[i] % cut);
        for (int i = 0; i < int(b.size()); i++)
            R[i] = cd(b[i] / cut, b[i] % cut);
        fft(L, false);
        fft(R, false);

        for (int i = 0; i < n; i++)
        {
            /// j = (n - i) % n
            int j = -i & (n - 1);
            outl[i] = (L[i] + conj(L[j])) * R[i] / 2.0l;
            outs[i] = (L[i] - conj(L[j])) * R[i] / 2il;
        }
        fft(outl, true), fft(outs, true);

        for (int i = 0; i < int(res.size()); i++)
        {
            ll av = ll(real(outl[i]) + 0.5);
            ll cv = ll(imag(outs[i]) + 0.5);
            ll bv = ll(imag(outl[i]) + 0.5) + ll(real(outs[i]) + 0.5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
}
