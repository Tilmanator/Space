//
// Created by Tilman Lindig on 2018-12-24.
//

#ifndef SPACE_DU_COMP_H
#define SPACE_DU_COMP_H

#include <string>

class du_comp {
public:
    inline bool operator()(const std::string &a, const std::string &b) {
        double anum, bnum;
        char aa, bb;
        for (int i = 0; i < a.size(); ++i) {
            if (a.at(i) == ' ') {
                continue;
            }
            int j = i;
            while (isdigit(a.at(j)) || a.at(j) == '.') {
                ++j;
            }
            anum = std::stod(a.substr(i, j));
            aa = a.at(j);
            break;
        }

        for (int i = 0; i < b.size(); ++i) {
            if (b.at(i) == ' ') {
                continue;
            }
            int j = i;
            while (isdigit(b.at(j)) || b.at(j) == '.') {
                ++j;
            }
            bnum = std::stod(b.substr(i, j));
            bb = b.at(j);
            break;
        }

        std::string abbreviations = "BKMGTEPYZ";
        return abbreviations.find(aa) == abbreviations.find(bb) ? anum < bnum : abbreviations.find(aa) <
                                                                                abbreviations.find(bb);
    }
};

#endif //SPACE_DU_COMP_H
