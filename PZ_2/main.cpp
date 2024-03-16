#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "MyQueue.h"

int main()
{
   setlocale(0, "");

   int num = 0;
   UCHAR choice = 0;
   queue *q = nullptr;

   puts("Операции над очередью:");
   puts("1 - Создать пустую очередь / очистить очередь");
   puts("2 - Вывести очередь");
   puts("3 - Проверить очередь на пустоту");
   puts("4 - Добавить элемент");
   puts("5 - Взять элемент");
   puts("6 - Выход");

   while (choice != 6)
   {
      scanf_s("%hhd", &choice);

      switch (choice)
      {
         case 1: {
            q = new queue();
            puts("Создана пустая очередь");
            break;
         }
         case 2: {
            if(q) q->print();
            else puts("Очередь не инициализирована");
            break;
         }
         case 3: {
            if(q) q->empty() ? puts("Пусто") : puts("Не пусто");
            else puts("Очередь не инициализирована");
            break;
         }
         case 4: {
            if (q)
            {
               printf_s("Элемент: ");
               scanf_s("%d", &num);
               q->push(num);
            }
            else puts("Очередь не инициализирована");
            break;
         }
         case 5:
            if (q) q->pop();
            else puts("Очередь не инициализирована");
            break;
         default:
            return 0;
            break;
      }
   }

   return 0;
}