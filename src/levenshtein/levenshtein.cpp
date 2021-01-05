#include "levenshtein/levenshtein.hpp"

#include <algorithm>  // std::min
#include <functional>
#include <iostream>
#include <queue>
#include <random>

#include "useful/various.hpp"  // FOR LOG

int64_t random_int(int64_t i);

/********************************************************************/
/* Levenstein Node   	      	     	     	     	     	    */
/********************************************************************/

levenshtein::Levenshtein::LevNode::LevNode() {
    score = 0;
    op = Unk;
    bestPath = false;
}

/********************************************************************/
/* Levenstein    	      	     	     	     	     	    */
/********************************************************************/

levenshtein::Levenshtein::Levenshtein(const std::string &wordH,
                                      const std::string &wordV,
                                      size_t cellWidth)
        : wordH(wordH), wordV(wordV), cellWidth(cellWidth) {
    computed = false;
}

void levenshtein::Levenshtein::init_lev_matrix() {
    m.resize(wordV.size() + 1, wordH.size() + 1);
    for (int i = 1; i <= wordV.size(); ++i) {
        LevNode levNode = LevNode();
        levNode.score = i;
        m.set(levNode, i, 0);
    }
    for (int j = 1; j <= wordH.size(); ++j) {
        LevNode levNode = LevNode();
        levNode.score = j;
        m.set(levNode, 0, j);
    }
}

std::vector<levenshtein::Levenshtein::Operation>
levenshtein::Levenshtein::backtrace() {
    if (not computed) {
        compute_lev();
    }

    std::vector<levenshtein::Levenshtein::Operation> r;
    r.reserve(m.nb_col() + m.nb_row());

    LOG(WARNING) << "TODO Levenshtein::backtrace";

    return r;
}

int64_t levenshtein::Levenshtein::compute_lev() {
    if (not computed) {
        LOG(DEBUG) << "Fill levenshtein matrix";
        init_lev_matrix();

        int cost;

        for (int i = 0; i <= wordV.size(); ++i) {
            for (int j = 0; j <= wordH.size(); ++j) {
                if (wordV[i] == wordH[j]) {
                    cost = 0;
                } else {
                    cost = 1;
                }

                LevNode levNode = LevNode();

                levNode.score = std::min(
                        std::min(m.at(i - 1, j).score + 1, m.at(i, j - 1).score + 1),
                        m.at(i - 1, j - 1).score + cost
                );

                m.set(levNode, i, j);
            }

        }

        computed = true;
    }
    return m.at(wordV.size(), wordH.size()).score;
}

int64_t levenshtein::Levenshtein::compute_lev_compact() {
    LOG(WARNING) << "TODO Levenshtein::compute_lev_compact";

    return 0;
}

/********************************************************************/

