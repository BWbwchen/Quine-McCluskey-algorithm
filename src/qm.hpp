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
    vector<Terms> essential_implicant;
    int expand_minterms_size;

    void expand_terms(vTerms, vTerms);
    void group_minterms(vTerms, vvTerms);
    void k_map(vvTerms, vTerms);
    void collect_unused_prime_implicant(vvTerms, vTerms);
    int get_literal_count(vTerms);
    void petrick_method(vTerms, vTerms);
    friend void remove_duplicate(vTerms);

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
        group_minterms(expand_minterms, implicant);

        k_map(implicant, prime_implicant);
    }

    void Minmum_covering() {
        // TODO:
        // petrick_method(prime_implicant, essential_implicant);
        // vector[binary represent][which minterms] = x
        // check vector[i] == 1
        //      yes, include vector[i]'s minterms
        //          mark done the minterms contain vector[i]
        // Choose the max number of minterms
        //
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
        // cout << get_literal_count(essential_implicant) << endl;
        // cout << essential_implicant.size() << endl;
        for (auto p : prime_implicant) {
            // for (auto p : essential_implicant) {
            p.Output();
        }
    }
};
