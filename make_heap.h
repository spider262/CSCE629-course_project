//
//  make_heap.h
//  project
//
//  Created by Zhang Bozhao on 11/23/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#ifndef make_heap_h
#define make_heap_h

#include <stdio.h>
#include <vector>

using namespace std;

struct edge{
    int u;
    int v;
    int weight;
    edge(int i, int j, int w): u(i),v(j),weight(w){}
};


class Heap{
public:
    Heap();
    int Max();
    edge MaxEdge();
    void Insert(int vertex, int val);
    void InsertEdge(edge e);
    void Pop();
    void PopEdge();
    void Delete(int vertex);
    bool Empty();
    int size;
    int H[5000];
    int D[5000];
    vector<edge> Edge;
};

#endif /* make_heap_h */
