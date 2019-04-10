#ifndef COMMON_ALGORITHM_H_INCLUDED
#define COMMON_ALGORITHM_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Input:
be: iterator of the begin
en: Iterator of the end(exculsive)
target: the element user want to find
comp: custom compare function, should use to compare which one is less than other one
Output:
the pair of the lower bound index and upper bound index(the one that input "be" point to is veiw as index 0)
example:
vector<int> a = {1, 2, 2, 2, 2, 2, 3, 9};
pair<int, int> test = _binary_search<vector<int>::iterator, int>(a.begin(), a.end(), 2);
cout << "result is " << test.first << " " << test.second << endl;
//result is 1 6
*/

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
    while(l != r)
    {
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

template<typename T>
pair<T, T> _binary_search(T low, T high, T target, ll max_iter = 1e3, bool (*stop)(T, T) = [](T a, T b){return false;},
                                    T (*func)(T) = [](T a){return a;}, bool (*comp)(T, T) = [](T a, T b){return less<T>()(a,b);})
{
    T l = low;
    T r = high;
    T m = (l+r)/ (T)2;
    for(ll i = 0; l != r && i < max_iter && !stop(func(m),target); i++)
    {
        m = (l+r)/ (T)2;
        if(comp(func(m), target))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }

    T lower = l;

    l = low;
    r = high;
    m = (l+r)/ (T)2;

    for(ll i = 0; l != r && i < max_iter && !stop(func(m),target); i++)
    {
        m = (l+r)/ (T)2;
        if(comp(target, func(m)))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    T upper = l;

    return make_pair(lower, upper);
}




#endif // COMMON_ALGORITHM_H_INCLUDED
