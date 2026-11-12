#pragma once
// debug.h -- shared CP debug-print helpers.
//
// #include "debug.h" at the top of any problem's .cpp. It compiles away to
// nothing UNLESS the LOCAL macro is defined at compile time -- run.py passes
// -DLOCAL automatically, so it's always active when you test locally, and
// always inactive on submission (no judge defines LOCAL, so there's no risk
// of debug output or freopen accidentally running on the real judge, even on
// judges that don't define ONLINE_JUDGE).
//
// Usage:
//   dbg(x);                 ->  [12] x = 5
//   dbg(a, b, c);            ->  [14] a = 5 | b = "hi" | c = 3.140000
//   dbg(v);                  where v is vector/set/map/pair/tuple/etc.
//                               -> pretty-printed recursively, nesting works
//                               (vector<vector<int>>, map<int,pair<int,int>>, ...)
//   dbg2d(grid);             -> prints a 2D container one row per line
//
// Covers everything typically needed up to ~CF 1600: primitives, pair,
// vector (incl. nested), array, native C-style arrays (incl. 2D, e.g.
// int grid[5][5]), set/multiset/unordered_set, map/multimap/unordered_map,
// deque, list, queue/stack/priority_queue, tuple.

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL

// ---- forward declarations so containers can nest inside one another ----
template<class T, class V> void _print(const pair<T, V>& p);
template<class T> void _print(const vector<T>& v);
template<class T, size_t N> void _print(const array<T, N>& v);
template<class T> void _print(const set<T>& v);
template<class T> void _print(const unordered_set<T>& v);
template<class T> void _print(const multiset<T>& v);
template<class K, class V> void _print(const map<K, V>& v);
template<class K, class V> void _print(const unordered_map<K, V>& v);
template<class K, class V> void _print(const multimap<K, V>& v);
template<class T> void _print(const deque<T>& v);
template<class T> void _print(const list<T>& v);
template<class T> void _print(queue<T> q);            // by value: drains a copy
template<class T> void _print(stack<T> s);             // by value: drains a copy
template<class T> void _print(priority_queue<T> pq);   // by value: drains a copy
template<class... Ts> void _print(const tuple<Ts...>& t);
template<class T, size_t N> void _print(const T (&arr)[N]);   // native C-style array
template<size_t N> void _print(const char (&s)[N]);           // char[N] -> printed as a string, not element-by-element

// ---- primitives ----
void _print(int x)                 { cerr << x; }
void _print(long x)                { cerr << x; }
void _print(long long x)           { cerr << x; }
void _print(unsigned x)            { cerr << x; }
void _print(unsigned long x)       { cerr << x; }
void _print(unsigned long long x)  { cerr << x; }
void _print(float x)               { cerr << x; }
void _print(double x)              { cerr << x; }
void _print(long double x)         { cerr << x; }
void _print(char x)                { cerr << '\'' << x << '\''; }
void _print(bool x)                { cerr << (x ? "true" : "false"); }
void _print(const string& x)       { cerr << '"' << x << '"'; }
void _print(const char* x)         { cerr << '"' << x << '"'; }

// ---- containers (defined after the forward decls above, so they can call
//      _print on each other -- e.g. vector<pair<int,int>> just works) ----
template<class T, class V> void _print(const pair<T, V>& p) {
    cerr << "("; _print(p.first); cerr << ", "; _print(p.second); cerr << ")";
}
template<class T> void _print(const vector<T>& v) {
    cerr << "[ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "]";
}
template<class T, size_t N> void _print(const array<T, N>& v) {
    cerr << "[ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "]";
}
template<class T> void _print(const set<T>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class T> void _print(const unordered_set<T>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class T> void _print(const multiset<T>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class K, class V> void _print(const map<K, V>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class K, class V> void _print(const unordered_map<K, V>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class K, class V> void _print(const multimap<K, V>& v) {
    cerr << "{ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "}";
}
template<class T> void _print(const deque<T>& v) {
    cerr << "[ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "]";
}
template<class T> void _print(const list<T>& v) {
    cerr << "[ "; for (const auto& x : v) { _print(x); cerr << " "; } cerr << "]";
}
template<class T> void _print(queue<T> q) {
    cerr << "[ "; while (!q.empty()) { _print(q.front()); cerr << " "; q.pop(); } cerr << "]";
}
template<class T> void _print(stack<T> s) {
    vector<T> tmp;
    while (!s.empty()) { tmp.push_back(s.top()); s.pop(); }
    reverse(tmp.begin(), tmp.end());
    _print(tmp);
}
template<class T> void _print(priority_queue<T> pq) {
    vector<T> tmp;
    while (!pq.empty()) { tmp.push_back(pq.top()); pq.pop(); }
    _print(tmp);
}
template<size_t I, class... Ts> void _print_tuple(const tuple<Ts...>& t) {
    if constexpr (I < sizeof...(Ts)) {
        if (I) cerr << ", ";
        _print(get<I>(t));
        _print_tuple<I + 1>(t);
    }
}
template<class... Ts> void _print(const tuple<Ts...>& t) {
    cerr << "("; _print_tuple<0>(t); cerr << ")";
}

// ---- native C-style arrays, e.g. int arr[5], double grid[3][4] ----
// Must take T(&)[N] (reference to array) rather than T* -- a plain pointer
// parameter would lose the size N entirely (arrays decay to pointers when
// passed by value), so N has to be deduced from a reference instead.
template<class T, size_t N> void _print(const T (&arr)[N]) {
    cerr << "[ "; for (const auto& x : arr) { _print(x); cerr << " "; } cerr << "]";
}
// More specialized than the generic template above, so overload resolution
// prefers this one for char arrays specifically -- prints as a normal
// quoted string ("hi") instead of a char-by-char list ([ 'h' 'i' ]).
template<size_t N> void _print(const char (&s)[N]) {
    cerr << '"' << s << '"';
}

// ---- variadic dbg(...): prints any number of vars, each with its name,
//      on one line, tagged with the source line number ----
template<class T, class... Rest>
void _debug_args(const string& names, const T& val, const Rest&... rest) {
    size_t comma = names.find(',');
    string first = (comma == string::npos) ? names : names.substr(0, comma);
    size_t l = first.find_first_not_of(' ');
    size_t r = first.find_last_not_of(' ');
    cerr << (l == string::npos ? first : first.substr(l, r - l + 1)) << " = ";
    _print(val);
    if constexpr (sizeof...(rest) > 0) {
        cerr << " | ";
        _debug_args(names.substr(comma + 1), rest...);
    } else {
        cerr << endl;
    }
}

#define dbg(...) do { cerr << "[" << __LINE__ << "] "; _debug_args(#__VA_ARGS__, __VA_ARGS__); } while (0)

// 2D pretty-printer -- one row per line, handy for grids / DP tables.
// Usage: dbg2d(grid);  or  dbg2d(grid, "grid");
template<class T> void dbg2d(const T& grid, const string& name = "") {
    if (!name.empty()) cerr << "[" << __LINE__ << "] " << name << ":\n";
    for (const auto& row : grid) { _print(row); cerr << "\n"; }
}

#else
#define dbg(...)
template<class T> void dbg2d(const T&, const string& = "") {}
#endif
