#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <list>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>

class Server : public QObject {
    Q_OBJECT
private:
    ///
    /// \brief tcpServer Лень менять название, это WebSocket сервер
    ///
    QWebSocketServer* tcpServer;

    ///
    /// \brief client Это клиент сервера
    ///
    QWebSocket* client;

    ///
    /// \brief db Это база данных для хранения истории
    /// \brief db Он содержит всю историю, а не только последние 10 сообщений, потому что так проще и лучше
    ///
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    ///
    /// \brief Это конструктор класса Server
    /// \param parent принимает в качестве аргумента ссылку на объект-родитель
    ///
    explicit Server(QObject *parent = nullptr);

    ///
    /// \brief users Это список подключённых пользователей
    ///
    std::list<QWebSocket*> users;

    ///
    /// \brief someList Это список, содержащий последние сообщения
    ///
    std::list<QByteArray> someList;

    ///
    /// \brief Эта функция комплектует системное сообщение
    /// \param msg этот параметр - текст системного сообщения
    /// \return возвращает QByteArray, содержащий системное сообщение
    ///
    QByteArray SystemCall(QString msg);

    ///
    /// \brief dbpath Это путь к базе данных
    ///
    QString dbpath;
    ///
    /// \brief Эта функция записывает последние 10 сообщений в бд
    /// Можно было бы реализовать запись по закрытию программы
    /// Но для этого нужно было бы использовать системные сигналы
    /// Которые сильно разнятся от системы к системе
    /// Поэтому ради совместимости платформ было решено записывать историю после каждого нового сообщения
    /// Это также увеличит надёжность в случаях перебоев питания
    ///
    void archive();

    ///
    /// \brief startup Это функция запуска самого сервера
    ///
    void startup();

    ///
    /// \brief serverPort Это поле, содержащее порт сервера
    ///
    qint16 serverPort;
private slots:

    ///
    /// \brief Это слот, который срабатывает при подключении пользователя
    ///
    void connectUser();

    ///
    /// \brief Это слот, срабатывающий по сигналу readyRead со стороны пользователя
    ///
    void runClientAction(QByteArray data);

    ///
    /// \brief Этот слот срабатывает, когда пользователь отключается
    ///
    void userLeft();

signals:
    ///
    /// \brief updateUsers Это сигнал для обновления данных о количестве подключённых пользователей
    /// \param num Принимает количество пользователей
    ///
    void updateUsers(int num);

    ///
    /// \brief updateState Это сигнал для обновления состояния сервера
    /// \param state Принимает состояние сервера
    ///
    void updateState(QString state);

    ///
    /// \brief showMessageOnServer Это сигнал для вывода сообщения в окно сервера
    /// \param message Принимает само сообщение
    ///
    void showMessageOnServer(QString message);
};
#endif // SERVER_H
