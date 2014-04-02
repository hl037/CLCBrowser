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

#include <QTabWidget>
#include <QStatusBar>
#include <QBoxLayout>
#include <QResizeEvent>
#include "model.h"
#include "clctab.h"

CLCWindow::CLCWindow(const QString & _name, QWidget *parent)
: QMainWindow(parent),
p_name(_name),
p_tabs(new QTabWidget),
p_size_lab(new QLabel)
{
   setAttribute(Qt::WA_DeleteOnClose, true);
   setWindowTitle(p_name);
   setCentralWidget(p_tabs);
   statusBar()->addWidget(p_size_lab);
   p_size_lab->setTextInteractionFlags(
      Qt::TextSelectableByMouse |
      Qt::TextSelectableByKeyboard |
      Qt::LinksAccessibleByMouse |
      Qt::LinksAccessibleByKeyboard
   );
}

CLCWindow::~CLCWindow()
{
   Model::get().windowDestroyed(this);
}

void CLCWindow::resizeEvent(QResizeEvent * )
{
   printSize();
}

void CLCWindow::moveEvent(QMoveEvent * )
{
   printSize();
}

void CLCWindow::printSize()
{
   p_size_lab->setText(tr("Window geometry : %1").arg(QString("%1x%2+%3+%4").arg(width()).arg(height()).arg(x()).arg(y())));
}

void CLCWindow::addTab(CLCTab * t)
{
   p_tabs->addTab(t, t->name());
   connect(t->p_webView, SIGNAL(statusBarMessage(QString)), statusBar(), SLOT(showMessage(QString)));
}
