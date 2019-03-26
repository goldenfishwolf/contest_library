#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
class Tree_node
{
    public:
        Tree_node(T data, ll parent_index, ll depth)
       	{
       		data = tuple<T, ll, ll>(data, parent_index, depth);
       	}
       
       	~Tree_node()
       	{
       		;
       	}
       
       	tuple<T, ll, ll> data;
};


template <typename T>
class Tree
{
    public:
        Tree()
       	{
       		;
       	}
       
       	~Tree()
       	{
       		;
       	}
       
       	bool add_edge(T u, T v)
       	{
       		;
       	}
       
       	vector<tuple<T, ll, ll> > data;
       
};





template <class T>
class Graph
{
    public:
        Graph()
        {
            ;
        }

        ~Graph()
        {
            data.clear();
            degree.clear();
        }

        bool simple_add_edge(T u, T v)
        {
            if(data.find(u) != data.end())
            {
                if(data[u].find(v) != data[u].end())
                {
                    //cout << "this edge is already in te graph!" << endl;
                    return false;
                }
            }
            data[u][v] = -1;
            data[v][u] = -1;
            degree[u]++;
            degree[v]++;
            return true;
        }

        void dfs(map<T, bool>& vis, T source)
        {
            if(vis.find(source) == vis.end()) return;
            if(data.find(source) == data.end()) return;
            stack<T> s;
            s.push(source);
            vis[source] = true;
            while(!s.empty())
            {
                T top = s.top();
                s.pop();
                for(typename map<T, map<T, ll> >::iterator it = data[top].begin(); it != data[top].end(); ++it)
                {
                    if(vis.find(*it) == vis.end()) continue;
                    s.push(source);
                    s.push(*it);
                    break;
                }
            }
        }

        map<T, map<T, ll> > data;
        map<T, ll> degree;
};


#endif // DATA_STRUCTURE_H_INCLUDED
