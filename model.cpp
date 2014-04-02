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

void Model::addWindow(CLCWindow * w)
{
   p_windows.insert(w->name(), w);
}

void Model::addTab(CLCTab * t)
{
   p_tabs.insert(t->path(), t);
}

void Model::pm_loadUrl(const QString & tabpath, const QString & url)
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
         addWindow(win);
         win->show();
      }
      else
      {
         win = it2.value();
      }
      tab = new CLCTab(l[1], tabpath);
      win->addTab(tab);
      addTab(tab);
   }
   else
   {
      tab = it.value();
   }
   tab->load(url);
}

QString Model::loadUrl(const QString & tabpath, const QString & url)
{
   QString p;
   switch(tabpath.count(QChar('%')))
   {
   case 0:
   //TODO : gérer avec les options new window/tab
      p = "1%"+(tabpath.isEmpty() ? "1" : tabpath);
      pm_loadUrl(p, url);
      return p;
   case 1:
      pm_loadUrl(tabpath, url);
      return tabpath;
   default:
   //TODO : gérer ce cas.
      return QString();
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
   (void)tabpath;
   (void)js;
   //TODO
}

void Model::resizeWindow(const QString & windowpath, const QString & w_geometry)
{
   QHash<QString, CLCWindow *>::iterator it = p_windows.find(windowpath);
   if(it == p_windows.end()) return;
   CLCWindow * window = it.value();
   QStringList w_offset = w_geometry.split(QChar('+'));
   QStringList w_size = w_offset[0].split('x');
   int x,y,w,h;
   if(w_size.size() == 2)
   {
      w = w_size[0].toInt();
      h = w_size[1].toInt();
   }
   else
   {
      w = window->width();
      h = window->height();
   }
   if(w_offset.size() == 3)
   {
      x = w_offset[1].toInt();
      y = w_offset[2].toInt();
   }
   else
   {
      x = window->x();
      y = window->y();
   }
   window->setGeometry(x, y, w, h);
}

void Model::resizeWindow(const QString & windowpath, const QRect & w_geometry)
{
   QHash<QString, CLCWindow *>::iterator it = p_windows.find(windowpath);
   if(it == p_windows.end()) return;
   CLCWindow * window = it.value();
   window->setGeometry(w_geometry);
}

QString Model::getWindowPath(const QString & tabpath)
{
   QStringList l = tabpath.split(QChar('%'));
   return l[0];
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

void Model::windowDestroyed(CLCWindow * w)
{
   p_windows.remove(w->name());
}

void Model::tabDestroyed(CLCTab * t)
{
   p_tabs.remove(t->path());
}
