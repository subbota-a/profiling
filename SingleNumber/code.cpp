#include "code.h"

using namespace std;

int Solution1::singleNumber(vector<int> &nums) {
  vector<int> one_counts(32, 0);
  for (auto n : nums) {
    for (int i = 0; i < 32; ++i) {
      if (n & 0x1) {
        one_counts[i]++;
      }
      n >>= 1;
    }
  }
  int result = 0;
  for (int i = 31; i >= 0; --i) {
    result <<= 1;
    result = result | ((one_counts[i] % 3 == 0) ? 0 : 1);
  }
  return result;
}

int Solution2::singleNumber(vector<int> &nums) {
  vector<int> one_counts(32, 0);

  for (auto n : nums) {
    for (int i = 0; i < 32; ++i) {
      one_counts[i] += (n >> i) & 1;
    }
  }

  int result = 0;
  for (int i = 31; i >= 0; --i) {
    result <<= 1;
    result |= (one_counts[i] % 3 == 0) ? 0 : 1;
  }

  return result;
}

int Solution3::singleNumber(vector<int> &nums) {
  int result = 0;

  for (int i = 0; i < 32; ++i) {
    int sum = 0;
    for (int num : nums) {
      sum += (num >> i) & 1;
    }
    result |= (sum % 3) << i;
  }

  return result;
}

int Solution4::singleNumber(vector<int> &nums) {
  int ones = 0, twos = 0;
  for (int n : nums) {
    ones = (ones ^ n) & ~twos;
    twos = (twos ^ n) & ~ones;
  }
  return ones;
}
