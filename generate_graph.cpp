//
//  generate_graph.cpp
//  project
//
//  Created by Zhang Bozhao on 11/21/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "generate_graph.h"

using namespace std;

Graph::Graph(){
    edgeNum = 0;
    for (int i=0;i<5000;++i){
        for (int j=i;j<5000;++j){
            vertex[i][j]=0;
            vertex[j][i]=vertex[i][j];
        }
    }
}

void Graph::InitGraph(){
    vector<int> tmp(5000);
    for (int i=0; i<5000; ++i){
        tmp[i] = i;
    }
    random_shuffle(tmp.begin(),tmp.end());
    for (int i=0; i<4999; ++i){
        int tmpWeight=rand()%50000+1;
        vertex[tmp[i]][tmp[i+1]]=tmpWeight;
        vertex[tmp[i+1]][tmp[i]]=tmpWeight;
    }
    // corner case
    int tmpWeight=rand()%50000+1;
    vertex[tmp[0]][tmp[4999]]=tmpWeight;
    vertex[tmp[4999]][tmp[0]]=tmpWeight;
    edgeNum=5000;
    return;
}

void Graph::BulidGraphG1(){
    while (edgeNum<15000){
        int i=rand()%5000;
        int j=rand()%5000;
        if (i==j || vertex[i][j]!=0){
            continue;       // edge has already existed
        }
        int tmpWeight=rand()%50000+1;
        vertex[i][j]=tmpWeight;
        vertex[j][i]=tmpWeight;
        ++edgeNum;
    }
    return;
}

bool hasEdge(){
    int m = rand()%10;
    if (m < 2)
        return true;
    else
        return false;
}

void Graph::BuildGraphG2(){
    for (int i=0;i<5000;++i){
        for (int j=i+1;j<5000;++j){
            if (hasEdge()){
                int tmpWeight=rand()%50000+1;
                vertex[i][j]=tmpWeight;
                vertex[j][i]=tmpWeight;
            }
        }
    }
    return;
}
