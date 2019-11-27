//
//  main.cpp
//  project
//
//  Created by Zhang Bozhao on 11/21/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "generate_graph.h"
#include "make_heap.h"
#include "kruskal.h"

using namespace std;

vector<int> DijNoHeap(int vertex[5000][5000], int s, int t){
    int visited[5000];
    int wt[5000];
    int dad[5000];
    for (int i=0;i<5000;++i){
        visited[i]=0;       //visited:0 means unseen, -1 means fringe, 1 means in-tree
        dad[i]=-1;
        wt[i]=INT_MAX;
    }
    visited[s]=1;
    wt[s]=0;
    dad[s]=s;
    vector<int> fringe;
    for (int i=0;i<5000;++i){
        if (s==i || vertex[s][i]==0){
            continue;
        }
        visited[i]=-1;      //i is fringe then insert it into queue
        wt[i]=vertex[s][i];
        dad[i]=s;
        fringe.push_back(i);
    }
    int tmp_vertex, index;
    while (!fringe.empty()){
        tmp_vertex=fringe[0];
        index=0;
        for (int i=1;i<fringe.size();++i){
            if (wt[fringe[i]]>wt[tmp_vertex]){
                tmp_vertex=fringe[i];
                index=i;
            }
        }
        fringe.erase(fringe.begin()+index);
        visited[tmp_vertex]=1;
        if (tmp_vertex==t)
            break;
        for (int j=0;j<5000;++j){
            if (tmp_vertex==j || vertex[tmp_vertex][j]==0)
                continue;
            else{
                if (visited[j]==0){
                    visited[j]=-1;
                    dad[j]=tmp_vertex;
                    wt[j]=min(wt[tmp_vertex],vertex[tmp_vertex][j]);
                    fringe.push_back(j);
                } else if (visited[j]==-1 && wt[j]<min(wt[tmp_vertex],vertex[tmp_vertex][j])){
                    dad[j]=tmp_vertex;
                    wt[j]=min(wt[tmp_vertex],vertex[tmp_vertex][j]);
                }
            }
        }
    }
    vector<int> path;
    int tmp=t;
    while (tmp!=s){
        path.push_back(tmp);
        tmp=dad[tmp];
    }
    path.push_back(s);
    vector<int> res(path.rbegin(),path.rend());
    return res;
}

vector<int> DijWithHeap(int vertex[5000][5000], int s, int t){
    int visited[5000];
    int wt[5000];
    int dad[5000];
    Heap *h=new Heap();
    for (int i=0;i<5000;++i){
        visited[i]=0;       //visited:0 means unseen, -1 means fringe, 1 means in-tree
        dad[i]=-1;
        wt[i]=INT_MAX;
    }
    visited[s]=1;
    wt[s]=0;
    dad[s]=s;
    for (int i=0;i<5000;++i){
        if (i==s || vertex[s][i]==0){
            continue;
        }
        visited[i]=-1;      //i is fringe then insert it into heap
        wt[i]=vertex[s][i];
        dad[i]=s;
        h->Insert(i, wt[i]);
    }
    while (!h->Empty()){
        int tmp_vertex=h->Max();
        visited[tmp_vertex]=1;
        h->Pop();
        if (tmp_vertex==t)
            break;
        for (int j=0;j<5000;++j){
            if (tmp_vertex==j || vertex[tmp_vertex][j]==0)
                continue;
            else{
                if (visited[j]==0){
                    visited[j]=-1;
                    dad[j]=tmp_vertex;
                    wt[j]=min(wt[tmp_vertex],vertex[tmp_vertex][j]);
                    h->Insert(j, wt[j]);
                } else if (visited[j]==-1 && wt[j]<min(wt[tmp_vertex],vertex[tmp_vertex][j])){
                    dad[j]=tmp_vertex;
                    h->Delete(j);
                    wt[j]=min(wt[tmp_vertex],vertex[tmp_vertex][j]);
                    h->Insert(j, wt[j]);
                }
            }
        }
    }
    vector<int> path;
    int tmp=t;
    while (tmp!=s){
        path.push_back(tmp);
        tmp=dad[tmp];
    }
    path.push_back(s);
    vector<int> res(path.rbegin(),path.rend());
    return res;

}


