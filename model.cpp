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

#include "model.h"

#include "clcwindow.h"
#include "clctab.h"

Model::Model(QObject *parent) :
QObject(parent)
{
}

void Model::pm_loadUrl(const QString & tabpath, const QUrl & url)
{
   CLCTab * tab;
   QHash<QString, CLCTab *>::iterator it = p_tabs.find(tabpath);
   if(it == p_tabs.end())
   {
      CLCWindow * win;
      QStringList l = tabpath.split(QChar('%'));
      QHash<QString, CLCWindow *>::iterator it2 = p_windows.find(l.first());
      if(it2 == p_windows.end())
      {
         win = new CLCWindow(l.first());
         p_windows.insert(l[0], win);
         win->show();
      }
      else
      {
         win = it2.value();
      }
      tab = new CLCTab(l[1], tabpath);
      win->addTab(tab);
      p_tabs.insert(tabpath, tab);
   }
   else
   {
      tab = it.value();
   }
   tab->load(url);
}

void Model::loadUrl(const QString & tabpath, const QUrl & url)
{
   switch(tabpath.count(QChar('%')))
   {
   case 0:
   //TODO : gérer avec les options new window/tab
      pm_loadUrl("1%"+(tabpath.isEmpty() ? "1" : tabpath), url);
      break;
   case 1:
      pm_loadUrl(tabpath, url);
      break;
   default:
   //TODO : gérer ce cas.
      break;
   }
}

void Model::deleteTab(const QString & tabpath)
{
   CLCTab * tab;
   QHash<QString, CLCTab *>::iterator it = p_tabs.find(tabpath);
   if(it == p_tabs.end())
   {
      return;
   }
   else
   {
      tab = it.value();
      CLCWindow * win;
      QStringList l = tabpath.split(QChar('%'));
      QHash<QString, CLCWindow *>::iterator it2 = p_windows.find(l.first());
      Q_ASSERT(it2 != p_windows.end());
      win = it2.value();
      win->p_tabs->removeTab(win->p_tabs->indexOf(tab));
      tab->deleteLater();
      p_tabs.erase(it);
      if(!win->p_tabs->count())
      {
         win->deleteLater();
         p_windows.erase(it2);
      }
   }
}

void Model::execJs(const QString & tabpath, const QString & js)
{
   //TODO
}

QString Model::listTabs()
{
   QString pattern = "%1:%2\n";
   QString res;
   QHash<QString, CLCTab *>::iterator it = p_tabs.begin(), end = p_tabs.end();
   for(; it != end ; ++it)
   {
      res += pattern.arg(it.key(), it.value()->url().toString());
   }
   return res;
}
