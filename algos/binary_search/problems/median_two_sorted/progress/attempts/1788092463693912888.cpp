#include <climits>
#include <vector>
using namespace std;

double findMedianSortedArrays(const vector<int> &first,
                              const vector<int> &second) {
  const vector<int> &A = (first.size() <= second.size()) ? first : second;
  const vector<int> &B = (first.size() <= second.size()) ? second : first;

  int n = A.size();
  int m = B.size();

  int low = 0, high = n, cutA, cutB;
  double Aleft, Aright, Bleft, Bright;

  while (low <= high) {
    cutA = low + (high - low) / 2;
    cutB = (n + m + 1) / 2 - cutA;

    Aleft = cutA == 0 ? INT_MIN : A[cutA - 1];
    Aright = cutA == n ? INT_MAX : A[cutA];

    Bleft = cutB == 0 ? INT_MIN : B[cutB - 1];
    Bright = cutB == m ? INT_MAX : B[cutB];

    if ((Aleft <= Bright) && (Bleft <= Aright)) {
      if ((n + m) % 2 == 1)
        return max(Aleft, Bleft);
      else
        return (max(Aleft, Bleft) + min(Aright, Bright)) / 2;
    } else if (Aleft > Bright) {
      high = cutA - 1;
    } else {
      low = cutA + 1;
    }
  }

  return 0.0;
}