int main(int argc, const char * argv[]) {
    clock_t startTime,endTime;
    for (int num=1;num<6;++num){
        Graph *g1=new Graph();
        g1->InitGraph();
        g1->BulidGraphG1();
        Graph *g2=new Graph();
        g2->InitGraph();
        g2->BuildGraphG2();
        cout<<"Pair "<<num<<" graph:"<<endl;
        for (int i=1;i<6;++i){
            cout<<"Pair "<<i<<" start and end vertex:"<<endl;
            int s=rand()%5000+1;
            int t=rand()%5000+1;
            cout<<"s="<<s<<','<<"t="<<t<<endl;
            cout<<"----------"<<endl;
            //G1
            startTime=clock();
            vector<int> g1Path1=DijWithHeap(g1->vertex, s, t);
            endTime=clock();
            cout<<"Run time of G1 using dijkstra with heap is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G1 using dij with heap path:"<<endl;
            for (int i=0;i<g1Path1.size()-1;++i)
                cout<<g1Path1[i]<<"->";
            cout<<g1Path1[g1Path1.size()-1]<<endl;
            cout<<"-----"<<endl;

            startTime=clock();
            vector<int> g1Path2=DijNoHeap(g1->vertex, s, t);
            endTime=clock();
            cout<<"Run time of G1 using dijkstra without heap is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G1 using dij without heap path:"<<endl;
            for (int i=0;i<g1Path2.size()-1;++i)
                cout<<g1Path2[i]<<"->";
            cout<<g1Path2[g1Path2.size()-1]<<endl;
            cout<<"-----"<<endl;

            startTime=clock();
            Kruskal *kru1=new Kruskal(g1->vertex,s,t);
            vector<int> g1Path3=kru1->Bfs();
            endTime=clock();
            cout<<"Run time of G1 using kruskal is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G1 using kruskal path:"<<endl;
            for (int i=0;i<g1Path3.size()-1;++i)
                cout<<g1Path3[i]<<"->";
            cout<<g1Path3[g1Path3.size()-1]<<endl;
            cout<<"----------"<<endl;

            //G2
            startTime=clock();
            vector<int> g2Path1=DijWithHeap(g2->vertex, s, t);
            endTime=clock();
            cout<<"Run time of G2 using dijkstra with heap is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G2 using dij with heap path:"<<endl;
            for (int i=0;i<g2Path1.size()-1;++i)
                cout<<g2Path1[i]<<"->";
            cout<<g2Path1[g2Path1.size()-1]<<endl;
            cout<<"-----"<<endl;

            startTime=clock();
            vector<int> g2Path2=DijNoHeap(g2->vertex, s, t);
            endTime=clock();
            cout<<"Run time of G2 using dijkstra without heap is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G2 using dij without heap path:"<<endl;
            for (int i=0;i<g2Path2.size()-1;++i)
                cout<<g2Path2[i]<<"->";
            cout<<g2Path2[g2Path2.size()-1]<<endl;
            cout<<"-----"<<endl;

            startTime=clock();
            Kruskal *kru2=new Kruskal(g2->vertex,s,t);
            vector<int> g2Path3=kru2->Bfs();
            endTime=clock();
            cout<<"Run time of G2 using kruskal is:"<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
            cout<<"G2 using kruskal path:"<<endl;
            for (int i=0;i<g2Path3.size()-1;++i)
                cout<<g2Path3[i]<<"->";
            cout<<g2Path3[g2Path3.size()-1]<<endl;
            cout<<"--------------------------------------------------"<<endl;
        }
        cout<<"----------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl;
        cout<<endl;
    }
    
    return 0;
}
