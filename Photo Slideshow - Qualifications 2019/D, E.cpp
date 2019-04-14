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
#include <chrono>

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

const int N = 1e5+5;
const int M = 1e7+5;

struct slide
{
	ii ids;
	set<int>tags;
	bool visited;
};

map<string, int>mp;
int mapper;
char inStr[11];
bool evisit[M];
void dfs(slide& u);
vector<vector<slide*>>nodes; //nodes(slides) of a certain edge(tag)

int main()
{
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
	int n;
	cin>>n;
	mp.clear();
	mapper = 0;
	vector<slide>ver, hor;
	for (int i = 0; i < n; i++)
	{
		char type;
		scanf(" %c", &type);
		int m;
		sc(m);
		slide newSl;
		newSl.visited = false;
		newSl.ids = MP(i, -1);
		for (int j = 0; j < m; j++)
		{
			string str;
			scanf("%s", &inStr);
			str = inStr;
			if(!mp.count(str))
			{
				newSl.tags.insert(mapper);
				mp[str] = mapper++;
			}
			else
			{
				int num = mp[str];
				newSl.tags.insert(num);
			}
		}
		if(type == 'H')
			hor.push_back(newSl);
		else
			ver.push_back(newSl);

	}
	vector<slide>temp;
	for (int i = 0; i < sz(ver); i+=2)
	{
		slide s;
		s.visited = false;
		s.ids = MP(ver[i].ids.first, ver[i+1].ids.first);
		s.tags = ver[i].tags;
		s.tags.insert(all(ver[i+1].tags));
		temp.push_back(s);
	}
	ver = temp;
	temp.clear();
	nodes.resize(sz(mp));
	for (int i = 0; i < sz(hor); i++)
	{
		for(const auto t: hor[i].tags)
			nodes[t].push_back( &hor[i] );
	}
	for (int i = 0; i < sz(ver); i++)
	{
		for(const auto t: ver[i].tags)
			nodes[t].push_back( &ver[i]);
	}
	printf("%d\n", sz(hor)+sz(ver));

	for (int i = 0; i < sz(hor); i++)
	{
		if(!hor[i].visited)
			dfs(hor[i]);
	}
	for (int i = 0; i < sz(ver); i++)
	{
		if(!ver[i].visited)
			dfs(ver[i]);
	}
	
	return 0;
}

void dfs(slide& u)
{
	u.visited = true;
	printf("%d ", u.ids.first);
	if(u.ids.second != -1)
		printf("%d", u.ids.second);
	printf("\n");
	for(const auto& edge: u.tags)
	{
		if(!evisit[edge])
		{
			for(const auto& node: nodes[edge])
				if(!node->visited)
					dfs(*node);
			evisit[edge] = 1;
		}
	}
}
