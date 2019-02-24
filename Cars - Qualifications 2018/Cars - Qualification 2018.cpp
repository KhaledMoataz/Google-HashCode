////////////includes/////////////////
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <cstdint>
using namespace std;
///////////shortname/////////////
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using vi = vector<int>;
using vd = vector<double>;
#define vec vector
#define dict unordered_map
#define uset unordered_set
#define endl '\n'
const int INF = 1 << 29;
///////////functions/////////////
inline bool equal(const double& a, const double& b) { return fabs(a - b) < 1e-9; }
inline int two(const int& n) { return 1 << n; }
inline int test(const int& n, const int& b) { return (n >> b) & 1; }
inline void set_bit(int& n, const int& b) { n |= two(b); }
inline void unset_bit(int& n, const int& b) { n &= ~two(b); }
inline int last_bit(const int& n) { return n & (-n); }
inline int ones(int n)
{
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
template <class T>
void chmax(T& a, const T& b) { a = max(a, b); }
template <class T>
void chmin(T& a, const T& b) { a = min(a, b); }
////////////operator overloading////////////
#ifndef ONLINE_JUDGE
    #define debug(x) cerr << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

template <typename F, typename S>
ostream& operator<<(ostream& os, const pair<F, S>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    typename vector<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& v)
{
    os << "[";
    typename set<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename T>
ostream& operator<<(ostream& os, const uset<T>& v)
{
    os << "[";
    typename uset<T>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    return os << "]";
}

template <typename F, typename S>
ostream& operator<<(ostream& os, const map<F, S>& v)
{
    os << "{";
    typename map<F, S>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << it->first << ": " << it->second;
    }
    return os << "}";
}

template <typename F, typename S>
ostream& operator<<(ostream& os, const unordered_map<F, S>& v)
{
    os << "{";
    typename unordered_map<F, S>::const_iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        if (it != v.begin())
            os << ", ";
        os << it->first << ": " << it->second;
    }
    return os << "}";
}
////////////main////////////
uint64_t allScore = 0;
void solve(fstream in, fstream out);
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    for (char file = 'a'; file <= 'e'; file++) {
        cout << "::" << file << "::Start\n";

        auto start = std::chrono::high_resolution_clock::now();
        solve(
            fstream(file + string(".in"), ios::in), 
            fstream(file + string(".out"), ios::out)
        );
        auto finish = std::chrono::high_resolution_clock::now();

        cout << "::" << file << "::Elapsed time: " 
            << std::chrono::duration<double>(finish - start).count() << " s\n";
    }
    cout << "Total Score = " << allScore << endl;

    return 0;
}
/////////////////////////////////////////////////solve////////////////////////////////////////////////////////////


#define dist(a, b, x, y) abs(a-x)+abs(b-y)

struct Ride {int a, b, x, y, start, finish, points, num; bool visited;};

void solve(fstream in, fstream out) {
    int r, c, nCars, nRides, bonus, totalTime;
    //------------Taking the Input------------
    in >> r >> c >> nCars >> nRides >> bonus >> totalTime;

    vector<Ride> rides(nRides);
    for (int i = 0; i < nRides; i++) {
        auto& ride = rides[i];

        in >> ride.a >> ride.b >> ride.x >> ride.y >> 
            ride.start >> ride.finish;
            
        ride.points = dist(ride.a, ride.b, ride.x, ride.y);
        ride.num = i;
        ride.visited = false;
    }
     //------------Sorting rides------------    according to earliest start, points
    sort(rides.begin(), rides.end(), [&](const Ride& a, const Ride& b) {
            if (a.start == b.start) return a.points > b.points;
            return a.start < b.start;
    });

    ///////////////
    
    uint64_t score = 0;
    for (int i = 0; i < nCars; i++) {   //Loop on all cars and solve the problem
        int x = 0, y = 0, t = 0;
        vector<int> success;

        for (auto& ride : rides) {  //loop on all non taken rides untill now and check its validity
            if (!ride.visited) {
                auto timetogetthere = dist(x, y, ride.a, ride.b);
                if (timetogetthere + t + ride.points < ride.finish) {
                    score += ride.points;

                    auto margin = ride.start - (timetogetthere + t);
                    if (margin >= 0) {
                        score += bonus;
                    }

                    t += timetogetthere + max(0, margin) + ride.points;
                    x = ride.x;
                    y = ride.y;
                    success.push_back(ride.num);
                    ride.visited = true;
                    //Sort remaining cars according to its latest finish, points
                    sort(rides.begin(), rides.end(), [&](const Ride& a, const Ride& b) {
                        if (a.finish == b.finish) return a.points > b.points;
                        return a.finish < b.finish;
                    });
                }
            }
        }
        //------------Printing the output------------
        out << success.size();
        for (auto& i : success) {out << ' ' << i;}
        out << endl;
    }
    cout << "score = " << score << endl;
    allScore += score;
}
