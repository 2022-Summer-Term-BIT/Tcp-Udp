#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;
    QUdpSocket *udp1;
};
#endif // SERVER_H
