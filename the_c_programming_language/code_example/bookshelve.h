#ifndef BOOKSHELVE_H
#define BOOKSHELVE_H

typedef struct Book 
{
    char *book_name;                   // name of the book
    char *borrower_name;               // name of the borrower
    struct GregorianDate *borrow_date; // date of borrow
    struct GregorianDate *return_date; // date the book should return in the library
} book;

typedef struct BookSeries 
{
    char *book_name;                   // name of the book
    char *borrower_name;               // name of the borrower
    struct GregorianDate *borrow_date; // date of borrow
    struct GregorianDate *return_date; // date the book should return in the library
    struct BookSeries *next_one;       // next book in the series
} book_series;

#endif