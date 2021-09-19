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
struct Stack {
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

    void push(T* item) {
        Node* n = new Node(item);
        n->next = start;
        n->prev = nullptr;
        if (start != nullptr) {
            start->prev = n;
        }
        start = n;
        if (end == nullptr) {
            end = start;
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

struct Library16_1 : Library {
    explicit Library16_1(BookReader *reader) : Library(reader) {}

    void directInsert(Book *book) override {
        insertSorted(book);
    }

    void printAll() override {
        Stack<Book> temp;
        int size = stack.size();
        for (int i = 0; i < size; ++i) {
            Book* b = stack.pop();
            temp.push(b);
            wcout << i << ") " << *b << endl;
        }
        for (int i = 0; i < size; ++i) {
            stack.push(temp.pop());
        }
    }

protected:
    Stack<Book> stack;

    void insertSorted(Book* book) override {
        if (stack.size() == 0) {
            stack.push(book);
            return;
        }

        Stack<Book> temp;
        while (stack.size() > 0) {
            Book* item = stack.pop();
            if (authorComparator(item, book) > 0) {
                stack.push(item);
                break;
            }
            temp.push(item);
        }
        stack.push(book);
        while (temp.size() > 0) {
            stack.push(temp.pop());
        }
    }

    bool insertBefore(wstring bookId) override {
        Stack<Book> temp;
        bool found;
        while (true) {
            if (stack.size() == 0) {
                found = false;
                break;
            }

            Book* item = stack.pop();
            if (item->id == bookId) {
                stack.push(item);
                Book* book = readBook();
                stack.push(book);
                found = true;
                break;
            }
            temp.push(item);
        }
        while (temp.size() > 0) {
            stack.push(temp.pop());
        }
        return found;
    }

    bool insertAfter(wstring bookId) override {
        Stack<Book> temp;
        bool found;
        while (true) {
            if (stack.size() == 0) {
                found = false;
                break;
            }

            Book* item = stack.pop();
            if (item->id == bookId) {
                Book* book = readBook();
                stack.push(book);
                stack.push(item);
                found = true;
                break;
            }
            temp.push(item);
        }
        while (temp.size() > 0) {
            stack.push(temp.pop());
        }
        return found;
    }

    bool deleteBook(wstring bookId) override {
        Stack<Book> temp;
        bool found;
        while (true) {
            if (stack.size() == 0) {
                found = false;
                break;
            }

            Book* item = stack.pop();
            if (item->id == bookId) {
                found = true;
                break;
            }
            temp.push(item);
        }
        while (temp.size() > 0) {
            stack.push(temp.pop());
        }
        return found;
    }

    Book* getBookById(wstring &bookId) override {
        Stack<Book> temp;
        Book* result = nullptr;
        while (true) {
            if (stack.size() == 0) {
                break;
            }

            Book* item = stack.pop();
            temp.push(item);
            if (item->id == bookId) {
                result = item;
                while (temp.size() > 0) {
                    stack.push(temp.pop());
                }
                break;
            }
        }
        while (temp.size() > 0) {
            stack.push(temp.pop());
        }
        return result;
    }
};
