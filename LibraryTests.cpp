#include "lib/googletest/include/gtest/gtest.h"
//#include "lib/googlemock/include/gmock/gmock.h"
#include "Lab14/Library14.cpp"
#include "Lab15/Library15.cpp"
#include "Lab16/Library16_1.cpp"
#include "Lab16/Library16_2.cpp"
namespace {
    // wstring id, wstring author, wstring name, int year, int count
    struct TestBookReader: BookReader {
        Book** books;
        wstring* ids;

        int iBooks = 0;
        int iId = 0;

        Book* readBook() override {
            Book* b = this->books[iBooks++];
            wcout << endl << L"Fake book from terminal: " << *b << endl ;
            return b;
        }

        wstring readBookId(const wstring &additionalMsg) override {
            wstring* b = &this->ids[iId++];;
            wcout << endl << L"Fake book id from terminal: " << *b << endl ;
            return *b;
        }

        TestBookReader() {
            books = new Book*[50] {
                // 2
                new Book(L"UDK_20", L"A4", L"N20", 2020, 5),
                new Book(L"UDK_21", L"A4", L"N21", 2020, 5),
                new Book(L"UDK_22", L"A0", L"N22", 2020, 5),
                new Book(L"UDK_23", L"A3", L"N23", 2020, 5),
                new Book(L"UDK_24", L"A+", L"N24", 2020, 5),
                new Book(L"UDK_25", L"A99", L"N25", 2020, 5),

                //3
                new Book(L"UDK_31", L"A30", L"N31", 1950, 9),
                new Book(L"UDK_32", L"A30", L"N32", 1950, 9),
                new Book(L"UDK_33", L"A30", L"N33", 1950, 9),
                new Book(L"UDK_34", L"A30", L"N34", 1950, 9),


                new Book(L"UDK_31", L"A30", L"N31", 1950, 9),
                new Book(L"UDK_32", L"A30", L"N32", 1950, 9),
                new Book(L"UDK_33", L"A30", L"N33", 1950, 9),
                new Book(L"UDK_34", L"A30", L"N34", 1950, 9),
            };

            ids = new wstring[50] {
                // 2
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX",
                // 3
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX",
                // 4
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX", L"UDK_4", L"UDK_6",
                // 5-6
                L"UDK_2", L"UDK_2", L"UDK_2",
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX",
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX",
                // 7
                L"UDK_0", L"UDK_2", L"UDK_8", L"UDK_XX",
            };
        }
    };

    TestBookReader* commonReader = new TestBookReader();

    Library14* getLib14(BookReader* reader = nullptr) {
        Library14* l = new Library14(reader == nullptr ? new TestBookReader() : reader);

        for (int i = 0; i < 5; ++i) {
            Book* book = new Book(
                    L"UDK_" + to_wstring(i*2),
                    L"A" + to_wstring(i*2),
                    L"N" + to_wstring(i*2),
                    rand() % 122 + 1900,
                    rand() % 5);
            l->directInsert(book);
        }
        return l;
    }

    template<typename T>
    T* getLib(function<Library*(BookReader* reader)> libraryEmitter, BookReader* reader = nullptr) {
        Library* l = libraryEmitter(reader == nullptr ? new TestBookReader() : reader);

        for (int i = 0; i < 5; ++i) {
            Book* book = new Book(
                    L"UDK_" + to_wstring(i*2),
                    L"A" + to_wstring(i*2),
                    L"N" + to_wstring(i*2),
                    rand() % 122 + 1900,
                    rand() % 5);
            l->directInsert(book);
        }
        return l;
    }

    void testLibrary(function<Library*(BookReader* reader)> libraryProvider, BookReader* reader = nullptr) {
        setlocale( LC_ALL , "russian_russia.866" );
        _setmode(_fileno(stdout), _O_U8TEXT);

        wcout << "\n\n" << L"1. Вывести все книги" << endl;
        Library* library = libraryProvider(reader);
        library->printAll();


        wcout << "\n\n" << L"2. Добавить книгу, отсортированной по автору (знать бы, что имел ввиду автор)" << endl;
        wprintf(L"\n\nInsert sorted:\n");
        library = libraryProvider(reader);

        for (int i = 0; i < 6; ++i) {
            library->Library::insertSorted();
            library->printAll();
        }


        wcout << "\n\n" << L"3. Добавить книгу после существующей книги" << endl;
        library = libraryProvider(reader);

        for (int i = 0; i < 4; ++i) {
            library->Library::insertAfter();
            library->printAll();
        }


        wcout << "\n\n" << L"4. Добавить книгу перед существующей книгой" << endl;
        library = libraryProvider(reader);

        for (int i = 0; i < 4; ++i) {
            library->Library::insertBefore();
            library->printAll();
        }


        wcout << "\n\n" << L"5. Удалить книгу" << endl;
        library = libraryProvider(reader);
        library->printAll();

        for (int i = 0; i < 6; ++i) {
            library->Library::deleteBook();
            library->printAll();
        }
        library->Library::insertSorted();
        library->printAll();


        wcout << "\n\n" << L"6. Выдать книгу" << endl;
        library = libraryProvider(reader);
        library->printAll();

        for (int i = 0; i < 7; ++i) {
            library->Library::issueBook();
            library->printAll();
        }

        wcout << "\n\n"<< L"7. Вернуть книгу" << endl;

        for (int i = 0; i < 4; ++i) {
            library->Library::returnBook();
            library->printAll();
        }



        wcout << "\n\n" << L"8. Проверить наличие" << endl;
        library = libraryProvider(reader);

        library->printAll();

        for (int i = 0; i < 4; ++i) {
            library->Library::checkPresence();
        }
    }

    Library* fillLibrary(Library* library) {
        for (int i = 0; i < 5; ++i) {
            Book* book = new Book(
                    L"UDK_" + to_wstring(i*2),
                    L"A" + to_wstring(i*2),
                    L"N" + to_wstring(i*2),
                    rand() % 122 + 1900,
                    rand() % 5);
            library->directInsert(book);
        }
        return library;
    }

    TEST(LibraryTest, SignlyLinkedList) {
        auto libraryProvider = [](BookReader* reader) -> Library* {
            Library* l = new Library14(reader == nullptr ? new TestBookReader() : reader);
            return fillLibrary(l);
        };

        testLibrary(libraryProvider, commonReader);
    }

    TEST(LibraryTest, DoublyLinkedList) {
        auto libraryProvider = [](BookReader* reader) -> Library* {
            Library* l = new Library15(reader == nullptr ? new TestBookReader() : reader);
            return fillLibrary(l);
        };

        testLibrary(libraryProvider, commonReader);
    }

    TEST(LibraryTest, Stack) {
        auto libraryProvider = [](BookReader* reader) -> Library* {
            Library* l = new Library16_1(reader == nullptr ? new TestBookReader() : reader);
            return fillLibrary(l);
        };

        testLibrary(libraryProvider, commonReader);
    }

    TEST(LibraryTest, Queue) {
        auto libraryProvider = [](BookReader* reader) -> Library* {
            Library* l = new Library16_2(reader == nullptr ? new TestBookReader() : reader);
            return fillLibrary(l);
        };

        testLibrary(libraryProvider, commonReader);
    }



}