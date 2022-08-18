#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    // init
    ui->ipLineEdit->setText("127.0.0.1");
    ui->cPortLineEdit->setText("9999");
    ui->sPortLineEdit->setText("8888");
    ui->recordEdit->setText("New connection...");

    udp1 = new QUdpSocket(this);

    // must bind a port to receive data
    udp1->bind(ui->sPortLineEdit->text().toInt());

    // send message
    connect(ui->sendButton, &QPushButton::clicked, this, [=]()
    {
        udp1->writeDatagram(ui->msgEdit->toPlainText().toUtf8(), QHostAddress(ui->ipLineEdit->text()), ui->cPortLineEdit->text().toInt());
        ui->recordEdit->append("Me: " + ui->msgEdit->toPlainText());
        ui->msgEdit->clear();
    });

    // read message
    connect(udp1, &QUdpSocket::readyRead, this, [=]()
    {
        qint64 size = udp1->pendingDatagramSize();
        QByteArray array(size, 0);
        udp1->readDatagram(array.data(), size);
        ui->recordEdit->append("Client: " + array);
    });

}

Server::~Server()
{
    delete ui;
}

