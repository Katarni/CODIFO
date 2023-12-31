//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "App.h"

App::App() {
  openDataWindow(false);
}

void App::openDataWindow(bool again) {
  data_window_ = new QWidget();
  data_window_->setFixedSize(400, 250);
  data_window_->setStyleSheet("QWidget { background: #fff; }");

  data_header = new QLabel(data_window_);
  data_header->resize(125, 40);
  data_header->move(136, 15);

  QFont header_font = data_header->font();
  header_font.setPixelSize(32);
  header_font.setBold(true);

  data_header->setFont(header_font);
  data_header->setStyleSheet("QLabel { color: #000; }");
  data_header->setText("CODIFO");

  number_edit_ = new QLineEdit(data_window_);
  number_edit_->resize(350, 25);
  number_edit_->move(25, 80);
  number_edit_->setPlaceholderText("Function number");
  number_edit_->setStyleSheet("QLineEdit { color: #000;"
                              "border-radius: 8px;"
                              "padding-left: 5px;"
                              "background: #ebd7f5; }");

  params_edit_ = new QLineEdit(data_window_);
  params_edit_->resize(350, 25);
  params_edit_->move(25, 120);
  params_edit_->setPlaceholderText("Number of parameters");
  params_edit_->setStyleSheet("QLineEdit { color: #000;"
                              "border-radius: 8px;"
                              "padding-left: 5px;"
                              "background: #ebd7f5; }");

  submit_button_ = new QPushButton(data_window_);
  submit_button_->resize(72, 30);
  submit_button_->move(25, 160);
  submit_button_->setText("Construct");
  submit_button_->setStyleSheet("QPushButton { background: #ebd7f5;"
                                "color: #000;"
                                "padding-right: 3px;"
                                "border-radius: 8px; }");
  connect(submit_button_, SIGNAL(released()), this, SLOT(submitData()));

  data_load_ = new QPushButton(data_window_);
  data_load_->resize(72, 30);
  data_load_->move(108, 160);
  data_load_->setText("Load");
  data_load_->setStyleSheet("QPushButton { background: #ebd7f5;"
                                "color: #000;"
                                "padding-right: 3px;"
                                "border-radius: 8px; }");
  connect(data_load_, SIGNAL(released()), this, SLOT(loadData()));

  if (again) {
    number_edit_->setText(QString::fromStdString(number_));
    params_edit_->setText(QString::fromStdString(std::to_string(params_)));
  }

  data_window_->show();
}

void App::loadData() {
  number_edit_->clear();
  params_edit_->clear();

  QString file = QFileDialog::getOpenFileName(nullptr, "Выбрать txt файл", "", "*.txt");
  QFile in(file);
  if (!in.open(QIODevice::ReadOnly)) return;
  QString data = in.readAll();
  in.close();

  QStringList text = data.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);
  if (text.empty() || text[0].isEmpty()) {
    number_edit_->setText(("Empty file"));
  }
  QStringList words_first_line = text[0].split(QRegularExpression("[ ]"), Qt::SkipEmptyParts);
  if (words_first_line.size() > 2) {
    number_edit_->setText(words_first_line[0]);
    params_edit_->setText(words_first_line[1]);
    return;
  }

  if (text.size() < 2) {
    number_edit_->setText(("Not enough numbers in the file"));
    return;
  }

  QStringList words_second_line = text[0].split(QRegularExpression("[ ]"), Qt::SkipEmptyParts);
  number_edit_->setText(words_first_line[0]);
  params_edit_->setText(words_second_line[0]);
}

void App::closeDataWindow() {
  data_window_->hide();

  delete data_load_;
  delete submit_button_;
  delete data_header;
  delete number_edit_;
  delete params_edit_;
  delete data_window_;
}

void App::submitData() {
  std::string number = number_edit_->text().toStdString();
  std::string params = params_edit_->text().toStdString();

  number_edit_->clear();
  params_edit_->clear();

  if (number.empty()) {
    number_edit_->setText("The number is empty");
    return;
  }

  if (params.empty()) {
    params_edit_->setText("Number of parameters is empty");
    return;
  }

  for (char let : number) {
    if (let < '0' || let > '9') {
      number_edit_->setText("The number is incorrect");
      return;
    }
  }

  for (char let : params) {
    if (let < '0' || let > '9') {
      params_edit_->setText("Number of parameters is incorrect");
      return;
    }
  }

  number_ = number;
  params_ = std::stoi(params);

  closeDataWindow();
  openConstructorWindow();
}

