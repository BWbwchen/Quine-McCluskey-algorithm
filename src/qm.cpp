#include "qm.hpp"
using namespace std;

void QM::expand_terms(vector<Terms> &input, vector<Terms> &output) {
    for (auto t : input) {
        auto expanded = t.expand_dont_care();
        // cout << expanded.size() << endl;
        output.insert(output.end(), expanded.begin(), expanded.end());
    }
}

void QM::group_minterms() {
    vector<Terms> tmp;
    for (int i = 0; i < expand_minterms.size() - 1; ++i) {
        if (expand_minterms[i].diffGroup(expand_minterms[i + 1])) {
            tmp.push_back(expand_minterms[i]);
            implicant.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(expand_minterms[i]);
        }
    }
    if (tmp.size() != 0) {
        tmp.push_back(expand_minterms.back());
        implicant.push_back(tmp);
    }

    return;
}


void QM::k_map() {
    // TODO: Need collect the unused implicant into prime implicant.
    bool done = false;
    vector<vector<Terms>> new_implicant;
    vector<Terms> tmp;
    // int count = 1;
    while (!done) {
        // cout << count++ << endl;
        done = true;

        for (int group = 0; group < implicant.size() - 1; ++group) {
            auto &group1 = implicant[group];
            for (int i = 0; i < group1.size(); ++i) {
                auto &group2 = implicant[group + 1];
                for (int j = 0; j < group2.size(); ++j) {
                    if (can_merge(group1[i], group2[j])) {
                        done = false;
                        tmp.push_back(merge(group1[i], group2[j]));
                        group1[i].use();
                        group2[j].use();
                    }
                }
            }
            sort(tmp.begin(), tmp.end(), cmpOrder);
            remove_duplicate(tmp);
            new_implicant.push_back(tmp);
            tmp.clear();
        }

        collect_unused_prime_implicant();

        if (!done) {
            implicant = new_implicant;
            new_implicant.clear();
        }
    }
}

void QM::collect_unused_prime_implicant() {
    for (auto g : implicant) {
        for (auto m : g) {
            if (m.is_unused()) {
                prime_implicant.push_back(m);
            }
        }
    }
}

int QM::get_literal_count(vector<Terms> &v) {
    int ans = 0;
    for (auto t : v) {
        ans += t.get_literal_count();
    }
    return ans;
}
