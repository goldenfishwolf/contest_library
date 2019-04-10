#ifndef DATA_STRUCTURE_H_INCLUDED
#define DATA_STRUCTURE_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


template <typename T>
class Tree
{
    public:
        Tree(T root)
       	{
       		data.clear();
            data[root] = make_tuple(root, 0, vector<T>());
       	}

       	~Tree()
       	{
       		data.clear();
       	}

       	bool add_edge(T child, T parent)
       	{
       		if(data.find(child) == data.end() && data.find(parent) != data.end())
            {
                data[child] = make_tuple(parent, get<1>(data[parent])+1, vector<T>());
                get<2>(data[parent]).push_back(child);
            }
            else
            {
                return false;
            }
            return true;
       	}

        T find(T value, bool is_flatten = false, T default_v = -1)
        {
            if(data.find(value) == data.end()) return default_v;
            T p = get<0>(data[value]);
            if(p == value)
            { 
                return value;
            }
            else
            {
                if(is_flatten)
                {
                    T tem = find(p, is_flatten, default_v);
                    typename vector<T>::iterator it = std::find(get<2>(data[p]).begin(), get<2>(data[p]).end(), value);
                    if(it != get<2>(data[p]).end())
                    {
                        get<2>(data[p]).erase(it);
                    }
                    it = std::find(get<2>(data[tem]).begin(), get<2>(data[tem]).end(), value);
                    if(it == get<2>(data[tem]).end())
                    {
                        get<2>(data[tem]).push_back(value);
                    }
                    get<1>(data[value]) = get<1>(data[tem])+1;
                    get<0>(data[value]) = tem;
                }
                return get<0>(data[value]);
            }

        }

        void dfs(T source)
        {
            map<T, bool> vis;
            stack<T> s;
            vis[source] = true;
            s.push(source);
            while(!s.empty())
            {
                T top = s.top();
                s.pop();
                vector<T> tem_children = get<2>(data[top]);
                for(typename vector<T>::iterator it = tem_children.begin(); it != tem_children.end(); ++it)
                {
                    if(vis.find(*it) == vis.end()) continue;
                    vis[*it] = true;
                    s.push(top);
                    s.push(*it);
                    break;
                }
            }
        }

        void bfs(T source)
        {
            map<T, bool> vis;
            queue<T> q;
            vis[source] = true;
            q.push(source);
            while(!q.empty())
            {
                T top = q.front();
                q.pop();
                vector<T> tem_children = get<2>(data[top]);
                for(typename vector<T>::iterator it = tem_children.begin(); it != tem_children.end(); ++it)
                {
                    if(vis.find(*it) == vis.end()) continue;
                    vis[*it] = true;
                    q.push(*it);
                }
            }
        }

        void print()
        {
            for(typename map<T, tuple<T, ll, vector<T> > >::iterator it = data.begin(); it != data.end(); ++it)
            {
                tuple<T, ll, vector<T> > tem = it->second;
                cout << it->first << " parent data = " << get<0>(tem) << " depth = " << get<1>(tem) << " children : ";
                vector<T> tem_vec = get<2>(tem);
                for(typename vector<T>::iterator ite = tem_vec.begin(); ite != tem_vec.end(); ++ite)
                {
                    cout << *ite << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }

       	map<T, tuple<T, ll, vector<T> > > data; // data, parent data, depth, children

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
            if(data.find(u) != data.end() && find(data[u].begin(),data[u].end(),v) != data[u].end())
            {
                return false;
            }
            data[u].push_back(v);
            data[v].push_back(u);
            degree[u]++;
            degree[v]++;
            return true;
        }

        Tree<T> dfs(map<T, bool>& vis, T source)
        {
            Tree<T> d_tree(source);
            if(vis.find(source) != vis.end()) return d_tree;
            if(data.find(source) == data.end()) return d_tree;
            stack<T> s;
            s.push(source);
            vis[source] = true;
            while(!s.empty())
            {
                T top = s.top();
                s.pop();
                vector<T> tem = data[top];
                for(typename vector<T>::iterator it = tem.begin(); it != tem.end(); ++it)
                {
                    if(vis.find(*it) != vis.end()) continue;
                    d_tree.add_edge(*it, top);
                    vis[*it] = true;
                    s.push(top);
                    s.push(*it);
                    break;
                }
            }
            return d_tree;
        }

        Tree<T> bfs(map<T, bool>& vis, T source)
        {
            Tree<T> b_tree(source);
            if(vis.find(source) != vis.end()) return b_tree;
            if(data.find(source) == data.end()) return b_tree;
            queue<T> q;
            q.push(source);
            vis[source] = true;
            while(!q.empty())
            {
                T top = q.front();
                q.pop();
                vector<T> tem = data[top];
                for(typename vector<T>::iterator it = tem.begin(); it != tem.end(); ++it)
                {
                    if(vis.find(*it) != vis.end()) continue;
                    b_tree.add_edge(*it, top);
                    vis[*it] = true;
                    q.push(*it);
                }
            }
            return b_tree;
        }

        bool is_connect(T a, T b)
        {
            map<T, bool> vis;
            if(data.find(a) == data.end()) return false;
            stack<T> s;
            s.push(a);
            vis[a] = true;
            while(!s.empty())
            {
                T top = s.top();
                s.pop();
                vector<T> tem = data[top];
                for(typename vector<T>::iterator it = tem.begin(); it != tem.end(); ++it)
                {
                    if(vis.find(*it) != vis.end()) continue;
                    if(*it == b) return true;
                    vis[*it] = true;
                    s.push(top);
                    s.push(*it);
                    break;
                }
            }
            return false;
        }

        void print()
        {
             cout << "\ngraph:\n";
             for(typename map<T, vector<T> >::iterator it = data.begin(); it != data.end(); ++it)
             {
                 cout << it->first << " : ";
                 vector<T> tem = it->second;
                 for(typename vector<T>::iterator ite = tem.begin(); ite != tem.end(); ++ite)
                 {
                     cout << *ite << " ";
                 }
                 cout << "\n";
             }
        
             cout << "\ndegree:\n";
             for(typename map<T, ll>::iterator it = degree.begin(); it != degree.end(); ++it)
             {
                 cout << it->first << " : " << it->second << "\n";
             }
        }
    
    public:
        map<T, vector<T> > data;
        map<T, ll> degree;
};


#endif // DATA_STRUCTURE_H_INCLUDED
