#include <stdio.h>
#include <windows.h>

const int N = 5;
struct queue
{
   int beg, end;
   int data[N] {};

   void init()
   {
      beg = -1;
      end = -1;
   }

   queue() { init(); }

   bool empty() { return end == -1; }

   void push(int elem)
   {
      if ((end + 1) % N == beg)
      {
         puts("Очередь заполнена");
         return;
      }
      if (beg == -1) beg = 0;

      end = (end + 1) % N;
      data[end] = elem;
   }

   int pop()
   {
      if (empty())
      {
         puts("Очередь пустая");
         return -1;
      }

      auto tmp = data[beg];

      if (beg == end) init();
      else beg = (beg + 1) % N;

      printf_s("Взятый элемент: %d\n", tmp);
      return tmp;
   }

   void print()
   {
      if (empty())
      {
         puts("Пустая очередь");
         return;
      }

      UCHAR i = 0;
      for (i = beg; i != end; i = (i + 1) % N)
         printf_s("%d ", data[i]);
      printf_s("%d\n", data[end]);
   }
};