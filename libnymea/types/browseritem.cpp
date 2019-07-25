/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2019 Michael Zanetti <michael.zanetti@nymea.io>          *
 *                                                                         *
 *  This file is part of nymea.                                            *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "browseritem.h"


BrowserItem::BrowserItem(const QString &id, const QString &displayName, bool browsable, bool executable):
    m_id(id),
    m_displayName(displayName),
    m_browsable(browsable),
  m_executable(executable)
{

}

QString BrowserItem::id() const
{
    return m_id;
}

QString BrowserItem::displayName() const
{
    return m_displayName;
}

void BrowserItem::setDisplayName(const QString &displayName)
{
    m_displayName = displayName;
}

QString BrowserItem::description() const
{
    return m_description;
}

void BrowserItem::setDescription(const QString &description)
{
    m_description = description;
}

bool BrowserItem::executable() const
{
    return m_executable;
}

void BrowserItem::setExecutable(bool executable)
{
    m_executable = executable;
}

bool BrowserItem::browsable() const
{
    return m_browsable;
}

void BrowserItem::setBrowsable(bool browsable)
{
    m_browsable = browsable;
}

bool BrowserItem::disabled() const
{
    return m_disabled;
}

void BrowserItem::setDisabled(bool disabled)
{
    m_disabled = disabled;
}

BrowserItem::BrowserIcon BrowserItem::icon() const
{
    return m_icon;
}

void BrowserItem::setIcon(BrowserIcon icon)
{
    m_icon = icon;
}

QString BrowserItem::thumbnail() const
{
    return m_thumbnail;
}

void BrowserItem::setThumbnail(const QString &thumbnail)
{
    m_thumbnail = thumbnail;
}

QList<ActionTypeId> BrowserItem::actionTypeIds() const
{
    return m_actionTypeIds;
}

void BrowserItem::setActionTypeIs(const QList<ActionTypeId> &actionTypeIds)
{
    m_actionTypeIds = actionTypeIds;
}

BrowserItem::ExtendedPropertiesFlags BrowserItem::extendedPropertiesFlags() const
{
    return m_extendedPropertiesFlags;
}

QVariant BrowserItem::extendedProperty(const QString &propertyName) const
{
    return m_extendedProperties[propertyName];
}

BrowserItems::BrowserItems()
{

}

BrowserItems::BrowserItems(const QList<BrowserItem> &other): QList<BrowserItem>(other)
{

}
