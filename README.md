# E-Wallet

A C++ console-based bank account simulator project with Admin and Client roles.

## Features
- Client registration with auto-generated account ID.
- Login system that detects Admin or Client automatically.
- Admin functionalities: view clients, enable/disable accounts, view statistics.
- Client functionalities: view profile, transfer money, view transaction history.
- Unique username and phone validation for Clients.
- Interactive console menus with arrow-key navigation.

## Project Structure
```
code/ # Source code
diagrams/ # Use case & class diagrams
requirements/ # Project requirements
```

## Usage
1. Compile and run `main.cpp`.
2. Use arrow keys to navigate menus.
3. Login or register as a client, or login as an admin (preloaded admin: `username=admin`, `password=admin`).

## Preloaded Accounts
- Clients: `C001`, `C002` (example)
- Admin: `A001` (username: admin, password: admin)

## Requirements
See `requirements/requirements.pdf` for full functional and non-functional requirements.

## Diagrams
- `diagrams/use_case.png`
- `diagrams/class_diagram.png`
