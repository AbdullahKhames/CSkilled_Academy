#ifndef LIBRARY_LIBRARY_H_
#define LIBRARY_LIBRARY_H_

#include "../dynamicarray/dynamicarray.h"
#include <algorithm>
#include <string>


struct Book {
	int id;
	string name;
	int quantity;
	int currentQuantity;

	Book(int id, string name, int size)
		: id(id), name(name), quantity(size), currentQuantity(size) {}

	bool hasPrefix(const string& prefix) const {
		if (prefix.size() > name.size()) return false;
		for (size_t i = 0; i < prefix.size(); ++i) {
			if (name[i] != prefix[i]) return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& output, const Book& book) {
		output << "id : " << book.id
		       << " name : " << book.name
		       << " quantity : " << book.quantity
		       << " total borrowed : " << book.quantity - book.currentQuantity;
		return output;
	}
};

struct User {
	int id;
	string name;
	User(int id, string name): id(id), name(name) {}
};


struct BookUser {
	Book *book = nullptr;
	User *user = nullptr;
	BookUser(Book *book) : book(book) {}
	BookUser(Book *book, User *user) : book(book), user(user) {}
};

inline bool cmpByName(Book* book1, Book* book2) {
	return book1->name < book2->name;
}

inline bool cmpById(Book* book1, Book* book2) {
	return book1->id < book2->id;
}

struct Library {
	int idx = 0;
	int userIdx = 0;
	DynamicArray<User> users{5};
	DynamicArray<Book> books{5};
	DynamicArray<BookUser> borrowedBooks{5};


	void librarySystem() {
		int choice = 0;
		while (choice != 10) {
			menu();
			cin >> choice;
			switch (choice)
			{
				case 1:
					this->addBook();
					break;
				case 2:
					this->searchBooksByPrefix();
					break;
				case 3:
					this->searchBooksBorrowers();
					break;
				case 4:
					this->listLibraryById();
					break;
				case 5:
					this->listLibraryByName();
					break;
				case 6:
					this->addUser();
					break;
				case 7:
					this->borrowBook();
					break;
				case 8:
					this->returnBook();
					break;
				case 9:
					this->printUsers();
					break;
				default:
					cout << "invalid choice please choose from 1- 10";
			}
		}
		
	}
	void menu() {
		cout << "********************************************************************" << endl;
		cout << "Library Menu : " << endl;
		cout << "1- Add Book" << endl;
		cout << "2- search books by prefix" << endl;
		cout << "3- print who borrowed book by name" << endl;
		cout << "4- print library by id" << endl;
		cout << "5- print library by name" << endl;
		cout << "6- add user" << endl;
		cout << "7- user borrow book" << endl;
		cout << "8- user return book" << endl;
		cout << "9- print users" << endl;
		cout << "10- exit" << endl;
		cout << "Enter Your Menu Choice [1 - 10] : " << endl;
		cout << "********************************************************************" << endl;

	}
	Book* findBook() {
		string name;
		cout << "Enter Book name : " << endl;
		cin >> name;
		return findBook(name);
	}
	User* findUser() {
		string name;
		cout << "Enter User name : " << endl;
		cin >> name;
		return findUser(name);
	}
	Book* findBook(string &name) {
		Book* temp = nullptr;
		for (int i = 0; i < books.getSize(); i++) {
			if (books.get(i) && books.get(i)->name == name) {
				temp = books.get(i);
				break;
			}
		}
		return temp;
	}
	User* findUser(string &name) {
		User* temp = nullptr;
		for (int i = 0; i < users.getSize(); i++) {
			if (users.get(i) && users.get(i)->name == name) {
				temp = users.get(i);
				break;
			}
		}
		return temp;
	}
	DynamicArray<BookUser>* findBookUserByBook(Book *book) {
		DynamicArray<BookUser> *bookUsers = new DynamicArray<BookUser>(5);
		BookUser* temp = nullptr;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			temp = borrowedBooks.get(i);
			if (temp && temp->book == book) {
				bookUsers->push_back(temp);
			}
		}
		return bookUsers;
	}

