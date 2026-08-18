#include <bits/stdc++.h>
using namespace std;
int numberOfIslands(vector<vector<char>> grid) { if(grid.empty())return 0;int rows=grid.size(),cols=grid[0].size(),ans=0;for(int r=0;r<rows;++r)for(int c=0;c<cols;++c)if(grid[r][c]=='1'){++ans;queue<pair<int,int>>q;q.push({r,c});grid[r][c]='0';while(!q.empty()){auto [x,y]=q.front();q.pop();for(auto [dx,dy]:vector<pair<int,int>>{{1,0},{-1,0},{0,1},{0,-1}}){int nx=x+dx,ny=y+dy;if(nx>=0&&nx<rows&&ny>=0&&ny<cols&&grid[nx][ny]=='1')grid[nx][ny]='0',q.push({nx,ny});}}}return ans; }

