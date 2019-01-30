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
#define foran(t, i, a, n) for (t i = (a); i < (n); ++i)
#define rforn(t, i, n) for (t i = (n) - 1; i >= 0; --i)


using namespace std;

// TC_REMOVE_BEGIN
/// caide keep
bool __hack = std::ios::sync_with_stdio(false);
/// caide keep
auto __hack1 = cin.tie(nullptr);
// TC_REMOVE_END


// Section with adoption of array and vector algorithms.


namespace option_detail {
    /// caide keep
    struct NoneHelper {};
}


template<class Value>
class Option {
public:
    

    static_assert(!std::is_reference<Value>::value,
                  "Option may not be used with reference types");
    static_assert(!std::is_abstract<Value>::value,
                  "Option may not be used with abstract types");

    
    Value* get_pointer() && = delete;

    
    // Return b copy of the value if set, or b given default if not.
    

    // Return b copy of the value if set, or b given default if not.
    

private:
    

    struct StorageTriviallyDestructible {
        // uninitialized
        
        bool hasValue;

        
    };

    /// caide keep
    struct StorageNonTriviallyDestructible {
        // uninitialized
        union { Value value; };
        bool hasValue;

        
        ~StorageNonTriviallyDestructible() {
            clear();
        }

        void clear() {
            if (hasValue) {
                hasValue = false;
                value.~Value();
            }
        }
    };

    /// caide keep
    using Storage =
    typename std::conditional<std::is_trivially_destructible<Value>::value,
            StorageTriviallyDestructible,
            StorageNonTriviallyDestructible>::type;

    Storage storage_;
};


// Comparisons.


template<class V> bool operator< (const Option<V>&, const V& other) = delete;
template<class V> bool operator<=(const Option<V>&, const V& other) = delete;
template<class V> bool operator>=(const Option<V>&, const V& other) = delete;
template<class V> bool operator> (const Option<V>&, const V& other) = delete;
template<class V> bool operator< (const V& other, const Option<V>&) = delete;
template<class V> bool operator<=(const V& other, const Option<V>&) = delete;
template<class V> bool operator>=(const V& other, const Option<V>&) = delete;
template<class V> bool operator> (const V& other, const Option<V>&) = delete;


#define ENABLE_IF(e) typename enable_if<e>::type* = nullptr

namespace template_util {
    

    constexpr int bytecount(uint64_t x) {
        return x ? 1 + bytecount(x >> 8) : 0;
    }

    template<int N>
    struct bytetype {
        typedef uint64_t type;
    };

    template<>
    struct bytetype<4> {
        typedef uint32_t type;
    };

    
    template<>
    struct bytetype<1> {
        typedef uint8_t type;
    };

    template<>
    struct bytetype<0> {
        typedef uint8_t type;
    };

    /// caide keep
    template<uint64_t N>
    struct minimal_uint : bytetype<bytecount(N)> {
    };
}


namespace index_iterator_impl {
    template <class T>
    struct member_dispatch_helper {
        

    private:
        T value;
    };

    // Have to caide keep all the members to comply to iterator concept
    // Otherwise generated code won't be portable between clang and g++
    template <class C, bool reverse = false>
    struct index_iterator {
        /// caide keep
        typedef random_access_iterator_tag iterator_category;
        /// caide keep
        typedef decltype(((C*)nullptr)->operator[](size_t(0))) reference;
        /// caide keep
        typedef typename remove_reference<reference>::type value_type;
        /// caide keep
        typedef ptrdiff_t difference_type;
        /// caide keep
        typedef conditional<
                is_reference<reference>::value,
                typename add_pointer<value_type>::type,
                member_dispatch_helper<value_type>> pointer;

        /// caide keep
        typedef index_iterator<C, reverse> self_t;

        /// caide keep
        static const difference_type dir = reverse ? -1 : 1;

