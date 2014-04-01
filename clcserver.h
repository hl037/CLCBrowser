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

#ifndef CLCSERVER_H
#define CLCSERVER_H

#include "common.h"
#include <QTcpServer>

#include <QCommandLineParser>
#include <QCommandLineOption>

class CLCServer : public QTcpServer
{
   Q_OBJECT
public:
   CLCServer(QObject * parent = 0);
   ~CLCServer();

protected:
   QCommandLineParser m_parser;

   QCommandLineOption m_help;
   QCommandLineOption m_tab;
   QCommandLineOption m_del;
   QCommandLineOption m_list;
   QCommandLineOption m_exit;

public:
   void parseArgs(const QStringList & args, QIODevice * d);

private slots:
   void readConnection();
};

#endif // CLCSERVER_H
