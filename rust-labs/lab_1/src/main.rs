use std::io;

// ---------- Задание 1 ----------
fn task1() {
    println!("--- Задание 1 ---");
    println!("Введите ваше имя:");
    let mut name = String::new();
    io::stdin().read_line(&mut name).expect("Ошибка ввода");
    println!("Привет, {}!", name.trim());
}

// ---------- Задание 2 ----------
fn task2() {
    println!("--- Задание 2 ---");
    let mut num: u32 = 10;
    println!("Начальное значение: {}", num);
    num = 42;
    println!("Новое значение: {}", num);
}

// ---------- Задание 3 ----------
fn string_length(s: &str) -> usize {
    s.len()
}

fn task3() {
    println!("--- Задание 3 ---");
    println!("Длина 'hello' = {}", string_length("hello"));
    println!("Длина 'Rust язык' = {}", string_length("Rust язык"));
}

// ---------- Задание 4 ----------
struct Car {
    brand: String,
    model: String,
    year: u16,
}

fn task4() {
    println!("--- Задание 4 ---");
    let cars = vec![
        Car { brand: "Toyota".into(), model: "Corolla".into(), year: 2015 },
        Car { brand: "Volkswagen".into(), model: "Polo".into(), year: 2018 },
        Car { brand: "Ford".into(), model: "Focus".into(), year: 2012 },
    ];

    for car in cars {
        println!("{} {} ({})", car.brand, car.model, car.year);
    }
}

// ---------- Задание 5 ----------
fn fib(n: u32) -> u32 {
    if n <= 1 { n } else { fib(n - 1) + fib(n - 2) }
}

fn task5() {
    println!("--- Задание 5 ---");
    println!("Введите N:");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Ошибка ввода");

    let n: u32 = input.trim().parse().expect("Введите число!");
    println!("Число Фибоначчи №{} = {}", n, fib(n));
}

// ---------- Задание 6 ----------
#[derive(Debug, Copy, Clone)]
enum DayOfWeek {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
}

fn next_day(day: DayOfWeek) -> DayOfWeek {
    match day {
        DayOfWeek::Monday    => DayOfWeek::Tuesday,
        DayOfWeek::Tuesday   => DayOfWeek::Wednesday,
        DayOfWeek::Wednesday => DayOfWeek::Thursday,
        DayOfWeek::Thursday  => DayOfWeek::Friday,
        DayOfWeek::Friday    => DayOfWeek::Saturday,
        DayOfWeek::Saturday  => DayOfWeek::Sunday,
        DayOfWeek::Sunday    => DayOfWeek::Monday,
    }
}

fn task6() {
    println!("--- Задание 6 ---");
    let today = DayOfWeek::Sunday;
    println!("Сегодня: {:?}, завтра: {:?}", today, next_day(today));
}


// ---------- Задание 7 ----------
#[derive(Debug, Clone)]
enum Category {
    Food,
    Electronics,
    Clothes,
}

#[derive(Debug, Clone)]
struct Product {
    name: String,
    price: f32,
    category: Category,
}

impl Product {
    fn print_info(&self) {
        println!("Товар: {}, цена: {}, категория: {:?}", 
            self.name, self.price, self.category);
    }

    fn total_by_category(products: &[Product], cat: &Category) -> f32 {
        products
            .iter()
            .filter(|p| std::mem::discriminant(&p.category) == std::mem::discriminant(cat))
            .map(|p| p.price)
            .sum()
    }
}

fn task7() {
    println!("--- Задание 7 ---");
    let products = vec![
        Product { name: "Хлеб".into(), price: 30.0, category: Category::Food },
        Product { name: "Телефон".into(), price: 20000.0, category: Category::Electronics },
        Product { name: "Куртка".into(), price: 3500.0, category: Category::Clothes },
        Product { name: "Молоко".into(), price: 60.0, category: Category::Food },
    ];

    for p in &products {
        p.print_info();
    }

    let total = Product::total_by_category(&products, &Category::Food);
    println!("Сумма товаров категории Food: {}", total);
}

// ---------- Задание 8 ----------
#[derive(Debug, Clone, PartialEq)]
enum Position {
    Manager,
    Developer,
    Analyst,
}

#[derive(Debug, Clone)]
struct Employee {
    name: String,
    position: Position,
    salary: f32,
}

fn filter_by_position(employees: Vec<Employee>, pos: Position) -> Vec<Employee> {
    employees.into_iter().filter(|e| e.position == pos).collect()
}

fn task8() {
    println!("--- Задание 8 ---");
    let staff = vec![
        Employee { name: "Иван".into(), position: Position::Developer, salary: 120000.0 },
        Employee { name: "Анна".into(), position: Position::Manager, salary: 150000.0 },
        Employee { name: "Павел".into(), position: Position::Developer, salary: 110000.0 },
        Employee { name: "Ольга".into(), position: Position::Analyst, salary: 90000.0 },
    ];

    let devs = filter_by_position(staff, Position::Developer);

    println!("Разработчики:");
    for d in devs {
        println!("{:?}", d);
    }
}

// ---------- Точка входа ----------
fn main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
}
