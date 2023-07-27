// https://gist.github.com/halloweeks/8bb0a745229b4674aaacffc7a23e5956

#include <iostream>
#include <string.h>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <zlib.h>

class myzlib {
public:
  static std::string compress(const std::string&, int);
  static std::string decompress(const std::string&);

private:
  myzlib();
  ~myzlib();
};