void App::openConstructorWindow() {
  constructor_window_ = new QWidget();
  constructor_window_->setFixedSize(1200, 700);
  constructor_window_->setStyleSheet("QWidget { background: #fff; }");

  constructor_bar_ = new QWidget(constructor_window_);
  constructor_bar_->setFixedSize(1200, 75);
  constructor_bar_->setStyleSheet("QWidget { border-bottom-left-radius: 8px;"
                                  "border-bottom-right-radius: 8px;"
                                  "border-bottom: 3px solid #ebd7f5; }");

  back_button_ = new QPushButton(constructor_bar_);
  back_button_->resize(60, 31);
  back_button_->move(1055, 22);
  back_button_->setText("<- Back");
  back_button_->setStyleSheet("QPushButton { background: #ebd7f5;"
                              "color: #000;"
                              "padding-top: 1px;"
                              "padding-right: 3px;"
                              "border-radius: 8px; }");
  connect(back_button_, SIGNAL(released()), this, SLOT(prevStep()));

  forward_button_ = new QPushButton(constructor_bar_);
  forward_button_->resize(60, 31);
  forward_button_->move(1125, 22);
  forward_button_->setText("Next ->");
  forward_button_->setStyleSheet("QPushButton { background: #ebd7f5;"
                              "color: #000;"
                              "padding-top: 1px;"
                              "padding-right: 3px;"
                              "border-radius: 8px; }");
  connect(forward_button_, SIGNAL(released()), this, SLOT(nextStep()));

  constructor_number_holder = new QLabel(constructor_bar_);
  constructor_number_holder->resize(200, 20);
  constructor_number_holder->move(20, 17);

  QFont params_font = constructor_number_holder->font();
  params_font.setPixelSize(15);

  constructor_number_holder->setFont(params_font);
  constructor_number_holder->setText("Function number: " + QString::fromStdString(number_));
  constructor_number_holder->setStyleSheet("QLabel { border: none;"
                                           "color: #000; }");

  constructor_params_holder = new QLabel(constructor_bar_);
  constructor_params_holder->resize(200, 20);
  constructor_params_holder->move(20, 37);
  constructor_params_holder->setFont(params_font);
  constructor_params_holder->setText("Number of parameters: " + QString::fromStdString(std::to_string(params_)));
  constructor_params_holder->setStyleSheet("QLabel { border: none;"
                                           "color: #000; }");

  new_func_btn_ = new QPushButton(constructor_bar_);
  new_func_btn_->resize(60, 31);
  new_func_btn_->move(std::max(constructor_number_holder->width(),
                               constructor_params_holder->width()) + 35, 22);
  new_func_btn_->setText("New +");
  new_func_btn_->setStyleSheet("QPushButton { background: #ebd7f5;"
                               "color: #000;"
                               "padding-top: 1px;"
                               "padding-right: 3px;"
                               "border-radius: 8px; }");
  connect(new_func_btn_, SIGNAL(released()), this, SLOT(newFunc()));

  current_date = 0;

  createTable();

  constructor_window_->show();
}

void App::closeConstructorWindow() {
  constructor_window_->hide();

  answers_.clear();
  uniq_vars_.clear();

  for (int i = 0; i < cells_.size(); ++i) {
    for (int j = 0; j < cells_[i].size(); ++j) {
      delete cells_[i][j];
    }
  }

  delete new_func_btn_;
  delete table_label_;
  delete table_scroll_area_;
  delete forward_button_;
  delete back_button_;
  delete constructor_number_holder;
  delete constructor_params_holder;
  delete constructor_bar_;
  delete constructor_window_;
}

