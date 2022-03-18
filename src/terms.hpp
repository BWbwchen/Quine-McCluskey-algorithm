#include <bits/stdc++.h>
#include <iterator>
using namespace std;
#define DONT_CARE '-'

class Terms {
private:
    string minterms;
    // number of don't care
    int numberOfOne;
    int numberOfDC;
    int numberOfZero;

    bool used;

    void expand(int, vector<Terms> &);
    friend bool can_merge(const Terms &, const Terms &);
    friend Terms merge(const Terms &, const Terms &);
    friend void remove_duplicate(vector<Terms> &);
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
    }

    void Output() {
        cout << minterms /* << " its # of dc is " << numberOfDC */ << endl;
    }

    int getNOfDC() { return numberOfDC; }
    int getNOfOne() { return numberOfOne; }

    bool diffGroup(const Terms &rhs) { return numberOfOne != rhs.numberOfOne; }

    vector<Terms> expand_dont_care() {
        vector<Terms> ans;

        if (numberOfDC == 0)
            return {*this};

        expand(0, ans);
        return ans;
    }
    bool operator<(const Terms &rhs) {
        // TODO:
        return numberOfOne < rhs.numberOfOne;
    }
    bool operator==(const Terms &rhs) {
        // TODO:
        return this->minterms == rhs.minterms;
    }
    bool operator!=(const Terms &rhs) {
        // TODO:
        return !(*this == rhs);
    }

    void use() { used = true; }
    bool is_unused() { return !used; }
    int get_literal_count() { return numberOfOne + numberOfZero; }
};

bool cmpGroup(const Terms &, const Terms &);
bool cmpOrder(const Terms &, const Terms &);
void remove_duplicate(vector<Terms> &);