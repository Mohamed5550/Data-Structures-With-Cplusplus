#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int size = 1;
    vector <int> mins;

    void init(int n) {
        while(size < n) size *= 2;

        mins.assign(size*2, 0);
    }

    void set(int i , int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            mins[x] = v;
            return;
        }

        int m = (rx+lx)/2;
        if(i < m) {
            set(i, v, 2*x+1, lx, m);
        } else {
            set(i, v, 2*x+2, m, rx);
        }

        mins[x] = min(mins[2*x+1], mins[2*x+2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if(rx <= l || lx >= r) return 1e9;
        if(lx >= l && rx <= r) return mins[x];

        int m = (lx+rx)/2;
        int m1 = calc(l, r, 2*x+1, lx, m);
        int m2 = calc(l, r, 2*x+2, m, rx);

        return min(m1,m2);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    segtree st;
    st.init(n);

    for (int i = 0; i < n; i ++) {
        int v;
        cin >> v;
        st.set(i, v);
    }

    while(m --) {
        int op;
        cin >> op;

        if(op == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.calc(l, r) << "\n";
        }
    }
}