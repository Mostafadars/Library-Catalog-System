#include <bits/stdc++.h>
using namespace std;
struct Author {
    char AuthorID [15];
    char AuthorName [30];
    char Address[30];
};
struct Book {
    char ISBN [15];
    char Title [30];
    char AuthorID [15];
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
    char  ISBN [15];
    char AuthorID [15];
};
struct Sorting
{
    int ID;
    int offset;
};
bool Sorting_By_ID(Sorting S1, Sorting S2) {
    return S1.ID < S2.ID;
}
struct Sorting2
{
    string Name;
    int index ;
};
struct Sorting3
{
    int ID;
    int index ;
};
bool Sorting_By_Name(Sorting2 S1, Sorting2 S2)
{
    if (S1.Name == S2.Name)
    {
        return (S1.index < S2.index);
    }
    return (S1.Name < S2.Name);
}
bool Sorting_By_SID(Sorting3 S1, Sorting3 S2)
{
    if (S1.ID == S2.ID)
    {
        return (S1.index < S2.index);
    }
    return (S1.ID < S2.ID);
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
        if (line==""){
            break;
        }
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
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out | ios::app | ios::binary | ios::in);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in | ios::out | ios::app | ios::binary);
    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line==""){
            break;
        }
        Sorting2 sorting1;
        sorting1.Name = line.substr(0, line.find("|"));
        if (sorting1.Name==authorSIndex.AuthorName) {
            found= true;
        }
    }
    file.close();
    if ( !found) {
        file2<<authorSIndex.AuthorID << "|" << "-1"<< "\n";
        file2.close();
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in | ios::out | ios::binary);
        int index = 0;
        while (getline(file2, line)) {
            if (line==""){
                break;
            }
            string Id = line.substr(0, line.find("|"));
            if (Id == authorSIndex.AuthorID) {
                break;
            }
            index++;
        }
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out | ios::app);
        file << authorSIndex.AuthorName << "|" << index << "\n";
        file.close();
    }
    else {
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::in | ios::out | ios::binary);
        int index = 0;
        while (getline(file, line)) {
            if (line==""){
                break;
            }
            Sorting2 sorting1;
            sorting1.Name = line.substr(0, line.find("|"));
            sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            index = sorting1.index;
            if (sorting1.Name == authorSIndex.AuthorName) {
                break;
            }
        }
        file.close();
        file2.close();
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt",
                   ios::in | ios::out | ios::binary);
        vector<map<string, int>> invertedList;
        while (getline(file2, line)) {
            if (line == "") {
                break;
            }
            string Id = line.substr(0, line.find("|"));
            string offset = line.substr(line.find("|") + 1, line.length());
            map<string, int> invertedList1;
            invertedList1.insert(pair<string, int>(Id, atoi(offset.c_str())));
            invertedList.push_back(invertedList1);
        }
        file2.close();
        int size = invertedList.size();
        map<string, int> invertedList1= invertedList[index];
        while (true) {
            if (invertedList1.begin()->second == -1) {
                invertedList1.begin()->second = size;
//                cout <<index<<endl;
                invertedList[index] = invertedList1;
                break;
            }
            else {
                index = invertedList1.begin()->second;
                invertedList1 = invertedList[index];
            }
        }
        map<string, int> NewInvertedList;
        NewInvertedList.insert(pair<string, int>(authorSIndex.AuthorID, -1));
        invertedList.push_back(NewInvertedList);
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt",
                   ios::out | ios::binary);
        for (int i = 0; i < invertedList.size(); i++) {
            map<string, int> invertedList2 = invertedList[i];
            for (auto itr = invertedList2.begin(); itr != invertedList2.end(); ++itr) {
                file2 << itr->first << "|" << itr->second << "\n";
            }
        }
    }
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
        if (line==""){
            break;
        }
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
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out | ios::app | ios::binary|ios::in);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt",
                  ios::in | ios::out | ios::app | ios::binary);
    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line == "") {
            break;
        }
        Sorting3 sorting1;
        sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
        if (to_string(sorting1.ID) == bookSIndex.AuthorID) {
            found = true;
        }
    }
    file.close();
    if (!found) {
        file2 << bookSIndex.ISBN << "|" << "-1" << "\n";
        file2.close();
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt",
                   ios::in | ios::out | ios::app);
        int index = 0;
        while (getline(file2, line)) {
            if (line == "") {
                break;
            }
            string Id = line.substr(0, line.find("|"));
            if (Id == bookSIndex.ISBN) {
                break;
            }
            index++;
        }
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out | ios::app | ios::binary);
        file << bookSIndex.AuthorID << "|" << index << "\n";
        file.close();
    } else {
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out | ios::app);
        int index = 0;
        while (getline(file, line)) {
            if (line == "") {
                break;
            }
            Sorting3 sorting1;
            sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
            sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            index = sorting1.index;
            if (to_string(sorting1.ID) == bookSIndex.AuthorID) {
                break;
            }
        }
        file.close();
        file2.close();
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt",
                   ios::in | ios::out | ios::app);
        vector<map<string, int>> invertedList;
        while (getline(file2, line)) {
            if (line == "") {
                break;
            }
            string Id = line.substr(0, line.find("|"));
            string offset = line.substr(line.find("|") + 1, line.length());
            map<string, int> invertedList1;
            invertedList1.insert(pair<string, int>(Id, atoi(offset.c_str())));
            invertedList.push_back(invertedList1);
        }
        file2.close();
        int size = invertedList.size();
        map<string, int> invertedList1 = invertedList[index];
        while (true) {
            if (invertedList1.begin()->second == -1) {
                invertedList1.begin()->second = size;
                invertedList[index] = invertedList1;
                break;
            } else {
                index = invertedList1.begin()->second;
                invertedList1 = invertedList[index];
            }
        }
        map<string, int> NewInvertedList;
        NewInvertedList.insert(pair<string, int>(bookSIndex.ISBN, -1));
        invertedList.push_back(NewInvertedList);
        file2.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt",
                   ios::out | ios::trunc);
        for (int i = 0; i < invertedList.size(); i++) {
            map<string, int> invertedList2 = invertedList[i];
            for (auto itr = invertedList2.begin(); itr != invertedList2.end(); ++itr) {
                file2 << itr->first << "|" << itr->second << "\n";
            }
        }
    }
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
        if (line==""){
            break;
        }
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
    vector<Sorting3> sorting;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::in);
    string line;
    while (getline(file, line)) {
        if (line==""){
            break;
        }
        Sorting3 sorting1;
        sorting1.ID= atoi(line.substr(0, line.find("|")).c_str());
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        sorting.push_back(sorting1);
    }
    file.close();
    if (sorting.size()<2){
        return;
    }
    sort(sorting.begin(), sorting.end(), Sorting_By_SID);
    fstream file2("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].ID << "|" << sorting[i].index << "\n";
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
    if (bookPIndex.offset == -1) {
        bookPIndex.offset = 0;
    }
    WriteBookInDataFile(book);
    strcpy(bookPIndex.ISBN, book.ISBN);
    InsertBookInPrimaryIndex(bookPIndex);
    BookSIndex bookSIndex;
    strcpy(bookSIndex.ISBN, book.ISBN);
    strcpy(bookSIndex.AuthorID, book.AuthorID);
    InsertBookInSecondaryIndex(bookSIndex);
    SortBookPIndex();
    SortBookSIndex();
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
    if (authorPIndex.offset == -1) {
        authorPIndex.offset = 0;
    }
    WriteAuthorInDataFile(author);
    strcpy(authorPIndex.AuthorID, author.AuthorID);
    WriteAuthorInPrimaryIndex(authorPIndex);
    AuthorSIndex authorSIndex;
    strcpy(authorSIndex.AuthorName, author.AuthorName);
    strcpy(authorSIndex.AuthorID, author.AuthorID);
    WriteAuthorInSecondaryIndex(authorSIndex);
    SortAuthorPIndex();
    SortAuthorSIndex();
}
void Clear(){
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::out);
    file.close();
}
int main(){
    while (true){
        int choice;
        cout << "1- Add Author" << endl;
        cout << "2- Add Book" << endl;
        cout << "3- Search Author by ID" << endl;
        cout << "4- Search Book by ISBN" << endl;
        cout << "5- Exit" << endl;
        cout << "6- Clear" << endl;
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
        else if (choice == 6) {
            Clear();
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    return 0;
}