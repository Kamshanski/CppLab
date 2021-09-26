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
двухсвязного списка;
 добавление книги, отсортированной по автору;
 добавление книги перед указанной книгой;
 добавление книги после указанной книги.
 удаление выбранной книги.
 при выдаче каждой книги на руки вводится номер УДК, и программа
уменьшает значение количества книг на единицу или выдает сообщение о том, что
требуемой книги в библиотеке нет или требуемая книга находится на руках;
 при возвращении каждой книги вводится номер УДК, и программа
увеличивает значение количества книг на единицу;
 по запросу выдаются сведения о наличии книг в библиотеке
 */

template<typename T>
struct DoublyLinkedList {
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

    Node* getNode(int i) {
        Node* node = start;
        for (int j = 0; j < i; ++j) {
            node = node->next;
        }
        return node;
    }

    void addInEmpty(T* item) {
        start = new Node(item);
        end = start;
        _size++;
    }

public:
    int size() {return _size;}

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
            Node* nn = new Node(item);
            nn->prev = end;
            end->next = nn;
            end = nn;
            _size++;
        }
    }

    void addAt(int pos, T* item) {
        if (pos < 0 || pos > _size) {
            throw out_of_range("Index out of bounds. Size: " + to_string(_size) + ". Index: " + to_string(pos));
        }
        if (pos == _size) {
            addLast(item);
        } else if (_size == 0) {
            addInEmpty(item);
        } else {
            Node* nn = new Node(item);
            Node *n = getNode(pos);
            nn->next = n;
            nn->prev = n->prev;
            if (n->prev != nullptr) {
                n->prev->next = nn;
                n->prev = nn;
            } else {
                start = nn;
            }
            _size++;
        }
    }

    void addSorted(T* item, function<int(T*, T*)> comparator) {
        if (_size == 0) {
            addInEmpty(item);
        } else {
            Node *n = start;
            int i = 0;
            for (; i < _size; ++i) {
                if (comparator(n->item, item) > 0) {
                    break;
                }
                n = n->next;
            }
            if (i == _size) {
                addLast(item);
            } else {
                addAt(i, item);
            }
        }
    }

    bool remove(function<bool(T*)> predicate) {
        Node* node = start;
        for (int i = 0; i < _size; ++i) {
            if (predicate(node->item)) {
                if (node == start) {
                    start = start->next;
                    if (start != nullptr) {
                        start->prev = nullptr;
                    } else {
                        end = nullptr;
                    }
                } else {
                    node->prev->next = node->next;
                    if (node->next != nullptr) {
                        node->next->prev = node->prev;
                    } else {
                        end = nullptr;
                    }
                }
                delete node;
                _size--;
                return true;
            }
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


struct Library15 : Library {
private:
    DoublyLinkedList<Book> list;

public:
    explicit Library15(BookReader *reader) : Library(reader) {}
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
            list.addAt( pos, book);
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
            if (pos == list.size() - 1) {
                list.addLast(book);
            } else {
                list.addAt(pos + 1, book);
            }
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