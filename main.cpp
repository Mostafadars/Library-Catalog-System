#include <bits/stdc++.h>
using namespace std;

// Youssef Work
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
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        if (sorting1.Name==authorSIndex.AuthorName &&sorting1.index!=-1) {
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
            int index1 = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            if (Id == authorSIndex.AuthorID && index1!=-2) {
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
            if (sorting1.Name == authorSIndex.AuthorName && sorting1.index!=-1) {
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
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        if (to_string(sorting1.ID) == bookSIndex.AuthorID &&sorting1.index!=-1)
        {
            found = true;
            break;
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
            string index1 = line.substr(line.find("|") + 1, line.length());
            if (Id == bookSIndex.ISBN &&index1!="-2") {
                break;
            }
            index++;
        }
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out | ios::app | ios::binary);
        file << bookSIndex.AuthorID << "|" << index << "\n";
        file.close();
    }
    else {
        file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ios::out | ios::app | ios::in);
        int index = 0;
        while (getline(file, line)) {
            if (line == "") {
                break;
            }
            Sorting3 sorting1;
            sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
            sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
            index = sorting1.index;
            if (to_string(sorting1.ID) == bookSIndex.AuthorID && sorting1.index!=-1)
            {
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

    if (line[0] == '*') {
        cout << "Author not found" << endl;
        file.close();
        return;
    }

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


string GetAuthorIdFromBook(char ISBN[]) {
    int offset = SearchBookByISBN(ISBN);
    if (offset == -1) {
        cout << "Book not found" << endl;
        return "";
    }
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    size-=2;
    size -= line.substr(0, line.find("|")).length()+1;
    line = line.substr(line.find("|") + 1, line.length());
    size -= line.substr(0, line.find("|")).length()+1 ;
    line = line.substr(line.find("|") + 1, line.length());
    string authorID = line.substr(0, size);
    return authorID;
    file.close();
}


string GetAuthorNameFromAuthorID(char ID[]) {
    int offset = SearchAuthorByID(ID);
    if (offset == -1) {
        cout << "Author not found" << endl;
        return "";
    }
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    size-=2;
    line = line.substr(line.find("|") + 1, line.length());
    string AuthorName = line.substr(0, line.find("|"));
    file.close();
    return AuthorName;
}


void PrintBook (int offset) {
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);

    if (line[0] == '*') {
        cout << "Book not found" << endl;
        file.close();
        return;
    }

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
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorAvailList.txt", ios::out);
    file.close();
    file.open("C:\\Users\\dell\\CLionProjects\\untitled4\\BookAvailList.txt", ios::out);
    file.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Mostafa Work
vector<int> authorAvailList;
vector<int> bookAvailList;

vector<int> ReadAuthorAvailList() {
    vector<int> authorAvailList;
    fstream file("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorAvailList.txt", ios::in);
    string line;
    while (getline(file, line)) {
        authorAvailList.push_back(atoi(line.c_str()));
    }
    file.close();
    return authorAvailList;
}


vector<int> ReadBookAvailList() {
    vector<int> bookAvailList;
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\BookAvailList.txt", ios::in);
    string line;
    while (getline(file, line)) {
        bookAvailList.push_back(atoi(line.c_str()));
    }
    file.close();
    return bookAvailList;
}


void WriteAuthorAvailList(vector<int> authorAvailList) {
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\AuthorAvailList.txt", ios::out);
    for (int i = 0; i < authorAvailList.size(); i++) {
        file << authorAvailList[i] << "\n";
    }
    file.close();
}


void WriteBookAvailList(vector<int> bookAvailList) {
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\BookAvailList.txt", ios::out);
    for (int i = 0; i < bookAvailList.size(); i++) {
        file << bookAvailList[i] << "\n";
    }
    file.close();
}


void DeleteFromPrimaryIndex(string primaryIndexFile, string key) {
    vector<Sorting> sorting;
    fstream file(primaryIndexFile.c_str(), ios::in);
    string line;
    while (getline(file, line)) {
        Sorting sorting1;
        if (line == "") {
            break;
        }
        sorting1.ID = atoi(line.substr(0, line.find("|")).c_str());
        sorting1.offset = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        if (to_string(sorting1.ID) != key) {
            sorting.push_back(sorting1);
        }
    }
    file.close();
    sort(sorting.begin(), sorting.end(), Sorting_By_ID);
    fstream file2(primaryIndexFile.c_str(), ios::out);
    for (int i = 0; i < sorting.size(); i++) {
        file2 << sorting[i].ID << "|" << sorting[i].offset << "\n";
    }
    file2.close();
}


// New function to delete records from the inverted list
void DeleteFromInvertedListBook(string invertedListFile, int key, string ISBN) {
    vector<map<string, int>> invertedList;
    fstream file(invertedListFile.c_str(), ios::in);
    string line;
    int i = 0,j;
    while (getline(file, line)) {
        if (line == "") {
            break;
        }
        map<string, int> invertedList1;
        invertedList1.insert(pair<string, int>(line.substr(0, line.find("|")),
                                               atoi(line.substr(line.find("|") + 1, line.length()).c_str())));
        invertedList.push_back(invertedList1);
        if (invertedList1.begin()->first == ISBN && invertedList1.begin()->second !=-2) {
            j = i;
        }
        i++;
    }
    file.close();
    if (invertedList[key].begin()->first==ISBN) {
        invertedList[key].begin()->second=-2;
    }
    else if  (invertedList[j].begin()->second==-1)
    {
        map<string, int> it,prev= invertedList[key];
        it=invertedList[key];
        while (true){
            it=invertedList[it.begin()->second];
            if (it.begin()->first==ISBN){
                if (it.begin()->second==-1)
                {
                    prev.begin()->second=-1;
                }
                break;
            }
            prev=it;
        }
        for (int i = 0; i < invertedList.size(); i++) {
            if (invertedList[i].begin()->first == prev.begin()->first) {
                invertedList[i] = prev;
            }
            if (invertedList[i].begin()->first == ISBN) {
                invertedList[i].begin()->second = -2;
            }
        }
    }
    else {
        map<string, int> it, prev = invertedList[key];
        it = invertedList[key];
        while (true) {
            it = invertedList[it.begin()->second];
            if (it.begin()->first == ISBN) {
                prev.begin()->second = it.begin()->second;
                break;
            }
            prev = it;
        }
        for (int i = 0; i < invertedList.size(); i++) {
            if (invertedList[i].begin()->first == prev.begin()->first) {
                invertedList[i] = prev;
            }
            if (invertedList[i].begin()->first == ISBN) {
                invertedList[i].begin()->second = -2;
            }
        }
    }
    fstream file2(invertedListFile.c_str(), ios::out);
    for (int i = 0; i < invertedList.size(); i++) {
        file2 << invertedList[i].begin()->first << "|" << invertedList[i].begin()->second << "\n";
    }
    file2.close();
}


// Add this function to delete from the secondary index
void DeleteFromSecondaryIndexBook(string secondaryIndexFile, string ID , string ISBN) {
    fstream file(secondaryIndexFile.c_str(), ios::in);
    string line;
    int index = 0;
    vector<Sorting2> sorting;
    while (getline(file, line)) {
        Sorting2 sorting1;
        if (line == "") {
            break;
        }
        sorting1.Name = line.substr(0, line.find("|"));
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        if (sorting1.Name == ID && sorting1.index != -1)
        {
            index = sorting1.index;
        }
        sorting.push_back(sorting1);
    }
    file.close();
    fstream file2("c:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt", ios::in);
    vector<map<string, int>> invertedList;
    while (getline(file2, line)) {
        if (line == "") {
            break;
        }
        map<string, int> invertedList1;
        invertedList1.insert(pair<string, int>(line.substr(0, line.find("|")),
                                               atoi(line.substr(line.find("|") + 1, line.length()).c_str())));
        invertedList.push_back(invertedList1);
    }
    file2.close();
    bool flag = false;
    if (invertedList[index].begin()->second == -1) {
        flag = true;
    }
    if (flag== true){
        file.open(secondaryIndexFile.c_str(), ios::out);
        for (int i = 0; i < sorting.size(); i++) {
            if (sorting[i].Name == ID) {
                file << sorting[i].Name << "|" << -1 << "\n";
            }
            else {
                file << sorting[i].Name << "|" << sorting[i].index << "\n";
            }
        }
    }
    else {
        file.open(secondaryIndexFile.c_str(), ios::out);
        for (int i = 0; i < sorting.size(); i++) {
            if (sorting[i].Name == ID) {
                if (invertedList[index].begin()->first == ISBN) {
                    file << sorting[i].Name << "|" << invertedList[index].begin()->second << "\n";
                }
                else {
                    file << sorting[i].Name << "|" << sorting[i].index << "\n";
                }
            } else {
                file << sorting[i].Name << "|" << sorting[i].index << "\n";
            }
        }
    }
    file.close();
    DeleteFromInvertedListBook("c:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndexInvertedList.txt", index, ISBN);
}


void DeleteBook(char ISBN[]) {
    int offset = SearchBookByISBN(ISBN);
    string ID= GetAuthorIdFromBook(ISBN);
    if (offset == -1) {
        cout << "Book ISBN doesn't exist" << endl;
        return;
    }
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in | ios::out);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    file.close();

    file.open("c:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in | ios::out);
    file.seekp(offset, ios::beg);

    if (bookAvailList.empty()) {
        file << "*-1|" << size << "|";
    }
    else {
        file << "*" << bookAvailList.back() << "|" << size << "|";
    }

    for (int i = 0; i < size - 7; i++) {
        file << "-";
    }
    file.close();
    // Update primary index
    DeleteFromPrimaryIndex("C:\\Users\\dell\\CLionProjects\\untitled4\\BookPIndex.txt", ISBN);
    // Delete from the secondary index
    DeleteFromSecondaryIndexBook("c:\\Users\\dell\\CLionProjects\\untitled4\\BookSIndex.txt", ID, ISBN);
    // add the offset to the avail list
    bookAvailList.push_back(offset);
    WriteBookAvailList(bookAvailList);
    cout << "Book deleted successfully" << endl;
}


void DeleteInvertedListAuthor(string invertedListFile, int index, string ID) {
    vector<map<string, int>> invertedList;
    fstream file(invertedListFile.c_str(), ios::in);
    string line;
    int i = 0, j;
    while (getline(file, line)) {
        if (line == "") {
            break;
        }
        map<string, int> invertedList1;
        invertedList1.insert(pair<string, int>(line.substr(0, line.find("|")),
                                               atoi(line.substr(line.find("|") + 1, line.length()).c_str())));
        invertedList.push_back(invertedList1);
        if (invertedList1.begin()->first == ID && invertedList1.begin()->second != -2) {
            j = i;
        }
        i++;
    }
    file.close();
    if (invertedList[index].begin()->first == ID) {
        invertedList[index].begin()->second = -2;
    }
    else if (invertedList[j].begin()->second == -1) {
        map<string, int> it, prev = invertedList[index];
        it = invertedList[index];
        while (true) {
            it = invertedList[it.begin()->second];
            if (it.begin()->first == ID) {
                if (it.begin()->second == -1) {
                    prev.begin()->second = -1;
                }
                break;
            }
            prev = it;
        }
        for (int i = 0; i < invertedList.size(); i++) {
            if (invertedList[i].begin()->first == prev.begin()->first) {
                invertedList[i] = prev;
            }
            if (invertedList[i].begin()->first == ID) {
                invertedList[i].begin()->second = -2;
            }
        }
    }
    else {
        map<string, int> it, prev = invertedList[index];
        it = invertedList[index];
        while (true) {
            it = invertedList[it.begin()->second];
            if (it.begin()->first == ID) {
                prev.begin()->second = it.begin()->second;
                break;
            }
            prev = it;
        }
        for (int i = 0; i < invertedList.size(); i++) {
            if (invertedList[i].begin()->first == prev.begin()->first) {
                invertedList[i] = prev;
            }
            if (invertedList[i].begin()->first == ID) {
                invertedList[i].begin()->second = -2;
            }
        }
    }
    fstream file2(invertedListFile.c_str(), ios::out);
    for (int i = 0; i < invertedList.size(); i++) {
        file2 << invertedList[i].begin()->first << "|" << invertedList[i].begin()->second << "\n";
    }
    file2.close();
}


void DeleteFromSecondaryIndexAuthor(string secondaryIndexFile, string Name, string ID) {
    fstream file(secondaryIndexFile.c_str(), ios::in);
    string line;
    int index = 0;
    vector<Sorting2> sorting;
    while (getline(file, line)) {
        Sorting2 sorting1;
        if (line == "") {
            break;
        }
        sorting1.Name = line.substr(0, line.find("|"));
        sorting1.index = atoi(line.substr(line.find("|") + 1, line.length()).c_str());
        if (sorting1.Name == Name && sorting1.index != -1) {
            index = sorting1.index;
        }
        sorting.push_back(sorting1);
    }
    file.close();
    fstream file2("c:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", ios::in);
    vector<map<string, int>> invertedList;
    while (getline(file2, line)) {
        if (line == "") {
            break;
        }
        map<string, int> invertedList1;
        invertedList1.insert(pair<string, int>(line.substr(0, line.find("|")),
                                               atoi(line.substr(line.find("|") + 1, line.length()).c_str())));
        invertedList.push_back(invertedList1);
    }
    file2.close();
    bool flag = false;
    if (invertedList[index].begin()->second == -1) {
        flag = true;
    }
    if (flag == true) {
        file.open(secondaryIndexFile.c_str(), ios::out);
        for (int i = 0; i < sorting.size(); i++) {
            if (sorting[i].Name == Name) {
                file << sorting[i].Name << "|" << -1 << "\n";
            } else {
                file << sorting[i].Name << "|" << sorting[i].index << "\n";
            }
        }
    } else {
        file.open(secondaryIndexFile.c_str(), ios::out);
        for (int i = 0; i < sorting.size(); i++) {
            if (sorting[i].Name == Name) {
                if (invertedList[index].begin()->first == ID) {
                    file << sorting[i].Name << "|" << invertedList[index].begin()->second << "\n";
                } else {
                    file << sorting[i].Name << "|" << sorting[i].index << "\n";
                }
            } else {
                file << sorting[i].Name << "|" << sorting[i].index << "\n";
            }
        }
    }
    file.close();
    DeleteInvertedListAuthor("c:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndexInvertedList.txt", index,ID);
}


void DeleteAuthor(char ID[]) {
    int offset = SearchAuthorByID(ID);
    string Name= GetAuthorNameFromAuthorID(ID);
    if (offset == -1) {
        cout << "Author ID doesn't exist" << endl;
        return;
    }
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in | ios::out);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    line = line.substr(2, line.length());
    file.close();
    file.open("c:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in | ios::out);
    file.seekp(offset, ios::beg);
    if (authorAvailList.empty()) {
        file << "*-1|" << size << "|";
    }
    else {
        file << "*" << authorAvailList.back() << "|" << size << "|";
    }
    for (int i = 0; i < size - 7; i++) {
        file << "-";
    }
    file.close();
    // Update primary index
    DeleteFromPrimaryIndex("C:\\Users\\dell\\CLionProjects\\untitled4\\AuthorPIndex.txt",ID);
    // Delete from the secondary index
    DeleteFromSecondaryIndexAuthor("c:\\Users\\dell\\CLionProjects\\untitled4\\AuthorSIndex.txt",Name,ID);
    // add the offset to the avail list
    authorAvailList.push_back(offset);
    WriteAuthorAvailList(authorAvailList);
    cout << "Book deleted successfully" << endl;
}

//////////////////////////////////////
// Ahmed Work

void updateAuthorName(char AuthorID[] ,char AuthorName [] ){
    int offset = SearchAuthorByID(AuthorID);
    if(offset == -1){
        cout << "Author ID doesn't exist" << endl;
        return;
    }
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in | ios::out);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    int oldsize = 0;
    line = line.substr(2, line.length());
    size-=2;
    oldsize = oldsize +2;
    size -= line.substr(0, line.find("|")).length()+1;
    oldsize += line.substr(0, line.find("|")).length()+1;
    line = line.substr(line.find("|") + 1, line.length());
    string oldName =  line.substr(0, line.find("|"));
    file.close();
    if(oldName.length() < strlen(AuthorName)){
        cout << "Author name is too long"<< endl;
        return;
    }
    file.open("c:\\Users\\dell\\CLionProjects\\untitled4\\Author.txt", ios::in | ios::out);
    file.seekp(offset+oldsize, ios::beg);
    file<<AuthorName;
    int empty = oldName.length()- strlen(AuthorName);

    for (int i = 0; i <empty; i++) {
        file << "-";
    }
    cout<<"update successfully"<<endl;
    file.close();
}


void updateBookTitle(char ISBN[] ,char BookTitle [] ){
    int offset = SearchBookByISBN(ISBN);

    if(offset == -1){
        cout << "ISBN doesn't exist" << endl;
        return;
    }
    fstream file("c:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in | ios::out);
    file.seekg(offset, ios::beg);
    string line;
    getline(file, line);
    int size = atoi(line.substr(0, 2).c_str());
    int oldsize = 0;
    line = line.substr(2, line.length());
    size-=2;
    oldsize = oldsize +2;
    size -= line.substr(0, line.find("|")).length()+1;
    oldsize += line.substr(0, line.find("|")).length()+1;
    line = line.substr(line.find("|") + 1, line.length());
    string oldTitle =  line.substr(0, line.find("|"));
    file.close();
    if(oldTitle.length() < strlen(BookTitle)){
        cout << "Book Title is too long"<< endl;
        return;
    }

    file.open("c:\\Users\\dell\\CLionProjects\\untitled4\\Book.txt", ios::in | ios::out);
    file.seekp(offset+oldsize, ios::beg);
    file<<BookTitle;

    int empty = oldTitle.length()- strlen(BookTitle);

    for (int i = 0; i <empty; i++) {
        file << "-";
    }

    cout<<"update successfully"<<endl;
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// salma work

vector<string> ReadAllBooks(char authorId[]) {
    vector<string> bookISBNs;
    int index = 0;

    // Open the secondary index file
    ifstream indexFile("BookSIndex.txt");
    if (!indexFile.is_open()) {
        cout << "Error opening secondary index file" << endl;
        return bookISBNs;
    }

    string line;
    while (getline(indexFile, line)) {
        // Split the line into AuthorID and Index in Inverted List
        stringstream ss(line);
        string token;
        getline(ss, token, '|'); // AuthorID
        string id = token;
        getline(ss, token, '|'); // Index of first ISBN in Inverted List
        // change token from string to int
        index = atoi(token.c_str());

        // If the AuthorID matches, read the corresponding ISBNs from inverted list
        if (id == authorId)
            break;
    }

    fstream file("BookSIndexInvertedList.txt", ios::in | ios::out | ios::binary);

    vector<map<string, int>> invertedList;

    while (getline(file, line)) {
        if (line == "") {
            break;
        }
        string Id = line.substr(0, line.find("|"));
        string offset = line.substr(line.find("|") + 1, line.length());

        map<string, int> invertedList1;
        invertedList1.insert(pair<string, int>(Id, atoi(offset.c_str())));
        invertedList.push_back(invertedList1);
    }

    file.close();

    int size = invertedList.size();
    map<string, int> invertedList1 = invertedList[index];

    while (true) {
        bookISBNs.push_back(invertedList1.begin()->first);

        if (invertedList1.begin()->second == -1) {
            break;
        }
        else {
            index = invertedList1.begin()->second;
            invertedList1 = invertedList[index];
        }
    }
    return bookISBNs;
}


string GetAuthorName(char authorId[]) {
    string authorName;
    vector<map<string, int>> sIndex;
    int index = 0;

    ifstream file1("AuthorSIndex.txt");
    if (!file1.is_open()) {
        cout << "Error opening secondary index file" << endl;
        return authorName;
    }

    string line;
    while (getline(file1, line)) {
        // Split the line into authorName and Index in Inverted List
        stringstream ss(line);
        string token;
        getline(ss, token, '|'); // authorName
        string name = token;
        getline(ss, token, '|'); // Index of first ISBN in Inverted List
        index = atoi(token.c_str());
        // push name and index in the sIndex vector
        map<string, int> add;
        add.insert(pair<string, int>(name, index));
        sIndex.push_back(add);
    }
    file1.close();

    ifstream file("AuthorSIndexInvertedList.txt");

    for (auto &i : sIndex) {

        file.seekg(0, ios::cur);
        string line;
        while (getline(file, line)) {
            if (line == "") {
                break;
            }
            string Id = line.substr(0, line.find("|"));
            string offset = line.substr(line.find("|") + 1, line.length());

            if (Id == authorId){
                authorName = i.begin()->first;
                return authorName;
            }

            if (offset != "-1")
                file.seekg(0, ios::cur);
            else
                break;
        }
    }
}


// Function to execute a query
void ExecuteQuery(const string& query) {
    // Tokenize the query
    stringstream ss(query);
    vector<string> tokens;
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    // Check the type of query
    if (tokens.size() < 6) {
        cout << "Invalid query format" << endl;
        return;
    }

    if (tokens[0] == "select" || tokens[0] == "SELECT")
        tokens[0] = "select";

    if (tokens[2] == "from" || tokens[2] == "FROM")
        tokens[2] = "from";

    if (tokens[4] == "where" || tokens[4] == "WHERE")
        tokens[4] = "where";

    string action = tokens[0]; // select *
    string select = tokens[1]; // all
    string from = tokens[2]; // from *
    string file = tokens[3]; // Author
    string where = tokens[4]; // where *
    string condition = tokens[5]; // ID=5;

    char AuthorID[20];
    strcpy(AuthorID, condition.substr(condition.find("=") + 1, condition.length()).c_str());

    // Implement actions based on the query
    if (action == "select" && from == "from" && where == "where") {
        if (select == "all" && file == "Author") {
            int offset = SearchAuthorByID(AuthorID);
            if (offset == -1) {
                cout << "Author ID doesn't exist" << endl;
            } else {
                PrintAuthor(offset);
            }
        }
        else if (select == "name" && file == "Author") {
            string authorName = GetAuthorName(AuthorID);
            cout << "Author Name: " << authorName << endl;
        }
        else if (select == "all" && file == "Book") {
            vector<string> bookISBNs = ReadAllBooks(AuthorID);

            if (bookISBNs.empty()) {
                cout << "No books found for the given Author ID" << endl;
            } else {
                // Loop through the ISBNs and print or process the corresponding books
                for (const string& ISBN : bookISBNs) {
                    char isban[20];
                    strcpy(isban, ISBN.c_str());
                    int bookOffset = SearchBookByISBN(isban);
                    if (bookOffset != -1) {
                        PrintBook(bookOffset);
                    }
                }
            }
        }
    } else {
        cout << "Invalid query" << endl;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    authorAvailList = ReadAuthorAvailList();
    bookAvailList = ReadBookAvailList();

    while (true){
        int choice;
        cout << "1- Add Author" << endl;
        cout << "2- Add Book" << endl;
        cout << "3- update Author" << endl;
        cout << "4- Update Book" << endl;
        cout << "5- Search Author by ID" << endl;
        cout << "6- Search Book by ISBN" << endl;
        cout << "7- Delete Author" << endl;
        cout << "8- Delete Book" << endl;
        cout << "9- Execute Query" << endl;
        cout << "10- Clear" << endl;
        cout << "11- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            AddAuthor();
        } else if (choice == 2) {
            AddBook();
        } else if (choice == 3) {
            char AuthorID[15];
            cout << "Enter Author ID: ";
            cin >> AuthorID;
            char AuthorName[30];
            cout << "Enter Author Name: ";
            cin >> AuthorName;

            updateAuthorName(AuthorID , AuthorName);
        } else if (choice == 4) {
            char ISBN[15];
            cout << "Enter ISBN: ";
            cin >>ISBN;
            char bookTitle[30];
            cout << "Enter book Title: ";
            cin >> bookTitle;

            updateBookTitle(ISBN , bookTitle);

        }
        else if (choice == 5) {
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
        else if (choice == 6) {
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
        else if (choice == 7) {
            char AuthorID[20];
            cout << "Enter Author ID: ";
            cin >> AuthorID;
            DeleteAuthor(AuthorID);
        }
        else if (choice == 8) {
            char ISBN[20];
            cout << "Enter Book ISBN: ";
            cin >> ISBN;
            DeleteBook(ISBN);
        }
        else if (choice == 9) {
            string query;
            cout << "Enter query: ";
            cin.ignore();
            getline(cin, query);
            ExecuteQuery(query);
        }
        else if (choice == 10) {
            Clear();
        }
        else if (choice == 11) {
            WriteAuthorAvailList(authorAvailList);
            WriteBookAvailList(bookAvailList);
            break;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    return 0;
}