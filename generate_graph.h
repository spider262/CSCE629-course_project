//
//  generate_graph.h
//  project
//
//  Created by Zhang Bozhao on 11/21/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#ifndef generate_graph_h
#define generate_graph_h

#include <vector>
#include <iterator>

using namespace std;

class Graph{
public:
    Graph();
    void InitGraph();
    void BulidGraphG1();
    void BuildGraphG2();
    int vertex[5000][5000];
    int edgeNum;
    
};

#endif /* generate_graph_h */
