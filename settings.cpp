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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 ********************************************/

#include "settings.h"

Settings::Settings(const QString &organization, const QString &application, QObject *parent) :
QSettings(organization, application, parent)
{

}

Settings::Settings(QSettings::Scope scope, const QString &organization, const QString &application, QObject *parent) :
QSettings(scope, organization, application, parent)
{

}

Settings::Settings(QSettings::Format format, QSettings::Scope scope, const QString &organization, const QString &application, QObject *parent) :
QSettings(format, scope, organization, application, parent)
{

}

Settings::Settings(const QString &fileName, QSettings::Format format, QObject *parent) :
QSettings(fileName, format, parent)
{

}

Settings::Settings(QObject *parent) :
QSettings(parent)
{
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue)
{
   QVariant r = QSettings::value(key, defaultValue);
   if(r == defaultValue)
   {
      setValue(key, defaultValue);
   }
   return r;
}
