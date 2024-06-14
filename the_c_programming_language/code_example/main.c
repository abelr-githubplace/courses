#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "bookshelve.h"
#include "student.h"

void print_date_gregorian(struct GregorianDate *date)
{
    printf("%s the %i%s, %lli", english_months(date->month), date->day, english_day_extentions(date->day), date->year);
}

void print_date_republican(struct RepublicanDate *date)
{
    if (date->epagomenal) {
        printf("Epagomenal %d", date->epagomenal);
        return;
    }
    printf("%d (%d) / %d (%d) / %lli", date->day, date->decade, date->month, date->season, date->year);
}

void print_book(struct Book *book)
{
    printf("%s", book->book_name);
    if (book->borrow_date) {
        printf("(");
        print_date_gregorian(book->borrow_date);
        printf(" -> ");
        print_date_gregorian(book->return_date);
        printf(" [%s])", book->borrower_name);
    }
    printf("\n");
}

void print_books(struct BookSeries *books)
{
    printf("\n\t-> %s", books->book_name);
    if (books->borrow_date) {
        printf(" (");
        print_date_gregorian(books->borrow_date);
        printf(" -> ");
        print_date_gregorian(books->return_date);
        printf(" [%s])", books->borrower_name);
    }
    if (books->next_one) {
        print_books(books->next_one);
        return;
    }
    printf("\n");
}

void print_student(struct Student *student) {
    printf("%s(%i)[%s]\n", student->name, student->age, batch(student->year));
}

int main()
{
    struct GregorianDate today = {14, 6, 2024};
    union Date now = { today };

    {
        unsigned char this_day = today.day;
        unsigned char this_month = today.month;
        long long this_year = today.year;
        printf("Today: %i/%i/%lli -> ", this_day, this_month, this_year);
        print_date_gregorian(&today);
        printf("\n");
        print_date_gregorian(&now.gregorian);
        printf("\n");
        print_date_republican(&now.republican);
    }

    struct Book harry_potter = {"Harry Potter", NULL, NULL, NULL};
    struct Book lord_of_the_rings = {"The Lord of the Rings", harry_potter.book_name, &today, &(struct GregorianDate){21, 9, 2024}};

    struct BookSeries harry_potter_7 = {"Harry Potter and the Deathly Hallows", "Camille", &(struct GregorianDate){14, 3, 2023}, &(struct GregorianDate){13, 4, 2023}, NULL};
    struct BookSeries harry_potter_6 = {"Harry Potter and the Half-Blood Prince", NULL, NULL, NULL, &harry_potter_7};
    struct BookSeries harry_potter_5 = {"Harry Potter and the Order of the Phoenix", NULL, NULL, NULL, &harry_potter_6};
    struct BookSeries harry_potter_4 = {"Harry Potter and the Gobelet of Fire", NULL, NULL, NULL, &harry_potter_5};
    struct BookSeries harry_potter_3 = {"Harry Potter and the Prisoner of Azkaban", NULL, NULL, NULL, &harry_potter_4};
    struct BookSeries harry_potter_2 = {"Harry Potter and the Chamber of Secrets", NULL, NULL, NULL, &harry_potter_3};
    struct BookSeries harry_potter_1 = {"Harry Potter and the Philosopher's stone", NULL, NULL, NULL, &harry_potter_2};

    {
        unsigned char return_month = lord_of_the_rings.return_date->month;
        printf("\n%s will be back in %s (%i) -> ", lord_of_the_rings.book_name, english_months(return_month), return_month);   
        print_date_gregorian(lord_of_the_rings.return_date);

        printf("\nHarry Potter:\nThe first book: ");
        print_book(&harry_potter);
        printf("The series:");
        print_books(&harry_potter_1);
    }

    struct Student your_asm = {"Abel", 21, ING1};
    print_student(&your_asm);

    return 0;
}