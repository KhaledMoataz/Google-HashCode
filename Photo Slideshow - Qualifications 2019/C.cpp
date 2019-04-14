#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <functional>
#include <numeric>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define SRT(v) sort(all(v))
#define rall(v) (v).rbegin(),(v).rend()
#define rSRT(v) sort(rall(v))
#define sz(a) int((a).size())
#define watch(x) cout<<(#x)<<" = "<<x;
#define MP make_pair
#define sc(x) scanf("%d", &(x))
#define sclld(x) scanf("%lld", &(x))
#define pf(x) printf("%d", (x))
#define pflld(x) printf("%lld", (x))
typedef long long ll;
typedef pair<int,int> ii;
const ll Mod = 1e9+7;
const double pi = 2*acos(0.0);

const int N = 1e7+5;

struct slide
{
	ii ids;
	set<int>tags;
	bool visited;
};
map<string, int>mp;
int mapper;
char inStr[11];

int getIntersection(const set<int>& t1, const set<int>& t2)
{
	int res = 0;
	auto it1 = t1.begin(); 
	auto it2 = t2.begin();
	while(it1 != t1.end() && it2 != t2.end())
	{
		if(*it1 == *it2)
			res++, it1++, it2++;
		else if(*it1 < *it2)
			it1++;
		else
			it2++;
	}
	return res;
}

int main()
{
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	int n;
	cin>>n;
	vector<slide>ver, hor;
	for (int i = 0; i < n; i++)
	{
		char type;
		scanf(" %c", &type);
		int m;
		sc(m);
		slide sl;
		sl.ids = MP(i, -1);
		sl.visited = false;
		for (int i = 0; i < m; i++)
		{
			string str;
			scanf("%s", &inStr);
			str = inStr;
			if(!mp.count(str))
			{
				sl.tags.insert(mapper);
				mp[str] = mapper++;
			}
			else
			{
				int correspondingNum = mp[str];
				sl.tags.insert(correspondingNum);
			}
		}
		if(type == 'H')
			hor.push_back(sl);
		else
			ver.push_back(sl);
	}
	//combine vertical photos together into one slide
	vector<slide>temp;
	int verCnt = 0;
	for (int i = 0; i < sz(ver) && verCnt < sz(ver); i++)
	{
		if(!ver[i].visited)
		{
			ver[i].visited = true;
			slide newSl;
			newSl.ids = MP(ver[i].ids.first, -1);
			newSl.visited = false;
			newSl.tags = ver[i].tags;
			int mn = 1e9, mnIdx = -1;
			for (int j = 0; j < sz(ver); j++)
			{
				if(!ver[j].visited)
				{
					int intersection = getIntersection(newSl.tags, ver[j].tags);

					if(intersection < mn)
					{
						mn = intersection, mnIdx = j;
						if(intersection == 0)
							break;
					}
				}
			}

			ver[mnIdx].visited = true;
			newSl.tags.insert(all(ver[mnIdx].tags));
			newSl.ids.second = ver[mnIdx].ids.first;
			verCnt += 2;
			temp.push_back(newSl);
		}
	}
	ver.clear();
	vector<slide>total = temp;
	temp.clear();
	total.insert(total.end(), all(hor));
	hor.clear();
	int totalCnt = 0;
	printf("%d\n", sz(total));
	for (int i = 0; totalCnt < sz(total); )
	{
		if(!total[i].visited)
		{
			total[i].visited = true;
			printf("%d ", total[i].ids.first);
			if(total[i].ids.second != -1)
				printf("%d", total[i].ids.second);
			printf("\n");
			int mx = -1, mxIdx = -1;
			for (int j = 0; j < sz(total); j++)
			{
				if(!total[j].visited)
				{
					int intersection = getIntersection(total[i].tags, total[j].tags);
					int s1 = sz(total[i].tags)-intersection;
					int s2 = sz(total[j].tags)-intersection;
					int score = min(intersection, min(s1, s2));
					if(score > mx)
						mx = score, mxIdx = j;
					else if(score == mx && abs(sz(total[i].tags)-sz(total[j].tags)) < abs(sz(total[i].tags)-sz(total[mxIdx].tags)))
						mxIdx = j;
				}
			}
			i = mxIdx;
			totalCnt++;
		}

	}
	return 0;
}
