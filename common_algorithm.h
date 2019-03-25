#ifndef COMMON_ALGORITHM_H_INCLUDED
#define COMMON_ALGORITHM_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
T bfs(vector<vector<T> > a, vector<bool> vis, T source)
{
    static_assert(is_same<T, int>::value || is_same<T, ll>::value, "this bfs function can only be in type \"int\" or \"long long int\"!\n");
    T element_num = 1;
    queue<T> q;
    q.emplace(source);
    vis.at(source) = true;
    while(!q.empty())
    {
        T top = q.front();
        q.pop();
        for(T i = 0; i < (T)a.at(top).size(); i++)
        {
            T tem = a.at(top).at(i);
            if(vis.at(tem)) continue;
            vis.at(tem) = true;
            q.emplace(tem);
            element_num++;
        }
    }
    return element_num;
}

template <typename T>
T dfs(vector<vector<T> > a, vector<bool> vis, T source)
{
    static_assert(is_same<T, int>::value || is_same<T, ll>::value, "this dfs function can only be in type \"int\" or \"long long int\"!\n");
    T element_num = 1;
    stack<T> s;
    s.push(source);
    vis.at(source) = true;
    while(!s.empty())
    {
        T top = s.top();
        s.pop();
        for(T i = 0; i < (T)a.at(top).size(); i++)
        {
            T tem = a.at(top).at(i);
            if(vis.at(tem)) continue;
            vis.at(tem) = true;
            s.emplace(top);
            s.emplace(tem);
            element_num++;
            break;
        }
    }
    return element_num;
}

template <typename Iterate, typename T>
pair<typename iterator_traits<Iterate>::difference_type, typename iterator_traits<Iterate>::difference_type> _binary_search(
                                Iterate be, Iterate en, T target, bool (*comp)(T, T) = [](T a, T b){return less<T>()(a,b);})
{
    Iterate l = be, r = en;
    typename iterator_traits<Iterate>::difference_type lower;
    while(l != r)
    {
        typename iterator_traits<Iterate>::difference_type half_diff = distance(l, r) / 2;
        Iterate tem_it = l;
        advance(tem_it, half_diff);
        if(comp(*tem_it, target))
        {
            l = tem_it;
            ++l;
        }
        else
        {
            r = tem_it;
        }
    }
    lower = distance(be, l);

    l = be;
    r = en;
    typename iterator_traits<Iterate>::difference_type upper;
    int i = 0;
    while(l != r && i < 10)
    {
        i++;
        typename iterator_traits<Iterate>::difference_type half_diff = distance(l, r) / 2;
        Iterate tem_it = l;
        advance(tem_it, half_diff);
        if(comp(target, *tem_it))
        {
            r = tem_it;
        }
        else
        {
            l = tem_it;
            ++l;
        }
    }
    upper = distance(be, l);

    return make_pair(lower, upper);
}



#endif // COMMON_ALGORITHM_H_INCLUDED
