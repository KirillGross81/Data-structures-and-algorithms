#include <stdio.h>

struct list
{
   int elem;
   list *next;

   list(int _elem = 0, list *_next = nullptr)
      : elem(_elem), next(_next) {}

   bool empty() { return this == nullptr; }

   list *find_tail()
   {
      auto tail = this;
      for ( ; tail && tail->next != this; tail = tail->next);
      return tail;
   }

   // Добавление элемента в конец списка
   void push_back(list *&head, int elem)
   {
      list *tail = head->find_tail();

      auto l = new list(elem);

      if (head->empty())
      {
         head = tail = l;
         head->next = tail;
         tail->next = head;
         return;
      }

      tail->next = l;
      l->next = head;
   }
};

// Создание списка размера n
void create_list(list *&head, int n)
{
   for (int i = 1; i < n + 1; head->push_back(head, i++));
}

// Функция удаления ребят из круга
void remove(list *p, int k)
{
   auto head = p->next;
   if (head->empty()) return;

   auto prev = head->find_tail();

   auto curr = head, last_p = p;
   int count = 1;

   for ( ; !head->next->empty(); )
   {
      // Если найден k-тый элемент
      if (count == k)
      {
         prev->next = curr->next;

         // Запомининаем текущий элемент и ставим сразу после фиктивного звена
         auto tmp = curr;
         if (curr == head) head = curr->next;
         curr = curr->next;
         last_p->next = tmp;
         last_p = tmp;

         last_p->next = head;
         count = 1;

         //Если остался один элемент
         if (head == head->next) head->next = nullptr;
      }
      else
      {
         prev = curr;
         curr = curr->next;
         count++;
      }
   }
}

// Чтение данных из файла
void input(int &n, int &k)
{
   FILE *f = nullptr;

   if (fopen_s(&f, "in.txt", "r")) return;

   // Чтение n и k
   fscanf_s(f, "%d %d", &n, &k);
}

list *process(int n, int k)
{
   auto p = new list(); // Создание фиктивного звена

   list *head = nullptr;

   create_list(head, n);
   p->next = head; // Фиктивное звено указывает на голову списка

   remove(p, k);

   return p;
}

// Вывод измененного списка в файл
void output(list *p, int n, int k)
{
   FILE *f = nullptr;
   if (fopen_s(&f, "out.txt", "w")) return;

   fprintf_s(f, "Поочередно удаленные номера: \n");

   auto curr = p->next;

   // Выводим значения каждого круга удаления
   do
   {
      fprintf_s(f, "%d ", curr->elem);

      if (n < k)
         fprintf_s(f, "\n");

      else if (curr->next && curr->elem > curr->next->elem) 
         fprintf_s(f, "\n");

      curr = curr->next;

   } 
   while (curr && curr != p);
}

int main()
{
   int n = 0, k = 0;

   input(n, k);
   if (n > 0 && k > 0) output(process(n, k), n, k);

   return 0;
}