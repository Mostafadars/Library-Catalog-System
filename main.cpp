#include <bits/stdc++.h>
using namespace std;
struct Author {
    char AuthorID [15];//primary key
    char AuthorName [30];
    char Address[30];
};
struct Book {
    char ISBN [15];//primary key
    char Title [30];
    char AuthorID [15];//foreign key
};
struct AuthorPIndex {
    char AuthorID [15];
    int offset;
};
struct BookPIndex {
    char ISBN [15];
    int offset;
};
struct AuthorSIndex {
    char AuthorName [30];
    char AuthorID [15];
};
struct BookSIndex {
    char Title [30];
    char AuthorID [15];
};
struct Sorting
{
    int ID;
    int offset;
};
bool Sorting_By_ID(Sorting depart1, Sorting depart2)
{
    return (depart1.ID < depart2.ID);
}
struct Sorting2
{
   string Name;
    int index ;
};
bool Sorting_By_Name(Sorting2 depart1, Sorting2 depart2)
{
    if (depart1.Name == depart2.Name)
    {
        return (depart1.index < depart2.index);
    }
    return (depart1.Name < depart2.Name);
}
void WriteAuthorInPrimaryIndex(AuthorPIndex authorPIndex) {
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt", ios::out | ios::app);
    file << authorPIndex.AuthorID << "|" << authorPIndex.offset << "\n";
    file.close();
}
void SortAuthorSIndex() {
    vector<Sorting2> sorting;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        Sorting2 sorting1;
        sorting1.Name = line.substr(0, line.find("|"));
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        sorting.push_back(sorting1);
    }
    file.close();
    sort(sorting.begin(), sorting.end(), Sorting_By_Name);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].Name << "|" << sorting[i].index << "\n";
    }
    file2.close();
}
void WriteAuthorInSecondaryIndex(AuthorSIndex authorSIndex) {
//    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out | ios::app | ios::binary | ios::in);
//    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in | ios::out | ios::app | ios::binary);
//    bool found = false;
//    string line;
//    while (getline(file, line)) {
//        Sorting2 sorting1;
//        sorting1.Name = line.substr(0, line.find("|"));
//        if (sorting1.Name==authorSIndex.AuthorName) {
//            found= true;
//        }
//    }
//    file.close();
//    if ( !found) {
//        file2<<authorSIndex.AuthorID << "|" << "-1"<< "\n";
//        file2.close();
//        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in | ios::out | ios::binary);
//        int index = 0;
//        while (getline(file2, line)) {
//            string Id = line.substr(0, line.find("|"));
//            if (Id == authorSIndex.AuthorID) {
//                break;
//            }
//            index++;
//        }
//        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out | ios::app);
//        file << authorSIndex.AuthorName << "|" << index << "\n";
//        file.close();
//    }
//    else {
//        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::in | ios::out | ios::binary);
//        int index = 0;
//        while (getline(file, line)) {
//            Sorting2 sorting1;
//            sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
//            index = sorting1.index;
//        }
//        cout << index << endl;
//        file.close();
//        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in | ios::out | ios::binary);
//        int index2 = 0;
//        while (getline(file2, line)) {
//            if (index2 == index) {
//                string Id = line.substr(0, line.find("|"));
//                int Index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
//                while (true){
//                    if (index == -1{
//                    }
//                    else{
//
//                    }
//                }
//            }
//            index2++;
//        }
//    }
//}
}
void WriteAuthorInDataFile(Author author) {
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::out | ios::app);
    int size = strlen(author.AuthorID) + strlen(author.AuthorName) + strlen(author.Address) + 4;
    if (size < 10) {
        file << "0" << size << author.AuthorID << "|" << author.AuthorName << "|" << author.Address;
    } else {
        file << size<< author.AuthorID << "|" << author.AuthorName << "|" << author.Address ;
    }
}
void SortAuthorPIndex() {
    vector<Sorting> sorting;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        Sorting sorting1;
        sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
        sorting1.offset = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        sorting.push_back(sorting1);
    }
    file.close();
    sort(sorting.begin(), sorting.end(), Sorting_By_ID);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt", ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].ID << "|" << sorting[i].offset << "\n";
    }
    file2.close();
}
void InsertBookInPrimaryIndex(BookPIndex bookPIndex){
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ios::out | ios::app);
    file << bookPIndex.ISBN << "|" << bookPIndex.offset << "\n";
    file.close();
}
void InsertBookInSecondaryIndex(BookSIndex bookSIndex) {
}
void WriteBookInDataFile(Book book) {
       fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::out | ios::app);
        int size = strlen(book.ISBN) + strlen(book.Title) + strlen(book.AuthorID) + 4;
        if (size < 10) {
            file << "0" << size << book.ISBN << "|" << book.Title << "|" << book.AuthorID;
        } else {
            file << size << book.ISBN << "|" << book.Title << "|" << book.AuthorID;
        }
}
void SortBookPIndex() {
    vector<Sorting> sorting;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        Sorting sorting1;
        sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
        sorting1.offset = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        sorting.push_back(sorting1);
    }
    file.close();
    sort(sorting.begin(), sorting.end(), Sorting_By_ID);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].ID << "|" << sorting[i].offset << "\n";
    }
    file2.close();
}
void SortBookSIndex() {
    vector<Sorting2> sorting;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        Sorting2 sorting1;
        sorting1.Name = line.substr(0, line.find("|"));
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        sorting.push_back(sorting1);
    }
    file.close();
    sort(sorting.begin(), sorting.end(), Sorting_By_Name);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].Name << "|" << sorting[i].index << "\n";
    }
    file2.close();
}
int SearchBookByISBN(char ISBN[]) {
    int offset = -1;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        if (atoi(line.substr(0, line.find("|")).c_str()) == atoi(ISBN)) {
            offset = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            break;
        }
    }
    file.close();
    return offset;
}
int SearchAuthorByID(char ID[]) {
    int offset = -1;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        if (atoi(line.substr(0, line.find("|")).c_str()) == atoi(ID)) {
            offset = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            break;
        }
    }
    file.close();
    return offset;
}
void PrintAuthor (int offset) {
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    size-=2;
    cout << "Author ID: " << line.substr(0, line.find("|")) << endl;
    size -= line.substr(0, line.find("|")).length()+1;
    line = line.substr(line.find("|") + 1, line.length());
    cout << "Author Name: " << line.substr(0, line.find("|")) << endl;
    size -= line.substr(0, line.find("|")).length()+1 ;
    line = line.substr(line.find("|") + 1, line.length());
    cout << "Author Address: " << line.substr(0, size) << endl;
    file.close();
}
void PrintBook (int offset) {
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    size-=2;
    cout << "Book ISBN: " << line.substr(0, line.find("|")) << endl;
    size -= line.substr(0, line.find("|")).length()+1;
    line = line.substr(line.find("|") + 1, line.length());
    cout << "Book Title: " << line.substr(0, line.find("|")) << endl;
    size -= line.substr(0, line.find("|")).length()+1 ;
    line = line.substr(line.find("|") + 1, line.length());
    cout << "Book Author ID: " << line.substr(0, size) << endl;
    file.close();
}
void AddBook() {
    Book book;
    cout << "Enter Book ISBN: ";
    cin >> book.ISBN;
    if (SearchBookByISBN(book.ISBN) != -1) {
        cout << "Book already exists" << endl;
        return;
    }
    cout << "Enter Book Title: ";
    cin >> book.Title;
    cout << "Enter Book Author ID: ";
    cin >> book.AuthorID;
    if (SearchAuthorByID(book.AuthorID) == -1) {
        cout << "Author doesn't exist" << endl;
        return;
    }
    if (strlen(book.ISBN) > 10 || strlen(book.Title) > 20 || strlen(book.AuthorID) > 10) {
        cout << "Invalid Input" << endl;
        return;
    }
    BookPIndex bookPIndex;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in);
    file.seekg(0, ios::end);
    bookPIndex.offset = file.tellp();
    WriteBookInDataFile(book);
    strcpy(bookPIndex.ISBN, book.ISBN);
    InsertBookInPrimaryIndex(bookPIndex);
    BookSIndex bookSIndex;
    strcpy(bookSIndex.Title, book.Title);
    strcpy(bookSIndex.AuthorID, book.AuthorID);
    InsertBookInSecondaryIndex(bookSIndex);
    SortBookPIndex();
}
void AddAuthor() {
    Author author;
    cout << "Enter Author ID: ";
    cin >> author.AuthorID;
    if (SearchAuthorByID(author.AuthorID) != -1) {
        cout << "Author already exists" << endl;
        return;
    }
    cout << "Enter Author Name: ";
    cin >> author.AuthorName;
    cout << "Enter Author Address: ";
    cin >> author.Address;
    if (strlen(author.AuthorID) > 15 || strlen(author.AuthorName) > 30 || strlen(author.Address) > 30) {
        cout << "Error: Invalid Input" << endl;
        return;
    }
    AuthorPIndex authorPIndex;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in);
    file.seekg(0, ios::end);
    authorPIndex.offset = file.tellp();
    WriteAuthorInDataFile(author);
    strcpy(authorPIndex.AuthorID, author.AuthorID);
    WriteAuthorInPrimaryIndex(authorPIndex);
    AuthorSIndex authorSIndex;
    strcpy(authorSIndex.AuthorName, author.AuthorName);
    strcpy(authorSIndex.AuthorID, author.AuthorID);
    WriteAuthorInSecondaryIndex(authorSIndex);
    SortAuthorPIndex();
}
int main(){
    while (true){
        int choice;
        cout << "1- Add Author" << endl;
        cout << "2- Add Book" << endl;
        cout << "3- Search Author by ID" << endl;
        cout << "4- Search Book by ISBN" << endl;
        cout << "5- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            AddAuthor();
        } else if (choice == 2) {
            AddBook();
        } else if (choice == 3) {
            char ID[20];
            cout << "Enter Author ID: ";
            cin >> ID;
            int offset = SearchAuthorByID(ID);
            if (offset == -1) {
                cout << "Author ID doesn't exist" << endl;
            } else {
                PrintAuthor(offset);
            }
        }
        else if (choice == 4) {
            char ISBN[20];
            cout << "Enter Book ISBN: ";
            cin >> ISBN;
            int offset = SearchBookByISBN(ISBN);
            if (offset == -1) {
                cout << "Book ISBN doesn't exist" << endl;
            } else
            {
                PrintBook(offset);
            }
        }
        else if (choice == 5) {
            break;
        }
    }
    return 0;
}
