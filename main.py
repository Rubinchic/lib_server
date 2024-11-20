import socket

def send_request(command, data=""):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("127.0.0.1", 8080))
        s.sendall(f"{command}\n{data}".encode())
        response = s.recv(1024).decode()
        print(response)

def add_book():
    title = input("Enter title: ")
    author = input("Enter author: ")
    year = input("Enter year: ")
    genre = input("Enter genre: ")
    data = f"{title}\n{author}\n{year}\n{genre}"
    send_request("ADD", data)

def list_books():
    send_request("LIST")

def update_book():
    book_id = input("Enter book ID to update: ")
    title = input("Enter new title: ")
    author = input("Enter new author: ")
    year = input("Enter new year: ")
    genre = input("Enter new genre: ")
    data = f"{book_id}\n{title}\n{author}\n{year}\n{genre}"
    send_request("UPDATE", data)

def delete_book():
    book_id = input("Enter book ID to delete: ")
    send_request("DELETE", book_id)

while True:
    print("\n1. Add Book")
    print("2. List Books")
    print("3. Update Book")
    print("4. Delete Book")
    print("5. Exit")

    choice = input("Enter choice: ")
    if choice == "1":
        add_book()
    elif choice == "2":
        list_books()
    elif choice == "3":
        update_book()
    elif choice == "4":
        delete_book()
    elif choice == "5":
        break
    else:
        print("Invalid choice")
