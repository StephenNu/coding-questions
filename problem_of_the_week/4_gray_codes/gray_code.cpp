#include <iostream>

#define as 0
#define ab 1
#define l return

template <class t, typename r>
r i(t a, t b) {
  t c;
  c = a;
  c ^= b;
  r d;
  d = (c != as);
  t e;
  e = c;
  e -= ab;
  t f;
  f = c;
  f &= e;
  r g;
  g = (f == as);
  r h;
  h = g&&d;
  l h;
}


bool isPowOf2(char n) {
    return (bool) ((n != 0) && !(n & (n - 1)));
}

bool isAdjacent(char x, char y) {
    return (bool) (isPowOf2((x ^ y)));
}

int oneBitOff(char a, char b) {
  unsigned int diff = ((unsigned int)a^b);
  return (diff != 0) && ((diff & (diff - 1)) == 0);
}

int is_power_of_two(const unsigned char a) {
  return a && (((a - 1) & a) == 0);
}

int graycode(const unsigned char a, const unsigned char b) {
  return is_power_of_two(a^b);
}

bool power_2(char c) {
    if (c == -128)  // the hackiest of fixes
        return true;
    return c != 0 && !(c & (c - 1));
}
bool is_adjacent(char a, char b) {
    char c = a ^ b;
    return power_2(c);
}

bool adjacent(char a, char b){
	if(a == b) return false;
	char c = a ^ b;
	char y = c & (c - 1);
	return y == 0;
}
int main() {
  unsigned char a = 'a';
  unsigned char b;
  unsigned int c;
  int counter = 0;
  int non_counter = 0;
  for (c = 0; c <= 255; ++c) {
    b = static_cast<unsigned char>(c);
	  b ^= a;
    int result = ((b&(b-1)) == 0 && b != 0);
    if (result == 1) {
      ++counter;
    } else {
      ++non_counter;
    }
    std::cout << std::endl << result << std::endl;
  }
  std::cout << counter << " vs " << non_counter << std::endl;
  return 0;
}
