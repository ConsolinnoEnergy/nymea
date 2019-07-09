/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stürz <simon.stuerz@guh.io>                   *
 *  Copyright (C) 2014 Michael Zanetti <michael_zanetti@gmx.net>           *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  nymea is free software: you can redistribute it and/or modify          *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 2 of the License.                *
 *                                                                         *
 **
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with nymea. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "nymeatestbase.h"

using namespace nymeaserver;

class TestActions: public NymeaTestBase
{
    Q_OBJECT

private slots:
    void executeAction_data();
    void executeAction();

    void getActionType_data();
    void getActionType();

};

void TestActions::executeAction_data()
{
    QTest::addColumn<DeviceId>("deviceId");
    QTest::addColumn<ActionTypeId>("actionTypeId");
    QTest::addColumn<QVariantList>("actionParams");
    QTest::addColumn<Device::DeviceError>("error");

    QVariantList params;
    QVariantMap param1;
    param1.insert("paramTypeId", mockWithParamsActionParam1ParamTypeId);
    param1.insert("value", 5);
    params.append(param1);
    QVariantMap param2;
    param2.insert("paramTypeId", mockWithParamsActionParam2ParamTypeId);
    param2.insert("value", true);
    params.append(param2);

    QTest::newRow("valid action") << m_mockDeviceId << mockWithParamsActionTypeId << params << Device::DeviceErrorNoError;
    QTest::newRow("invalid deviceId") << DeviceId::createDeviceId() << mockWithParamsActionTypeId << params << Device::DeviceErrorDeviceNotFound;
    QTest::newRow("invalid actionTypeId") << m_mockDeviceId << ActionTypeId::createActionTypeId() << params << Device::DeviceErrorActionTypeNotFound;
    QTest::newRow("missing params") << m_mockDeviceId << mockWithParamsActionTypeId << QVariantList() << Device::DeviceErrorMissingParameter;
    QTest::newRow("async action") << m_mockDeviceId << mockAsyncActionTypeId << QVariantList() << Device::DeviceErrorNoError;
    QTest::newRow("broken action") << m_mockDeviceId << mockFailingActionTypeId << QVariantList() << Device::DeviceErrorSetupFailed;
    QTest::newRow("async broken action") << m_mockDeviceId << mockAsyncFailingActionTypeId << QVariantList() << Device::DeviceErrorSetupFailed;
}

void TestActions::executeAction()
{
    QFETCH(DeviceId, deviceId);
    QFETCH(ActionTypeId, actionTypeId);
    QFETCH(QVariantList, actionParams);
    QFETCH(Device::DeviceError, error);

    QVariantMap params;
    params.insert("actionTypeId", actionTypeId);
    params.insert("deviceId", deviceId);
    params.insert("params", actionParams);
    QVariant response = injectAndWait("Actions.ExecuteAction", params);
    qDebug() << "executeActionresponse" << response;
    verifyDeviceError(response, error);

    // Fetch action execution history from mock device
    QNetworkAccessManager nam;
    QSignalSpy spy(&nam, SIGNAL(finished(QNetworkReply*)));

    QNetworkRequest request(QUrl(QString("http://localhost:%1/actionhistory").arg(m_mockDevice1Port)));
    QNetworkReply *reply = nam.get(request);
    spy.wait();
    QCOMPARE(spy.count(), 1);
    reply->deleteLater();
    QByteArray data = reply->readAll();

    if (error == Device::DeviceErrorNoError) {
        QVERIFY2(actionTypeId == ActionTypeId(data), QString("ActionTypeId mismatch. Got %1, Expected: %2")
                 .arg(ActionTypeId(data).toString()).arg(actionTypeId.toString()).toLatin1().data());
    } else {
        QVERIFY2(data.length() == 0, QString("Data is %1, should be empty.").arg(QString(data)).toLatin1().data());
    }

    // cleanup for the next run
    spy.clear();
    request.setUrl(QUrl(QString("http://localhost:%1/clearactionhistory").arg(m_mockDevice1Port)));
    reply = nam.get(request);
    spy.wait();
    QCOMPARE(spy.count(), 1);
    reply->deleteLater();

    spy.clear();
    request.setUrl(QUrl(QString("http://localhost:%1/actionhistory").arg(m_mockDevice1Port)));
    reply = nam.get(request);
    spy.wait();
    QCOMPARE(spy.count(), 1);
    reply->deleteLater();
    data = reply->readAll();
    qDebug() << "cleared data:" << data;

}

void TestActions::getActionType_data()
{
    QTest::addColumn<ActionTypeId>("actionTypeId");
    QTest::addColumn<Device::DeviceError>("error");

    QTest::newRow("valid actiontypeid") << mockWithParamsActionTypeId << Device::DeviceErrorNoError;
    QTest::newRow("invalid actiontypeid") << ActionTypeId::createActionTypeId() << Device::DeviceErrorActionTypeNotFound;
}

void TestActions::getActionType()
{
    QFETCH(ActionTypeId, actionTypeId);
    QFETCH(Device::DeviceError, error);

    QVariantMap params;
    params.insert("actionTypeId", actionTypeId.toString());
    QVariant response = injectAndWait("Actions.GetActionType", params);

    verifyDeviceError(response, error);

    if (error == Device::DeviceErrorNoError) {
        QVERIFY2(ActionTypeId(response.toMap().value("params").toMap().value("actionType").toMap().value("id").toString()) == actionTypeId, "Didn't get a reply for the same actionTypeId as requested.");
    }
}

#include "testactions.moc"
QTEST_MAIN(TestActions)
