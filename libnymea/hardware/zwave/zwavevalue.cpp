/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2022, nymea GmbH
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

#include "zwavevalue.h"

#include <QDebug>

ZWaveValue::ZWaveValue()
{

}

ZWaveValue::ZWaveValue(quint64 id, Genre genre, CommandClass commandClass, quint8 instance, quint16 index, Type type, const QString &description):
    m_id(id),
    m_genre(genre),
    m_commandClass(commandClass),
    m_instance(instance),
    m_index(index),
    m_type(type),
    m_description(description)
{

}

quint64 ZWaveValue::id() const
{
    return m_id;
}

ZWaveValue::Genre ZWaveValue::genre() const
{
    return m_genre;
}

ZWaveValue::CommandClass ZWaveValue::commandClass() const
{
    return m_commandClass;
}

quint8 ZWaveValue::instance() const
{
    return m_instance;
}

quint16 ZWaveValue::index() const
{
    return m_index;
}

ZWaveValue::Type ZWaveValue::type() const
{
    return m_type;
}

QVariant ZWaveValue::value() const
{
    return m_value;
}

int ZWaveValue::valueListSelection() const
{
    return m_listSelection;
}

void ZWaveValue::selectListValue(int selection)
{
    m_listSelection = selection;
}

void ZWaveValue::setValue(const QVariant &value, int listSelection)
{
    m_value = value;
    m_listSelection = listSelection;
}

QString ZWaveValue::description() const
{
    return m_description;
}

bool ZWaveValue::isValid() const
{
    return m_value.isValid();
}

QDebug operator<<(QDebug debug, ZWaveValue value)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "Value(ID: " << value.id() << ", "
                    << "Ins: " << value.instance() << ", "
                    << value.genre() << ", "
                    << "Idx: " << value.index() << ", "
                    << value.type() << ", "
                    << value.commandClass() << ", "
                    << "Value: " << value.value()
                    << (value.type() == ZWaveValue::TypeList ? QString(" Selection: %1").arg(value.valueListSelection()) : "" ) << ")";
    return debug;
}
