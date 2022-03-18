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
    vector<Terms> prime_implicant;
    int expand_minterms_size;

    void expand_terms(vector<Terms> &, vector<Terms> &);
    void group_minterms();
    void k_map();
    void collect_unused_prime_implicant();
    int get_literal_count(vector<Terms> &);
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
        expand_terms(input_minterms, expand_minterms);
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
        // int mintermsSize = 0;
        // for (auto s : input_minterms) {
        //     mintermsSize += (1 << s.getNOfDC());
        //     s.Output();
        // }
        // cout << "========================================" << endl;
        // if (expand_minterms_size == mintermsSize) {
        //     cout << "Expanded successfully, total : " << mintermsSize <<
        //     endl;
        // } else {
        //     cout << "Expanded failed, minterms.size() == "
        //          << expand_minterms_size << " mintermsSize == " <<
        //          mintermsSize
        //          << endl;
        // }
        // assert(expand_minterms_size == mintermsSize);

        cout << get_literal_count(prime_implicant) << endl;
        cout << prime_implicant.size() << endl;
        for (auto p : prime_implicant) {
            p.Output();
        }
    }
};
