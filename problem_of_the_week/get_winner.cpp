#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <functional>

using namespace std;

vector<std::pair<string, int>> november_contestents = {
  {"Anthony Deschamps descham1@uwindsor.ca", 2},
  {"Quinn Perfetto <perfettq@uwindsor.ca>", 4},
  {"David Valleau <valleaud@uwindsor.ca>", 2},
  {"Joshua Hompoth <hompoth@cs.uwindsor.ca>", 1},
  {"Efron Berlian <berliane@uwindsor.ca>", 1},
  {"Jeremy High <highj@uwindsor.ca>", 1}
}; // Winner is Quinn Perfetto <perfettq@uwindsor.ca>.

vector<std::pair<string, int>> march_contestents = {
  {"Quinn Perfetto <perfettq@uwindsor.ca>", 4},
  {"David Valleau <valleaud@uwindsor.ca>", 3},
  {"Chris Bennett <benne112@uwindsor.ca>", 1},
  {"Jeremy High <highj@uwindsor.ca>", 2}
}; // Winner is Jeremy High <highj@uwindsor.ca>.

const auto& current_contestents = march_contestents;


const string get_winner(const vector<string>& winners) {
  seed_seq seq{time(NULL)};
  vector<uint32_t> seeds{2};
  seq.generate(seeds.begin(), seeds.end());
  std::default_random_engine generator;
  generator.seed(seeds[0]);
  std::uniform_int_distribution<unsigned int> dist(0, winners.size()-1) ;
  auto size_gen = std::bind ( dist, generator );
  return winners[size_gen()];
}


int main() {
  std::vector<int> real;
  vector<string> winners;
  for (const auto& e : current_contestents) {
    for (int i = 0; i < e.second; ++i) {
      winners.push_back(e.first);
    }
  }
  cout << get_winner(winners) << endl;
  return 0;
}
