# The C programming language: data types

The C programming language is a hard typed language meaning each variable has a defined type at compile time and is _explicitely written in the code_.

## Primitive types

| Type                                                  | Bytes |                  Lower bound |                 Higher bound |
| :---------------------------------------------------- | :---: | ---------------------------: | ---------------------------: |
| **Signed types**                                      |       |                              |                              |
| `char`                                                |  $1$  |                       $-128$ |                        $127$ |
| `short`, (16 bits processors) `int`                   |  $2$  |                    $-32,768$ |                     $32,767$ |
| `long`, (32 bits processors) `int`                    |  $4$  |             $-2,147,483,648$ |              $2,147,483,647$ |
| `long long`                                           |  $8$  | $-9,223,372,036,854,775,808$ |  $9,223,372,036,854,775,807$ |
| **Unsigned types**                                    |       |                              |                              |
| `unsigned char`                                       |  $1$  |                          $0$ |                        $255$ |
| `unsigned short`, (16 bits processors) `unsigned int` |  $2$  |                          $0$ |                     $65,535$ |
| `unsigned long`, (32 bits processors) `unsigned int`  |  $4$  |                          $0$ |              $4,294,967,295$ |
| `unsigned long long`                                  |  $8$  |                          $0$ | $18,446,744,073,709,551,615$ |
| **Floatting types**                                   |       |                              |                              |
| `float`                                               |  $4$  |     $3.4 \times 10^{\, -38}$ |      $3.4 \times 10^{\, 38}$ |
| `double`                                              |  $8$  |    $1.7 \times 10^{\, -308}$ |     $1.7 \times 10^{\, 308}$ |
| `long double`                                         | $10$  |   $3.4 \times 10^{\, -4932}$ |    $3.4 \times 10^{\, 4932}$ |

> Note that in C everything is a number.  
> Even a `char` is only the decimal value of an ASCII character.

## Structures

### Structure definition

A structure is defined using the keyword `struct`.
It contains one or more **fields** (or members) of any specified type.
It is identified by a name or **tag**.  
The following structure can hold most of dates in the Gregorian calendar.

```c
struct GregorianDate
{
    unsigned char day;   // from 0 to 31 days
    unsigned char month; // from 0 to 12 months
    long long year;      // from -9 quintillion to 9 quintillion years
};
```

> Note that a structure definition cannot initialize any value.  
> Initialization happens when creating an instance.

It has three fields: `day`, `month` and `year`. Its tag is `GregorianDate`.  
Let's initialize today's date.

```c
struct GregorianDate today = {14, 6, 2024};
```

> Note that to use the type you must specify that it is a structure with the keyword `struct`.

### Dot operator

To access today's fields we must use the dot operator `.` as follows.

```c
unsigned char this_day = today.day;
unsigned char this_month = today.month;
long long this_year = today.year;
```

### Nested structures

As the `struct GregorianDate` is a type in itself, it can be nested into another structure. Let's create a structure that reference a book from a library.

```c
struct Book
{
    char *book_name;                   // name of the book
    char *borrower_name;               // name of the borrower
    struct GregorianDate *borrow_date; // date of borrow
    struct GregorianDate *return_date; // date the book should return in the library
};
```

As implemented we can create some books.

```c
struct Book harry_potter = {"Harry Potter", 0, 0, 0};
struct Book lord_of_the_rings =
{
    "The Lord of the Rings",
    harry_potter.book_name,
    &today,
    &(struct GregorianDate){21, 9, 2024}
};
```

> Note that when a pointer value is $0$ it is considered a `NULL` pointer. The above could be written using the standard library as follows.
>
> ```c
> #include <stdlib.h>
>
> ...
>
> struct Book harry_potter = {"Harry Potter", NULL, NULL, NULL};
> ```
>
> Also when a struct is initialized without any tag it has to be casted otherwise the compiler doesnot recognize its type.

### Arrow operator

To access the month in which the book "The Lord of the Rings" will return to the library we have to use the arrow operator `->` as follows.

```c
unsigned char return_month = lord_of_the_rings.return_date->month;
```

This happens because `lord_of_the_rings.return_date` is of type `struct GregorianDate *`. To access a field of any structure that is behind a pointer we need to use the arrow operator instead of the dot operator.

### Self reference

When reading a book series we might want to read the second one after reading the first one. We can extend our structure definition of a book to account for that.

```c
typedef struct BookSeries
{
    char *book_name;                   // name of the book
    char *borrower_name;               // name of the borrower
    struct GregorianDate *borrow_date; // date of borrow
    struct GregorianDate *return_date; // date the book should return in the library
    struct BookSeries *next_one;       // next book in the series
};
```

See that we can use the structure we are currently defining into the definition.  
Let's update our books.

```c
struct BookSeries harry_potter_7 =
{
    "Harry Potter and the Deathly Hallows",
    "Camille",
    &(struct GregorianDate){14, 3, 2023},
    &(struct GregorianDate){13, 4, 2023},
    NULL
};
struct BookSeries harry_potter_6 =
{
    "Harry Potter and the Half-Blood Prince",
    NULL, NULL, NULL, &harry_potter_7
};
struct BookSeries harry_potter_5 =
{
    "Harry Potter and the Order of the Phoenix",
    NULL, NULL, NULL, &harry_potter_6
};
struct BookSeries harry_potter_4 =
{
    "Harry Potter and the Gobelet of Fire",
    NULL, NULL, NULL, &harry_potter_5
};
struct BookSeries harry_potter_3 =
{
    "Harry Potter and the Prisoner of Azkaban",
    NULL, NULL, NULL, &harry_potter_4
};
struct BookSeries harry_potter_2 =
{
    "Harry Potter and the Chamber of Secrets",
    NULL, NULL, NULL, &harry_potter_3
};
struct BookSeries harry_potter_1 =
{
    "Harry Potter and the Philosopher's stone",
    NULL, NULL, NULL, &harry_potter_2
};
```

