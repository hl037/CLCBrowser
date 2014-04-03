/*******************************************
 *
 * Copyright © 2014 Léo Flaventin Hauchecorne
 *
 * This file is part of CLCBrowser.
 *
 * CLCBrowser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CLCBrowser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CLCBrowser. If not, see <http://www.gnu.org/licenses/>.
 *
 ********************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "common.h"
#include <QSettings>

class Settings : public QSettings
{
   Q_OBJECT
public:
   explicit Settings(const QString &organization, const QString &application = QString(), QObject *parent = 0);
   Settings(Scope scope, const QString &organization, const QString &application = QString(), QObject *parent = 0);
   Settings(Format format, Scope scope, const QString &organization, const QString &application = QString(), QObject *parent = 0);
   Settings(const QString &fileName, Format format, QObject *parent = 0);
   explicit Settings(QObject *parent = 0);

   QVariant value(const QString &key, const QVariant &defaultValue = QVariant());

signals:

public slots:

};

#endif // SETTINGS_H
