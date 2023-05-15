#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class AllBooks;
class Fiction;
class NonFiction;

class Person{ // Will be used to inherit buyer and seller
   protected:
        string username;
        string password;
};

class Cart{
    private:
        int booksbought;
        float totalprice;

    public:
    Cart(){
        booksbought=0;
        totalprice = 0;
    }

    // function to add a book to cart
    void addtocart(string bookname, float price){
        fstream file;
        file.open("D:// cart.txt", ios::out | ios::app);

        file << " " << bookname <<" " << price << '\n';
        booksbought++;
        totalprice+=price;
        file.close();
    }
    // function to display the cart
    void cartdisplay(){
        fstream file;
        file.open("D:// cart.txt", ios::in);

        string name;
        float price;

        while(file >> name >> price){

            cout << setw(20) << name << "# PKR" << price  << endl;

        }

        cout << "Total books bought: " << booksbought << endl;
        cout << "Total price is : PKR " << totalprice << endl << endl;

    }

};
class Seller : public Person{
    private:
        int ID;
    public:

        // function to sign up to the store
        void signup(){
            fstream file;
            file.open("D:// sellers.txt", ios::out | ios::app);

            cout << "SIGN UP!" << endl << endl;
            cout << "Name: ";
            cin.ignore();
            getline(cin,username);
            cout << "Password: ";
            getline(cin,password);
            cout << "ID: ";
            cin >> ID;
            cout << endl;

            file << " " << username << " " << password << " " << ID << '\n';
            file.close();
        }

        // function to login to the store
        bool login(){
            string name, pass;
            bool check = false;
            cout << "LOGIN!" <<endl << endl;

            fstream file;
            file.open("D:// sellers.txt", ios :: in);

            cout << "Enter your username: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter your password: ";
            getline(cin,pass);

            do{
                file >> username >> password >> ID;
                if(username==name && password==pass){
                    cout << "You're logged in..." << endl << endl;
                    check = true;
                    break;
                }
            }while(!file.eof());

            return check;
        }
        // function to add books to the system
        void addBooksseller(AllBooks &);

        // function to delete books from system
        void deleteBooksseller(AllBooks &);
};

class Buyer : public Person{
    private:
        int street_no;
        int house_no;
        string city;
    public:
        // function to signup the buyer
        void signup(){
            fstream file;
            file.open("D:// buyers.txt", ios::out | ios::app);

            cout << "Name: ";
            cin.ignore();
            getline(cin,username);
            cout << "Password: ";
            getline(cin,password);
            cout << "Your Postal Address Required!" << endl << endl;
            cout << "House Number: ";
            cin >> house_no;
            cout << "Street Number: ";
            cin >> street_no;
            cout << "City: ";
            cin.ignore();
            getline(cin,city);



            file << " " << username << " " << password << " " << house_no << " " << street_no << " " << city <<  '\n';
            file.close();
        }

        // function to login to the store
        bool login(){
            string name, pass;
            bool check = false;
            cout << "LOGIN!" <<endl << endl;

            fstream file;
            file.open("D:// buyers.txt", ios :: in);

            cout << "Enter your username: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter your password: ";
            getline(cin,pass);

            do{
                file >> username >> password >> house_no >> street_no >> city;
                if(username==name && password==pass){
                    cout << "You're logged in..." << endl << endl;
                    check = true;
                    break;
                }
            }while(!file.eof());

            return check;
        }

        //function to buy books
        void buybooksbuyer(AllBooks &);
};

// class for an individual book
class Book{
    public:
        string name;
        string author;
        float price;
        long int ISBN;
        int availabecopies;
};
//class to inherit all the categories from
class Category{
    public:
        string descp;
        int types_of_books_available;

        // allowing virtual inheritance
        void virtual addBooks()  = 0;
        void virtual buyBooks() = 0;
        void virtual delBook() = 0;
};

class Fiction : public Category{
    public:

