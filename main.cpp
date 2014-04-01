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

#include "clcwindow.h"
#include <QApplication>

#include "clctab.h"
#include "clcserver.h"
#include "model.h"
#include "settings.h"
#include <QTcpSocket>
#include <QFile>
#include <QProcess>
#include <iostream>

int main(int argc, char *argv[])
{
   Settings settings;
   QTcpSocket * sock = new QTcpSocket();
   sock->connectToHost(
      settings.value("host", QVariant(QString("localhost"))).toString(),
      settings.value("port", QVariant(qint16(7777))).toInt()
   );

   if(!sock->waitForConnected())
   {

      if(QString(argv[argc-1]) == "-")
      {
         --argc;
         QApplication a(argc, argv);
         Model::ini();
         CLCServer serv;
         serv.listen(QHostAddress::Any, settings.value("port", QVariant(qint16(7777))).toInt());
         QFile * f = new QFile();
         f->open(1, QFile::WriteOnly);
         f->close();
         delete f;
         serv.parseArgs(a.arguments(), f);
         return a.exec();
      }
      else
      {
         QStringList l;
         for(int i=1 ; i<argc ; ++i)
         {
            l<<argv[i];
         }
         l<<"-";
         QProcess::startDetached(argv[0], l);
         return 0;
      }
   }
   else
   {
      QStringList l;
      for(int i=1 ; i<argc ; ++i)
      {
         l<<("\"" + QString(argv[i]).replace("\"", "\\\"") + "\"");
      }
      sock->write(l.join(" ").toUtf8()+"\n");
      sock->waitForBytesWritten();
      sock->waitForReadyRead(500);
      std::cout << QString::fromUtf8(sock->readAll()).toStdString() << std::endl;
      return 0;
   }
}
