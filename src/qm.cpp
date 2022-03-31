#include "qm.hpp"
#include <algorithm>
using namespace std;

void QM::expand_terms(vTerms input, vTerms output) {
    for (auto t : input) {
        auto expanded = t.expand_dont_care();
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
    tmp.push_back(input.back());
    output.push_back(tmp);

    return;
}


void QM::k_map(vvTerms in_implicant, vTerms p_implicant) {
    bool done = false;
    vector<vector<Terms>> new_implicant;
    vector<Terms> tmp;

    while (!done) {
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

void QM::petrick_method(vTerms p_implicant, vTerms e_implicant) {
    // value -> {id of prime implicant}
    unordered_map<int, vector<int>> ptable;
    vector<Terms> tmp;
    vector<vector<Terms>> p_expanded;
    // implicant id -> how many value it contribute
    vector<pair<int, int>> contribution;
    vector<bool> included(p_implicant.size(), false);

    for (int i = 0; i < p_implicant.size(); ++i) {
        tmp = p_implicant[i].expand_dont_care();
        contribution.push_back({i, tmp.size()});
        p_expanded.push_back(tmp);
        for (auto t : tmp) {
            int key = t.getValue();
            if (ptable.count(key) != 0) {
                ptable[key].push_back(i);
            } else {
                ptable[key] = {i};
            }
        }
    }

    /*
    // find the implicant that MUST in the essential implicant
    vector<int> to_delete;
    for (auto _p : ptable) {
        auto v = _p.first;
        auto &terms = _p.second;
        if (terms.size() == 1) {
            if (!included[terms[0]]) {
                e_implicant.push_back(p_implicant[terms[0]]);
                included[terms[0]] = true;
            }
            to_delete.push_back(v);
        }
    }

    for (auto r : to_delete) {
        for (auto i : ptable[r]) {
            contribution[i]--;
        }
        ptable.erase(r);
    }
    */

    // find the implicant that maybe in the essential implicant
    vector<int> only_you(contribution.size(), 0);
    for (int i = 0; i < p_expanded.size(); ++i) {
        tmp = p_expanded[i];
        for (auto r : tmp) {
            if (ptable[r.getValue()].size() == 1) {
                only_you[i]++;
            }
        }
    }
    while (!ptable.empty()) {
        int max_contributor =
            max_element(
                contribution.begin(), contribution.end(),
                [&](pair<int, int> A, pair<int, int> B) {
                    auto a = p_implicant[A.first];
                    auto b = p_implicant[B.first];
                    auto a_cost = a.getNOfOne() + a.getNOfZero();
                    auto b_cost = b.getNOfOne() + b.getNOfZero();
                    double a_cost_ratio = (double) A.second / (double) a_cost;
                    double b_cost_ratio = (double) B.second / (double) b_cost;
                    if (A.second != 0 && B.second != 0) {
                        double a_only_ratio =
                            (double) only_you[A.first] / (double) A.second;
                        double b_only_ratio =
                            (double) only_you[B.first] / (double) B.second;
                        if (A.second == B.second) {
                            if (a.getNOfDC() != b.getNOfDC())
                                return a.getNOfDC() < b.getNOfDC();
                            else
                                return a_only_ratio < b_only_ratio;
                        } else {
                            return A.second < B.second;
                        }
                    } else {
                        return A.second < B.second;
                    }
                }) -
            contribution.begin();
        if (!included[max_contributor]) {
            e_implicant.push_back(p_implicant[max_contributor]);
            included[max_contributor] = true;
        }
        tmp = p_expanded[max_contributor];

        for (auto r : tmp) {
            if (ptable[r.getValue()].size() == 1) {
                only_you[max_contributor]--;
            }
            for (auto i : ptable[r.getValue()]) {
                contribution[i].second--;
            }
            ptable.erase(r.getValue());
        }
    }

    return;
}