        // function to add books to a file
        void addBooks(){
            fstream file;
            file.open("D:// fiction.txt", ios::out | ios::app);

            Book book;

            cout << "Add description for Fiction: " << endl;
            cin.ignore();
            getline(cin,descp);

            char option;
            while(true){
                cout << "Enter a book to fiction? (y/n)" << endl;
                cin >> option;

                if(option == 'y' || option=='Y'){

                    cout << "Name: ";
                    cin.ignore();
                    getline(cin, book.name);

                    cout << "Author: ";
                    getline(cin,book.author);

                    cout << "Price: ";
                    cin >> book.price;

                    cout << "ISBN: ";
                    cin >>  book.ISBN;

                    cout << "Copies Available: ";
                    cin >> book.availabecopies;

                    file << " " << book.name << " " << book.author << " " << book.price << " " << book.ISBN << " " << book.availabecopies << '\n';
                    file.close();

                }

                else{
                    break;
                }
            }
        }

        // function to show the added books
        void buyBooks(){
            char option;
            fstream file;
            file.open("D:// fiction.txt", ios:: in);

            Book book;
            Cart cart;

            int i = 0;

            while(file >> book.name >> book.author >> book.price >> book.ISBN >> book.availabecopies){
                cout << "Name: " << book.name << endl;
                cout << "Author: " << book.author << endl;
                cout << "Price: " << book.price << endl;
                cout << "ISBN: " << book.ISBN <<endl;
                cout << "Available Copies: " << book.availabecopies << endl << endl;
                cout << "You wish to buy this book?(y/n)" << endl;
                cin >> option;
                
                if(option=='y' || option=='Y'){
                    file.close();
                    cart.addtocart(book.name, book.price);

            }

            }
            
            cart.cartdisplay();

            file.close();
        }

        // function to delete a book from the category
        void delBook(){
            long int isbn;
            cout << "Enter the ISBN of the book to be deleted from fiction:  ";
            cin >> isbn;

            Book book;

            fstream file, file2;
            file.open("D:// fiction.txt", ios :: in);
            file2.open("D:// fiction2.txt", ios :: out | ios :: app);

            do{
                file >> book.name >> book.author >> book.price >> book.ISBN >> book.availabecopies;
                if(isbn==book.ISBN){
                    cout << "Book Successfully Deleted..." << endl << endl;
                }
                file2 <<" " << book.name << " " << book.author << " " << book.price << " " << book.ISBN << " " << book.availabecopies << '\n';
            }while(!file.eof());

            remove("D:// fiction.txt");
            rename("D:// fiction2.txt", "D:// fiction.txt");
        }

};

class NonFiction : public Category{
        public:
            void addBooks(){
            fstream file;
            file.open("D:// nonfiction.txt", ios::out | ios::app);

            Book book;

            cout << "Add description for Non Fiction: " << endl;
            cin.ignore();
            getline(cin,descp);

            char option;
            while(true){
                cout << "Enter a book to non fiction? (y/n)" << endl;
                cin >> option;

                if(option == 'y' || option=='Y'){

                    cout << "Name: ";
                    cin.ignore();
                    getline(cin, book.name);

                    cout << "Author: ";
                    getline(cin,book.author);

                    cout << "Price: ";
                    cin >> book.price;

                    cout << "ISBN: ";
                     cin >>  book.ISBN;

                    cout << "Copies Available: ";
                    cin >> book.availabecopies;

                    file << " " << book.name << " " << book.author << " " << book.price << " " << book.ISBN << " " << book.availabecopies << '\n';
                    file.close();

                }

                else{
                    break;
                }
            }
        }

        // function to show the books in category
        void buyBooks(){
            char option;
            fstream file;
            file.open("D:// nonfiction.txt", ios:: in);

            Book book;
            Cart cart;

           while(file >> book.name >> book.author >> book.price >> book.ISBN >> book.availabecopies){

                cout << "Name: " << book.name << endl;
                cout << "Author: " << book.author << endl;
                cout << "Price: " << book.price << endl;
                cout << "ISBN: " << book.ISBN <<endl;
                cout << "Available Copies: " << book.availabecopies << endl << endl;
                cout << "You wish to buy this book?(y/n)" << endl;
                cin >> option;
                
                if(option=='y' || option=='Y'){
                    cart.addtocart(book.name, book.price);
                }

            };

            cart.cartdisplay();

            file.close();
        }