### Advanced data management

#### Packing

The C programming language uses padding in between fields of a structure to minimize CPU read cycles when reading multiple fields in the same structure.  
To avoid this padding whe can use packing with the `__attribute((packed))__` attribute in the structure definition.

```c
struct Student
{
    char *name; // name of the student
    char age;   // their age
    short year; // the year they are enroled in
} __attribute((packed)) __;
```

#### Bit fields

Remember how we had more than enough numbers for days and months when defining our `GregorianDate` structure?  
When deciding for a type to hold a value we can sometimes squeeze a little more and only use a specified number of bits. This is called **bit fields**.

```c
struct GregorianDate
{
    unsigned char day : 5;   // 2^5 = 32 enough to store 31 days
    unsigned char month : 4; // 2^4 = 16 enough to store 12 months
    long long year;
};
```

## Unions

A union is a kind of structure where only one field can be used at a time.  
It is defined using the `union` keyword.

```c
/// A structure to hold a date in the Republican Calendar.
struct RepublicanDate
{
    unsigned char day;
    unsigned char decade;
    unsigned char month;
    unsigned char season;
    long long year;
    unsigned char epagomenal;
};

/// A union to hold a date in any format.
union Date
{
    struct GregorianDate gregorian;
    struct RepublicanDate republican;
};
```

> Note that this union cannot hold two dates but only one at a time.

Like a struct, its field can be accessed with the dot operator or arrow operator when behind a pointer.

### Difference with a structure

The difference between unions and structures lies in how they use the memory space.  
A structure size is the sum of all its fields' sizes.  
A union size is the size of its biggest field.

In a structure each field **has its own memory space** where in a union every fields **share the memory space**.

## Enumerations

An enumeration is a type that holds only one value at a time from a group of possible values called **variants**.
To define an enumeration, we use the keyword `enum`.  
Let's create one that holds our students `year` field.

```c
enum YearBatch
{
    SUP,
    SPE,
    ING1,
    ING2,
    ING3,
};
```

> Remember that any variant is an unsigned number.

However, this enumeration starts at $0$ where we want to start at our first year. Thankfully, we can just specify the index value of every variant as follows.

```c
enum YearBatch
{
    SUP = 1,
    SPE = 2,
    ING1 = 3,
    ING2 = 4,
    ING3 = 5,
};
```

But the C programming language indexes its enumeration variants in order so we only need to specify the first one in this case.

```c
enum YearBatch
{
    SUP = 1,
    SPE,
    ING1,
    ING2,
    ING3,
};
```

## Type aliases

It is sometimes tideous to write `struct GregorianDate` or `enum YearBatch` all the time with the keyword in front.
To avoid that we can alias the type with the `typedef` keyword.  
Let's alias our previous types.

```c
typedef struct GregorianDate gregorian_date;
typedef struct Book book;
typedef struct BookSeries book_series;
typedef struct Student student;
typedef enum YearBatch year_batch;
typedef struct RepublicanDate;
typedef union Date;
```

> Note that the norm _ISO C_ recommend for enumerations not to be refered to before being defined.  
> Therefore the following is not recommended.
>
> ```c
> typedef enum YearBatch year_batch;
> enum YearBatch
> {
>     SUP = 1,
>     SPE,
>     ING1,
>     ING2,
>     ING3,
> };
> ```
>
> Instead do the type alias afterward.
>
> ```c
> enum YearBatch
> {
>     SUP = 1,
>     SPE,
>     ING1,
>     ING2,
>     ING3,
> };
> typedef enum YearBatch year_batch;
> ```

### On definition

That's one way to do it but you can actually do it while defining your type.

```c
typedef struct GregorianDate
{
    unsigned char day;
    unsigned char month;
    long long year;
} gregorian_date;

typedef struct RepublicanDate
{
    unsigned char day;
    unsigned char decade;
    unsigned char month;
    unsigned char season;
    long long year;
    unsigned char epagomenal;
} republican_date;

typedef union Date
{
    gregorian_date gregorian;
    republican_date republican;
} date;

typedef struct Book
{
    char *book_name;
    char *borrower_name;
    struct GregorianDate *borrow_date;
    struct GregorianDate *return_date;
} book;

typedef struct BookSeries
{
    char *book_name;
    char *borrower_name;
    struct GregorianDate *borrow_date;
    struct GregorianDate *return_date;
    struct BookSeries *next_one;
} book_series;

typedef struct Student
{
    char *name;
    char age;
    short year;
} student;

typedef enum YearBatch
{
    SUP = 1,
    SPE,
    ING1,
    ING2,
    ING3,
}; year_batch;
```

If the type alias is done with the definition we can even remove the tag from the structure or enumeration.

```c
typedef struct
{
    unsigned char day;
    unsigned char month;
    long long year;
} gregorian_date;

typedef struct
{
    unsigned char day;
    unsigned char decade;
    unsigned char month;
    unsigned char season;
    long long year;
    unsigned char epagomenal;
} republican_date;

typedef union
{
    gregorian_date gregorian;
    republican_date republican;
} date;

typedef struct
{
    char *book_name;
    char *borrower_name;
    gregorian_date *borrow_date;
    gregorian_date *return_date;
} book;

typedef struct
{
    char *book_name;
    char *borrower_name;
    gregorian_date *borrow_date;
    gregorian_date *return_date;
    book_series *next_one;
} book_series;

typedef struct
{
    char *name;
    char age;
    short year;
} student;

typedef enum
{
    SUP = 1,
    SPE,
    ING1,
    ING2,
    ING3,
}; year_batch;
```
