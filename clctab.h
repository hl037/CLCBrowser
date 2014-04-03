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

#ifndef CLCTAB_H
#define CLCTAB_H

#include "common.h"
#include <QWidget>

#include <QWebView>

class QLineEdit;

class CLCTab : public QWidget
{
   Q_OBJECT
   friend class Model;
   friend class CLCWindow;

private:
   QString p_name;
   QString p_path;

   QWebView * p_webView;
   QLineEdit * p_addr_le;

public:
   CLCTab(const QString & _name, const QString & _path, QWidget *parent = 0);
   ~CLCTab();

   inline const QString & name() { return p_name; }
   inline const QString & path() { return p_path; }
   inline QUrl url() { return p_webView->url(); }

public slots:
   void load(const QUrl & url);
   void load(QString addr);
   void changeAddr(const QUrl & url);
   void changeAddr(const QString & addr);
   void loadAddrBar();

};

#endif // CLCTAB_H
