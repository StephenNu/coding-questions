#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdio>
using namespace std;

int sol_find_marble(const vector<int>& marbles);

template <class Iter>
int sol_find_marble(const Iter& b, const Iter& e);

template <class Iter>
Iter mid(Iter first, Iter last);
static int count_calls = 0;
int heavier(const vector<int>& a, const vector<int>& b) {
  ++count_calls;
  auto a_w = accumulate(begin(a), end(a), 0);
  auto b_w = accumulate(begin(b), end(b), 0);
  if (a_w == b_w) {
    return 0;
  } else if (a_w > b_w) {
    return 1;
  } else {
    return 2;
  }
}
template <class T>
int heavier(T a_b, T a_e, T b_b, T b_e) {
  ++count_calls;
  auto a_w = accumulate(a_b, a_e, 0);
  auto b_w = accumulate(b_b, b_e, 0);
  if (a_w == b_w) {
    return 0;
  } else if (a_w > b_w) {
    return 1;
  } else {
    return 2;
  }
}

// David V

/*
    Translates the iterator which points to the heavy marble into an index.
    *NOTE*: This method of iterator subtraction will only work on sequence
            containers which are stored contiguously in memory.
            (ie: vector, array)
*/

int find_index(std::vector<int> marbles);

template <class Iter>
Iter find_marble(Iter first, Iter last);

template <class Iter>
Iter partition1(Iter first, Iter last, int len);

int find_index(std::vector<int> marbles) {
    auto iter = find_marble(std::begin(marbles), std::end(marbles));
    return iter - std::begin(marbles);
}

/*
    Returns an iterator to the heavy marble in a sequence of marble weights
*/
template <class Iter>
Iter find_marble(Iter first, Iter last) {
    auto len = std::distance(first, last);
    if (len <= 3) {
        if (len == 2) {
            int n = heavier(first, std::next(first), std::next(first), last);
            if (n == 1)
                return first;
            return std::next(first);
        } else {
            Iter m = partition1(first, last, len);
            int n = heavier(first, m, m, std::next(m));
            if (n == 1)
                return first;
            else if (n == 2)
                return m;
            return std::next(m);
        }
    }
    /*
        Split the list into 3 (relatively) equal portions.
        portion 1: [first, end_1)
        portion 2: [end_1, end_2)
        portion 3: [end_2, last)
    */

    Iter end_1 = partition1(first, last, len);
    Iter end_2 = partition1(end_1, last, len);

    int n = heavier(first, end_1, end_1, end_2);

    if (n == 2)
        return find_marble(end_1, end_2);   // Marble is in middle portion
    else if (n == 1)
        return find_marble(first, end_1);   // Marble is in first portion
    return find_marble(end_2, last);        // Marble is in last portion
}

// Function used to split the list into 3 portions
template <class Iter>
Iter partition1(Iter first, Iter last, int len) {
    for (int i = 0; i < std::ceil(len/3.0) && first != last; ++i)
        ++first;
    return first;
}

// Quinn P
//
template <typename T>
T heavy_marble(T first, T last);
template <typename T>
std::pair<T, T> third(T first, T last);
template <typename T>
int heavy_marble_index_to_make_nusko_happy(T first, T last);

template <typename T>
int heavy_marble_index_to_make_nusko_happy(T first, T last) {
    auto i = heavy_marble(first, last);
    return std::distance(first, i);
}

template <typename T>
std::pair<T, T> thirds(T first, T last) {
    auto size = std::distance(first, last);
    auto i = first + std::ceil(size / 3.0);
    auto j = i + std::ceil(size / 3.0);
    return std::make_pair(i, j);
}

template <typename T>
T heavy_marble(T first, T last) {
    auto size = std::distance(first, last);
    if (size == 1)
        return first;
    auto splits = thirds(first, last);
    auto r = heavier(first, splits.first, splits.first, splits.second);

#if DEBUG
    std::cout << "first split: ";
    for (auto i = first; i != splits.first; ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "second split: ";
    for (auto i = splits.first; i != splits.second; ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "third split: ";
    for (auto i = splits.second; i != last; ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
    std::cout << "----------------" << std::endl;
    std::string wait;
    std::cin >> wait;
#endif
    if (r == 0)
        return heavy_marble(splits.second, last);
    else if (r == 1)
        return  heavy_marble(first, splits.first);
    else
        return heavy_marble(splits.first, splits.second);
}



// Main
int main() {
  int counter = 1;
  mt19937 generator;
  std::uniform_int_distribution<int> distributionN(1,60);
  std::uniform_int_distribution<int> dist(1,10);
  std::uniform_int_distribution<int> dist_larger(1,10);
  while (true)
  {
  vector<int> marbles;
  int N = distributionN(generator);
  std::uniform_int_distribution<int> dist_index(1,N);
  cout << N << endl;
  int same = dist(generator);
  int different = dist_larger(generator)+same;
  int index = dist_index(generator) - 1;
  cout << index << endl;
  for (int i = 0; i < N; ++i) {
    if (i == index) {
      marbles.emplace_back(different);
    } else {
      marbles.emplace_back(same);
    }
  }
  auto correct_idx = sol_find_marble(marbles.begin(), marbles.end());
  count_calls = 0;
  auto i = find_index(marbles);
  cout << endl << "test case " << (counter++) << endl;
  cout << "max found by solution at index: " << i << endl;
  cout << "max found by correct solution at index: " << correct_idx << endl;
  cout << "number of calls: " << count_calls << " vs " << (log(N)/log(3)) << endl;
    if ((count_calls != ceil(log(N)/log(3)) && count_calls != floor(log(N)/log(3))) || correct_idx != i) {
      cout << "test case failed size = " << N << endl;
      for (int i = 0; i < N; ++i) {
        printf(" %2d", i);
      }
      cout << endl;
      for (const auto& e : marbles) {
        printf(" %2d", e);
      }
      cout << endl;
      assert(false);
    }
  }
  return 0;
}





































// correct solution
int sol_find_marble(const vector<int>& marbles) {
  auto partition = (marbles.size()%3 == 2) ? marbles.size()/3 + 1 : marbles.size();
  if (marbles.size() == 1) {
    return 0;
  }
  auto result = heavier(vector<int>(marbles.begin(), marbles.begin()+partition), 
                        vector<int>(marbles.begin()+partition, marbles.begin() + partition*2));
  if (result == 0) {
    return partition*2 + sol_find_marble(vector<int>(marbles.begin() + partition*2, marbles.end()));
  } else if (result == 1) {
    return sol_find_marble(vector<int>(marbles.begin(), marbles.begin()+partition));
  } else {
    return partition + sol_find_marble(vector<int>(marbles.begin()+partition, marbles.begin() + partition*2));
  }
  return -1;
}
template <class Iter>
int sol_find_marble(const Iter& b, const Iter& e) {
  auto partition = (distance(b,e)%3 == 2) ? distance(b,e)/3 + 1 : distance(b,e)/3;
  if (distance(b,e) == 1) {
    return 0;
  }
  auto result = heavier(b, b+partition, b+partition, b + partition*2);
  if (result == 0) {
    return partition*2 + sol_find_marble(b + partition*2, e);
  } else if (result == 1) {
    return sol_find_marble(b, b+partition);
  } else {
    return partition + sol_find_marble(b+partition, b + partition*2);
  }
  return -1;
}
