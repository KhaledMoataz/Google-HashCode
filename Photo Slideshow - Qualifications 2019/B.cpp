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

map<string, int>mp;
int mapper;
char inStr[11];
vector<vector<int>> nodes;	//nodes(photos) of a certain tag
vector<int> edges[N];	//edges(tags) of a certain node
bool visited[N];
bool evisit[M];
int freq[M];
void dfs(int u);

int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	int n;
	cin>>n;
	mp.clear();
	mapper = 0;
	for (int i = 0; i < n; i++)
	{
		char type;
		scanf(" %c", &type);
		int m;
		sc(m);
		for (int j = 0; j < m; j++)
		{
			string str;
			scanf("%s", &inStr);
			str = inStr;
			if(!mp.count(str))
			{
				edges[i].push_back(mapper);
				freq[mapper]++;
				mp[str] = mapper++;
				nodes.push_back(vector<int>(1, i));
			}
			else
			{
				int num = mp[str];
				nodes[num].push_back(i);
				edges[i].push_back(num);
				freq[num]++;
			}

		}

	}
	printf("%d\n", n);
	for (int i = 0; i < sz(nodes); i++)
	{
		sort(all(nodes[i]), [](const int& n1, const int& n2){
			return sz(edges[n1]) > sz(edges[n2]);
		});
	}
	for (int i = 0; i < n; i++)
	{
		sort(all(edges[i]), [](const int& t1, const int& t2){
			return freq[t1]>freq[t2];
		});
	}
	dfs(0);
	return 0;
}

void dfs(int u)
{
	visited[u] = 1;
	printf("%d\n", u);
	for(const auto edge: edges[u])
	{
		if(!evisit[edge])
		{
			for(const auto node: nodes[edge])
				if(!visited[node])
					dfs(node);
			evisit[edge] = 1;
		}
	}
}
