#include <bits/stdc++.h>
#include "qm.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (argc != 3) {
        cout << "**************** [Error] ***************" << endl;
        cout << "*                                      *" << endl;
        cout << "*  [Usage] ./pa1 case0x.in case0x.out  *" << endl;
        cout << "*                                      *" << endl;
        cout << "**************** [Error] ***************" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    freopen(inputFile.c_str(), "r", stdin);

    int nv, terms;
    cin >> nv >> terms;

    QM q(nv);
    q.Input_minterms(terms);


    q.Generate_prime_implicant();
    q.Minmum_covering();


    freopen(outputFile.c_str(), "w", stdout);
    q.Output_result();


    return 0;
}
