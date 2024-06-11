# SFSD Project: Contact Management System

## Overview

This project is a simple contact management system implemented in C. It allows users to create a file with random contacts, search for a contact, insert a new contact, and perform a logical deletion of a contact. The system utilizes linked lists, pointers, binary files, memory allocation, and other fundamental concepts in C programming.

## Features

- Create a file with random contacts
- Search for a contact by ID
- Insert a new contact
- Logical deletion of a contact
- Display file contents

## Project Structure

```
project/
├── main.c
├── LOVC.h
└── Contacts.bin
```

### Prerequisites

- C Compiler (e.g., GCC)
- VSCode or any other C development environment

## Functionalities

- **Create Contacts File**: Generate a file populated with random contact details.
- **Search Contacts**: Look up specific contacts using various search criteria.
- **Insert New Contact**: Add new contact entries to the file.
- **Logical Deletion**: Mark contacts as deleted without physically removing them from the file.

## Implementation Details

### Linked List

The project utilizes a linked list data structure to efficiently manage the contacts. Each node in the linked list represents a contact, containing information such as name, phone number, email, etc. Pointers are used to link the nodes together, enabling dynamic memory allocation and manipulation.

### File Handling

Contacts are stored in a binary file (`Contacts.bin`) using structured file I/O operations. This ensures persistent storage of contact information even after the program terminates. The binary file format optimizes read and write operations, enhancing performance and data integrity.

### Memory Allocation

Dynamic memory allocation is employed for creating and managing contact structures within the linked list. This allows for flexible memory usage, enabling the system to adapt to varying numbers of contacts without wasting memory.

## Authors

- Haddadi Chakib
- Baslimane Lokmane Elhakim
