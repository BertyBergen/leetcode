#include <stdio.h>       // Подключаем стандартную библиотеку ввода-вывода
#include <stdlib.h>      // Подключаем библиотеку для работы с памятью (malloc, free)

// Определение структуры ListNode — узел односвязного списка
struct ListNode {
    int val;             // Значение узла (одна цифра числа)
    struct ListNode *next; // Указатель на следующий узел
};

// Функция, складывающая два числа, представленных списками
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy = {0, NULL}; // Фиктивный (временный) узел-голова для результата
    struct ListNode *tail = &dummy;    // Указатель на последний узел в списке результата
    int carry = 0;                     // Перенос при сложении (например, 9 + 8 = 17, перенос = 1)

    // Пока есть хотя бы один элемент в списках или есть перенос
    while (l1 || l2 || carry) {
        int sum = carry;              // Начинаем с переноса

        if (l1) {                     // Если есть элемент в первом списке
            sum += l1->val;          // Добавляем его значение к сумме
            l1 = l1->next;           // Переходим к следующему узлу
        }

        if (l2) {                     // Аналогично для второго списка
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;            // Обновляем перенос (если сумма ≥ 10)
        int digit = sum % 10;        // Оставляем только текущую цифру

        struct ListNode *node = malloc(sizeof *node); // Выделяем память под новый узел
        node->val = digit;           // Записываем цифру
        node->next = NULL;           // Пока это последний узел, следующий = NULL

        tail->next = node;           // Присоединяем новый узел к результату
        tail = node;                 // Перемещаем tail на новый последний узел
    }

    return dummy.next;               // Возвращаем результат, пропуская фиктивный узел
}

// Функция для создания нового узла со значением `val`
struct ListNode* createNode(int val) {
    struct ListNode* node = malloc(sizeof *node); // Выделяем память
    node->val = val;              // Присваиваем значение
    node->next = NULL;            // Изначально он ни на что не указывает
    return node;                  // Возвращаем указатель на новый узел
}

// Функция для печати содержимого списка
void printList(struct ListNode* head) {
    while (head) {                          // Пока есть узлы
        printf("%d", head->val);            // Печатаем значение узла
        if (head->next) printf(" -> ");     // Если есть следующий узел, печатаем стрелку
        head = head->next;                  // Переходим к следующему узлу
    }
    printf("\n");                           // Завершаем строку
}

// Функция для очистки памяти списка
void freeList(struct ListNode* head) {
    while (head) {                          // Пока есть узлы
        struct ListNode* tmp = head;        // Сохраняем текущий узел
        head = head->next;                  // Переходим к следующему
        free(tmp);                          // Освобождаем память текущего узла
    }
}

int main() {
    // Создаем список, представляющий число 342 (в обратном порядке: 2 -> 4 -> 3)
    struct ListNode* l1 = createNode(2);
    l1->next = createNode(4);
    l1->next->next = createNode(3);

    // Создаем второй список, представляющий число 465 (в обратном порядке: 5 -> 6 -> 4)
    struct ListNode* l2 = createNode(5);
    l2->next = createNode(6);
    l2->next->next = createNode(4);

    // Складываем два числа
    struct ListNode* result = addTwoNumbers(l1, l2);

    // Печатаем результат: 807 → 7 -> 0 -> 8
    printf("Result: ");
    printList(result);

    // Освобождаем всю выделенную память
    freeList(l1);
    freeList(l2);
    freeList(result);

    return 0; // Завершение программы
}
