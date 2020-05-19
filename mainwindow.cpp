#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QMessageBox>

///
/// \brief MainWindow Это конструктор класса
/// \param parent Принимает родителя
///
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/tray.png"));
    server = new Server(this);
    this->setWindowTitle("EZ Server");
    connect(server, SIGNAL(updateUsers(int)), this, SLOT(setUsers(int)));
    connect(server, &Server::updateState, ui->statusLine, &QLineEdit::setText);
    connect(server, &Server::showMessageOnServer, ui->textEdit, &QTextEdit::append);

    setup = new QSettings("conf.ini", QSettings::IniFormat);

    if (setup->value("serverport").toInt() > 0 && setup->value("serverport").toInt() <= 65535) {
        qDebug() << "Port exists";
        qDebug() << setup->value("serverport").toInt();
        server->serverPort = setup->value("serverport").toInt();
        server->startup();
    } else {
        firstPortSetup();
    }

    configure = new ConfDialog(this);
    configure->hide();

    QIcon newIcon;
    newIcon.addFile(":/res/tray.png");
    tray.setIcon(newIcon);
    trayMenu = new QMenu("Server menu", this);
    trayMenu->addAction("Show server window", this, &MainWindow::showAdvanced, QKeySequence(Qt::CTRL + Qt::Key_1));
    trayMenu->addAction("Configure", this, &MainWindow::configureServer, QKeySequence(Qt::CTRL + Qt::Key_2));
    trayMenu->addAction("Stop server", this, &MainWindow::close, QKeySequence(Qt::CTRL + Qt::Key_E));
    tray.setContextMenu(trayMenu);
    tray.setToolTip("EZ Server tray icon");
    connect(&tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(handleTray(QSystemTrayIcon::ActivationReason)));
    connect(ui->toolButton, &QAbstractButton::clicked, this, &MainWindow::configureServer);
    connect(configure, SIGNAL(setPort(qint16)), this, SLOT(saveSettings(qint16)));
}

///
/// \brief Это деструктор класса
///
MainWindow::~MainWindow() {
    delete ui;
}

///
/// \brief setUsers Это слот установки количества пользователей
/// \param cnt Принимает количество пользователей
///
void MainWindow::setUsers(int num) {
    QString number = QString::number(num);
    ui->usersLine->setText(number);
};

///
/// \brief setState Это слот установки состояния сервера (скорее просто затычка, потому что отслеживать состояние сервера сложновато)
/// \param state Принимает состояние сервера
///
void MainWindow::setState(QString state) {
    ui->statusLine->setText(state);
};

///
/// \brief handleTray Это слот активации меню трея
/// \param reason Принимает причину активации (левое/правое нажатие)
///
void MainWindow::handleTray(QSystemTrayIcon::ActivationReason reason) {
    if (reason == 1) {
        trayMenu->exec();
    } else {
        tray.showMessage("Wrong action", "Try right-clicking the tray icon to see the menu.", QIcon(":/res/tray.png"), 5000);
    }
};

///
/// \brief closeEvent Это перегрузка эвента закрытия основного окна
/// \param event Принимает эвент закрытия
///
void MainWindow::closeEvent(QCloseEvent *event) {
    if (!this->isHidden() && !tray.isVisible()) {
        QMessageBox box;
        box.addButton(tr("Close"), QMessageBox::ActionRole);
        box.addButton(tr("Minimize"), QMessageBox::ActionRole);
        box.setText("Do you want to close or minimize to tray?");
        box.exec();
        if (box.clickedButton()->text() == "Minimize") {
            event->ignore();
            tray.show();
            this->hide();
        } else {
            event->accept();
        }
    };
};

///
/// \brief showAdvanced Это слот, который срабатывает при выборе "показать" в меню трея, он показывает окно и скрывает трей
///
void MainWindow::showAdvanced() {
    this->show();
    tray.hide();
};

///
/// \brief configureServer Это слот, который срабатывает при выборе "конфигурировать" в меню трея, он показывает окно конфига
///
void MainWindow::configureServer() {
    configure->setPortToDialog(this->server);
    configure->show();
};

///
/// \brief firstPortSetup Это функция первичной установки порта
///
void MainWindow::firstPortSetup() {
    qint16 userPort;
    userPort = QInputDialog::getInt(this, "Enter server port:", "Port:", 0, 0, 65535, 1);
    server->serverPort = userPort;
    saveSettings(userPort);
    server->startup();
};

///
/// \brief saveSettings Это слот сохранения настроек сервера
/// \param port Принимает только порт, но если нужно будет сохранять другие настройки - их можно легко добавить
///
void MainWindow::saveSettings(qint16 port) {
    qDebug() << "Port received:";
    qDebug() << port;
    setup->setValue("serverport", port);
    setup->sync();
};


