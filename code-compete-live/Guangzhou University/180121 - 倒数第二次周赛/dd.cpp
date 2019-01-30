#include <bits/stdc++.h>
using namespace std;
 
long long tot;
vector<int> pos[4];
bool mark[5][100];
int mark4_cnt;

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
     
    int t; scanf("%d", &t);
    while (t--)
    {
        tot = 0, mark4_cnt = 0;
        memset(mark, 0, sizeof(mark));
         
        for (int i = 0; i < 4; ++i)
        {
        	pos[i].clear();
            char pic[110]; scanf("%s", pic);
            for (int j = 0;j < 100; ++j)
            {
                if (pic[j] == '#')
                {
                	pos[i].push_back(j);
					mark[i][j] = true;	 
				}
            }
        }
        
        for (int i = 0; i < 100; ++i)
        {
        	mark[4][i] = mark[2][i]&&mark[3][i];
        	if (mark[4][i]) ++mark4_cnt;
		}

        for (int i = 0; i < pos[0].size(); ++i)
        {
        	int q = pos[0][i];
        	for (int j = 0; j < pos[1].size(); ++j)
        	{
        		int p = pos[1][j]; if (q == p) continue;
        		tot += (pos[2].size()-mark[2][q]-mark[2][p])*(pos[3].size()-mark[3][q]-mark[3][p]);
        		tot -= mark4_cnt - mark[4][q] - mark[4][p];
			}
		}
        
        printf("%lld\n", tot);
    }
}
