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

#include "cmd_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
   void * d;
   struct Node * next;
} Node;

typedef struct Fifo
{
   Node * first;
   Node * last;
   int size;
   void (*destroy)(void*);
} Fifo;

Fifo *  Fifo_ini(void (*destroy)(void*));
void Fifo_destroy(Fifo * f);
void Fifo_enqueue(Fifo * f, void * d);
void * Fifo_dequeue(Fifo * f);
int Fifo_size(Fifo * f);

Fifo *  Fifo_ini(void (*destroy)(void*))
{
   Fifo * f = malloc(sizeof(Fifo));
   f->first = NULL;
   f->last = NULL;
   f->size = 0;
   f->destroy = destroy;
}

void Fifo_destroy(Fifo * f)
{
   Node * n;
   if(f->destroy)
   {
      while(f->first)
      {
         n = f->first;
         f->first = n->next;
         (f->destroy)(n->d);
         free(n);
      }
   }
   else
   {
      while(f->first)
      {
         n = f->first;
         f->first = n->next;
         free(n);
      }
   }
   free(f);
}

void Fifo_enqueue(Fifo * f, void * d)
{
   Node * n;
   n = malloc(sizeof(Node));
   n->d = d;
   n->next = NULL;
   if(f->last)
   {
      f->last->next = n;
   }
   else
   {
      f->first = n;
   }
   f->last = n;
   ++f->size;
}

void * Fifo_dequeue(Fifo * f)
{
   void * r;
   Node * n = f->first;
   f->first = n->next;
   if(!f->first)
   {
      f->last = NULL;
   }
   r = n->d;
   free(n);
   --f->size;
   return r;
}

int Fifo_size(Fifo * f)
{
   return f->size;
}


Arguments * Arguments_ini(int argc, char ** argv)
{
   Arguments * a = malloc(sizeof(Arguments));
   a->argc = argc;
   a->argv = argv;
   return a;
}

void Arguments_destroy(Arguments * a)
{
   int i;
   for(i=0 ; i<a->argc ; ++i)
   {
      free(a->argv[i]);
   }
   free(a->argv);
   free(a);
}

Arguments * parse_commandline(const char * const cmd)
{
   int cmdlen = 0;
   const char * ptrcmd = cmd;
   char * cpcmd;

   Fifo * current_token = Fifo_ini(NULL); //current token, Fifo<char>
   Fifo * tokens = Fifo_ini(NULL); //token list, Fifo<char *>

   Arguments * a;
   int argc;
   char ** argv;

   int i;

#define WRITE(c) {Fifo_enqueue(current_token, (void*) c);}
#define W WRITE(*ptrcmd)
#define WS {switch(*ptrcmd){ case 'n':WRITE('\n')break; case 'r':WRITE('\r')break; case 't':WRITE('\t')break; default:WRITE(*ptrcmd)break; }}
#define SAVE \
{\
   int len = Fifo_size(current_token);\
   char * str = malloc((len+1) * sizeof(char));\
   for(i=0 ; i<len ; ++i)\
   {\
      str[i] = (char) Fifo_dequeue(current_token);\
   }\
   str[i] = 0;\
   Fifo_enqueue(tokens, str);\
}
#define TO(s) {state = s;}
#define S ' ': case'\t': case '\n': case '\r'


   int state = 1;
   while(*ptrcmd)
   {
      switch(state)
      {
      case 1:
         switch(*ptrcmd)
         {
         case '\'':
            TO(2)
            break;
         case '"':
            TO(3)
            break;
         case S:
            TO(1)
            break;
         default:
            W
            TO(5)
            break;
         }
         break;

      case 2:
         switch(*ptrcmd)
         {
         case '\'':
            TO(5)
            break;
         default:
            W
            TO(2)
            break;
         }
         break;

      case 3:
         switch(*ptrcmd)
         {
         case '\\':
            TO(4)
            break;
         case '"':
            TO(5)
            break;
         default:
            W
            TO(3)
            break;
         }
         break;

      case 4:
         WS
         TO(3)
         break;

      case 5:
         switch(*ptrcmd)
         {
         case '\\':
            TO(6)
            break;
         case '\'':
            TO(2)
            break;
         case '"':
            TO(3)
            break;
         case S:
            SAVE
            TO(1)
            break;
         default:
            W
            TO(5)
            break;
         }
         break;

      case 6:
         WS
         TO(5)
         break;
      }
      ++ptrcmd;
      ++cmdlen;
   }
   if(Fifo_size(current_token))
   {
      SAVE
   }

   argc = Fifo_size(tokens)+1;
   argv = malloc(argc * sizeof(char *));

   cpcmd = malloc((cmdlen+1) * sizeof(char));
   memcpy(cpcmd, cmd, (cmdlen+1) * sizeof(char));

   argv[0] = cpcmd;
   for(i=1 ; i<argc ; ++i)
   {
      argv[i] = Fifo_dequeue(tokens);
   }

   a = Arguments_ini(argc, argv);

   Fifo_destroy(current_token);
   Fifo_destroy(tokens);

   return a;
}