        /// caide keep
        index_iterator() = default;

        
        /// caide keep
        inline bool operator!=(const self_t& o) { return index != o.index; }
        /// caide keep
        inline bool operator<(const self_t& o) { return reverse ? index > o.index : index < o.index; }
        /// caide keep
        inline bool operator>(const self_t& o) { return reverse ? index < o.index : index > o.index; }
        /// caide keep
        inline bool operator<=(const self_t& o) { return reverse ? index >= o.index : index <= o.index; }
        /// caide keep
        inline bool operator>=(const self_t& o) { return reverse ? index <= o.index : index >= o.index; }

        /// caide keep
        inline reference operator*() { return (*container)[index]; }
        /// caide keep
        inline const reference operator*() const { return (*container)[index]; }
        /// caide keep
        inline pointer operator->() { return pointer((*container)[index]); }

        /// caide keep
        inline self_t& operator++() { index += dir; return *this; }
        /// caide keep
        inline self_t operator++(int) { auto copy = *this; index += dir; return copy; }
        /// caide keep
        inline self_t& operator--() { index -= dir; return *this; }
        /// caide keep
        inline self_t operator--(int) { auto copy = *this; index -= dir; return copy; }

        /// caide keep
        inline self_t& operator+=(difference_type n) { index += dir * n; return *this; };
        /// caide keep
        inline self_t& operator-=(difference_type n) { index -= dir * n; return *this; };
        /// caide keep
        inline friend self_t operator-(self_t a, difference_type n) { return a -= n; };
        /// caide keep
        inline friend self_t operator+(difference_type n, self_t a) { return a += n; };
        /// caide keep
        inline friend self_t operator+(self_t a, difference_type n) { return a += n; };
        /// caide keep
        inline friend difference_type operator-(const self_t& a, const self_t& b) { return dir * (a.index - b.index); };

        /// caide keep
        inline reference operator[](difference_type n) { return (*container)[index + dir * n]; };
        /// caide keep
        inline const reference operator[](difference_type n) const { return (*container)[index + dir * n]; };

    private:
        C* container;
        difference_type index;
    };
}


namespace multivec_impl {
    template <size_t NDIMS>
    struct shape {
        size_t dim, stride;
        shape<NDIMS - 1> subshape;
        
        shape(size_t dim_, shape<NDIMS - 1>&& s): dim(dim_), stride(s.size()), subshape(std::move(s)) {}
        size_t size() const { return dim * stride; }
        
        
    };
    template <> struct shape<0> { size_t size() const { return 1; } };
    

    template <size_t I, size_t NDIMS>
    struct __shape_traverse {
        

        ///caide keep
        static const shape<NDIMS - I>& get_subshape(const shape<NDIMS>& s) {
            return __shape_traverse<I - 1, NDIMS - 1>::get_subshape(s.subshape);
        }
    };

    template <size_t NDIMS>
    struct __shape_traverse<0, NDIMS> {
        
        static const shape<NDIMS>& get_subshape(const shape<NDIMS>& s) { return s; }
    };

    
    ///caide keep
    template <size_t I, size_t NDIMS>
    const shape<NDIMS - I>& get_subshape(const shape<NDIMS>& s) { return __shape_traverse<I, NDIMS>::get_subshape(s); }

    
    template <class Index, class... Rest, size_t NDIMS, ENABLE_IF(is_integral<Index>::value)>
    size_t get_shift(const shape<NDIMS>& s, size_t cur_shift, Index i, Rest... is) {
        assert(0 <= i && i < s.dim);
        return get_shift(s.subshape, cur_shift + i * s.stride, is...);
    }

    template <size_t NDIMS> size_t get_shift(const shape<NDIMS>&, size_t cur_shift) { return cur_shift; }

    
    template <class... T> shape<sizeof...(T)> make_shape(T... dims);

    template <class Dim, class... Rest, ENABLE_IF(is_integral<Dim>::value)>
    shape<sizeof...(Rest) + 1> make_shape(Dim dim, Rest... dims) {
        assert(dim >= 0);
        return {(size_t)dim, make_shape<Rest...>(dims...)};
    }

