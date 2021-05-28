#include <iostream> 
#include <cstring>
using namespace std;
void printBooks(struct Books *book);

struct Books{
    char title[50];
    char author[50];
    char subject[100];
    int bookId;
};

int main(){
    struct Books book1; //Declare Book1 of type book
    struct Books book2; //Declare Book2 of type book

    // book 1 spec
    strcpy(book1.title, "Fuck you");
    strcpy(book1.author, "Fuck yourself");
    strcpy(book1.subject, "Fucking Yourself");
    book1.bookId = 69696969;

    // book 2 spec
    strcpy(book2.title, "unFuck you");
    strcpy(book2.author, "unFuck yourself");
    strcpy(book2.subject, "unFucking Yourself");
    book2.bookId = 96969696;

    // print info
    // cout << "Book 1 Title: " << book1.title << endl;
    // cout << "Book 1 Author: " << book1.author << endl;
    // cout << "Book 1 Subject: " << book1.subject << endl;
    // cout << "Book 1 ID: " << book1.bookId << endl;

    // cout << "Book 2 Title: " << book2.title << endl;
    // cout << "Book 2 Author: " << book2.author << endl;
    // cout << "Book 2 Subject: " << book2.subject << endl;
    // cout << "Book 2 ID: " << book2.bookId << endl;

    printBooks(&book1);
    printBooks(&book2);
    return 0;
    }

void printBooks(struct Books *book){
    cout << "Book Title: " << book->title << endl;
    cout << "Book Author: " << book->author << endl;
    cout << "Book Subject: " << book->subject << endl;
    cout << "Book ID: " << book->bookId << endl;
}