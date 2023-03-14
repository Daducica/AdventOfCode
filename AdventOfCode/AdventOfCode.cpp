#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main (int argc, char** argv)
{
    std::ifstream inf ("day8.txt");
    std::string l;
    std::vector<std::vector<int>> m;
    while (std::getline (inf, l)) {
        std::vector<int> t;
        for (int i = 0; i < l.size (); i++) {
            t.push_back (l[i] - '0');
        }
        m.push_back (t);
    }

    int vt = 0;
    for (int i = 0; i < m.size (); i++) {
        for (int j = 0; j < m[0].size (); j++) {
            if (i == 0 || j == 0 || i == m.size () - 1 || j == m[0].size () - 1) {
                vt++;
                continue;
            }
            bool v = true;
            for (int k = 0; k < i; k++) {
                if (m[k][j] >= m[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                vt++;
                continue;
            }
            v = true;
            for (int k = m.size () - 1; k > i; k--) {
                if (m[k][j] >= m[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                vt++;
                continue;
            }
            v = true;
            for (int k = 0; k < j; k++) {
                if (m[i][k] >= m[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                vt++;
                continue;
            }
            v = true;
            for (int k = m[0].size () - 1; k > j; k--) {
                if (m[i][k] >= m[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v)
                vt++;
        }
    }
    std::cout << vt << std::endl;

    int mss = 0;
    for (int i = 0; i < m.size (); i++) {
        for (int j = 0; j < m[0].size (); j++) {
            if (i == 0 || j == 0 || i == m.size () - 1 || j == m[0].size () - 1) {
                continue;
            }
            int lss1 = 0;
            for (int k = i - 1; k >= 0; k--) {
                lss1++;
                if (m[k][j] >= m[i][j])
                    break;
            }
            int lss2 = 0;
            for (int k = i + 1; k < m.size (); k++) {
                lss2++;
                if (m[k][j] >= m[i][j])
                    break;
            }
            int lss3 = 0;
            for (int k = j - 1; k >= 0; k--) {
                lss3++;
                if (m[i][k] >= m[i][j])
                    break;
            }
            int lss4 = 0;
            for (int k = j + 1; k < m[0].size (); k++) {
                lss4++;
                if (m[i][k] >= m[i][j])
                    break;
            }
            int ss = lss1 * lss2 * lss3 * lss4;
            if (ss > mss)
                mss = ss;
        }
    }
    std::cout << mss << std::endl;

    return 0;
}