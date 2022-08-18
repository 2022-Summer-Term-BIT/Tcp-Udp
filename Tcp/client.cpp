#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    // ui init
    ui->ipLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("9999");

    // init
    client = new QTcpSocket(this);
    // 连接服务器
    client->connectToHost(QHostAddress(ui->ipLineEdit->text()), ui->portLineEdit->text().toInt());
    // 接收数据
    connect(client, &QTcpSocket::readyRead, this, [=]()
    {
        QByteArray array = client->readAll();
        ui->recordEdit->append("Server:" + array);
    });

    // 发送
    connect(ui->sendButton, &QPushButton::clicked, this, [=]()
    {
        client->write(ui->inputEdit->toPlainText().toUtf8().data());
        ui->recordEdit->append("Me:" + ui->inputEdit->toPlainText());
        ui->inputEdit->clear();
    });
}

Client::~Client()
{
    delete ui;
}
