#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QAbstractButton>
#include "confdialog.h"
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

///
/// \brief Это класс MainWindow
///
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    ///
    /// \brief MainWindow Это конструктор класса
    /// \param parent Принимает родителя
    ///
    MainWindow(QWidget *parent = nullptr);

    ///
    /// \brief Это деструктор класса
    ///
    ~MainWindow();

    ///
    /// \brief server Держим экземпляр сервера в этом классе
    ///
    Server *server;

    ///
    /// \brief tray Держим иконку трея в этом классе
    ///
    QSystemTrayIcon tray;

    ///
    /// \brief trayMenu Держим меню трея в этом классе
    ///
    QMenu* trayMenu;

    ///
    /// \brief closeEvent Это перегрузка эвента закрытия основного окна
    /// \param event Принимает эвент закрытия
    ///
    void closeEvent(QCloseEvent *event);

    ///
    /// \brief firstPortSetup Это функция первичной установки порта
    ///
    void firstPortSetup();

    ///
    /// \brief setup Держим объект настроек в этом классе
    ///
    QSettings *setup;

private:
    ///
    /// \brief ui Это интерфейс
    ///
    Ui::MainWindow *ui;

    ///
    /// \brief configure Это (диалоговое) окно конфигурации сервера
    ///
    ConfDialog *configure;

signals:



public slots:
    ///
    /// \brief setUsers Это слот установки количества пользователей
    /// \param cnt Принимает количество пользователей
    ///
    void setUsers(int cnt);

    ///
    /// \brief setState Это слот установки состояния сервера (скорее просто затычка, потому что отслеживать состояние сервера сложновато)
    /// \param state Принимает состояние сервера
    ///
    void setState(QString state);

    ///
    /// \brief handleTray Это слот активации меню трея
    /// \param reason Принимает причину активации (левое/правое нажатие)
    ///
    void handleTray(QSystemTrayIcon::ActivationReason reason);

    ///
    /// \brief showAdvanced Это слот, который срабатывает при выборе "показать" в меню трея, он показывает окно и скрывает трей
    ///
    void showAdvanced();

    ///
    /// \brief configureServer Это слот, который срабатывает при выборе "конфигурировать" в меню трея, он показывает окно конфига
    ///
    void configureServer();

    ///
    /// \brief saveSettings Это слот сохранения настроек сервера
    /// \param port Принимает только порт, но если нужно будет сохранять другие настройки - их можно легко добавить
    ///
    void saveSettings(qint16 port);

};

#endif // MAINWINDOW_H
