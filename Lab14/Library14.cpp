#include <ostream>
#include <utility>
#include "../utilities.cpp"
#include "../sorting.cpp"
#include "../Library.cpp"

using namespace std;
/*
Составить программу, которая содержит текущую информацию о книгах в
библиотеке. Сведения о книгах включают:
 номер УДК;
 фамилию и инициалы автора;
 название;
 год издания;
 количество экземпляров данной книги в библиотеке.

Программа должна обеспечивать:
 начальное формирование данных обо всех книгах в библиотеке в виде
односвязного списка;
 добавление книги, отсортированной по автору;
 добавление книги перед указанной книгой;
 добавление книги после указанной книги.
 удаление выбранной книги.
 при выдаче каждой книги на руки вводится номер УДК, и программа
уменьшает значение количества книг на единицу или выдает сообщение о том, что
требуемой книги в библиотеке нет или требуемая книга находится на руках;
 при возвращении каждой книги вводится номер УДК, и программа
увеличивает значение количества книг на единицу;
 по запросу выдаются сведения о наличии книг в библиотеке.
 */

template<typename T>
struct SinglyLinkedList {
private:
    struct Node {
        T* item;
        Node* next = nullptr;

        Node(T* item) : item(item) {}
    };

    int _size = 0;
    Node* start = nullptr;

    Node* getNode(int i) {
        Node* node = start;
        for (int j = 0; j < i; ++j) {
            node = node->next;
        }
        return node;
    }

    void addInEmpty(T* item) {
        start = new Node(item);
        _size++;
    }

public:
    T* get(int i) {
        if (i < 0 || i >= _size) {
            return nullptr;
            //throw out_of_range("Index out of bounds. Size: " + to_string(_size) + ". Index: " + to_string(i));
        }

        Node* node = getNode(i);
        return node->item;
    }

    int indexOf(function<bool(T*)> predicate) {
        Node* node = start;
        for (int i = 0; i < _size; ++i) {
            if (predicate(node->item)) {
                return i;
            }
            node = node->next;
        }
        return -1;
    }

    void addLast(T* item) {
        if (_size == 0) {
            addInEmpty(item);
        } else {
            Node *n = getNode(_size - 1);
            n->next = new Node(item);
            _size++;
        }
    }

    void addAt(int pos, T* item) {
        if (pos < -1 || pos >= _size) {
            throw out_of_range("Index out of bounds. Size: " + to_string(_size) + ". Index: " + to_string(pos));
        }

        if (_size == 0) {
            addInEmpty(item);
        } else if (pos == -1) {
            Node* node = new Node(item);
            node->next = start;
            start = node;
            _size++;
        } else {
            Node *prev = getNode(pos);
            Node* node = prev->next;
            Node* nn = new Node(item);
            prev->next = nn;
            nn->next = node;
            _size++;
        }
    }

    void addSorted(T* item, function<int(T*, T*)> comparator) {
        Node* n = start;
        Node* prev = start;
        for (int i = 0; i < _size; ++i) {
            if (comparator(n->item, item) > 0) {
                break;
            }
            prev = n;
            n = n->next;
        }
        if (prev == nullptr) {
            addLast(item);
        } else if (n == start) {
            Node* nn = new Node(item);
            nn->next = start;
            start = nn;
            _size++;
        } else {
            Node* nn = new Node(item);
            nn->next = prev->next;
            prev->next = nn;
            _size++;
        }
    }

    bool remove(function<bool(T*)> predicate) {
        Node *node = start;
        Node* prev = start;
        for (int i = 0; i < _size; ++i) {
            if (predicate(node->item)) {
                if (prev == nullptr) {
                    return false;
                } else if (prev == start) {
                    start = start->next;
                } else {
                    prev->next = (node == nullptr) ? nullptr : node->next;
                }
                _size--;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    void forEach(function<void(T*, int)> consumer) {
        Node* n = start;
        for (int i = 0; i < _size; ++i) {
            consumer(n->item, i);
            n = n->next;
        }
    }
};



struct Library14 : Library {
    explicit Library14(BookReader *reader) : Library(reader) {}

private:
    SinglyLinkedList<Book> list;

public:
    void printAll() override {
        list.forEach([](const Book* book, int position) {
            wcout << position << ") " << *book << endl;
        });
    }

    void directInsert(Book* book) override {
        list.addSorted(book, authorComparator);
    }

protected:
    void insertSorted(Book* book) override {
        list.addSorted(book, authorComparator);
    }

    bool insertBefore(wstring bookId) override {
        int pos = list.indexOf([&bookId](Book* b) -> bool {
            return b->id == bookId;
        });
        if (pos < 0) {
            return false;
        } else {
            Book* book = readBook();
            list.addAt(pos-1, book);
        }
        return true;
    }

    bool insertAfter(wstring bookId) override {
        int pos = list.indexOf([&bookId](Book* b) -> bool {
            return b->id == bookId;
        });
        if (pos < 0) {
            return false;
        } else {
            Book* book = readBook();
            list.addAt(pos, book);
        }
        return true;
    }

    bool deleteBook(wstring bookId) override {
        return list.remove([&bookId](Book* b) -> bool {
            return b->id == bookId;
        });
    }

    Book* getBookById(wstring& inputId) override {
        int i = list.indexOf([&inputId](Book* b) -> bool {
            return b->id == inputId;
        });
        return list.get(i);
    }
};