use std::io::{self, Write};
use library_manager::{Library, Category};

const DB_FILE: &str = "library.json";

fn main() {
    let mut library = Library::load_from_file(DB_FILE).unwrap_or_else(|_| {
        println!("Файл данных не найден. Создана новая библиотека.");
        Library::new()
    });

    println!("=== Система управления студенческой библиотекой ===");
    println!("Добро пожаловать!\n");

    loop {
        print_menu();
        let choice = read_line().trim().to_string();

        match choice.as_str() {
            "1" => add_book(&mut library),
            "2" => register_reader(&mut library),
            "3" => borrow_book(&mut library),
            "4" => return_book(&mut library),
            "5" => list_books(&library),
            "6" => search_books_menu(&library),
            "7" => list_readers(&library),
            "8" => list_books_of_reader(&library),
            "9" => {
                println!("\nЗавершение работы...");
                break;
            }
            _ => println!("⚠ Неверный выбор."),
        }
    }

    show_library_memory_address(&library);

    match library.save_to_file(DB_FILE) {
        Ok(_) => println!("✔ Данные сохранены."),
        Err(e) => eprintln!("⚠ Ошибка сохранения: {}", e),
    }

    println!("До свидания!");
}

fn print_menu() {
    println!("\n┌─────────────────────────────────────┐");
    println!("│           ГЛАВНОЕ МЕНЮ             │");
    println!("├─────────────────────────────────────┤");
    println!("│ 1. Добавить книгу                  │");
    println!("│ 2. Зарегистрировать читателя       │");
    println!("│ 3. Выдать книгу                    │");
    println!("│ 4. Вернуть книгу                   │");
    println!("│ 5. Показать список книг            │");
    println!("│ 6. Поиск книги по названию         │");
    println!("│ 7. Показать список читателей       │");
    println!("│ 8. Показать книги читателя         │");
    println!("│ 9. Выход                           │");
    println!("└─────────────────────────────────────┘");
    print!("Ваш выбор: ");
    io::stdout().flush().unwrap();
}

fn read_line() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input
}

fn add_book(library: &mut Library) {
    println!("\n--- Добавление книги ---");

    print!("Название: ");
    io::stdout().flush().unwrap();
    let title = read_line().trim().to_string();

    print!("Автор: ");
    io::stdout().flush().unwrap();
    let author = read_line().trim().to_string();

    print!("Год издания: ");
    io::stdout().flush().unwrap();
    let year: u32 = match read_line().trim().parse() {
        Ok(y) => y,
        _ => {
            println!("⚠ Некорректный год.");
            return;
        }
    };

    print!("Категория (1 — Художественная, 2 — Учебная, 3 — Научная): ");
    io::stdout().flush().unwrap();
    let cat = match read_line().trim() {
        "1" => Category::Fiction,
        "2" => Category::Education,
        "3" => Category::Science,
        _ => {
            println!("⚠ Некорректная категория.");
            return;
        }
    };

    let book = library.add_book(title, author, year, cat);

    println!(
        "✔ Книга '{}' добавлена (ID {}, категория {:?})",
        book.title, book.id, book.category
    );
}

fn register_reader(library: &mut Library) {
    println!("\n--- Регистрация читателя ---");
    print!("Имя: ");
    io::stdout().flush().unwrap();

    let name = read_line().trim().to_string();
    if name.is_empty() {
        println!("⚠ Имя не может быть пустым.");
        return;
    }

    let reader = library.register_reader(name);
    println!("✔ Читатель '{}' зарегистрирован (ID {}).", reader.name, reader.id);
}

fn borrow_book(library: &mut Library) {
    println!("\n--- Выдача книги ---");

    print!("ID книги: ");
    io::stdout().flush().unwrap();
    let book_id: u32 = match read_line().trim().parse() {
        Ok(id) => id,
        _ => return,
    };

    print!("ID читателя: ");
    io::stdout().flush().unwrap();
    let reader_id: u32 = match read_line().trim().parse() {
        Ok(id) => id,
        _ => return,
    };

    match library.borrow_book(book_id, reader_id) {
        Ok(_) => println!("✔ Книга выдана."),
        Err(e) => println!("⚠ Ошибка: {}", e),
    }
}

fn return_book(library: &mut Library) {
    println!("\n--- Возврат книги ---");

    print!("ID книги: ");
    io::stdout().flush().unwrap();
    let book_id: u32 = match read_line().trim().parse() {
        Ok(id) => id,
        _ => return,
    };

    match library.return_book(book_id) {
        Ok(_) => println!("✔ Книга возвращена."),
        Err(e) => println!("⚠ Ошибка: {}", e),
    }
}

fn list_books_of_reader(library: &Library) {
    print!("\nВведите ID читателя: ");
    io::stdout().flush().unwrap();

    let id: u32 = match read_line().trim().parse() {
        Ok(id) => id,
        _ => return,
    };

    match library.list_books_of_reader(id) {
        Ok(books) => {
            println!("\nКниги читателя {}:", id);
            for b in books {
                println!("• {} ({})", b.title, b.author);
            }
        }
        Err(e) => println!("⚠ Ошибка: {}", e),
    }
}

fn list_books(library: &Library) {
    let books = library.list_books();
    if books.is_empty() {
        println!("⚠ Книг нет.");
        return;
    }

    println!("\n--- Список книг ---");
    for b in books {
        println!(
            "{} — {} ({}, {:?}) [{}]",
            b.id,
            b.title,
            b.year,
            b.category,
            if b.is_available { "доступна" } else { "выдана" }
        );
    }
}

fn list_readers(library: &Library) {
    println!("\n--- Список читателей ---");
    for r in library.list_readers() {
        println!("{} — {}", r.id, r.name);
    }
}

fn search_books_menu(library: &Library) {
    print!("\nВведите часть названия: ");
    io::stdout().flush().unwrap();

    let q = read_line().trim().to_string();

    let results = library.search_books(&q);

    if results.is_empty() {
        println!("⚠ Ничего не найдено.");
        return;
    }

    println!("\n--- Найденные книги ---");
    for b in results {
        println!("{} — {} ({})", b.id, b.title, b.author);
    }
}

fn show_library_memory_address(library: &Library) {
    let raw: *const Library = library;

    unsafe {
        println!("\n⚠ [Unsafe] адрес объекта Library: {:p}", raw);
    }
}
