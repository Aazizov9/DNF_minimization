#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int n, len;
vector<string> v[10];
string toBin(int m) {
    string s;
    for (int i = 0; i < len; i++) {
        s = (m & 1 ? "1" : "0") + s;
        m >>= 1;
    }
    return s;
}
string concated(int n, int ind1, int ind2) {
    //cout << "concat: " << v[n][ind1] << " - " << v[n][ind2] << " = ";
    int x = 0, k = 0;
    string s;
    for (int i = 0; i < len; i++) {
        if (v[n][ind1][i] != '3' && v[n][ind2][i] != '3') {
            k++;
            if (v[n][ind1][i] == v[n][ind2][i]) s += v[n][ind1][i], x++;
            else s += '3';
        }
        else {
            s += '3';
        }
    }
    if (k != n || x != n - 1) s = '.';
    //cout << "\ts= " << s << " -  " << x << endl;
    return s;
}

void concat(int n) {
    vector<bool> used(v[n].size());
    for (int i = 0; i < v[n].size(); i++) {
        for (int j = i + 1; j < v[n].size(); j++) {
            string x = concated(n, i, j);
            if (x[0] != '.') {
                used[i] = used[j] = 1;
                v[n - 1].push_back(x);
            }
        }
    }
    vector<string> temp;
    for (int i = 0; i < v[n].size(); i++) {
        if (!used[i]) {
            temp.push_back(v[n][i]);
        }
    }
    v[n] = temp;

    temp.clear();
    bool bn;
    for (int i = 0; i < v[n - 1].size(); i++) {
        bn = 0;
        for (int j = 0; j < i; j++) {
            if (v[n - 1][i] == v[n - 1][j]) bn = 1;
        }
        if (!bn) temp.push_back(v[n - 1][i]);
    }
    v[n - 1] = temp;
}

int main(int argc, char* argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open(argv[1]);
    fout.open(argv[2]);
    string s;
    fin >> n >> len;
    fin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            v[len].push_back(toBin(i));
        }
    }
    vector<string> ans;
    for (int i = len; i >= 1; i--) {
        concat(i);
        for (auto j : v[i]) ans.push_back(j);
    }
    sort(ans.begin(), ans.end());
    fout << len << " " << ans.size() << endl;
    for (auto i : ans) {
        for (int j = 0; j < i.size(); j++) {
            if (i[j] == '3') fout << '*';
            else fout << i[j];
        }
        fout << endl;
    }
    return 0;
}