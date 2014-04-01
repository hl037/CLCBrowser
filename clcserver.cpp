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

#include "clcserver.h"
#include "model.h"
#include "cmd_parser.h"

#include <QTcpSocket>
#include <QByteArray>
#include <QCommandLineOption>

CLCServer::CLCServer(QObject * parent):
QTcpServer(parent),
m_parser(),
m_help(QStringList() << "h" << "help", tr("Show help")),
m_tab(QStringList() << "t" << "tab", tr("Path to the tab with format window%tab"), tr("tab path")),
m_del(QStringList() << "d" << "delete", tr("Flag to delete the tab")),
m_list(QStringList() << "l" << "ls" << "list", tr("List the tabs")),
m_exit(QStringList() << "x" << "exit", tr("Exit CLCBrowser"))
{
   m_parser.addPositionalArgument(tr("url"), tr("url to open"), tr("[url]"));
   m_parser.addOption(m_help);
   m_parser.addOption(m_tab);
   m_parser.addOption(m_del);
   m_parser.addOption(m_list);
   m_parser.addOption(m_exit);

   connect(this, SIGNAL(newConnection()), this, SLOT(readConnection()));
}

CLCServer::~CLCServer()
{

}

void CLCServer::parseArgs(const QStringList & args, QIODevice * d)
{
   if(args.isEmpty()) return;
   if(!m_parser.parse(args))
   {
      return;
   }

   QString tab = m_parser.value(m_tab);
   QString addr = m_parser.positionalArguments().isEmpty() ? "" : m_parser.positionalArguments()[0];
   if(m_parser.isSet(m_exit))
   {
      qApp->exit(0);
      return;
   }
   if(m_parser.isSet(m_del))
   {
      Model::get().deleteTab(tab);
      return;
   }
   if(m_parser.isSet(m_list))
   {
      d->write(Model::get().listTabs().toUtf8());
      d->waitForBytesWritten(10000);
      return;
   }
   Model::get().loadUrl(tab, QUrl(addr));
   return;
}

void CLCServer::readConnection()
{
   QTcpSocket * sock = nextPendingConnection();
   sock->waitForReadyRead();
   QByteArray b = sock->readLine();
   if(b.isEmpty()) return;

   const char * cmd = b.data();

   Arguments * a = parse_commandline(cmd);

   QStringList l;
   l << "CLCBrowser";

   for(int i=1 ; i<a->argc ; ++i)
   {
      l << a->argv[i];
   }
   Arguments_destroy(a);

   parseArgs(l, sock);
   sock->close();
}
