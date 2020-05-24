/*Предметная область: Библиотека
Информационные объекты: Библиотека, Библиотекарь, Книги, Авторы, Посетитель
У книги может быть только один автор.
Посетитель посещает библиотеку с целью найти книгу по имени автора И/ИЛИ по названию книги.
Необходимо реализовать данный функционал, придерживаясь принципов DRY, KISS, YAGNI и Single Responsibility Principle*/

#include <iostream>
#include <string>
#include <vector>

class Book {
private:
    std::string name;
    std::string author;
public:
    Book(std::string name, std::string author) {
        this->name = name;
        this->author = author;
    }

    std::string getName() {
        return name;
    }

    std::string getAuthor() {
        return author;
    }
};

class Library {
private:
    std::vector<Book *> books;
public:
    explicit Library(std::vector<Book *> books) {
        this->books = books;
    }

    std::vector<Book *> getLib(){
        return books;
    }

    void addBook(Book &book) {
        books.push_back(&book);
    }

    int findBook(std::string name, std::string author) {

        size_t size = books.size();
        int result = 0;

        if (name != "" && author != "") {
            for (int i = 0; i < size; ++i) {
                if (books[i]->getName() == name && books[i]->getAuthor() == author) {
                    result = i;
                }
            }
        } else if (name == "" && author != "") {
            for (int i = 0; i < size; ++i) {
                if (books[i]->getAuthor() == author) {
                    result = i;
                }
            }
        } else if (name != "" && author == "") {
            for (int i = 0; i < size; ++i) {
                if (books[i]->getName() == name) {
                    result = i;
                }
            }
        } else if (name == "" && author == "") {
            result = -1;
        }
        return result;
    }

    void offerBook(int bookNumber) {
        if (bookNumber == -1) {
            std::cout << "Не указан автор и название книги!\n";
            std::cout<<std::endl;
        } else {
            std::cout << "Мы нашли вашу книгу!\n";
            std::cout << "Название: " << books[bookNumber]->getName() << std::endl;
            std::cout << "Автор: " << books[bookNumber]->getAuthor() << std::endl;
            std::cout<<std::endl;
        }
    }

};

class Librarian : Library {
private:
    std::string name;
public:
    Librarian(std::string name, std::vector<Book *> books) : Library(books){
        this->name = name;
    }

    void lookForBook(std::string name, std::string author) {
        offerBook(findBook(name, author));
    }
};

int main() {

    Book a1 ("Смешарики", "Шайхинуров");
    Book a2 ("Смешарики1", "Шайхинуров1");
    Book a3 ("Смешарики2", "Шайхинуров2");
    Book a4 ("Смешарики3", "Шайхинуров3");
    Book a5 ("Смешарики4", "Шайхинуров4");

    Library A({});
    A.addBook(a1);
    A.addBook(a2);
    A.addBook(a3);
    A.addBook(a4);
    A.addBook(a5);

    Librarian L1("Слава", A.getLib());

    L1.lookForBook("Смешарики3", "Шайхинуров3");
    L1.lookForBook("Смешарики", "");
    L1.lookForBook("", "Шайхинуров4");
    L1.lookForBook("", "");

    return 0;
}