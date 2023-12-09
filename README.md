# Library Catalog System Assigment 1
This is a collaboration to complete the project of the **File Management and Processing** Course at FCAI CU.

## Some rules To remember while we keep going in the assignment
In this assignment you will implement a simple library catalog system in which a user can
search for a book or an author. Also, the administrator of the system could add a book
record, delete a book record, add an author record and delete an author record.
 First, we want to store data about authors and books (for simplicity assume that each author
can write many books and the book is written by only one author).
We want to store 5 authors and 10 books.
Save the data for authors and books in the following format: delimited fields and length
indicator record.
 Consider the following specifications for the fields of each record in both the authors and
books data files:
Authors Data file
Char Author ID [15] //primary key
Char Author Name [30]// secondary key
Char Address [30] 

Books Data file
Char ISBN [15] //primary key
Char Book Title [30]
Char Author ID [15] // secondary key

Please consider building the following indexes:
o Primary index using the Author ID (for Authors data file).
o Primary index using the ISBN (for Books data file).
o Secondary index using the Author ID (for the Books data file).
o Secondary index using the Author Name (for the Authors data file).
 Implement add, update and delete functions. Make sure that consider the following situations
in your design:
o When you add a record, first look at the AVAIL LIST, then write the record. If there
is a record available in the AVAIL LIST, write the record to a record AVAIL LIST
points and make appropriate changes on the AVAIL LIST.
o If the record to be added already exits, do not write that record to the file.
o When you delete a record, do not physically delete the record from file, just put a
marker (*) on the file and make appropriate changes on AVAIL LIST.
o If the record to be deleted does not exist, display a warning message on the screen.
o For the update function, make updates to non-key fields only. Also, updates to these
fields will not exceed the allocated size.
o Note: all add and delete operations will affect indexes.
 Implement search operations. Make sure to consider the following:
o Search operations will use indexes (primary or secondary).
o All indexes are sorted ascending.
o Searching in indexes is performed using Binary search.
o Bind all secondary indexes with the primary index, don’t bind them by addresses
directly.
o You must implement secondary indexes using linked list technique.
 The user can write a query that contains specific key words (formatted in red below). Some
examples of user queries are as follows:
o Select all from Authors where Author ID=’xxx’; // this query will use primary index to get the
results
o Select all from Books where Author ID=’xxx’; // this query will use secondary index to get the
results.
o Select Author Name from Authors where Author ID=’xxx’; // this query will use secondary
index to get the results.
 The main welcome screen is below
 Add New Author
 Add New Book
 Update Author Name (Author ID)
 Update Book Title (ISBN)
 Delete Book (ISBN)
 Delete Author (Author ID)
 Print Author (Author ID)
 Print Book (ISBN)
 Write Query
 Exit
