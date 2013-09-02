#include "hiveclientcore.h"
#include <QtQml>
#include <QQmlEngine>
#include <QQuickWindow>

HiveClientCore::HiveClientCore(QObject *parent) :
    QObject(parent)
{

    m_id = 0;
    m_client = new Client(this);

    // QML Typs
    qmlRegisterType<Settings>("hive",1,0,"Settings");

    // QML application window
    m_engine = new QQmlApplicationEngine(this);
    m_engine->load(QUrl("qml/hive_client/main.qml"));

    m_engine->rootContext()->setContextProperty("client", m_client);

    topLevel = m_engine->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    window->show();


}

void HiveClientCore::onConnected()
{
    //sendSomething("device", "getAll");
    sendSomething("device", "add");

}

void HiveClientCore::sendSomething(QString deviceName, QString method)
{
    QVariantMap responseMap;
    responseMap.insert("device", deviceName);
    responseMap.insert("method", method);
    responseMap.insert("id", m_id++);

    QVariantMap params;
    params.insert("deviceType","actor");
    params.insert("name","Schreibtisch On");
    params.insert("protocol","RF433");
    params.insert("linecode","remote");
    params.insert("code","000000000000010101010001");

    responseMap.insert("params", params);

    QJsonDocument doc = QJsonDocument::fromVariant(responseMap);
    qDebug() << "_______________________________________";
    qDebug() << "send to hive:";
    QByteArray json = doc.toJson();
    qDebug() << json;
    m_client->sendData(json);
}
