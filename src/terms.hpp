#include <bits/stdc++.h>
#include <iterator>
using namespace std;
#define DONT_CARE '-'

class Terms;

using vTerms = vector<Terms> &;
using vvTerms = vector<vector<Terms>> &;

bool cmpGroup(const Terms &, const Terms &);
bool cmpOrder(const Terms &, const Terms &);
void remove_duplicate(vTerms);

class Terms {
private:
    string minterms;
    // number of don't care
    int numberOfOne;
    int numberOfDC;
    int numberOfZero;

    int value;

    bool used;

    void expand(int, vTerms);
    friend bool can_merge(const Terms &, const Terms &);
    friend Terms merge(const Terms &, const Terms &);
    friend void remove_duplicate(vTerms);
    friend bool cmpGroup(const Terms &, const Terms &);
    friend bool cmpOrder(const Terms &, const Terms &);

public:
    Terms() {
        minterms = "";
        used = false;
    }

    Terms(string s) {
        minterms = s;
        numberOfDC = numberOfOne = numberOfZero = 0;
        used = false;
        for (int i = 0; i < minterms.length(); ++i) {
            if (minterms[i] == DONT_CARE) {
                numberOfDC++;
            } else if (minterms[i] == '1') {
                numberOfOne++;
            } else {
                numberOfZero++;
            }
        }
        if (numberOfDC == 0) {
            value = stoi(minterms, 0, 2);
        }
    }

    void Output() {
        cout << minterms /* << " its # of dc is " << numberOfDC */ << endl;
    }

    int getNOfDC() { return numberOfDC; }
    int getNOfOne() { return numberOfOne; }
    int getNOfZero() { return numberOfZero; }
    int getValue() { return value; }

    bool diffGroup(const Terms &rhs) { return numberOfOne != rhs.numberOfOne; }

    vector<Terms> expand_dont_care() {
        vector<Terms> ans;

        if (numberOfDC == 0)
            return {*this};

        expand(0, ans);
        return ans;
    }
    bool operator<(const Terms &rhs) { return numberOfOne < rhs.numberOfOne; }
    bool operator==(const Terms &rhs) { return this->minterms == rhs.minterms; }
    bool operator!=(const Terms &rhs) { return !(*this == rhs); }

    void use() { used = true; }
    bool is_unused() { return !used; }
    int get_literal_count() { return numberOfOne + numberOfZero; }
};
