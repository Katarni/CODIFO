//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "Constructor.h"

std::vector<std::vector<Cell>> Constructor::constructTable(const std::string& number, int params) {
  std::vector<std::vector<Cell>> table((1<<params) + 1, std::vector<Cell>(1<<params));
  table[0][0] = Cell("f");
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
