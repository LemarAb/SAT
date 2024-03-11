// Niver Preprocessing Technique

#include "include/cdcl.hpp"
#include <algorithm>

int numOfVars;
int numOfClauses;
int numOfUnassigned;
int curVar;
std::stack<int> assig;
std::vector<std::vector<int>> cnf;
std::vector<Variable> vars;
std::set<int> satClauses;
std::queue<int> unitQueue;
bool niverChange = true;

bool totalLitsinClausesComp(std::vector<std::vector<int>> resolvents,
                            std::vector<int> with, std::vector<int> without) {
  int totalLitsinClauses = 0;
  int totalLitsinResolvents = 0;

  for (int i = 0; i < with.size(); i++) {
    totalLitsinClauses += cnf[with[i]].size();
  }

  for (int i = 0; i < without.size(); i++) {
    totalLitsinClauses += cnf[without[i]].size();
  }

  for (int i = 0; i < resolvents.size(); i++) {
    totalLitsinResolvents += resolvents[i].size();
  }

  printf("Total Lits in Clauses: %i\n", totalLitsinClauses);
  printf("Total Lits in Resolvents: %i\n", totalLitsinResolvents);

  if (totalLitsinResolvents < totalLitsinClauses) {
    printf("Resolvents are less than clauses\n");
    return true;
  } else {
    printf("Resolvents are not less than clauses\n");
    return false;
  }
}

bool resolve(std::vector<int> with, std::vector<int> without, int var) {
  std::vector<std::vector<int>> resolvents;

  for (int i = 0; i < with.size(); i++) {
    for (int j = 0; j < without.size(); j++) {
      std::vector<int> tmp_clause;

      // Copy all elements from with[i] and without[i] to tmp_clause if var
      // is not present in the clause
      std::copy_if(cnf[with[i]].begin(), cnf[with[i]].end(),
                   std::back_inserter(tmp_clause), [var](int x) {
                     return x != var && x != -var;
                     ;
                   });

      std::copy_if(cnf[without[j]].begin(), cnf[without[j]].end(),
                   std::back_inserter(tmp_clause), [var, &tmp_clause](int x) {
                     return x != var && x != -var &&
                            (std::find(tmp_clause.begin(), tmp_clause.end(),
                                       x) == tmp_clause.end());
                     ;
                     ;
                   });

      // Check for tautologies in each tmp_clause, push to resolvents if not

      bool tautology = false;

      for (int l = 0; l < tmp_clause.size(); l++) {

        if (std::find(tmp_clause.begin(), tmp_clause.end(), -tmp_clause[l]) !=
            tmp_clause.end()) {
          printf("Tautology found: %i and %i\n", tmp_clause[l], -tmp_clause[l]);
          tautology = true;
          break;
        }
      }
      if (!tautology)
        resolvents.push_back(tmp_clause);
    }
  }

  // print resolvents
  for (int i = 0; i < resolvents.size(); i++) {
    for (int j = 0; j < resolvents[i].size(); j++) {
      printf("%i ", resolvents[i][j]);
    }
    printf("\n");
  }

  /* if new resolvents, check the size of the resolvents with comparison to the
     original clauses. If clause count is less, alter cnf accordingly */

  if (resolvents.size() < with.size() + without.size()) {

    std::vector<int> toRemove;
    toRemove.insert(toRemove.end(), with.begin(), with.end());
    toRemove.insert(toRemove.end(), without.begin(), without.end());
    std::sort(toRemove.begin(), toRemove.end());

    // clauses to be deleted
    for (int i = 0; i < toRemove.size(); i++) {
      printf("To Remove: %i ", toRemove[i]);
    }
    printf("\n");

    for (int i = toRemove.size() - 1; i >= 0; i--) {
      cnf.erase(cnf.begin() + toRemove[i]);
    }

    for (int i = 0; i < resolvents.size(); i++) {
      cnf.push_back(resolvents[i]);
      niverChange = true;
    }
  } else if (resolvents.size() == with.size() + without.size()) {
    // For the case they are the same size
    printf("Resolvents are the same size as clauses\n");
    if (totalLitsinClausesComp(resolvents, with, without)) {

      std::vector<int> toRemove;
      toRemove.insert(toRemove.end(), with.begin(), with.end());
      toRemove.insert(toRemove.end(), without.begin(), without.end());
      std::sort(toRemove.begin(), toRemove.end());

      // clauses to be deleted
      for (int i = 0; i < toRemove.size(); i++) {
        printf("To Remove: %i ", toRemove[i]);
      }
      printf("\n");

      for (int i = toRemove.size() - 1; i >= 0; i--) {
        cnf.erase(cnf.begin() + toRemove[i]);
      }

      for (int i = 0; i < resolvents.size(); i++) {
        cnf.push_back(resolvents[i]);
        niverChange = true;
      }
    }
  } else {
    niverChange = false;
    printf("Resolvents are not less or equal than clauses\n");
    printf("No change\n");
    printf("clauses size %i and resolvents size %i\n",
           with.size() + without.size(), resolvents.size());
    totalLitsinClausesComp(resolvents, with, without);
  }

  // print cnf
  for (int i = 1; i < cnf.size(); i++) {
    printf("Clause %i: ", i);
    for (int j = 0; j < cnf[i].size(); j++) {
      printf("%i ", cnf[i][j]);
    }
    printf("\n");
  }

  if (niverChange)
    return true;
  else
    return false;
}

void clauseDecomp(int var) {
  std::vector<int> withVarPos(0);
  std::vector<int> withVarNeg(0);
  std::vector<int> remaining(0);

  for (int i = 1; i < cnf.size(); i++) {
    if (find(cnf[i].begin(), cnf[i].end(), var) != cnf[i].end()) {
      withVarPos.push_back(i);
    } else if (find(cnf[i].begin(), cnf[i].end(), -var) != cnf[i].end()) {
      withVarNeg.push_back(i);
    } else {
      remaining.push_back(i);
    }
  }

  std::cout << "Var= " << var << std::endl;

  // Print all elements of withVar
  std::cout << "withVarPos: ";
  for (int i = 0; i < withVarPos.size(); i++) {
    std::cout << withVarPos[i] << " ";
  }
  std::cout << std::endl;

  // Print all elements of woutVar
  std::cout << "withVarNeg: ";
  for (int i = 0; i < withVarNeg.size(); i++) {
    std::cout << withVarNeg[i] << " ";
  }
  std::cout << std::endl;

  // Print all elements of remaining
  std::cout << "remaining: ";
  for (int i = 0; i < remaining.size(); i++) {
    std::cout << remaining[i] << " ";
  }
  std::cout << std::endl;
  
  resolve(withVarPos, withVarNeg, var);
  
  printf("\n");
}

int main() {

  std::string filename = "benchmarks/comp/076_hole9_u.cnf";

  parseDIMACS(filename);

  int n = numOfVars;
  printf("Number of Variables: %i\n", n);

  for (int i = 1; i <= numOfVars; i++) {

    if (niverChange) clauseDecomp(i);
    
  }
  return 0;
}