    template <> shape<0> make_shape() { return {}; }

    
    ///caide keep
    template <class T, size_t NDIMS>
    struct vec_view_base;

    template <template<class, size_t> class Base, class T, size_t NDIMS>
    struct vec_mixin : public Base<T, NDIMS> {
        using Base<T, NDIMS>::Base;
        /// caide keep
        typedef Base<T, NDIMS> B;
        
        
        ///caide keep
        template <class... Indices, bool enabled = NDIMS == sizeof...(Indices), ENABLE_IF(enabled)>
        inline T& operator()(Indices... is) {
            size_t i = multivec_impl::get_shift(B::s, 0, is...);
            return B::data[i];
        }

        ///caide keep
        template <class... Indices, bool enabled = sizeof...(Indices) < NDIMS, ENABLE_IF(enabled)>
        inline vec_mixin<vec_view_base, T, NDIMS - sizeof...(Indices)> operator()(Indices... is) {
            size_t shift = multivec_impl::get_shift(B::s, 0, is...);
            const auto& subshape = multivec_impl::get_subshape<sizeof...(Indices)>(B::s);
            return {subshape, &B::data[shift]};
        }

        
        inline void fill(const T& val) {
            std::fill(raw_data(), raw_data() + B::s.size(), val);
        };

        
//    protected:
        inline T* raw_data() {
            return &B::data[0];
        }

        
    };

    template <class T, size_t NDIMS>
    struct vec_view_base {
        inline vec_view_base(const multivec_impl::shape<NDIMS>& s_, T* data_): s(s_), data(data_) {}
        
    protected:
        multivec_impl::shape<NDIMS> s;
        T* data;
    };

    template <class T, size_t NDIMS>
    struct vec_base {
        inline vec_base(multivec_impl::shape<NDIMS>&& s_): s(move(s_)), data(new T[s.size()]) {}
        
        
        inline vec_base(const vec_base& o): s(o.s), data(new T[s.size()]) {
            memcpy(data.get(), o.data.get(), sizeof(T) * s.size());
        }
        
    protected:
        multivec_impl::shape<NDIMS> s;
        unique_ptr<T[]> data;
    };
}

/*
TODO
 - do we need vec_view_const?
 - add more features (lambda initialization etc.)
 - properly use const
 - proper tests coverage
*/

template <class T, size_t NDIMS>
using vec = multivec_impl::vec_mixin<multivec_impl::vec_base, T, NDIMS>;


template <class T, class... NDIMS>
inline vec<T, sizeof...(NDIMS)> make_vec(NDIMS... dims) {
    return {multivec_impl::make_shape(dims...)};
}


/*
TODOs:
 primitive root
 discrete log

 tests!!!
*/

namespace mod_impl {
    /// caide keep
    template <class T>
    constexpr inline T mod(T MOD) {
        return MOD;
    }

    /// caide keep
    template <class T>
    constexpr inline T mod(T* MOD) {
        return *MOD;
    }

    /// caide keep
    template <class T>
    constexpr inline T max_mod(T MOD) {
        return MOD - 1;
    }

    /// caide keep
    template <class T>
    constexpr inline T max_mod(T*) {
        return numeric_limits<T>::max() - 1;
    }

    
    constexpr inline uint64_t combine_max_sum(uint64_t a, uint64_t b) {
        return a > ~b ? 0 : a + b;
    }

    constexpr inline uint64_t combine_max_mul(uint64_t a, uint64_t b) {
        return a > numeric_limits<uint64_t>::max() / b ? 0 : a * b;
    }

    /// caide keep
    template <class T>
    constexpr inline uint64_t next_divisible(T mod, uint64_t max) {
        return max % mod == 0 ? max : combine_max_sum(max, mod - max % mod);
    }

    /// caide keep
    template <class T>
    constexpr inline uint64_t next_divisible(T*, uint64_t) {
        return 0;
    }

    //caide keep
    constexpr int IF_THRESHOLD = 2;

