#ifndef LAB_LIBRARY_H
#define LAB_LIBRARY_H

using namespace std;

struct Book {
    wstring id;     // УДК
    wstring author; // фамилию и инициалы автора
    wstring name;   // название
    int year;       // год издания
    int count;      // количество экземпляров данной книги в библиотеке

    Book(wstring id, wstring author, wstring name, int year, int count) :
            id(id),
            author(author),
            name(name),
            year(year),
            count(count) {}

    Book(wistream& is) {
        wcout << L"УДК: ";
        wcin  >> id;

        wcout << L"Автор: ";
        wcin >>  author;

        wcout << L"Название: ";
        wcin  >> name;

        wcout << L"Год: ";
        wcin >> year;

        wcout << L"Количество: ";
        wcin >> count;
    }

    friend wostream &operator<<(wostream &os, const Book &book) {
        os << book.id << " " << book.author << " " << book.name << " " << book.year << " " << book.count;
        return os;
    }
};

struct BookReader {
    virtual Book* readBook() = 0;
    virtual wstring readBookId(const wstring& additionalMsg) = 0;
};

struct WBookReader: BookReader {
    Book *readBook() override {
        wcout << L"Введите книгу: УДК, автор, название, год выпуска и количество книг в наличии\n";
        Book* b = new Book(wcin);
        return b;
    }

    wstring readBookId(const wstring &additionalMsg) override {
        wcout << L"Введите УДК книги"<< additionalMsg <<":  \t";
        wstring inputId;
        wcin >> inputId;
        return inputId;
    }
};

struct Library {
    BookReader* reader;

    Library(BookReader* reader) : reader(reader) {}

public:
    virtual void directInsert(Book* book) = 0;

    Book* readBook() {
        return reader->readBook();
    }

    wstring readBookId(const wstring& additionalMsg) {
        return reader->readBookId(additionalMsg);
    }

    virtual void printAll() = 0;

    void insertSorted() {
        Book* book = readBook();
        insertSorted(book);
    }

    bool insertBefore() {
        wstring inputId = readBookId(L", перед которой нужно вставить книгу");
        if (!insertBefore(inputId)) {
            alertBookIsAbsent(inputId);
            return false;
        }
        return true;
    }

    bool insertAfter() {
        wstring inputId = readBookId(L", после которой нужно вставить книгу");
        if (!insertAfter(inputId)) {
            alertBookIsAbsent(inputId);
            return false;
        }
        return true;
    }

    bool deleteBook() {
        wstring inputId = readBookId(L", которую нужно удалить");
        bool success = deleteBook(inputId);
        if (success) {
            wcout << L"Книга была удалена" << endl;
            return true;
        } else {
            alertBookIsAbsent(inputId);
            return false;
        }
    }

    bool changeBookCount(wstring& inputId, int delta) {
        Book* b = getBookById(inputId);
        if (b != nullptr) {
            b->count += delta;
            if (b->count < 0) {
                b->count = 0;
                wcout << L"Все экземпляры этой книги на руках" << endl;
                return false;
            }
            return true;
        } else {
            wcout << L"Такой книги нет" << endl;
            return false;
        }
    }

    void issueBook() {
        wstring inputId = readBookId(L", которую нужно выдать");

        if (changeBookCount(inputId, -1)) {
            wcout << L"Книга была успешно выдана" << endl;
        }
    }

    void returnBook() {
        wstring inputId = readBookId(L", которую нужно вернуть");

        if (changeBookCount(inputId, 1)) {
            wcout << L"Книга была успешно возвращена" << endl;
        }
    }

    void checkPresence() {
        wstring inputId = readBookId(L", наличие которой нужно проверить");

        Book* book = getBookById(inputId);
        wcout << ((book == nullptr)
                  ? L"Такой книги нет"
                  : (book->count == 0)
                    ? L"Все экземпляры этой книги на руках"
                    : L"Количество экземпляров в наличии: " + to_wstring(book->count)
        );
    }


protected:
    function<int(Book*, Book*)> authorComparator = [](Book* b1, Book* b2) -> int {
        return b1->author > b2->author ? 1 : (b1->author < b2->author) ? -1 : 0;
    };

    void alertBookIsAbsent(const wstring& id) {
        wcout << L"Такой книги нет: " << id << endl;
    }

    virtual void insertSorted(Book* book) = 0;

    virtual bool insertBefore(wstring bookId) = 0;
    virtual bool insertAfter(wstring bookId) = 0;
    virtual bool deleteBook(wstring bookId) = 0;
    virtual Book* getBookById(wstring& inputId) = 0;
};


#endif //LAB_LIBRARY_H
