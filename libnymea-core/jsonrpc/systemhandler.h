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

#ifndef SYSTEMHANDLER_H
#define SYSTEMHANDLER_H

#include <QObject>

#include "jsonrpc/jsonhandler.h"

#include "platform/platform.h"
#include "platform/package.h"
#include "platform/repository.h"

namespace nymeaserver {

class SystemHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit SystemHandler(Platform *platform, QObject *parent = nullptr);

    QString name() const override;

    Q_INVOKABLE JsonReply *GetCapabilities(const QVariantMap &params);

    Q_INVOKABLE JsonReply *Restart(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *Reboot(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *Shutdown(const QVariantMap &params) const;

    Q_INVOKABLE JsonReply *GetUpdateStatus(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *CheckForUpdates(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *GetPackages(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *UpdatePackages(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *RollbackPackages(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *RemovePackages(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *GetRepositories(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *EnableRepository(const QVariantMap &params) const;

    Q_INVOKABLE JsonReply *GetTime(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *SetTime(const QVariantMap &params) const;
    Q_INVOKABLE JsonReply *GetTimeZones(const QVariantMap &params) const;

    Q_INVOKABLE JsonReply *GetSystemInfo(const QVariantMap &params) const;

signals:
    void CapabilitiesChanged(const QVariantMap &params);

    void UpdateStatusChanged(const QVariantMap &params);
    void PackageAdded(const QVariantMap &params);
    void PackageChanged(const QVariantMap &params);
    void PackageRemoved(const QVariantMap &params);
    void RepositoryAdded(const QVariantMap &params);
    void RepositoryChanged(const QVariantMap &params);
    void RepositoryRemoved(const QVariantMap &params);

    void TimeConfigurationChanged(const QVariantMap &params);

private slots:
    void onCapabilitiesChanged();

private:
    Platform *m_platform = nullptr;
};

}

#endif // SYSTEMHANDLER_H
