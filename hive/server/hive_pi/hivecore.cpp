#include "hivecore.h"
#include <QDebug>

HiveCore::HiveCore(QObject *parent) :
    QObject(parent)
{
    // start the server
    m_server = new Server(this);
    m_server->startServer();

    // create 433.92 MHz sender
    m_sender = new RadioSender(this);
    m_sender->setFrequency(RadioSender::RF433MHz);
    m_sender->setLineCode(RadioSender::REMOTE);
    m_sender->setPulseLength(320);
    //m_sender->sendBin("000000000000010101010001");

    // create 433.92 MHz receiver
    m_reciver = new RadioReciver(this);
    m_reciver->setFrequency(RadioReciver::RF433MHz);
    m_reciver->enableReceiver();


}
