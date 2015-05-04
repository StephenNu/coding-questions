/**
  Write a function that takes a pattern and an input (as strings), and determines whether you have a match. Return 1 if it is a match, and 0 if it is not a match.

  The pattern can contain any characters, in any order.

  All words must be at least one character long. The input will be at least as long as the pattern.

  Distinct pattern characters must correspond to distinct input words. Pattern of "aba" will not match "redredred"

Examples:
Pattern is "abba", input is "redbluebluered", should return 1.

Pattern is "abba", input is "abcxyzxyzabc", should return 1.

Pattern is "aaaa", input is "redbluebluered", should return 0.

Your solution should run in O(2^n)

 **/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;
int check(const unordered_map<char, string>& patterns) {
  unordered_set<string> patt;
  for (const auto& pair : patterns) {
    auto it = patt.insert(pair.second);
    if (!it.second) {
      return 0;
    }
  }
  return 1;
}

int sub_word_match(const string& pattern, const string& input, unordered_map<char, string> patterns) {
  if (input.size() != 0) {
    if (pattern.size() == 0) {
      return 0;
    }
  } else if (pattern.size() == 0) {
      return check(patterns);
  }
  auto it = patterns.find(pattern[0]);
  if (it == patterns.end()) { // If we haven't seen this pattern before.
    // Try all possible sizes of that pattern.
    for (unsigned int i = 1; i <= input.size(); ++i) {
      string match(input.begin(), input.begin()+i);
      string new_input(input.begin()+i, input.end());
      string new_pattern(pattern.begin() + 1, pattern.end());
      patterns[pattern[0]] = match;
      if (sub_word_match(new_pattern, new_input, patterns)) {
        return check(patterns);
      }
    }
    return 0;
  } else { // we have seen this pattern
    const string& previous_pattern = it->second;
    if (previous_pattern.size() <= input.size()) {
      unsigned int i;
      for (i = 0; i < previous_pattern.size() && i < input.size(); ++i) {
        if (input[i] != previous_pattern[i]) {
          return 0;
        }
      }
      string new_input(input.begin()+i, input.end());
      string new_pattern(pattern.begin() + 1, pattern.end());
      return sub_word_match(new_pattern, new_input, patterns);
    } else {
      return 0;
    }
  }
}

int word_match(const string& pattern, const string& input) {
  if (pattern.size() == 1) {
    return 1;
  } else {
    unordered_map<char, string> patterns;
    return sub_word_match(pattern, input, patterns);
  }
}

int main() {
  string pattern;
  string input;
  while (cin >> pattern >> input) {
    cout << word_match(pattern, input) << endl;
  }
  return 0;
}
