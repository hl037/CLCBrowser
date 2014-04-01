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

#include "clctab.h"

#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>

CLCTab::CLCTab(const QString & _name, const QString & _path, QWidget * parent) :
QWidget(parent),
p_name(_name),
p_path(_path),
p_webView(new QWebView)
{
   QVBoxLayout * l0 = new QVBoxLayout;

   QHBoxLayout * l1 = new QHBoxLayout;
   QLabel * p_addr_lab = new QLabel(tr("address"));
   l1->addWidget(p_addr_lab);
   p_addr_le = new QLineEdit();
   connect(p_addr_le, SIGNAL(returnPressed()), this, SLOT(loadAddrBar()));
   connect(p_webView, SIGNAL(urlChanged(QUrl)), this, SLOT(changeAddr(QUrl)));
   l1->addWidget(p_addr_le);
   QProgressBar * p_progress = new QProgressBar();
   p_progress->setValue(100);
   connect(p_webView, SIGNAL(loadProgress(int)), p_progress, SLOT(setValue(int)));
   l1->addWidget(p_progress);
   l0->addLayout(l1);

   l0->addWidget(p_webView);
   setLayout(l0);
}

CLCTab::~CLCTab()
{

}

void CLCTab::load(const QUrl & url)
{
   p_webView->load(url);
   p_addr_le->setText(url.toString());
}

void CLCTab::load(const QString & addr)
{
   p_webView->load(QUrl(addr));
   p_addr_le->setText(addr);
}

void CLCTab::changeAddr(const QUrl & url)
{
   p_addr_le->setText(url.toString());
}

void CLCTab::changeAddr(const QString & addr)
{
   p_addr_le->setText(addr);
}

void CLCTab::loadAddrBar()
{
   load(p_addr_le->text());
}
