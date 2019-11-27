//
//  kruskal.h
//  project
//
//  Created by Zhang Bozhao on 11/24/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#ifndef kruskal_h
#define kruskal_h

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class Kruskal{
public:
    Kruskal(int maxtrix[5000][5000], int start, int end);
    int vertex[5000][5000];
    int dad[5000];
    int rank[5000];
    int s;
    int t;
    int Find(int u);
    void Un(int u, int v);
    vector<vector<int> > MaxSpanningTree();
    vector<int> Bfs();
    
};

#endif /* kruskal_h */
