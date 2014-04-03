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

#ifndef CLCWINDOW_H
#define CLCWINDOW_H

#include "common.h"
#include <QMainWindow>
#include <QLabel>

#include <QString>

class Model;
class CLCTab;

class CLCWindow : public QMainWindow
{
   Q_OBJECT
   friend class Model;

private:
   QString p_name;
   QTabWidget * p_tabs;
   QLabel * p_size_lab;

public:
   CLCWindow(const QString & _name, QWidget *parent = 0);
   ~CLCWindow();

   inline const QString & name() { return p_name; }

protected:

   void resizeEvent(QResizeEvent *e);
   void moveEvent(QMoveEvent *e);

   void printSize();

private:
   void addTab(CLCTab * t);
};

#endif // CLCWINDOW_H
