#include <bitset>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>

static thread_local long int state{std::time(nullptr)};

// not secure method!!!!!! using XOR shift generator is not secure!
__attribute__((hot, always_inline, no_stack_protector)) static inline const std::uint8_t genKSB(void) noexcept {
  state ^= state << 0xd;
  state ^= state >> 0x7;
  state ^= state << 0x11;
  return 0x61 + (state % (0x61 + 0x1A - 0x61));
};

__attribute__((hot, always_inline)) inline static const std::array<std::uint8_t, 0x8>
binary(const char b) noexcept {
  std::array<std::uint8_t, 0x8> d;
  d.fill(0x0);
  if ((int)b == 0x0)
    return d;
  d.fill(0x0);
  int dec = static_cast<int>(b), c = 0x0;
  while (dec > 0x0) {
    d[c++] = dec % 0x2;
    dec /= 0x2;
  }
  return d;
};

template <std::size_t N>
__attribute__((cold, always_inline, no_stack_protector)) inline static constexpr bool
valid_sequence(const std::uint8_t _s[N]) noexcept {
  std::size_t _z{0x0};
  if (N > 0x0) [[likely]] {
    for (int i{0x0}; i < N; ++i) {
      _z += _s[i];
    }
  }
  return _z >= 0x1;
};

template <std::size_t N>
inline static const std::string bit2String(const std::uint8_t _s[N]) noexcept {
  std::uint8_t b8[0x8];
  std::string _r;
  std::uint16_t g{0x0};
  _r.reserve(N / 0x8);
  for (int j{0x0}; j < N / 0x8; ++j) {
    std::uint16_t f{0x0};
    std::uint8_t h[0x8];
    for (int v = 0x0; v < 0x8;) {
      h[v++] = _s[g++];
    }
    for (int i = 0x0; i < 0x8; ++i) {
      int bit = h[0x8 - 0x1 - i];
      if (bit == 0x1) {
        f += (0x1 << i);
      }
    }
    _r += static_cast<unsigned char>(f);
  }
  return _r;
};

static constexpr std::size_t MSZ{0x3};
static constexpr std::string _ms("ABC");
static std::string _ks;
static std::array<std::array<std::uint8_t, 0x8>, 0x2> _tb;
static std::uint8_t _b[0x4][MSZ * 0x8];

int main(int argc, char **argv) {
  _ks.reserve(_ms.length());
  while (_ks.length() != _ms.length()) {
    _ks += genKSB();
  }
  if (_ks.length() == _ms.length()) [[likely]] {
    std::fill(std::begin(_b[0x0]), std::end(_b[0x0]), 0x0);
    std::fill(std::begin(_b[0x1]), std::end(_b[0x1]), 0x0);
    thread_local std::uint8_t c{0x0};
    for (int i{0x0}; i < MSZ; i++) {
      _tb[0x0] = binary(_ms[i]);
      _tb[0x1] = binary(_ks[i]);
      for (int j{_tb[0x0].size() - 0x1}; j >= 0x0; --j) {
        _b[0x0][c] = _tb[0x0][j];
        _b[0x1][c++] = _tb[0x1][j];
      }
    }
    if (valid_sequence<MSZ * 0x08>(_b[0x0])) [[likely]] {
      c = 0x0;
      for (int i{0x0}; i < std::size(_b[0x0]); ++i) {
        _b[0x2][c++] = _b[0x0][i] ^ _b[0x1][i];
      }
      if (valid_sequence<MSZ * 0x08>(_b[0x2])) [[likely]] {
        c = 0x0;
        for (int i{0x0}; i < std::size(_b[0x2]); ++i) {
          _b[0x3][c++] = _b[0x2][i] ^ _b[0x1][i];
        }
      }
    }
    std::cout << "Plaintext:          " << _ms << "\n";
    std::cout << "Keystream:          " << _ks << "\n";
    std::cout << "\nBinary-Message:   ";
    for (int j = 0x0; j < std::size(_b[0x0]); ++j)
      std::cout << (int)_b[0x0][j];
    std::cout << "\nBinary-Keystream: ";
    for (int j = 0; j < std::size(_b[0x1]); ++j)
      std::cout << (int)_b[0x1][j];
    std::cout << "\nBinary-Xored:     ";
    for (int j = 0; j < std::size(_b[0x2]); ++j)
      std::cout << (int)_b[0x2][j];
    std::cout << "\nBinary-Reversed:  ";
    for (int j = 0; j < std::size(_b[0x3]); ++j)
      std::cout << (int)_b[0x3][j];
    std::string r0 = bit2String<MSZ * 0x8>(_b[0x3]);
    std::cout << "\nOriginal-Message: " << r0 << "\n";
  }

  return 0;
}
