# Address Book in C

A command-line address book I built in C while learning at Emertxe. You can add, list, search, edit and delete contacts, and everything is saved to a CSV file, so your contacts are still there the next time you run the program.

I built it to get comfortable with structures, multi-file C projects, file handling and input validation. Along the way it also taught me how a program keeps its data consistent and refuses bad input.

## Features

- **Add** a contact with a name, phone number and email
- **List** all saved contacts
- **Search** contacts by [name / phone / email]
- **Edit** an existing contact
- **Delete** a contact and save the change permanently
- **Validate** phone numbers and emails before anything is stored
- **Block duplicates**: no two contacts can share a phone number or an email
- **Save and load** all data from a CSV file automatically

## Project Structure

```
address-book/
├── addressbook.h    # structures and function declarations
├── addressbook.c    # function definitions
├── main.c           # menu and program flow
├── database.csv     # persistent storage
└── README.md
```

I split the code into three files on purpose:

- `addressbook.h` is the contract. It defines the structures and declares every function.
- `addressbook.c` holds the actual logic for each function.
- `main.c` stays small. It shows the menu, reads the user's choice and calls the right function.

This keeps each file focused, and it taught me how structures and functions are shared safely across files.

## Data Design

I used two structures.

```c
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
};
```

### `Contact`

One entry in the book. It holds the name, phone and email as fixed-size character arrays. The phone array has room for a country code, the digits and the terminating null character.

### `AddressBook`

The whole book, kept as a single unit:

- `contacts[100]` is an array of `Contact` structures, so the book holds up to 100 contacts.
- `contactCount` tracks how many of those 100 slots are actually in use. Every loop, add, delete and save depends on this number being correct.
- `index_record[100]` and `ir_size` are to keep the track of serial number which will be useful while deleting and editing contacts [ when a search finds matches, their positions in `contacts` are stored in `index_record`, and `ir_size` counts how many matches were found, so edit and delete can act on the right contact even when several results come back.]

Because the contacts and the counters live in one structure, I pass a single pointer (`struct AddressBook *`) to each function. The functions then read and update the real book instead of working on copies. Accessing members through that pointer, including the nested array of structures, across different files, was one of the most valuable things I learned in this project.

### Why a fixed array

I used a fixed array of 100 contacts rather than dynamic memory. It keeps the program simple and predictable while I focus on structures, functions and file handling. The limit is that the book cannot grow past 100 contacts, and the add function checks for that before inserting.

## How It Works

### Add

The program asks for a name, phone and email. The phone and email are validated, then checked against existing contacts so duplicates are rejected. Only when everything passes is the contact stored at position `contactCount`, and the count increases. If the book is full, it refuses instead of writing past the end of the array.

### List

It loops from the first contact to the last valid one (`contactCount`) and prints each contact. If the book is empty, it says so.

### Search

It looks through the saved contacts for matches against what the user typed and shows the results, or a "not found" message, strcmp is used here.

### Edit

It finds the contact, then lets the user change the details. New values go through the same validation and duplicate checks as when adding, and the current contact is excluded from the duplicate check so that saving a contact with its own unchanged phone number doesn't count as a duplicate.

### Delete

Removing a contact would leave a gap in the array, so every contact after it moves up one position and `contactCount` decreases by one. The change is then written to the file so the deletion is permanent.

## Validation

The program refuses bad data before it can reach the file. Each rule lives in its own function.

### Phone: `validate_phone`

- Must include a country code
- Must contain only valid characters
- Must match the expected length
- Many other validations

### Email: `validate_email`

- Must contain exactly one `@`
- The `.` cannot come directly after the `@`
- Must start with a lowercase letter
- Many other validations

### Duplicates

- `duplicate_Phone_validation` rejects a phone number that already exists in the book
- `unique_email_validation` rejects an email that already exists

Both functions take the index of the contact being edited (`current_index`), so editing a contact never conflicts with its own existing values.

## File Handling

All data lives in `database.csv`.

- **Saving** (`save_contacts_to_file`): opens the file for writing and uses `fprintf` to write one line per contact, exactly `contactCount` lines. 
- **Loading** (`load_contacts_from_file`): runs at startup and reads each line back into the array using `fscanf`, increasing `contactCount` for every contact read.

### Handling `fscanf` safely

`fscanf` returns the number of fields it read successfully. Each record has three fields (name, phone, email), so the loading loop checks that the return value equals 3. If it doesn't, the loop stops instead of loading incomplete or broken data. Understanding this return value was one of the key things I learned in this project.

### CSV format

```
[name],[phone],[email]
```

*(seerat, +91xxxxxxxxxx, helloxxx@gmail.com)*

## Build and Run

```bash
gcc main.c addressbook.c -o addressbook
./addressbook
```

## Sample Session

<img width="1847" height="945" alt="add 2" src="https://github.com/user-attachments/assets/e0dd194c-f935-4423-be48-3a88eb2f9522" />

<img width="1863" height="970" alt="image" src="https://github.com/user-attachments/assets/125202eb-5dd7-41a7-bc5e-9b57ede476cc" />


## What I Learned

- **Structures across files.** Using one structure inside another as an array, and accessing members correctly through pointers in different files.
- **File I/O.** Saving and loading reliably, and checking `fscanf`'s return value instead of assuming the read worked.
- **Validation.** Phone and email each have many small rules, and checking them before storing is far easier than cleaning bad data later.
- **State consistency.** Keeping `contactCount` accurate through every add and delete.
- **Working in the Linux terminal.** Writing, compiling, running and debugging everything with command-line tools.
- **It was tricky to handle File I/O**

## Known Limitations

- Holds at most 100 contacts
- Commas inside a field would break the CSV format

## Possible Improvements

- Use `malloc` and `realloc` so the book can grow
- Sort contacts alphabetically
- Handle commas and quotes in the CSV properly
- Add partial and case-insensitive search

## Author

Seerat · [GitHub](https://github.com/seeratirsh)
