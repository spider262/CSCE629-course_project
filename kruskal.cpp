//
//  kruskal.cpp
//  project
//
//  Created by Zhang Bozhao on 11/24/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#include <queue>
#include <vector>
#include <iostream>
#include "kruskal.h"
#include "make_heap.h"

using namespace std;

Kruskal::Kruskal(int matrix[5000][5000],int start, int end){
    for (int i=0;i<5000;++i){
        for (int j=0;j<5000;++j){
            vertex[i][j]=matrix[i][j];
        }
        dad[i]=i;
        rank[i]=0;
    }
    s=start;
    t=end;
}

int Kruskal::Find(int u){
    queue<int> q;
    int tmp=u;
    while (dad[tmp]!=tmp){
        q.push(tmp);
        tmp=dad[tmp];
    }
    while (!q.empty()){
        int temp=q.front();
        q.pop();
        dad[temp]=tmp;
    }
    return tmp;
}

void Kruskal::Un(int u, int v){
    if (rank[u]>rank[v]){
        dad[v]=u;
    } else if (rank[u]<rank[v]){
        dad[u]=v;
    } else {
        dad[u]=v;
        ++rank[v];
    }
    return;
}

vector<vector<int>> Kruskal::MaxSpanningTree(){
    Heap *heapEdge=new Heap();
    for (int i=0;i<5000;++i){   //insert all edges into heap
        for (int j=i+1;j<5000;++j){
            if (vertex[i][j]==0)
                continue;
            heapEdge->InsertEdge(*new edge(i,j,vertex[i][j]));
        }
    }
    int count=5000;
    vector<vector<int>> maxSpanningTree(5000, vector<int>(5000));
    int dad[5000], rank[5000];
    for (int i=0;i<5000;++i){   //make set
        dad[i]=i;
        rank[i]=0;
    }
    //cout<<"make set finish"<<endl;
    int u,v,weight,dadu,dadv;
    while (count>1 && !heapEdge->Empty()){
        //cout<<count<<endl;
        u=heapEdge->MaxEdge().u;
        v=heapEdge->MaxEdge().v;
        weight=heapEdge->MaxEdge().weight;
        heapEdge->PopEdge();
        dadu=Find(u);
        dadv=Find(v);
        if (dadu!=dadv){
            Un(dadu, dadv);
            --count;
            maxSpanningTree[u][v]=weight;
            maxSpanningTree[v][u]=weight;
        }
    }
    return maxSpanningTree;
}

vector<int> Kruskal::Bfs(){
    int visited[5000];
    for (int i=0; i<5000; ++i){
        visited[i]=0;
    }
    visited[s]=1;
    queue<int> q;
    q.push(s);
    vector<vector<int>> maxSpanningTree=MaxSpanningTree();
    int path[5000];
    path[s]=s;
    while (!q.empty()){
        int tmp=q.front();
        q.pop();
        if (tmp==t)
            break;
        for (int i=0;i<5000;++i){
            if (i==tmp || maxSpanningTree[tmp][i]==0)
                continue;
            else if (visited[i]==0){
                visited[i]=1;
                q.push(i);
                path[i]=tmp;
            }
        }
    }
    vector<int> temp;
    int tmp=t;
    while (tmp!=s){
        temp.push_back(tmp);
        tmp=path[tmp];
    }
    temp.push_back(s);
    vector<int> res(temp.rbegin(),temp.rend());
    return res;
}