	DynamicArray<BookUser>* findBookUserByBook(string &name) {
		DynamicArray<BookUser> *bookUsers = new DynamicArray<BookUser>(5);
		BookUser* temp = nullptr;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			temp = borrowedBooks.get(i);
			if (temp && temp->book->name == name) {
				bookUsers->push_back(temp);
			}
		}
		return bookUsers;
	}
	DynamicArray<BookUser>* findBookUserByUser(User *user) {
		DynamicArray<BookUser> *bookUsers = new DynamicArray<BookUser>(5);
		BookUser* temp = nullptr;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			temp = borrowedBooks.get(i);
			if (temp && temp->user == user) {
				bookUsers->push_back(temp);
			}
		}
		return bookUsers;
	}

	DynamicArray<BookUser>* findBookUserByUser(string &name) {
		DynamicArray<BookUser> *bookUsers = new DynamicArray<BookUser>(5);
		BookUser* temp = nullptr;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			temp = borrowedBooks.get(i);
			if (temp && temp->user->name == name) {
				bookUsers->push_back(temp);
			}
		}
		return bookUsers;
	}
	void addBook() {
		idx += 10;
		string name;
		int size;
		cout << "enter book name and quantity ! " << endl;
	 	cin >> name >> size;
		books.push_back(new Book{idx, name, size});
	}

	void searchBooksByPrefix() {
		string prefix;
		cout << "Enter Book name prefix : " << endl;
		cin >> prefix;
		for (int i = 0; i < books.getSize(); i++) {
			Book* temp = books.get(i);
			if (temp && temp->hasPrefix(prefix)) {
				cout << temp->name << endl;
			}
		}
	}

	void listLibraryById() {
		Book** arr = books.getArr();
		sort(arr, arr + books.getSize(), cmpById);
		for (int i = 0; i < books.getSize(); i++) {
			cout << *arr[i] << endl;
		}
	}

	void listLibraryByName() {
		Book** arr = books.getArr();
		sort(arr, arr + books.getSize(), cmpByName);
		for (int i = 0; i < books.getSize(); i++) {
			cout << *arr[i] << endl;
		}
	}
	
	void searchBooksBorrowers() {
		string name;
		cout << "Enter Book name : " << endl;
		cin >> name;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			BookUser* temp = borrowedBooks.get(i);
			if (temp && temp->book->name == name) {
				cout << temp->user->name << endl;
			}
		}
	}
	
	void addUser() {
		this->userIdx += 10;
		string name;
		cout << "Enter User name : " << endl;
		cin >> name;
		User *user = findUser(name);
		if (user != nullptr)
		{
			cout << "please choose different username" << endl;
		}
		
		this->users.push_back(new User(this->userIdx, name));
	}
	
	void borrowBook() {
		string userName, bookName;
		cout << "Enter User name and book name: " << endl;
		cin >> userName >> bookName;
		// find book and user first!
		Book *book = findBook(bookName);
		if (book == nullptr || book->currentQuantity <= 0)
		{
			cout << " book not found with given name " << bookName << endl;
			return;
		}
		
		User *user = findUser(userName);
		if (user == nullptr)
		{
			cout << " user not found with given name " << userName << endl;
			return;
		}
		// search if the book is borrowed before by same person
		DynamicArray<BookUser> *bookUsers = findBookUserByUser(user);
		for (int i = 0; i < bookUsers->getSize(); i++)
		{
			if (bookUsers->get(i)->book == book)
			{
				cout << "you already borrowed this book!" << endl;
				return;
			}
			
		}
		BookUser *bookUser = new BookUser(book, user);
		this->borrowedBooks.push_back(bookUser);
		book->currentQuantity--;
	}
	void returnBook() {
		string userName, bookName;
		cout << "Enter User name and book name: " << endl;
		cin >> userName >> bookName;
		// find book and user first!
		Book *book = findBook(bookName);
		if (book == nullptr)
		{
			cout << " book not found with given name " << bookName << endl;
			return;
		}
		
		User *user = findUser(userName);
		if (user == nullptr)
		{
			cout << " user not found with given name " << userName << endl;
			return;
		}
		
		// search if the book is borrowed before by same person
		BookUser* temp = nullptr;
		for (int i = 0; i < borrowedBooks.getSize(); i++) {
			if (borrowedBooks.get(i) && borrowedBooks.get(i)->user == user && borrowedBooks.get(i)->book == book) {
				temp = borrowedBooks.get(i);
			}
		}
		if (temp == nullptr)
		{
			cout << "you didn't borrow this book before! " << endl;
			return;
		}
		// remove this entry from the list and shift cells accordingly!
		borrowedBooks.deleteByEntry(temp);
		book->currentQuantity++;
	}
	void printUsers() {
		for (int i = 0; i < this->users.getSize(); i++)
		{
			User *user = this->users.get(i);
			cout << "user " << user->name
				<< " id " << user->id 
				<< " borrowed books ids : ";
			DynamicArray<BookUser> *bookUsers = findBookUserByUser(user);
			for (int j = 0; j < bookUsers->getSize(); j++)
			{
				cout << bookUsers->get(j)->book->id << " ";
			}

			cout << endl;
		}
		
	}
};

#endif /* LIBRARY_LIBRARY_H_ */
