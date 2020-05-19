#include "confdialog.h"
#include "ui_dialog.h"
#include <QMainWindow>
#include <QCloseEvent>

///
/// \brief ConfDialog Это конструктор класса
/// \param parent Принимает указатель на родителя
///
ConfDialog::ConfDialog(QWidget *parent) : QMainWindow(parent), ui(new Ui::ConfDialog) {
    ui->setupUi(this);
    this->setWindowFlag(Qt::Tool);
    connect(ui->pushButton, &QPushButton::clicked, [=] {emit setPort(ui->lineEdit->text().toInt());});
}

///
/// \brief ~ConfDialog Это деструктор класса
///
ConfDialog::~ConfDialog() {
    delete ui;
}

///
/// \brief closeEvent Это перегрузка эвента закрытия окна
/// \param event Принимает сам эвент закрытия
///
void ConfDialog::closeEvent(QCloseEvent *event) {
    this->hide();
    event->ignore();
}

///
/// \brief setPortToDialog Это функция, которая устанавливает порт в плейсхолдер лайнЭдита
/// \param instance Принимает указатель на экземпляр класса Server
///
void ConfDialog::setPortToDialog(Server *instance) {
    ui->lineEdit->setText(QString::number(instance->serverPort));
}
