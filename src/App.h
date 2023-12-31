//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#pragma once
#include "Constructor.h"


class App : public QMainWindow {
 Q_OBJECT

 public:
  App();

 private slots:
  // Data Window
  void submitData();
  void loadData();

  // Constructor Window
  void nextStep();
  void prevStep();
  void newFunc();

 private:
  std::vector<std::vector<Cell>> table_;
  std::string number_;
  int params_;

  // Data Window
  QWidget* data_window_;
  QLabel* data_header;
  QLineEdit* number_edit_;
  QLineEdit* params_edit_;
  QPushButton* submit_button_;
  QPushButton* data_load_;

  void openDataWindow(bool again);
  void closeDataWindow();

  // Constructor Window
  int cell_width_, cell_height_;
  int current_date;
  QWidget* constructor_window_;
  QWidget* constructor_bar_;
  QPushButton* forward_button_;
  QPushButton* back_button_;
  QPushButton* new_func_btn_;
  QLabel* constructor_number_holder;
  QLabel* constructor_params_holder;
  QLabel* table_label_;
  QScrollArea* table_scroll_area_;

  std::vector<std::vector<QLabel*>> cells_;

  void openConstructorWindow();
  void closeConstructorWindow();

  void createTable();

  // Get & Show Answer

  std::set<std::vector<std::string>> answers_;
  std::vector<std::string> uniq_vars_;

  QTextBrowser* ans_browser_;

  void calculateAnswer();
  void showAnswer();
  void hideAnswer();
};