void App::createTable() {
  table_ = Constructor::constructTable(number_, params_);

  cells_.resize(table_.size());
  for (int i = 0; i < cells_.size(); ++i) {
    cells_[i].resize(table_[i].size());
  }

  cell_height_ = 25;
  cell_width_ = 10 + 10 * params_;

  table_label_ = new QLabel(constructor_window_);
  table_label_->resize((int)cells_[0].size() * cell_width_,
                       (int)cells_.size() * cell_height_);

  table_scroll_area_ = new QScrollArea(constructor_window_);
  table_scroll_area_->resize(std::min((int)cells_[0].size() * cell_width_ + 3, 1150),
                             std::min((int)cells_.size() * cell_height_ + 3, 575));
  table_scroll_area_->move((1200 - table_scroll_area_->width()) / 2, 75 + (625 - table_scroll_area_->height()) / 2);
  table_scroll_area_->setWidget(table_label_);
  table_scroll_area_->setStyleSheet("QScrollArea QScrollBar::handle { background: #ebd7f5;"
                                    "border-radius: 8px; }"
                                    "QScrollArea QScrollBar { background: #fff; }");

  for (int i = 0; i < cells_.size(); ++i) {
    for (int j = 0; j < cells_[i].size(); ++j) {
      cells_[i][j] = new QLabel(table_label_);
      cells_[i][j]->resize(cell_width_, cell_height_);
      cells_[i][j]->move(cell_width_ * j, cell_height_ * i);
      cells_[i][j]->setAlignment(Qt::AlignCenter);
      cells_[i][j]->setText(QString::fromStdString(table_[i][j].getNum()));
      cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                  "background: #fff;"
                                  "color: #000; }");
    }
  }
}

void App::nextStep() {
  if (current_date == 3) {
    calculateAnswer();
    return;
  }

  if (current_date > 3) {
    return;
  }

  std::vector<std::pair<int, int>> checked;
  if (current_date == 0) {
    checked = Constructor::checkOutZeros(table_);
  } else if (current_date == 1) {
    checked = Constructor::checkOutDuplicates(table_);
  } else {
    checked = Constructor::checkOutBiggest(table_);
  }

  for(int i = 0; i < cells_.size(); ++i) {
    for (int j = 0; j < cells_[i].size(); ++j) {
      if (table_[i][j].isDeleted()) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "color: #fff;"
                                    "background: #000; }");
      }
    }
  }

  ++current_date;

  for (auto pair : checked) {
    int i = pair.first;
    int j = pair.second;
    table_[i][j].setDeleted(true);
    table_[i][j].setDate(current_date);
    cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                "color: #000;"
                                "background: #c92518; }");
  }

  constructor_window_->show();
}

void App::prevStep() {
  if (current_date == 0) {
    closeConstructorWindow();
    openDataWindow(true);
    return;
  }

  if (current_date == 4) {
    hideAnswer();
    return;
  }

  for (int i = 1; i < table_.size(); ++i) {
    for (int j = 1; j < table_[i].size(); ++j) {
      if (current_date - 1 != 0 && table_[i][j].getDate() == current_date - 1) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "color: #000;"
                                    "background: #c92518; }");
      } else if (table_[i][j].getDate() == current_date) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "background: #fff;"
                                    "color: #000; }");
        table_[i][j].setDate(0);
        table_[i][j].setDeleted(false);
      }
    }
  }
  --current_date;
}

void App::calculateAnswer() {
  if (!uniq_vars_.empty() || !answers_.empty()) {
    showAnswer();
    return;
  }

  bool get_all = true;
  for (int i = 1; i < table_.size(); ++i) {
    if (table_[i][0].getNum() != "1") {
      get_all = false;
    }
  }

  if (get_all) {
    uniq_vars_.emplace_back("1");
    showAnswer();
    return;
  }

  for (int i = 1; i < table_.size(); ++i) {
    if (table_[i][0].getNum() == "0" || table_[i][0].isGot()) {
      table_[i][0].setGot(true);
      continue;
    }

    int cnt_not_del = 0, el_idx = 0;
    for (int j = 1; j < table_[i].size(); ++j) {
      if (!table_[i][j].isDeleted()) {
        ++cnt_not_del;
        el_idx = j;
      }
    }

    if (cnt_not_del == 1) {
      uniq_vars_.push_back(Constructor::getNormalForm(table_[0][el_idx].getNum(), table_[i][el_idx].getNum()));
      for (int k = 1; k < table_.size(); ++k) {
        if (table_[k][el_idx].getNum() == table_[i][el_idx].getNum()) {
          table_[k][0].setGot(true);
        }
      }
    }
  }

  std::vector<std::pair<int, std::vector<int>>> vars;

  for (int i = 1; i < table_.size(); ++i) {
    if (table_[i][0].isGot()) {
      continue;
    }

    std::vector<int> indexes;
    for (int j = 1; j < table_[i].size(); ++j) {
      if (!table_[i][j].isDeleted()) {
        indexes.push_back(j);
      }
    }

    vars.emplace_back(i, indexes);
  }

  std::sort(uniq_vars_.begin(), uniq_vars_.end());

  int min_len = params_ * vars.size();
  if (vars.empty()) {
    showAnswer();
    return;
  }

  for (int j : vars[0].second) {
    Constructor::getAns(vars, vars[0].first, j, table_,
                        std::unordered_set<int>(),
                        std::vector<std::string>(0),
                        answers_, min_len, 0);
  }

  showAnswer();
}