namespace levenshtein {
    std::ostream &operator<<(std::ostream &os, Levenshtein &l) {
        if (not l.computed) {
            l.compute_lev();
        }

        size_t nbCol = l.m.nb_col() + 1;

        const std::string colSep = "|";
        const std::string crossSep = "+";  // TODO(JC): add direction
        const char borderSep = '-';
        const char emptyCell = ' ';
        const std::string fillerBorder =
                std::string(l.cellWidth, borderSep);  // TODO(JC): add direction
        const std::string fillerEmpty = std::string(l.cellWidth, emptyCell);

        // Print the first row
        // hline
        for (size_t j = 0; j < nbCol; ++j) {
            os << fillerEmpty << colSep;
        }
        os << std::endl;

        os << fillerEmpty << colSep << fillerEmpty << colSep;
        for (size_t j = 0; j < l.m.nb_col() - 1; ++j) {
            const std::string c = std::string(1, l.wordH[j]);

            // Build a filler
            const std::string fillerL =
                    std::string((l.cellWidth - c.length()) / 2, emptyCell);
            const std::string fillerR =
                    std::string(l.cellWidth - c.length() - fillerL.length(), emptyCell);

            os << fillerL << c << fillerR << colSep;
        }
        os << std::endl;
        // hline
        for (size_t j = 0; j < nbCol; ++j) {
            os << fillerEmpty << colSep;
        }
        os << std::endl;
        // print hline
        for (size_t j = 0; j + 1 < nbCol; ++j) {
            os << fillerBorder << crossSep;
        }
        os << fillerBorder << colSep << std::endl;

        // Print remaning matrix
        for (size_t i = 0; i < l.m.nb_row(); ++i) {
            // hline
            for (size_t j = 0; j < nbCol; ++j) {
                os << fillerEmpty << colSep;
            }
            os << std::endl;
            // First column, the word
            if (i == 0) {
                os << fillerEmpty << colSep;
            } else {
                const std::string c = std::string(1, l.wordV[i - 1]);

                // Build a filler
                const std::string fillerL =
                        std::string((l.cellWidth - c.length()) / 2, emptyCell);
                const std::string fillerR =
                        std::string(l.cellWidth - c.length() - fillerL.length(), emptyCell);
                os << fillerL << c << fillerR << colSep;
            }

            // Cost matrix

            for (size_t j = 0; j < l.m.nb_col(); ++j) {
                const std::string c = std::to_string(l.m.at(i, j).score);
                // Build a filler
                const std::string fillerL =
                        std::string((l.cellWidth - c.length()) / 2, emptyCell);
                const std::string fillerR =
                        std::string(l.cellWidth - c.length() - fillerL.length(), emptyCell);

                if (l.m.at(i, j).bestPath) {
                    os << fillerL << "\e[32m" << c << "\e[39m" << fillerR;
                } else {
                    os << fillerL << c << fillerR;
                }

                if ((j + 1 < l.m.nb_col()) and
                    (l.m.at(i, j + 1).op == Levenshtein::Del)) {
                    if (l.m.at(i, j + 1).bestPath) {
                        os << "\e[32m";
                    }
                    os << Levenshtein::op_to_string(Levenshtein::Del);
                    if (l.m.at(i, j + 1).bestPath) {
                        os << "\e[39m";
                    }
                } else {
                    os << colSep;
                }
            }

            os << std::endl;
            // print hline
            for (size_t j = 0; j < nbCol; ++j) {
                os << fillerEmpty << colSep;
            }
            os << std::endl;
            // First col
            os << fillerBorder;
            if (i + 1 == l.m.nb_row()) {
                os << borderSep;
            } else {
                os << crossSep;
            }

            for (size_t j = 0; j < l.m.nb_col(); ++j) {
                if ((i + 1 < l.m.nb_row()) and
                    (l.m.at(i + 1, j).op == Levenshtein::Ins)) {
                    std::string op = Levenshtein::op_to_string(Levenshtein::Ins);
                    const std::string fillerL =
                            std::string((l.cellWidth - 1) / 2,
                                        borderSep);  // -1 bc length not working with utf8
                    const std::string fillerR =
                            std::string(l.cellWidth - 1 - fillerL.length(),
                                        borderSep);  // -1 bc length not working with utf8

                    os << fillerL;
                    if (l.m.at(i + 1, j).bestPath) {
                        os << "\e[32m";
                    }
                    os << op;
                    if (l.m.at(i + 1, j).bestPath) {
                        os << "\e[39m";
                    }
                    os << fillerR;

                } else {
                    os << fillerBorder;
                }

                if ((j + 1 < l.m.nb_col()) and (i + 1 < l.m.nb_row()) and
                    (l.m.at(i + 1, j + 1).op == Levenshtein::Rep)) {
                    if (l.m.at(i + 1, j + 1).bestPath) {
                        os << "\e[32m";
                    }
                    os << Levenshtein::op_to_string(Levenshtein::Rep);
                    if (l.m.at(i + 1, j + 1).bestPath) {
                        os << "\e[39m";
                    }

                } else if (i + 1 == l.m.nb_row()) {
                    os << borderSep;
                } else if (j + 1 == l.m.nb_col()) {
                    os << colSep;
                } else {
                    os << crossSep;
                }
            }
            os << std::endl;
        }

        return os;
    }

    const std::string Levenshtein::op_to_string(Operation o) {
        switch (o) {
            case Ins:
                return "↓";
                break;
            case Del:
                return "→";
                break;
            case Rep:
                return "↘";
                break;
            default:
                return " ";
        }
    }

}  // End namespace levenshtein

/********************************************************************/
/* Test    	      	     	     	     	     	    */
/********************************************************************/

int64_t random_int(int64_t i) {
    static std::random_device rd;
    static std::mt19937 rngE(rd());
    static auto gen =
            std::bind(std::uniform_int_distribution<int64_t>(0, i), std::ref(rngE));
    return gen();
}

void levenshtein::print_hello() {
    std::cout << "Hello world!" << std::endl;
}

void levenshtein::print_rnd_int() {
    std::cout << random_int(100) << std::endl;
}
