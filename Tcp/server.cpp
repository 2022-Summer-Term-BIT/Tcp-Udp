#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    // ui init
    ui->ipLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("9999");

    // 实例化 init
    server = new QTcpServer(this);
    // 监听
    server->listen(QHostAddress(ui->ipLineEdit->text()), ui->portLineEdit->text().toInt());

    // 新的连接
    connect(server, &QTcpServer::newConnection, this, [=]()
    {
        // 接收客户端的套接字对象 accept
        // sock_addr 结构体 == 类 QTcpSocket
        conn = server->nextPendingConnection();
        ui->recordEdit->append("有新的连接...");

        // 保证conn是一个有效对象
        connect(conn, &QTcpSocket::readyRead, this, [=]()
        {
            // 接收数据
            QByteArray array = conn->readAll();
            ui->recordEdit->append("Client:" + array);
        });
    });

    // 发送
    connect(ui->sendButton, &QPushButton::clicked, this, [=]()
    {
        // 发送数据
        conn->write(ui->inputEdit->toPlainText().toUtf8().data());
        ui->recordEdit->append("Me:" + ui->inputEdit->toPlainText());
        // clear
        ui->inputEdit->clear();
    });
}

Server::~Server()
{
    delete ui;
}

