//
//  make_heap.cpp
//  project
//
//  Created by Zhang Bozhao on 11/23/19.
//  Copyright © 2019 Zhang Bozhao. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "make_heap.h"

using namespace std;

Heap::Heap(){
    size=-1;
    for (int i=0;i<5000;++i){
        H[i]=0;
        D[i]=INT_MAX;
    }
}

int Heap:: Max(){
    return H[0];
}

edge Heap::MaxEdge(){
    return Edge[0];
}

void Heap::Insert(int vertex, int val){  //index from 1 to 5000
    D[vertex]=val;
    ++size;
    H[size]=vertex;
    int i=size;
    for (; i!=0 && D[H[(i-1)/2]]<val;i=(i-1)/2){
        H[i]=H[(i-1)/2];
    }
    H[i]=vertex;
}

void Heap::InsertEdge(edge e){
    ++size;
    Edge.push_back(e);
    int i=size;
    for (; i!=0 && Edge[(i-1)/2].weight<e.weight;i=(i-1)/2){
        Edge[i]=Edge[(i-1)/2];
    }
    Edge[i]=e;
}

void Heap::Pop(){   //delete first
    H[0]=H[size];
    --size;
    int i=0;
    for(;2*i+1<=size;){
        if (2*i+1==size){
            if (D[H[2*i+1]]>D[H[i]]){
                int tmp=H[2*i+1];
                H[2*i+1]=H[i];
                H[i]=tmp;
                i=2*i+1;
            } else {
                break;
            }
        } else {    //2i+1<size
            if (D[H[i]]<max(D[H[2*i+1]],D[H[2*i+2]])){
                if (D[H[2*i+1]]>D[H[2*i+2]]){
                    int tmp=H[2*i+1];
                    H[2*i+1]=H[i];
                    H[i]=tmp;
                    i=2*i+1;
                } else {
                    int tmp=H[2*i+2];
                    H[2*i+2]=H[i];
                    H[i]=tmp;
                    i=2*i+2;
                }
            } else {
                break;
            }
        }
        
    }
}

void Heap::PopEdge(){
    Edge[0]=Edge[size];
    --size;
    int i=0;
    for(;2*i+1<=size;){
        if (2*i+1==size){
            if (Edge[2*i+1].weight>Edge[i].weight){
                edge tmp=Edge[2*i+1];
                Edge[2*i+1]=Edge[i];
                Edge[i]=tmp;
                i=2*i+1;
            } else {
                break;
            }
        } else {    //2i+1<size
            if (Edge[i].weight<max(Edge[2*i+1].weight,Edge[2*i+2].weight)){
                if (Edge[2*i+1].weight>Edge[2*i+2].weight){
                    edge tmp=Edge[2*i+1];
                    Edge[2*i+1]=Edge[i];
                    Edge[i]=tmp;
                    i=2*i+1;
                } else {
                    edge tmp=Edge[2*i+2];
                    Edge[2*i+2]=Edge[i];
                    Edge[i]=tmp;
                    i=2*i+2;
                }
            } else {
                break;
            }
        }
        
    }
}

void Heap::Delete(int vertex){
    D[vertex]=INT_MAX;
    int index=0;
    for (;index<=size;++index){
        if (H[index]==vertex)
            break;
    }
    H[index]=H[size];
    --size;
    int i=index;
    for(;2*i+1<=size;){
        if (2*i+1==size){
            if (D[H[2*i+1]]>D[H[i]]){
                int tmp=H[2*i+1];
                H[2*i+1]=H[i];
                H[i]=tmp;
                i=2*i+1;
            } else {
                break;
            }
        } else {    //2i+1<size
            if (D[H[i]]<max(D[H[2*i+1]],D[H[2*i+2]])){
                if (D[H[2*i+1]]>D[H[2*i+2]]){
                    int tmp=H[2*i+1];
                    H[2*i+1]=H[i];
                    H[i]=tmp;
                    i=2*i+1;
                } else {
                    int tmp=H[2*i+2];
                    H[2*i+2]=H[i];
                    H[i]=tmp;
                    i=2*i+2;
                }
            } else {
                break;
            }
        }
        
    }
    
}

bool Heap::Empty(){
    return size==-1;
}
