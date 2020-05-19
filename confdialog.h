#ifndef CONFDIALOG_H
#define CONFDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QLineEdit>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConfDialog; }
QT_END_NAMESPACE


///
/// \brief Это класс ConfDialog - диалоговое (в теории) окно конфигурации
///
class ConfDialog : public QMainWindow {
        Q_OBJECT
public:
    ///
    /// \brief ConfDialog Это конструктор класса
    /// \param parent Принимает указатель на родителя
    ///
    ConfDialog(QWidget *parent = nullptr);

    ///
    /// \brief ~ConfDialog Это деструктор класса
    ///
    ~ConfDialog();

    ///
    /// \brief closeEvent Это перегрузка эвента закрытия окна
    /// \param event Принимает сам эвент закрытия
    ///
   void closeEvent(QCloseEvent *event);

    ///
    /// \brief setPortToDialog Это функция, которая устанавливает порт в плейсхолдер лайнЭдита
    /// \param instance Принимает указатель на экземпляр класса Server
    ///
    void setPortToDialog(Server *instance);

private:
    ///
    /// \brief ui Это интерфейс
    ///
    Ui::ConfDialog *ui;

signals:
    ///
    /// \brief setPort Это сигнал для установки порта сервера
    /// \param port Принимает и передаёт порт
    ///
    void setPort(qint16 port);
};

#endif // CONFDIALOG_H
