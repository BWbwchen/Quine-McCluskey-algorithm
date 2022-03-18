#include "qm.hpp"
using namespace std;

void QM::expand_terms(vTerms input, vTerms output) {
    for (auto t : input) {
        auto expanded = t.expand_dont_care();
        // cout << expanded.size() << endl;
        output.insert(output.end(), expanded.begin(), expanded.end());
    }
}

void QM::group_minterms(vTerms input, vvTerms output) {
    vector<Terms> tmp;
    for (int i = 0; i < input.size() - 1; ++i) {
        if (input[i].diffGroup(input[i + 1])) {
            tmp.push_back(input[i]);
            output.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(input[i]);
        }
    }
    if (tmp.size() != 0) {
        tmp.push_back(input.back());
        output.push_back(tmp);
    }

    return;
}


void QM::k_map(vvTerms in_implicant, vTerms p_implicant) {
    // TODO: Need collect the unused implicant into prime implicant.
    bool done = false;
    vector<vector<Terms>> new_implicant;
    vector<Terms> tmp;
    // int count = 1;
    while (!done) {
        // cout << count++ << endl;
        done = true;

        for (int group = 0; group < in_implicant.size() - 1; ++group) {
            auto &group1 = in_implicant[group];
            for (int i = 0; i < group1.size(); ++i) {
                auto &group2 = in_implicant[group + 1];
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

        collect_unused_prime_implicant(in_implicant, p_implicant);

        if (!done) {
            in_implicant = new_implicant;
            new_implicant.clear();
        }
    }
}

void QM::collect_unused_prime_implicant(vvTerms in_implicant,
                                        vTerms p_implicant) {
    for (auto g : in_implicant) {
        for (auto m : g) {
            if (m.is_unused()) {
                p_implicant.push_back(m);
            }
        }
    }
}

int QM::get_literal_count(vTerms v) {
    int ans = 0;
    for (auto t : v) {
        ans += t.get_literal_count();
    }
    return ans;
}