    template <class T, T MOD_VALUE, uint64_t MAX,
            class RET = typename template_util::minimal_uint<max_mod(MOD_VALUE)>::type,
            ENABLE_IF(MAX <= max_mod(MOD_VALUE) && !is_pointer<T>::value)>
    inline RET smart_mod(typename template_util::minimal_uint<MAX>::type value) {
        return value;
    }

    template <class T, T MOD_VALUE, uint64_t MAX,
            class RET = typename template_util::minimal_uint<max_mod(MOD_VALUE)>::type,
            ENABLE_IF(max_mod(MOD_VALUE) < MAX && MAX <= IF_THRESHOLD * max_mod(MOD_VALUE) && !is_pointer<T>::value)>
    inline RET smart_mod(typename template_util::minimal_uint<MAX>::type value) {
        while (value >= mod(MOD_VALUE)) {
            value -= mod(MOD_VALUE);
        }
        return (RET)value;
    }

    template <class T, T MOD_VALUE, uint64_t MAX,
             class RET = typename template_util::minimal_uint<max_mod(MOD_VALUE)>::type,
             ENABLE_IF(IF_THRESHOLD * max_mod(MOD_VALUE) < MAX || is_pointer<T>::value)>
    inline RET smart_mod(typename template_util::minimal_uint<MAX>::type value) {
        return (RET)(value % mod(MOD_VALUE));
    }
}


#define MAX_MOD mod_impl::max_mod(MOD_VALUE)

struct DenormTag {};

template <class T, T MOD_VALUE, uint64_t MAX = MAX_MOD, ENABLE_IF(MAX_MOD >= 2)>
struct ModVal {
    typedef typename template_util::minimal_uint<MAX>::type storage;
    storage value;

    /// caide keep
    inline ModVal(): value(0) {
        assert(MOD >= 2);
    }

    
    inline ModVal(storage v, DenormTag): value(v) {
        assert(MOD >= 2);
        assert(v <= MAX);
    };

    inline operator ModVal<T, MOD_VALUE>() {
        return {v(), DenormTag()};
    };

    
    typename template_util::minimal_uint<mod_impl::max_mod(MOD_VALUE)>::type v() const {
        return mod_impl::smart_mod<T, MOD_VALUE, MAX>(value);
    }
};


template <class T, T MOD_VALUE, uint64_t MAX1, uint64_t MAX2,
        uint64_t NEW_MAX = mod_impl::combine_max_sum(MAX1, MAX2),
        ENABLE_IF(NEW_MAX != 0), class Ret = ModVal<T, MOD_VALUE, NEW_MAX>>
inline Ret operator+(ModVal<T, MOD_VALUE, MAX1> o1, ModVal<T, MOD_VALUE, MAX2> o2) {
    return {typename Ret::storage(typename Ret::storage() + o1.value + o2.value), DenormTag()};
}


template <class T, T MOD_VALUE, uint64_t MAX1, uint64_t MAX2,
        uint64_t NEW_MAX = mod_impl::combine_max_mul(MAX1, MAX2),
        ENABLE_IF(NEW_MAX != 0), class Ret = ModVal<T, MOD_VALUE, NEW_MAX>>
inline Ret operator*(ModVal<T, MOD_VALUE, MAX1> o1, ModVal<T, MOD_VALUE, MAX2> o2) {
    return {typename Ret::storage(typename Ret::storage(1) * o1.value * o2.value), DenormTag()};
}


template <class T, T MOD_VALUE, uint64_t MAX>
inline ModVal<T, MOD_VALUE>& operator+=(ModVal<T, MOD_VALUE>& lhs, const ModVal<T, MOD_VALUE, MAX>& rhs) {
    lhs = lhs + rhs;
    return lhs;
}


template <class T, T MOD_VALUE, uint64_t MAX>
inline ModVal<T, MOD_VALUE>& operator*=(ModVal<T, MOD_VALUE>& lhs, const ModVal<T, MOD_VALUE, MAX>& rhs) {
    lhs = lhs * rhs;
    return lhs;
}


