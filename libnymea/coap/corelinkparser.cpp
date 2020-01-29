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
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*!
    \class CoreLinkParser
    \brief Provides an easy way to parse a CoRE link list.

    \ingroup coap-group
    \inmodule libnymea

    \section2 Example

    \code
        if (reply->contentType == CoapPdu::ApplicationLink) {
            CoreLinkParser parser(reply->payload());

            foreach (const CoreLink &link, parser.links()) {
                qDebug() << link;
            }
        }
    \endcode

    \sa CoreLink

*/

#include "corelinkparser.h"

#include <QDebug>

/*! Constructs a CoRE link parser with the given \a parent. The given \a data should contain a CoRE link list from the discovery. */
CoreLinkParser::CoreLinkParser(const QByteArray &data, QObject *parent) :
    QObject(parent),
    m_data(data)
{
    QList<QByteArray> linkList = data.split(',');
    foreach (const QByteArray &linkLine, linkList) {
        QList<QByteArray> valueList = linkLine.split(';');
        CoreLink link;
        foreach (const QByteArray &value, valueList) {
            if (value.startsWith("<")) {
                link.setPath(QString(value.mid(1, value.length() - 2)));
            } else if (value.startsWith("rt=")) {
                link.setResourceType(QString(value.right(value.length() - 3)).remove('"'));
            } else if (value.startsWith("if=")) {
                link.setInterfaceDescription(QString(value.right(value.length() - 3)).remove('"'));
            } else if (value.startsWith("sz=")) {
                link.setMaximumSize(value.right(value.length() - 3).toInt());
            } else if (value.startsWith("ct=")) {
                link.setContentType(static_cast<CoapPdu::ContentType>(value.right(value.length() - 3).toUInt()));
            } else if (value.startsWith("title=")) {
                link.setTitle(QString(value.right(value.length() - 6)).remove('"'));
            } else if (value == "obs") {
                link.setObservable(true);
            }
        }
        m_links.append(link);
    }
}

/*! Returns the parsed list of \l{CoreLink}{CoreLinks}.*/
QList<CoreLink> CoreLinkParser::links() const
{
    return m_links;
}
