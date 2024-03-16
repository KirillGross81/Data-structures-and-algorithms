#include <stdio.h>
#include <windows.h>

struct list
{
   int n,	// Степень
      an; // Коэффициент

   list *next;

   list(int _n = 0, int _an = 0, list *_next = nullptr) : n(_n), an(_an), next(_next) { }

   bool empty() { return this == nullptr; }

   list *find_tail(list *head)
   {
      auto c = head;
      for ( ; c && c->next; c = c->next) { }
      return c;
   }

   void push_back(list *&head, int n, int an)
   {
      auto l = new list(n, an);
      auto tail = find_tail(head);

      if (head->empty()) head = tail = l;
      else
      {
         tail->next = l;
         l->next = nullptr;
      }
   }

   void insert_sorted(list *&head, int n, int an)
   {
      auto elem = new list(n, an);

      if (head == nullptr || head->n < elem->n)
      {
         elem->next = head;
         head = elem;
      }
      else
      {
         auto c = head;

         for ( ; c->next && c->next->n > elem->n; c = c->next) { }

         elem->next = c->next;
         c->next = elem;
      }
   }
};

const UCHAR Nmax = 100;

void input(list *&p, list *&q)
{
   FILE *f = nullptr;

   if (fopen_s(&f, "in.txt", "r")) return;

   int n = 0, an = 0, l = 0;

   char str[Nmax] { };

   // Читаем полином P из первой строки
   fgets(str, sizeof(str), f);
   for (auto pt = str; sscanf_s(pt, "%d %d%n", &n, &an, &l) == 2; p->push_back(p, n, an), pt += l) { }

   // Читаем полином Q из второй строки
   fgets(str, sizeof(str), f);
   for (auto pt = str; sscanf_s(pt, "%d %d%n", &n, &an, &l) == 2; q->push_back(q, n, an), pt += l) { }
}

void output(list *r)
{
   FILE *f = nullptr;

   if (fopen_s(&f, "out.txt", "w")) return;

   for ( ; r; r = r->next)
      fprintf_s(f, "%d %d ", r->n, r->an);
}

list *process(list *p, list *q)
{
   list *r = nullptr;

   // Заполняем r элементами из p
   for (auto c = p; c; c = c->next)
      r->push_back(r, c->n, c->an);

   // Сравниваем элементы из q и r
   for (auto c = q; c; c = c->next)
   {
      auto node = r;

      for (auto flag = false; node && !flag; )

         //// Если степени равны
         if (flag = node->n == c->n) node->an += c->an;
         else node = node->next;

      // Если степени не равны
      if (!node)
         r->insert_sorted(r, c->n, c->an);
   }

   return r;
}

int main()
{
   list *p = nullptr, *q = nullptr;

   input(p, q);

   if (!(p->empty() || q->empty()))
      output(process(p, q));

   return 0;
}