template <class T, T MOD_VALUE, class MOD_TYPE>
struct ModCompanion {
    typedef MOD_TYPE mod_type;
    typedef ModVal<mod_type, MOD_VALUE> type;
    

    template <uint64_t C>
    inline static constexpr ModVal<mod_type, MOD_VALUE, C> c() {
        return {C, DenormTag()};
    };

    template <uint64_t MAX = numeric_limits<uint64_t>::max()>
    inline static ModVal<mod_type, MOD_VALUE, MAX> wrap(uint64_t x) {
        assert(x <= MAX);
        return {typename ModVal<mod_type, MOD_VALUE, MAX>::storage(x), DenormTag()};
    };

    
};


#undef MAX_MOD

template <uint64_t MOD_VALUE>
struct Mod : ModCompanion<uint64_t, MOD_VALUE, typename template_util::minimal_uint<MOD_VALUE>::type> {
    template<uint64_t VAL>
    static constexpr uint64_t literal_builder() {
        return VAL;
    }

    template<uint64_t VAL, char DIGIT, char... REST>
    static constexpr uint64_t literal_builder() {
        return literal_builder<(10 * VAL + DIGIT - '0') % MOD_VALUE, REST...>();
    }
};


#define REGISTER_MOD_LITERAL(mod, suffix) \
template <char... DIGITS> mod::type operator "" _##suffix() { \
    return mod::c<mod::literal_builder<0, DIGITS...>()>(); \
}


template <class T, T MOD_VALUE, uint64_t MAX>
inline ostream& operator<<(ostream& s, ModVal<T, MOD_VALUE, MAX> val) {
    s << val.v();
    return s;
}


template<class T>
T next(istream& in) {
    T ret;
    in >> ret;
    return ret;
}


#define dbg(...) ;


// ^^^^^^^^^^^^^^^^^ Library code end

using md = Mod<1000000007>;
/// caide keep
using mt = md::type;
REGISTER_MOD_LITERAL(md, mod)

constexpr int MAX_LEN = 700;

auto precalc = []() {
    auto precalc = make_vec<mt>(MAX_LEN, MAX_LEN, 10);
    precalc(0, 0).fill(1_mod);
    foran (int, len, 1, MAX_LEN) {
        forn (int, cnt, len + 1) {
            forn (int, d, 10) {
                precalc(len, cnt, d) = md::wrap<10>(d) * precalc(len - 1, cnt, d);
                if (cnt > 0) {
                    precalc(len, cnt, d) += md::wrap<10>(10 - d) * precalc(len - 1, cnt - 1, d);
                }
            }
        }
    }
    return precalc;
}();

void solve(istream& in, ostream& out) {
    auto x = next<string>(in);
    int n = x.size();
    auto din = make_vec<mt>(n + 1, 10);
    din.fill(0_mod);
    auto prefixCounts = make_vec<int>(10);
    prefixCounts.fill(0);
    forn (int, i, n) {
        dbg(prefixCounts);
        int restLen = n - i - 1;
        forn (int, d, x[i] - '0' + (i == n - 1 ? 1 : 0)) {
            dbg(i, d);
            forn (int, c, 10) {
                forn (int, cnt, restLen + 1) {
                    din(cnt + prefixCounts(c) + (d >= c ? 1 : 0), c) += precalc(restLen, cnt, c);
                }
            }
        }
        forn (int, d, x[i] - '0' + 1) {
            prefixCounts(d)++;
        }
    }
    forn (int, c, 10) {
        rforn (int, i, n) {
            din(i, c) += din(i + 1, c);
        }
    }
    auto ans = 0_mod;
    auto pow10 = 1_mod;
    foran (int, i, 1, n + 1) {
        auto sum = 0_mod;
        foran (int, c, 1, 10) {
            sum += din(i, c);
        }
        ans += sum * pow10;
        pow10 *= 10_mod;
    }
    out << ans << "\n";
}


int main() {
    solve(cin, cout);
    return 0;
}
