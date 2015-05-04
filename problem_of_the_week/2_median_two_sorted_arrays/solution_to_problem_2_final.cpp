#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <thread>
#include <chrono>
#include <random>
#include <cassert>
#include <utility>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

template <class iter>
double base_cases_median(const iter& a_begin, const iter& a_end, const iter& b_begin, const iter& b_end) {
 /* cout << "Checking base case" << endl;
  for (iter i = a_begin; i != a_end; ++i) {
    cout << "a = " << *i << endl;
  }
  cout << endl;
  for (iter i = b_begin; i != b_end; ++i) {
    cout << "b = " << *i << endl;
  }*/
  auto calc = [](const pair<double, double>& a) { return (a.first + a.second)/2.0; };
  const int size_b = distance(b_begin, b_end);
  pair<pair<double,double>, pair<double,double>> median;
  iter b_median = b_begin;
  advance(b_median, (distance(b_begin, b_end) / 2));
  if (size_b <= 2) {
    auto minmax = minmax_element(b_begin, b_end);
    median.first = make_pair(*minmax.first, (minmax.second == b_end) ? *minmax.first : *minmax.second);
    minmax = minmax_element(a_begin, a_end);
    median.second = make_pair(*minmax.first, (minmax.second == a_end) ? *minmax.first : *minmax.second);
    if (size_b == 1) {
      if (distance(a_begin, a_end) == 1) {
        median.first.second = median.second.first;
        return calc(median.first);
      } else {
        if (median.second.first >= median.first.first) {
          return median.second.first;
        } else if (median.second.second < median.first.first) {
          return median.second.second;
        } else {
          return median.first.first;
        }
      }
    } else { //size_b = 2
      if (distance(a_begin, a_end) == 1) {
        if (*a_begin <= median.first.first) {
          return median.first.first;
        } else if (*a_begin >= median.first.second) {
          return median.first.second;
        } else {
          return *a_begin;
        } 
      } else { // size_a = 2;

        if (median.second.second <= median.first.first) {
          median.first.second = median.second.second;
          return calc(median.first);
        } else if (median.second.first >= median.first.second) {
          median.first.first = median.second.first;
          return calc(median.first);
        } else {
          if (median.second.first > median.first.first) {
            swap(median.second.first, median.first.first);
          } 
          if (median.second.second < median.first.second) {
            swap(median.second.second, median.first.second);
          }
          return calc(median.first);
        }
      }
    }
  }
  if (size_b%2 == 0) {
    median.first = make_pair(*(b_median-1), *b_median);
    median.second = make_pair(*(b_median-2), *(b_median+1));
  } else {
    median.first = make_pair(*b_median, *b_median);
    median.second = make_pair(*(b_median-1), *(b_median+1));
  }
  int i = 0;
  for (iter it = a_begin; it != a_end; ++it, ++i) {
 /*   cout << "adding " << *it << " to " << endl;
    cout << median.second.first << " : " << median.first.first << " : " << median.first.second << " : " << median.second.second << endl;
  */if (*it <= median.second.first) {
      if ((size_b + i)%2 == 0) {
        median.second.second = median.first.second;
        median.first.second = median.first.first;
      } else {
        median.first.first = median.second.first;
        median.second.first = *it;
      } 
    } else if (*it >= median.second.second) {
      if ((size_b + i)%2 == 0) {
        median.second.first = median.first.first;
        median.first.first = median.first.second;
      } else {
        median.first.second = median.second.second;
        median.second.second = *it;
      }
    } else {
      if ((size_b + i)%2 == 0) {
        if (*it <= median.first.first) {
          median.second.first = *it;
          median.second.second = median.first.second;
          median.first.second = median.first.first;
        } else if (*it <= median.first.second) {
          median.second.first = median.first.first;
          median.second.second = median.first.second;
          median.first = make_pair(*it, *it);
        } else {
          median.second.first = median.first.first;
          median.first.first = median.first.second;
          median.second.second = *it;
        }     
      } else {
        if (*it <= median.first.first) {
          median.first.first = *it;
        } else {
          median.first.second = *it;
        }
      }
    }
  }
//cout << median.second.first << " : " << median.first.first << " : " << median.first.second << " : " << median.second.second << endl;
  return calc(median.first);
}

