use std::collections::HashMap;
use std::fmt;
use std::fs::File;
use std::io::{Read, Write};
use serde::{Serialize, Deserialize};

pub mod models;
pub use models::{Book, Reader, Category}; 

#[derive(Debug)]
pub enum LibraryError {
    BookNotFound,
    BookNotAvailable,
    ReaderNotFound,
    InvalidInput,
}

impl fmt::Display for LibraryError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            LibraryError::BookNotFound => write!(f, "Книга не найдена."),
            LibraryError::BookNotAvailable => write!(f, "Книга уже выдана."),
            LibraryError::ReaderNotFound => write!(f, "Читатель не найден."),
            LibraryError::InvalidInput => write!(f, "Некорректный ввод."),
        }
    }
}

#[derive(Serialize, Deserialize)]
pub struct Library {
    books: Vec<Book>,
    readers: HashMap<u32, Reader>,
    next_book_id: u32,
    next_reader_id: u32,
}

impl Library {
    pub fn new() -> Self {
        Self {
            books: vec![],
            readers: HashMap::new(),
            next_book_id: 1,
            next_reader_id: 1,
        }
    }

    pub fn add_book(
        &mut self,
        title: String,
        author: String,
        year: u32,
        category: Category,
    ) -> &Book {
        let book = Book {
            id: self.next_book_id,
            title,
            author,
            year,
            category,
            is_available: true,
        };

        self.books.push(book);
        self.next_book_id += 1;

        self.books.last().unwrap()
    }

    pub fn register_reader(&mut self, name: String) -> &Reader {
        let reader = Reader {
            id: self.next_reader_id,
            name,
            borrowed_books: vec![],
        };

        self.readers.insert(reader.id, reader);
        self.next_reader_id += 1;

        self.readers.get(&(self.next_reader_id - 1)).unwrap()
    }

    fn find_book_mut(&mut self, id: u32) -> Option<&mut Book> {
        self.books.iter_mut().find(|b| b.id == id)
    }

    pub fn borrow_book(&mut self, book_id: u32, reader_id: u32) -> Result<(), LibraryError> {

        let reader = self
            .readers
            .get_mut(&reader_id)
            .ok_or(LibraryError::ReaderNotFound)?;

        {
            let book = self
                .books
                .iter_mut()
                .find(|b| b.id == book_id)
                .ok_or(LibraryError::BookNotFound)?;

            if !book.is_available {
                return Err(LibraryError::BookNotAvailable);
            }

            book.is_available = false;
        }

        reader.borrowed_books.push(book_id);

        Ok(())
    }

    pub fn return_book(&mut self, book_id: u32) -> Result<(), LibraryError> {
        let mut owner_reader_id = None;

        for (rid, reader) in self.readers.iter_mut() {
            if reader.borrowed_books.contains(&book_id) {
                reader.borrowed_books.retain(|&x| x != book_id);
                owner_reader_id = Some(*rid);
                break;
            }
        }

        if owner_reader_id.is_none() {
            return Err(LibraryError::ReaderNotFound);
        }

        let book = self
            .find_book_mut(book_id)
            .ok_or(LibraryError::BookNotFound)?;

        book.is_available = true;

        Ok(())
    }

    pub fn list_books(&self) -> &Vec<Book> {
        &self.books
    }

    pub fn search_books(&self, query: &str) -> Vec<&Book> {
        let q = query.to_lowercase();
        self.books
            .iter()
            .filter(|b| b.title.to_lowercase().contains(&q))
            .collect()
    }

    pub fn filter_by_category(&self, category: Category) -> Vec<&Book> {
        self.books.iter().filter(|b| b.category == category).collect()
    }

    pub fn list_readers(&self) -> Vec<&Reader> {
        self.readers.values().collect()
    }

    pub fn list_books_of_reader(&self, reader_id: u32) -> Result<Vec<&Book>, LibraryError> {
        let reader = self.readers.get(&reader_id)
            .ok_or(LibraryError::ReaderNotFound)?;

        let mut result = Vec::new();

        for &id in &reader.borrowed_books {
            if let Some(book) = self.books.iter().find(|b| b.id == id) {
                result.push(book);
            }
        }

        Ok(result)
    }

    pub fn save_to_file(&self, path: &str) -> Result<(), std::io::Error> {
        let data = serde_json::to_string_pretty(self)?;
        let mut file = File::create(path)?;
        file.write_all(data.as_bytes())?;
        Ok(())
    }

    pub fn load_from_file(path: &str) -> Result<Self, std::io::Error> {
        let mut file = File::open(path)?;
        let mut data = String::new();
        file.read_to_string(&mut data)?;
        let lib = serde_json::from_str(&data)?;
        Ok(lib)
    }
}

// ========== ТЕСТЫ ==========
#[cfg(test)]
mod tests {
    use super::*;

    fn setup_library() -> Library {
        let mut lib = Library::new();
        lib.add_book("Book A".into(), "Author A".into(), 2000, Category::Fiction);
        lib.add_book("Book B".into(), "Author B".into(), 2010, Category::Science);
        lib.add_book("Rust Guide".into(), "Gray".into(), 2022, Category::Education);
        lib.register_reader("Alice".into());
        lib.register_reader("Bob".into());
        lib
    }

    #[test]
    fn test_add_book() {
        let mut lib = Library::new();
        let book = lib.add_book("Test Book".into(), "Tester".into(), 2024, Category::Science);

        assert_eq!(book.id, 1);
        assert_eq!(book.title, "Test Book");
        assert!(book.is_available);
    }

    #[test]
    fn test_register_reader() {
        let mut lib = Library::new();
        let reader = lib.register_reader("Alice".into());

        assert_eq!(reader.id, 1);
        assert_eq!(reader.name, "Alice");
    }

    #[test]
    fn test_borrow_book() {
        let mut lib = setup_library();

        let result = lib.borrow_book(1, 1);
        assert!(result.is_ok());

        let book = lib.books.iter().find(|b| b.id == 1).unwrap();
        assert!(!book.is_available);
    }

    #[test]
    fn test_return_book() {
        let mut lib = setup_library();

        lib.borrow_book(1, 1).unwrap();
        lib.return_book(1).unwrap();

        let book = lib.books.iter().find(|b| b.id == 1).unwrap();
        assert!(book.is_available);
    }

    #[test]
    fn test_search_books() {
        let lib = setup_library();

        let results = lib.search_books("rust");
        assert_eq!(results.len(), 1);
        assert_eq!(results[0].title, "Rust Guide");
    }

    #[test]
    fn test_filter_by_category() {
        let lib = setup_library();

        let sci_books = lib.filter_by_category(Category::Science);
        assert_eq!(sci_books.len(), 1);
        assert_eq!(sci_books[0].title, "Book B");
    }

    #[test]
    fn test_books_of_reader() {
        let mut lib = setup_library();

        lib.borrow_book(1, 1).unwrap();
        let books = lib.list_books_of_reader(1).unwrap();

        assert_eq!(books.len(), 1);
        assert_eq!(books[0].id, 1);
    }
}
