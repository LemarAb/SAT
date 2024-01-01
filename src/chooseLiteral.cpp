#include "../include/cnf.hpp"

void chooseLiteral() {
    switch (heuristic) {
        case INC:
            while (vars[curVar].getValue() != FREE) curVar++;
            vars[curVar].setValue(TRUE);
            vars[curVar].forced = false;
            assig.push(curVar);
            std::cout << "CHOOSE_LIT:" << curVar;
            break;
        case DLIS:
            break;
        case DLCS:
            break;
        case MOM:
            break;
        case JW:
            break;
    }
    updateWatchedLiterals(curVar);
}