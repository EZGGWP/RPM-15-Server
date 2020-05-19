#include <QApplication>
#include <QObject>
#include <csignal>
#include "server.h"
#include "mainwindow.h"

///
/// \brief Это функция мэйн
/// \param argc
/// \param argv
/// \return Возвращает результат выполнения программы
///
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow app;
    app.show();
    return a.exec();
}

