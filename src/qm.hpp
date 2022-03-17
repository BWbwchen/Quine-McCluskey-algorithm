#include <bits/stdc++.h>
#include "terms.hpp"
using namespace std;

class QM {
private:
    int number_of_variable;
    // TODO: maybe use other array
    vector<Terms> input_minterms;
    vector<Terms> expand_minterms;
    vector<vector<Terms>> implicant;
    int expand_minterms_size;

    void expand_terms();
    void group_minterms();
    void k_map();
    friend void remove_duplicate(vector<Terms> &);

public:
    QM(int nv) {
        // TODO: estimate the number of expanded minterms
        number_of_variable = nv;
    }

    void Input_minterms(int terms) {
        string tmp;
        for (int i = 0; i < terms; ++i) {
            cin >> tmp;
            input_minterms.push_back(Terms(tmp));
        }
    }

    void Generate_prime_implicant() {
        expand_terms();
        expand_minterms_size = expand_minterms.size();
        sort(expand_minterms.begin(), expand_minterms.end(), cmpOrder);

        remove_duplicate(expand_minterms);

        sort(expand_minterms.begin(), expand_minterms.end(), cmpGroup);

        group_minterms();
        k_map();
    }

    void Minmum_covering() {
        // TODO:
    }

    void Output_result() {
        int mintermsSize = 0;
        for (auto s : input_minterms) {
            mintermsSize += (1 << s.getNOfDC());
            s.Output();
        }
        cout << "========================================" << endl;
        if (expand_minterms_size == mintermsSize) {
            cout << "Expanded successfully, total : " << mintermsSize << endl;
        } else {
            cout << "Expanded failed, minterms.size() == "
                 << expand_minterms_size << " mintermsSize == " << mintermsSize
                 << endl;
        }
        assert(expand_minterms_size == mintermsSize);

        for (auto m : implicant) {
            cout << "Group with size " << m[0].getNOfOne() << endl;
            for (auto s : m) {
                s.Output();
            }
        }
    }
};
