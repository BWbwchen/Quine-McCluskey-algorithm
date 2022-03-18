#include "terms.hpp"
using namespace std;

void Terms::expand(int index, vTerms ans) {
    if (index >= minterms.length()) {
        ans.push_back(Terms(minterms));
        return;
    } else if (minterms[index] != DONT_CARE) {
        expand(index + 1, ans);
        return;
    } else if (minterms[index] == DONT_CARE) {
        minterms[index] = '1';
        expand(index + 1, ans);
        minterms[index] = '0';
        expand(index + 1, ans);
        minterms[index] = '-';
    }
}

bool can_merge(const Terms &lhs, const Terms &rhs) {
    // TODO: why cannot I use operator overloading??
    if (lhs.numberOfDC == rhs.numberOfDC &&
        lhs.numberOfZero == rhs.numberOfZero) {
        return false;
    }
    int diff = 0;
    for (int i = 0; i < lhs.minterms.size(); ++i) {
        if (lhs.minterms[i] != rhs.minterms[i]) {
            diff++;
        }
    }
    return diff == 1;
}

Terms merge(const Terms &lhs, const Terms &rhs) {
    string new_minterms = lhs.minterms;
    for (int i = 0; i < new_minterms.size(); ++i) {
        if (lhs.minterms[i] != rhs.minterms[i]) {
            new_minterms[i] = DONT_CARE;
        }
    }
    return Terms(new_minterms);
}

bool cmpGroup(const Terms &lhs, const Terms &rhs) {
    return lhs.numberOfOne < rhs.numberOfOne;
}

bool cmpOrder(const Terms &lhs, const Terms &rhs) {
    return lhs.minterms < rhs.minterms;
}

// Need sorted vector
void remove_duplicate(vTerms v) {
    vector<Terms>::iterator it;
    it = std::unique(v.begin(), v.end());
    v.resize(std::distance(v.begin(), it));
}
