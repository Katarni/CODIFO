//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "Constructor.h"

std::vector<std::vector<Cell>> Constructor::constructTable(const std::string& number, int params) {
  std::vector<std::vector<Cell>> table((1<<params) + 1, std::vector<Cell>(1<<params));
  table[0][0] = Cell("func");
  std::string str = "0";
  for (int i = 1; i < table[0].size(); ++i) {
    unitAdditionParams(str, params + 1);
    table[0][i] = Cell(toLetterForm(str));
  }

  std::string binary_number = Constructor::toBinaryString(number);

  for (int i = (int)table.size() - 1, j = (int)binary_number.size() - 1; i > 0; --i, --j) {
    if (j >= 0) {
      table[i][0] = Cell(std::to_string(binary_number[j] - '0'));
    } else {
      table[i][0] = Cell("0");
    }
  }

  str.resize(params);
  for (char& c : str) {
    c = '0';
  }

  for (int i = 1; i < table.size(); ++i) {
    for (int j = 1; j < params + 1; ++j) {
      table[i][j] = Cell(std::to_string(str[j - 1] - '0'));
    }
    unitAdditionBinary(str);
  }

  for (int i = params + 1; i < table[0].size(); ++i) {
    for (int j = 1; j < table.size(); ++j) {
      for (int k = 0; k < table[0][i].size(); ++k) {
        table[j][i] += table[j][table[0][i][k] - 'a' + 1];
      }
    }
  }

  return table;
}

std::string Constructor::toLetterForm(const std::string &str) {
  std::string letter_form;
  for (char c : str) {
    letter_form.push_back(c - '0' - 1 + 'a');
  }
  return letter_form;
}

void Constructor::unitAdditionParams(std::string &num, int base) {
  num.insert(num.begin(), '0');
  for (int i = num.size() - 1; i >= 0; --i) {
    num[i] += 1;
    if (num[i] != base + '0') {
      break;
    }
    num[i] = '1';
  }
  while (num[0] == '0') {
    num.erase(num.begin());
  }
  if (!isIncrease(num)) {
    unitAdditionParams(num, base);
  }
}

bool Constructor::isIncrease(const std::string &str) {
  char last = str[0];
  for (int i = 1; i < str.size(); ++i) {
    if (str[i] <= last) return false;
    last = str[i];
  }
  return true;
}

void Constructor::unitAdditionBinary(std::string &num) {
  for (int i = num.size() - 1; i >= 0; --i) {
    num[i] += 1;
    if (num[i] != '2') {
      break;
    }
    num[i] = '0';
  }
}

std::string Constructor::toBinaryString(std::string num) {
  std::reverse(num.begin(), num.end());

  std::string binary;
  while (num[0] != '0' || num.size() != 1) {
    char carry = divisionByTwo(num);
    binary.insert(binary.begin(), carry);
  }
  return binary;
}

char Constructor::divisionByTwo(std::string &num) {
  char carry = 0;
  for (int i = (int)num.size() - 1; i >= 0; --i) {
    char cur = num[i] - '0' + carry * 10;
    num[i] = char(cur) / 2 + '0';
    carry = cur % 2;
  }
  while (num.size() > 1 && num.back() == '0') {
    num.pop_back();
  }
  return carry + '0';
}

std::vector<std::pair<int, int>> Constructor::checkOutZeros(const std::vector<std::vector<Cell>> &table) {
  std::vector<std::pair<int, int>> checked;

  for (int i = 0; i < table.size(); ++i) {
    if (table[i][0].getNum() != "0") {
      continue;
    }

    for (int j = 1; j < table[i].size(); ++j) {
      if (table[i][j].isDeleted()) {
        continue;
      }
      checked.emplace_back(i, j);
    }
  }

  return checked;
}

std::vector<std::pair<int, int>> Constructor::checkOutDuplicates(const std::vector<std::vector<Cell>> &table) {
  std::vector<std::pair<int, int>> checked;
  for (int j = 1; j < table[0].size(); ++j) {
    std::set<std::string> deleted;
    for (int i = 1; i < table.size(); ++i) {
      if (table[i][j].isDeleted()) {
        deleted.insert(table[i][j].getNum());
      }
    }

    for (int i = 1; i < table.size(); ++i) {
      if (!table[i][j].isDeleted() && deleted.find(table[i][j].getNum()) != deleted.end()) {
        checked.emplace_back(i, j);
      }
    }
  }
  return checked;
}

std::vector<std::pair<int, int>> Constructor::checkOutBiggest(const std::vector<std::vector<Cell>> &table) {
  std::vector<std::pair<int, int>> checked;
  for (int i = 1; i < table.size(); ++i) {
    std::vector<std::string> smaller;
    for (int j = 1; j < table[i].size(); ++j) {
      if (table[i][j].isDeleted()) {
        continue;
      }
      for (const std::string& small : smaller) {
        if (existString(table[i][j].getNum(), small) && table[i][j].getNum().size() != small.size()) {
          checked.emplace_back(i, j);
          break;
        }
      }
      if (checked.empty() || (checked.back().first != i && checked.back().second != j)) {
        smaller.emplace_back(table[i][j].getNum());
      }
    }
  }
  return checked;
}

bool Constructor::existString(const std::string &str, const std::string &find) {
  for (int i = 0; i < str.size() - find.size() + 1; ++i) {
    for (int j = 0; j <= find.size(); ++j) {
      if (j == find.size()) {
        return true;
      }
      if (str[i + j] != find[j]) {
        break;
      }
    }
  }
  return false;
}

std::string Constructor::getNormalForm(const std::string &params, const std::string &values) {
  std::string normal;
  for (int i = 0; i < params.size(); ++i) {
    if (values[i] == '0') {
      normal.push_back('!');
    }
    normal.push_back(params[i]);
    normal.push_back(' ');
  }
  return normal;
}

void Constructor::getAns(const std::vector<std::pair<int, std::vector<int>>> &vars, int row, int col,
                         const std::vector<std::vector<Cell>> &table, std::unordered_set<int> got,
                         std::vector<std::string> current,
                         std::set<std::vector<std::string>> &answers, int& min_len, int crt_len) {

  current.push_back(Constructor::getNormalForm(table[0][col].getNum(), table[row][col].getNum()));
  Constructor::getAll(row, col, table, got);
  crt_len += table[0][col].getNum().size();

  if (crt_len > min_len) {
    return;
  }

  int cnt = 0;

  for (int k = 0; k < vars.size(); ++k) {
    auto pair = vars[k];
    int i = pair.first;
    if (got.find(i) == got.end()) {
      for (int j : pair.second) {
        getAns(vars, i, j, table, got, current, answers, min_len, crt_len);
      }
    } else {
      ++cnt;
    }
  }

  if (cnt == vars.size()) {
    std::sort(current.begin(), current.end());

    if (crt_len < min_len) {
      answers.clear();
    }

    min_len = crt_len;
    answers.insert(current);
    return;
  }
}

void Constructor::getAll(int i, int j, const std::vector<std::vector<Cell>> &table, std::unordered_set<int>& got) {
  for (int k = 1; k < table.size(); ++k) {
    if (table[k][j].getNum() == table[i][j].getNum()) {
      got.insert(k);
    }
  }
}

