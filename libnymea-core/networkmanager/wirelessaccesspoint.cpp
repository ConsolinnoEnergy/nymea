/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2020, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU General Public License as published by the Free Software
* Foundation, GNU version 3. This project is distributed in the hope that it
* will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*!
    \class nymeaserver::WirelessAccessPoint
    \brief Represents a wireless access point from a \l{WirelessNetworkDevice}.

    \ingroup networkmanager
    \inmodule core

    \sa WirelessNetworkDevice
*/

/*! \enum nymeaserver::WirelessAccessPoint::ApSecurityMode
    \value ApSecurityModeNone
    \value ApSecurityModePairWep40
    \value ApSecurityModePairWep104
    \value ApSecurityModePairTkip
    \value ApSecurityModePairCcmp
    \value ApSecurityModeGroupWep40
    \value ApSecurityModeGroupWep104
    \value ApSecurityModeGroupTkip
    \value ApSecurityModeGroupCcmp
    \value ApSecurityModeKeyMgmtPsk
    \value ApSecurityModeKeyMgmt8021X
*/

/*! \fn void WirelessAccessPoint::signalStrengthChanged();
    This signal will be emitted when the signalStrength of this \l{WirelessAccessPoint} has changed.
*/

#include "wirelessaccesspoint.h"
#include "loggingcategories.h"
#include "dbus-interfaces.h"

namespace nymeaserver {

/*! Constructs a new \l{WirelessAccessPoint} with the given dbus \a objectPath and \a parent. */
WirelessAccessPoint::WirelessAccessPoint(const QDBusObjectPath &objectPath, QObject *parent) :
    QObject(parent),
    m_objectPath(objectPath),
    m_securityFlags(0)
{
    QDBusInterface accessPointInterface(serviceString, m_objectPath.path(), accessPointInterfaceString, QDBusConnection::systemBus());
    if(!accessPointInterface.isValid()) {
        qCWarning(dcNetworkManager()) << "Invalid access point dbus interface";
        return;
    }

    // Init properties
    setSsid(accessPointInterface.property("Ssid").toString());
    setMacAddress(accessPointInterface.property("HwAddress").toString());
    setFrequency(accessPointInterface.property("Frequency").toDouble() / 1000);
    setSignalStrength(accessPointInterface.property("Strength").toUInt());
    setSecurityFlags(WirelessAccessPoint::ApSecurityModes(accessPointInterface.property("WpaFlags").toUInt()));
    setIsProtected((bool)accessPointInterface.property("Flags").toUInt());

    QDBusConnection::systemBus().connect(serviceString, objectPath.path(), accessPointInterfaceString, "PropertiesChanged", this, SLOT(onPropertiesChanged(QVariantMap)));
}

/*! Returns the dbus object path of this \l{WirelessAccessPoint}. */
QDBusObjectPath WirelessAccessPoint::objectPath() const
{
    return m_objectPath;
}

/*! Returns the ssid of this \l{WirelessAccessPoint}. */
QString WirelessAccessPoint::ssid() const
{
    return m_ssid;
}

void WirelessAccessPoint::setSsid(const QString &ssid)
{
    m_ssid = ssid;
}

/*! Returns the mac address of this \l{WirelessAccessPoint}. */
QString WirelessAccessPoint::macAddress() const
{
    return m_macAddress;
}

void WirelessAccessPoint::setMacAddress(const QString &macAddress)
{
    m_macAddress = macAddress;
}

/*! Returns the frequency of this \l{WirelessAccessPoint}. (2.4 GHz or 5GHz) */
double WirelessAccessPoint::frequency() const
{
    return m_frequency;
}

void WirelessAccessPoint::setFrequency(const double &frequency)
{
    m_frequency = frequency;
}

/*! Returns the signal strength in percentage [0, 100] % of this \l{WirelessAccessPoint}. */
int WirelessAccessPoint::signalStrength() const
{
    return m_signalStrength;
}

void WirelessAccessPoint::setSignalStrength(const int &signalStrength)
{
    m_signalStrength = signalStrength;
    emit signalStrengthChanged();
}

void WirelessAccessPoint::setIsProtected(const bool &isProtected)
{
    m_isProtected = isProtected;
}

/*! Returns true if this \l{WirelessAccessPoint} is password protected. */
bool WirelessAccessPoint::isProtected() const
{
    return m_isProtected;
}

/*! Returns the security flags of this \l{WirelessAccessPoint}.

    \sa ApSecurityModes
*/
WirelessAccessPoint::ApSecurityModes WirelessAccessPoint::securityFlags() const
{
    return m_securityFlags;
}

void WirelessAccessPoint::setSecurityFlags(const WirelessAccessPoint::ApSecurityModes &securityFlags)
{
    m_securityFlags = securityFlags;
}

void WirelessAccessPoint::onPropertiesChanged(const QVariantMap &properties)
{
    if (properties.contains("Strength"))
        setSignalStrength(properties.value("Strength").toUInt());

}

QDebug operator<<(QDebug debug, WirelessAccessPoint *accessPoint)
{
    return debug.nospace() << "AccessPoint(" << accessPoint->signalStrength() << "%, " <<  accessPoint->frequency()<< " GHz, " << accessPoint->ssid() << ", " << (accessPoint->isProtected() ? "protected" : "open" ) << ")";
}

}