void App::hideAnswer() {
  for (int i = 1; i < table_.size(); ++i) {
    for (int j = 1; j < table_[i].size(); ++j) {
      if (current_date - 1 != 0 && table_[i][j].getDate() == current_date - 1) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "color: #000;"
                                    "background: #c92518; }");
      } else if (table_[i][j].getDate() == current_date) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "background: #fff;"
                                    "color: #000; }");
        table_[i][j].setDate(0);
        table_[i][j].setDeleted(false);
      }
    }
  }

  table_label_->resize((int)cells_[0].size() * cell_width_,
                       (int)cells_.size() * cell_height_);

  table_scroll_area_->resize(std::min((int)cells_[0].size() * cell_width_ + 3, 1150),
                             std::min((int)cells_.size() * cell_height_ + 3, 575));
  table_scroll_area_->move((1200 - table_scroll_area_->width()) / 2, 75 + (625 - table_scroll_area_->height()) / 2);

  --current_date;

  ans_browser_->hide();
  delete ans_browser_;
}

void App::showAnswer() {
  for (int i = 0; i < cells_.size(); ++i) {
    for (int j = 0; j < cells_[i].size(); ++j) {
      if (table_[i][j].isDeleted()) {
        cells_[i][j]->setStyleSheet("QLabel { border: 1px solid #000;"
                                    "color: #fff;"
                                    "background: #000; }");
      }
    }
  }

  int endl_cnt = 0;
  std::string ans;
  std::string sep = " | ";
  for (auto it = answers_.begin(); it != answers_.end(); ++it) {
    for (const auto& uniq : uniq_vars_) {
      ans.insert(ans.end(), uniq.begin(), uniq.end());
      ans.insert(ans.end(), sep.begin(), sep.end());
    }

    for (const auto& str : *it) {
      ans.insert(ans.end(), str.begin(), str.end());
      ans.insert(ans.end(), sep.begin(), sep.end());
    }

    ans.resize(ans.size() - 3);
    ans.push_back('\n');
    ++endl_cnt;
  }

  if (answers_.empty()) {
    for (const auto& uniq : uniq_vars_) {
      ans.insert(ans.end(), uniq.begin(), uniq.end());
      ans.insert(ans.end(), sep.begin(), sep.end());
    }
    ans.resize(ans.size() - 3);
    ans.push_back('\n');
    ++endl_cnt;
  }

  ans.pop_back();

  table_label_->resize((int)cells_[0].size() * cell_width_,
                       (int)cells_.size() * cell_height_);

  table_scroll_area_->resize(std::min(table_scroll_area_->width(), table_label_->width()) + 3,
                             std::min(300, table_label_->height() + 3));
  table_scroll_area_->move((1200 - table_scroll_area_->width()) / 2, 100);

  ++current_date;

  ans_browser_ = new QTextBrowser(constructor_window_);
  ans_browser_->move((1200 - table_scroll_area_->width()) / 2, 425);
  ans_browser_->resize(table_scroll_area_->width(), std::min(225, endl_cnt * 17 + 20));
  ans_browser_->setStyleSheet("QTextBrowser { background: #fff;"
                              "border: 1px solid #ebd7f5;"
                              "color: #000;"
                              "border-radius: 5px;"
                              "padding: 5px; }"
                              "QTextBrowser QScrollBar::handle { background: #ebd7f5;"
                              "border-radius: 8px; }"
                              "QTextBrowser QScrollBar { background: #fff; }");

  ans_browser_->setText(QString::fromStdString(ans));
  ans_browser_->show();
}

void App::newFunc() {
  closeConstructorWindow();
  openDataWindow(false);
}
