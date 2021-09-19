#include <ostream>
#include <utility>
#include "../utils.cpp"
#include "../sorting.cpp"
#include "../Library.cpp"

using namespace std;
/*
 *  Решить задачу в виде стека, убрав действия, которые невозможно
выполнить над данной структурой.
 *
Составить программу, которая содержит текущую информацию о книгах в
библиотеке. Сведения о книгах включают:
 номер УДК;
 фамилию и инициалы автора;
 название;
 год издания;
 количество экземпляров данной книги в библиотеке.
Программа должна обеспечивать:
 начальное формирование данных обо всех книгах в библиотеке в виде стека
или очереди;
 добавление книги, отсортированной по автору;
 добавление книги перед указанной книгой;
 добавление книги после указанной книги.
 удаление выбранной книги.
 при выдаче каждой книги на руки вводится номер УДК, и программа
уменьшает значение количества книг на единицу или выдает сообщение о том, что
требуемой книги в библиотеке нет или требуемая книга находится на руках;
159
 при возвращении каждой книги вводится номер УДК, и программа
увеличивает значение количества книг на единицу;
 по запросу выдаются сведения о наличии книг в библиотеке.
 */


template<typename T>
struct Queue {
private:
    struct Node {
        T* item;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(T* item) : item(item) {}
    };

    int _size = 0;
    Node* start = nullptr;
    Node* end = nullptr;

public:
    int size() { return _size; }

    void pushEnd(T* item) {
        Node* n = new Node(item);
        n->prev = end;
        n->next = nullptr;
        if (end != nullptr) {
            end->next = n;
        }
        end = n;
        if (start == nullptr) {
            start = end;
        }
        _size++;
    }

    T* pop() {
        Node* top = start;
        if (top == nullptr) {
            return nullptr;
        }
        T* item = top->item;
        start = start->next;
        if (start != nullptr) {
            start->prev = nullptr;
        } else {
            end = nullptr;
        }
        _size--;
        return item;
    }

};

struct Library16_2 : Library {
    explicit Library16_2(BookReader *reader) : Library(reader) {}

    void directInsert(Book *book) override {
        insertSorted(book);
    }

    void printAll() override {
        Queue<Book>* temp = new Queue<Book>;
        int size = queue->size();
        for (int i = 0; i < size; ++i) {
            Book* b = queue->pop();
            temp->pushEnd(b);
            wcout << i << ") " << *b << endl;
        }
        queue = temp;
    }

protected:
    Queue<Book>* queue = new Queue<Book>();

    void insertSorted(Book* book) override {
        Queue<Book>* temp = new Queue<Book>;
        bool found = false;
        while (queue->size() > 0) {
            Book* item = queue->pop();
            if (!found && authorComparator(item, book) > 0) {
                temp->pushEnd(book);
                found = true;
            }
            temp->pushEnd(item);
        }
        if (!found)
            temp->pushEnd(book);

        queue = temp;
    }

    bool insertBefore(wstring bookId) override {
        Queue<Book>* temp = new Queue<Book>;
        bool found = false;
        while (queue->size() > 0) {
            Book* item = queue->pop();
            if (!found && item->id == bookId) {
                Book* book = readBook();
                temp->pushEnd(book);
                found = true;
            }
            temp->pushEnd(item);
        }
        queue = temp;
        return found;
    }

    bool insertAfter(wstring bookId) override {
        Queue<Book>* temp = new Queue<Book>;
        bool found = false;
        while (queue->size() > 0) {
            Book* item = queue->pop();
            temp->pushEnd(item);
            if (!found && item->id == bookId) {
                Book* book = readBook();
                temp->pushEnd(book);
                found = true;
            }
        }
        queue = temp;
        return found;
    }

    bool deleteBook(wstring bookId) override {
        Queue<Book>* temp = new Queue<Book>;
        bool found = false;
        while (queue->size() > 0) {
            Book* item = queue->pop();
            if (!found && item->id == bookId) {
                found = true;
                continue;
            }
            temp->pushEnd(item);
        }
        queue = temp;
        return found;
    }

    Book* getBookById(wstring &bookId) override {
        Queue<Book>* temp = new Queue<Book>;
        Book* result = nullptr;
        bool found = false;
        while (queue->size() >= 0) {
            Book* item = queue->pop();
            temp->pushEnd(item);
            if (!found && item->id == bookId) {
                result = item;
                found = true;
            }
        }
        queue = temp;
        return result;
    }
};
