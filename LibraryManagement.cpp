#include <iostream>
#include <vector>
using namespace std;

// We gonna need Book, User and Library classes for basic library management system
class Book
{
public:
    // Book having title, author name and number of copies available
    string title;
    string author;
    int availableCopies; // Stor number of copies of book
    // Default constructor for Book class
    Book(const string &title, const string &author, int copies = 1)
        : title(title), author(author), availableCopies(copies) {}
};

class User
{
public:
    string name;
    vector<Book> borrowedBooks; // Container to store borrowed books
    // Default constructor for User class
    User(const string &name) : name(name) {}
};

class Library
{
public:
    vector<Book> books; // Container to store books available in library

    // Method for Adding book to library
    void addBook(const Book &book)
    {
        books.push_back(book);
    }

    // Method for View books available in library
    vector<Book> viewAvailableBooks() const
    {
        vector<Book> availableBooks;
        for (const Book &book : books)
        {
            if (book.availableCopies > 0)
            {
                availableBooks.push_back(book);
            }
        }
        return availableBooks;
    }

    // Method for borrowing book based on Book title given by user
    bool borrowBook(const string &title, User &user)
    {
        for (Book &book : books)
        {
            if (book.title == title && book.availableCopies > 0)
            {
                if (user.borrowedBooks.size() < 2)
                {
                    book.availableCopies--;
                    user.borrowedBooks.push_back(book);
                    return true;
                }
                else
                {
                    cout << "Borrowing limit reached.\n";
                }
            }
        }
        return false;
    }

    // Method for returning book based on title input by User
    void returnBook(const string &title, User &user)
    {
        for (auto it = user.borrowedBooks.begin(); it != user.borrowedBooks.end(); ++it)
        {
            if (it->title == title)
            {
                for (Book &book : books)
                {
                    if (book.title == title)
                    {
                        book.availableCopies++;
                    }
                }
                user.borrowedBooks.erase(it);
                return;
            }
        }
        cout << "Book not found in borrowed list.\n";
    }
};

int main()
{
    Library library;
    User user = User("Sumit"); // Initialising user instance

    int choice; // choice from user

    do
    {
        // Available choices for user
        cout << "\nLibrary Menu:\n";
        cout << "1. View available books\n";
        cout << "2. Add a book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Executing functions according to user choice
        switch (choice)
        {
        case 1:
        {
            vector<Book> availableBooks = library.viewAvailableBooks();
            if (availableBooks.empty())
            {
                cout << "The library is empty.\n";
            }
            else
            {
                cout << "Available books:\n";
                for (const Book &book : availableBooks)
                {
                    cout << book.title << " by " << book.author << " (Available: " << book.availableCopies << ")\n";
                }
            }
            break;
        }
        case 2:
        {

            string title, author;
            int copies;
            cout << "Enter the title of the book to add: ";
            cin >> title;
            cout << "Enter the author of the book: ";
            cin >> author;
            cout << "Enter the number of copies to add: ";
            cin >> copies;
            library.addBook(Book(title, author, copies));
            cout << "Book added successfully.\n";
            break;
        }
        case 3:
        {
            string title;
            cout << "Enter the title of the book to borrow: ";
            cin >> title;
            if (library.borrowBook(title, user))
            {
                cout << "Book borrowed successfully.\n";
            }
            break;
        }
        case 4:
        {
            string title;
            cout << "Enter the title of the book to return: ";
            cin >> title;
            library.returnBook(title, user);
            break;
        }
        case 5:
        {
            cout << "Exiting...\n";
            break;
        }
        default:
        {
            cout << "Invalid choice.\n";
        }
        }
    } while (choice != 5);

    return 0;
}
