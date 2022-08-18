#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    // init
    ui->ipLineEdit->setText("127.0.0.1");
    ui->sPortLineEdit->setText("8888");
    ui->cPortLineEdit->setText("9999");

    udp2 = new QUdpSocket(this);

    // must bind a port to receive data
    udp2->bind(ui->cPortLineEdit->text().toInt());

    // send message
    connect(ui->sendButton, &QPushButton::clicked, this, [=]()
    {
        udp2->writeDatagram(ui->msgEdit->toPlainText().toUtf8(), QHostAddress(ui->ipLineEdit->text()), ui->sPortLineEdit->text().toInt());
        ui->recordEdit->append("Me: " + ui->msgEdit->toPlainText());
        ui->msgEdit->clear();
    });

    // read message
    connect(udp2, &QUdpSocket::readyRead, this, [=]()
    {
        qint64 size = udp2->pendingDatagramSize();
        QByteArray array(size, 0);
        udp2->readDatagram(array.data(), size);
        ui->recordEdit->append("Server: " + array);
    });
}

Client::~Client()
{
    delete ui;
}
