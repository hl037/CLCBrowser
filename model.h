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

#ifndef MODEL_H
#define MODEL_H

#include "common.h"
#include <QObject>
#include "singleton.h"

#include <QHash>
#include <QString>
#include <QUrl>

class CLCWindow;
class CLCTab;

class Model : public QObject, public Singleton<Model>
{
   Q_OBJECT
   friend class Singleton<Model>;
private:
   explicit Model(QObject *parent = 0);

   QHash<QString, CLCWindow *> p_windows;
   QHash<QString, CLCTab *> p_tabs;


   /**
    * load \p url in specified \p tabpath.
    * \note tabpath must be \c window%tab.
    */
   void pm_loadUrl(const QString & tabpath, const QUrl & url);

public:
   void loadUrl(const QString & tabpath, const QUrl & url);
   void deleteTab(const QString & tabpath);
   void execJs(const QString & tabpath, const QString & js);

   QString listTabs();

signals:

public slots:

};

#endif // MODEL_H
