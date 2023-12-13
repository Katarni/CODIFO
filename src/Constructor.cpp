//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "Constructor.h"

std::vector<std::vector<std::string>> Constructor::constructTable(int number, int params) {
  std::vector<std::vector<std::string>> table((1<<params) + 1, std::vector<std::string>(1<<params));
  table[0][0] = "f";
  std::string str = "0";
  for (int i = 1; i < table[0].size(); ++i) {
    unitAdditionParams(str, params + 1);
    table[0][i] = toLetterForm(str);
  }

  for (int i = table.size() - 1; i > 0; --i) {
    table[i][0] = std::to_string(number % 2);
    number /= 2;
  }

  str.resize(params);
  for (char& c : str) {
    c = '0';
  }

  for (int i = 1; i < table.size(); ++i) {
    for (int j = 1; j < params + 1; ++j) {
      table[i][j] = str[j - 1];
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