template <class iter>
double find_median(const iter& a_begin, const iter& a_end, const iter& b_begin, const iter& b_end) {
  iter a_median = a_begin;
  advance(a_median, (distance(a_begin, a_end) / 2));
  iter b_median = b_begin;
  advance(b_median, (distance(b_begin, b_end) / 2));
  if (distance(b_begin, b_end) == 0) {
    return (distance(a_begin, a_end)%2 == 0) ? (*a_median + *(a_median - 1))/2.0 : *a_median;
  } else  if (distance(a_begin, a_end) == 0) {
   /* for (iter i = b_begin; i != b_end; ++i) {
      cout << "b = " << *i << endl;
    }*/
    return (distance(b_begin, b_end)%2 == 0) ? (*b_median + *(b_median - 1))/2.0 : *b_median;
  }
  if (distance(a_begin, a_end) <= 2) {
    return base_cases_median(a_begin, a_end, b_begin, b_end);
  } else if (distance(b_begin, b_end) <= 2) { 
    return base_cases_median(b_begin, b_end, a_begin, a_end);
  } else {
    // check values and decide which part of the array to discard.
    int removal;
    if (*a_median <= *b_median) {
 /*     cout << distance(a_begin, a_end) << " a_med <= b_med" << endl;
      for (iter i = a_begin; i != a_end; ++i) {
        cout << "a = " << *i << endl;
      }
      cout << endl;
      for (iter i = b_begin; i != b_end; ++i) {
        cout << "b = " << *i << endl;
      }
   */ removal = (distance(a_begin, a_end)%2 == 0) ? 
        min(distance(a_begin, a_median)-1, distance(b_median, b_end)-1) : 
        min(distance(a_begin, a_median), distance(b_median, b_end)-1);
    } else {
  /*  cout << distance(b_begin, b_end) << " b_med > a_med" << endl;
      for (iter i = a_begin; i != a_end; ++i) {
        cout << "a = " << *i << endl;
      }
      cout << endl;
      for (iter i = b_begin; i != b_end; ++i) {
        cout << "b = " << *i << endl;
      }
   */ removal = (distance(b_begin, b_end)%2 == 0) ?
        min(distance(b_begin, b_median) - 1, distance(a_median, a_end) -1 ) : 
        min(distance(b_begin, b_median), distance(a_median, a_end)-1 );

    }
   // cout << " found removal = " << removal << endl;
    const iter& a_new_begin =
      (*a_median <= *b_median) ? a_begin + removal : a_begin;
    const iter& a_new_end = 
      (*a_median <= *b_median) ? a_end : a_end - removal;
    const iter& b_new_begin =
      (*a_median <= *b_median) ? b_begin : b_begin + removal;
    const iter& b_new_end = 
      (*a_median <= *b_median) ? b_end - removal: b_end;
 /*   cout << "about to recurse a median = " << *a_median << " while b_median = " << *b_median << endl;
    for (iter i = a_new_begin; i != a_new_end; ++i) {
      cout << "a = " << *i << endl;
    }
    cout << endl;
    for (iter i = b_new_begin; i != b_new_end; ++i) {
      cout << "b = " << *i << endl;
    }
  */return find_median(a_new_begin, a_new_end, b_new_begin, b_new_end);
  }
}

int main() {
  vector<int> a_values;
  vector<int> b_values;
  int m, n;
  while (cin >> m >> n) {
    a_values.clear();
    b_values.clear();
    int temp;
    for (int i = 0; i < m; ++i) {
      cin >> temp;
      a_values.push_back(temp);
    }
      for (int i = 0; i < n; ++i) {
        cin >> temp;
        b_values.push_back(temp);
      }
    }
    auto calculated = find_median(a_values.begin(), a_values.end(), b_values.begin(), b_values.end());
    cout << fixed << setprecision(1) << calculated << endl;
  return 0;
}
