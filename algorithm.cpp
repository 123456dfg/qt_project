#include "algorithm.h"

algorithm::algorithm()
{

}

string algorithm::i_to_s(int num)
{
    int j=0;
    char str1[20]="";
    string str2="";
    while (num > 0)
    {
        str1[j] = num % 10 + '0';
        num = num / 10;
        j++;
    }
    for (int i = strlen(str1) - 1; i >= 0; i--)
    {
        str2 += str1[i];
    }
    return str2;
}

vector<int> algorithm::dijkstra(vector<vector<int>> maps, int x, int y, int node_size) //X 表示 起始点 ,n表示点的数量
{
    int dis[100];//用来存储点到原点的距离 假设 点由数字 1-100 表示
    string path[100];
    int flag[100];//用来判断点是否计算过
    memset(flag,-1,sizeof(int)*100);
    int i,j,k;
    for(int k=1;k<=node_size;k++)
        path[k]=i_to_s(x)+"->"+i_to_s(k);

    for (i=1;i<=node_size;i++)
        dis[i] = maps[x-1][i-1];

    dis[x] = 0;
    flag[x] = 1;

    for (i=1;i<=node_size;i++)
    {
        int min = 1000000000;
        for (j=1;j<=node_size;j++) //寻找离起始点最小的点
        {
            if (flag[j]==-1 && min > dis[j])
            {
                min = dis[j]; //记录最小值
                k = j; // 记录最小值的点
            }
        }
        flag[k] = 1;//标记最小值的点 该点距离起始点已是最短距离
        for (j=1;j<=node_size;j++)
        {
            if (flag[j]!=1&&dis[k]+maps[k-1][j-1] < dis[j])
            {
                dis[j] = min + maps[k-1][j-1];
                path[j]=path[k]+"->"+i_to_s(j);
            }
        }

    }
    vector <int> path1;
    size_t len_s = path[y].size();
    int aa=0,bb=0;
    while ( aa < len_s)
    {
        if (path[y][aa] >= '0'&& path[y][aa] <= '9')
        {
            bb =aa;
            int len = 0;
            while (path[y][aa] >= '0'&& path[y][aa] <= '9')
            {
                aa++;
                len++;
            }
            string s0 = path[y].substr(bb, len);//获取子串
            int num=0;//数字字符串转换为整型数字
            stringstream s1(s0);
            s1 >> num;

            path1.push_back(num);
        }
        else
        {
            aa++;
        }
    }
    /*
        for(vector<int>::iterator it = path1.begin(); it != path1.end(); it++)
        {
            cout << *it ;
        }
        cout<<dis[y]<<endl;
        */

    return path1;
}
