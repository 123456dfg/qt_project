#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include<sstream>
#include <string.h>
using namespace std;
class algorithm
{
public:
    algorithm();
    string i_to_s(int num);
    vector<int> dijkstra(vector<vector<int>> maps,int x,int y,int n);
};

#endif // ALGORITHM_H
