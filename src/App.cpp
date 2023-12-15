//
// Created by Timur Akhmetzianov on 13.12.2023.
//

#include "App.h"

App::App() {
  openDataWindow();
}

void App::openDataWindow() {
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
  params_edit_->resize(155, 25);
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

void App::submitData() {

}
