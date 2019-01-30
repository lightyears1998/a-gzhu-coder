// vvvvvvvvvvvvvvvvv Library code start


#define NDEBUG
NDEBUG


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <queue>
#include <random>


#define forn(t, i, n) for (t i = 0; i < (n); ++i)

#define rforn(t, i, n) for (t i = (n) - 1; i >= 0; --i)


using namespace std;

// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END


template <class T>
T gen_pow(T ret, T x, uint64_t pow) {
    while (pow) {
        if (pow & 1) {
            ret *= x;
        }
        pow /= 2;
        if (pow) {
            x *= x;
        }
    }
    return ret;
}


// Section with adoption of array and vector algorithms.


namespace template_util {
    

    constexpr int bytecount(uint64_t x) {
        return x ? 1 + bytecount(x >> 8) : 0;
    }

    template<int N>
    struct bytetype {
        
    };

    
    /// caide keep
    template<uint64_t N>
    struct minimal_uint : bytetype<bytecount(N)> {
    };
}


template<class T>
T next(istream& in) {
    T ret;
    in >> ret;
    return ret;
}

template<class T>
vector<T> next_vector(istream& in, size_t n) {
    vector<T> ret(n);
    for (size_t i = 0; i < n; ++i) {
        ret[i] = next<T>(in);
    }
    return ret;
}


template <class T>
inline T set_bit(T mask, int bit) {
    assert(0 <= bit && bit < numeric_limits<T>::digits);
    return mask | ((T)(1) << bit);
}


template <class T>
inline bool get_bit(T mask, int bit) {
    assert(0 <= bit && bit < numeric_limits<T>::digits);
    return mask & ((T)(1) << bit);
}


inline int bitcnt(unsigned int mask) {
    return __builtin_popcount(mask);
}


inline int bitcnt(unsigned long long mask) {
    return __builtin_popcountll(mask);
}


// ^^^^^^^^^^^^^^^^^ Library code end

void solve(istream& in, ostream& out) {
    int n = next<int>(in);
    vector<string> g0 = next_vector<string>(in, n);
    vector<uint64_t> comps;
    uint64_t col = 0;
    function<uint64_t(int)> dfs = [&](int i) -> uint64_t {
        if (get_bit(col, i)) {
            return 0;
        }
        col = set_bit(col, i);
        uint64_t ret = 1ULL << i;
        forn (int, j, n) {
            if (g0[i][j] == 'A' || g0[j][i] == 'A') {
                ret |= dfs(j);
            }
        }
        return ret;
    };
    forn (int, i, n) {
        uint64_t comp = dfs(i);
        if (bitcnt(comp) > 1) {
            comps.push_back(comp);
        }
    }
    vector<uint32_t> g(comps.size());
    forn (int, i, comps.size()) {
        uint64_t ns = 0;
        forn (int, u, n) {
            if (!get_bit(comps[i], u)) {
                continue;
            }
            forn (int, v, n) {
                if (g0[u][v] == 'X' || g0[v][u] == 'X') {
                    ns |= 1ULL << v;
                }
            }
        }
        forn (int, j, comps.size()) {
            if ((ns & comps[j]) != 0) {
                g[i] |= 1 << j;
            }
        }
        if (get_bit(g[i], i)) {
            out << "-1\n";
            return;
        }
    }
    vector<uint32_t> f(1 << comps.size());
    rforn (int, i, 1 << comps.size()) {
        forn (int, u, comps.size()) {
            if (get_bit(i, u) ? ((g[u] & i) != 0) : f[set_bit(i, u)]) {
                goto cont;
            }
        }
        f[i] = 1;
        cont:;
    }
    forn (int, u, comps.size()) {
        forn (int, i, 1 << comps.size()) {
            if (get_bit(i, u)) {
                f[i] += f[i ^ (1 << u)];
            }
        }
    }
    vector<uint64_t> counts(comps.size() + 1);
    forn (uint32_t, i, 1 << comps.size()) {
        uint64_t pow = bitcnt(i) % 2 ? -1ULL : 1ULL;
        uint64_t val = f[i];
        forn (int, k, comps.size() + 1) {
            counts[k] += pow;
            pow *= val;
        }
    }
    int k = 0;
    while (counts[k] == 0) {
        k++;
    }
    out << n - 1 + k << "\n";
}


int main() {
    solve(cin, cout);
    return 0;
}