        // function to delete a book from the category
        void delBook(){
            long int isbn;
            cout << "Enter the ISBN of the book to be deleted from fiction:  ";
            cin >> isbn;

            Book book;

            fstream file, file2;
            file.open("D:// fiction.txt", ios :: in);
            file2.open("D:// fiction2.txt", ios :: out | ios :: app);

            do{
                file >> book.name >> book.author >> book.price >> book.ISBN >> book.availabecopies;
                if(isbn==book.ISBN){
                    cout << "Book Successfully Deleted..." << endl << endl;
                }
                file2 <<" " << book.name << " " << book.author << " " << book.price << " " << book.ISBN << " " << book.availabecopies << '\n';
            }while(!file.eof());

            remove("D:// fiction.txt");
            rename("D:// fiction2.txt", "D:// fiction.txt");
        }
};

// class for all thde books available
class AllBooks{
    private:
        Fiction books_fiction;
        NonFiction books_nonfiction;

        friend class  Seller;
        friend class Buyer;

};


class Shop{
    public:
        AllBooks allbooksinshop; // it has fiction+nonfiction books
        Seller seller;
        Buyer buyer;

    void drive_seller(){
        char option;
        bool check = false;
        bool cont = true;

        while(cont){

            cout << "1.signup\n2.login\n3.Add Books\n4.Delete Books\n5.Exit\n";
            cin >> option;

            switch(option){
                case '1':
                    seller.signup();
                    break;
                case '2':
                    check = seller.login();
                    break;
                case '3':
                    if(check==true){
                        seller.addBooksseller(allbooksinshop);
                        break;
                    }
                    else{
                        cout << "Login First" << endl;
                        break;
                    }
                case '4':
                    if(check==true){
                        seller.deleteBooksseller(allbooksinshop);
                        break;
                    }
                    else{
                        cout << "Login First" << endl;
                        break;
                    }
                case '5':
                    cont = false;
                    break;
            }
        }
    }
    void drive_buyer(){
        char option;
        bool check = false;
        bool cont = true;

        while(cont){

            cout << "1.signup\n2.login\n3.Buy Books\n4.Exit\n";
            cin >> option;

            switch(option){
                case '1':
                    buyer.signup();
                    break;
                case '2':
                    check = buyer.login();
                    break;
                case '3':
                   buyer.buybooksbuyer(allbooksinshop);
                case '4':
                    cont = false;
                    break;
            }
        }
    }
};
void Seller::  addBooksseller(AllBooks &allbooks){
            char option;
            cout << "1.Fiction\n2.Non Fiction\n";
            cin >> option;

            switch(option){
                case '1':
                    allbooks.books_fiction.addBooks();
                    break;
                case '2':
                    allbooks.books_nonfiction.addBooks();
                    break;
            }
        }
void Seller:: deleteBooksseller(AllBooks &allbooks){
            char option;
            cout << "1.Fiction\n2.Non Fiction\n";
            cin >> option;

            switch(option){
                case '1':
                    allbooks.books_fiction.delBook();
                    break;
                case '2':
                    allbooks.books_nonfiction.delBook();
                    break;
            }
        }
void Buyer:: buybooksbuyer(AllBooks &allbooks){
            char option;
            cout << "1.Fiction\n2.Non Fiction\n";
            cin >> option;

            switch(option){
                case '1':
                    allbooks.books_fiction.buyBooks();
                    break;
                case '2':
                    allbooks.books_nonfiction.buyBooks();
                    break;
            }
            cout << endl <<endl;
            cout << "CART" << endl;
            cout << "The books you ordered will be delivered to the following address: " << endl;
            cout <<"Name: " <<  username << endl
            << "House No# " << house_no <<endl
            << "Street No# "<< street_no << endl
            << "City# " << city << endl << endl
            << "Please keep the cash ready when we come to your doorstep!" << endl << endl;
}
int main(){
    Shop flourishandBlotts;
    bool cont = true;
    char identity;
    cout << "WELCOME TO FLOURISH AND BLOTTS!" << endl;
    cout << "'It's where stories come to life'" << endl << endl;

    while(cont){
    cout << "1. Seller\n2. Buyer\n3. Exit\n";
    cin >> identity;

    switch(identity){
        case '1':
            flourishandBlotts.drive_seller();
            break;
        case '2':
            flourishandBlotts.drive_buyer();
            break;
        case '3':
            cout << "Thankyou for paying us a visit. We hope to see you soon <3" << endl;
            cont = false;
            break;
    }

    }

    return 0;
}
