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

#ifndef SINGLETON_H
#define SINGLETON_H

#include "common.h"

#include <assert.h>

template <class T>
class Singleton
{

private:
   static T * obj;

public:
   template <typename... Args>
   static void ini(Args... args)
   {
      if (!obj)
      {
         obj = new T(std::forward<Args>(args)...);
      }
   }

   static T & get()
   {
      assert(obj);
      return *obj;
   }

   static const T & getConst()
   {
      assert(obj);
      return *obj;
   }

   static T * getPtr()
   {
      assert(obj);
      return obj;
   }

   static const T * getConstPtr()
   {
      assert(obj);
      return obj;
   }

   static void destroy()
   {
      delete obj;
      obj = nullptr;
   }
};

template <class T>
T*  Singleton<T>::obj = nullptr;

#endif // SINGLETON_H
