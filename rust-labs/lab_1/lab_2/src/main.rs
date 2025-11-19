use std::ops::Add;

// ---------- Задание 1 ----------
#[derive(Debug, Clone)]
struct Pair<T> {
    first: T,
    second: T,
}

impl<T> Pair<T> {
    fn new(first: T, second: T) -> Self {
        Self { first, second }
    }

    fn get_first(&self) -> &T {
        &self.first
    }

    fn get_second(&self) -> &T {
        &self.second
    }

    fn set_first(&mut self, value: T) {
        self.first = value;
    }

    fn set_second(&mut self, value: T) {
        self.second = value;
    }
}

fn task1() {
    let mut pair = Pair::new(10, 20);
    println!("Task 1 — initial pair: {:?}", pair);
    pair.set_first(100);
    pair.set_second(200);
    println!("Task 1 — updated pair: {:?}", pair);
}

// ---------- Задание 2 ----------
trait PrintInfo {
    fn print_info(&self);
}

struct Person {
    name: String,
    age: u32,
}

impl PrintInfo for Person {
    fn print_info(&self) {
        println!("Person: {}, age {}", self.name, self.age);
    }
}

fn task2() {
    let p = Person {
        name: "Anna".into(),
        age: 25,
    };
    println!("Task 2:");
    p.print_info();
}

// ---------- Задание 3 ----------
#[derive(Debug)]
struct Task {
    id: u32,
    title: String,
    completed: bool,
}

struct TodoList {
    tasks: Vec<Task>,
}

impl TodoList {
    fn new() -> Self {
        Self { tasks: Vec::new() }
    }

    fn add_task(&mut self, id: u32, title: &str) {
        self.tasks.push(Task {
            id,
            title: title.to_string(),
            completed: false,
        });
    }

    fn remove_task(&mut self, id: u32) {
        self.tasks.retain(|t| t.id != id);
    }

    fn toggle_status(&mut self, id: u32) {
        if let Some(task) = self.tasks.iter_mut().find(|t| t.id == id) {
            task.completed = !task.completed;
        }
    }

    fn print_all(&self) {
        for task in &self.tasks {
            println!("{:?}", task);
        }
    }
}

fn task3() {
    println!("Task 3:");
    let mut list = TodoList::new();
    list.add_task(1, "Learn Rust");
    list.add_task(2, "Write code");

    list.toggle_status(1);
    list.print_all();
}

// ---------- Задание 4 ----------
trait Unique<T> {
    fn is_unique(&self, collection: &[T]) -> bool
    where
        T: PartialEq;
}

impl<T: PartialEq> Unique<T> for T {
    fn is_unique(&self, collection: &[T]) -> bool {
        collection.iter().filter(|x| *x == self).count() == 1
    }
}

fn find_unique_elements<T: PartialEq + Clone>(vec: Vec<T>) -> Vec<T> {
    vec.iter()
        .filter(|&item| item.is_unique(&vec))
        .cloned()
        .collect()
}

fn task4() {
    println!("Task 4:");
    let numbers = vec![1, 2, 2, 3, 4, 4, 5];
    let unique = find_unique_elements(numbers);
    println!("Unique elements: {:?}", unique);
}

// ---------- Задание 5 ----------
trait Addable {
    fn addition(&self, other: &Self) -> Self;
}

#[derive(Clone, Debug)]
struct Number {
    value: u32,
}

impl Addable for Number {
    fn addition(&self, other: &Self) -> Self {
        Number {
            value: self.value + other.value,
        }
    }
}

fn sum_collection<T: Addable + Clone>(collection: &[T]) -> T {
    let mut sum = collection[0].clone();
    for item in &collection[1..] {
        sum = sum.addition(item);
    }
    sum
}

fn task5() {
    println!("Task 5:");
    let nums = vec![
        Number { value: 5 },
        Number { value: 10 },
        Number { value: 20 },
    ];
    let result = sum_collection(&nums);
    println!("Sum = {:?}", result);
}

// ---------- Задание 6 ----------
#[derive(Debug)]
struct Collection<T: Clone> {
    elements: Vec<T>,
}

impl<T: Clone> Collection<T> {
    fn new() -> Self {
        Self { elements: Vec::new() }
    }

    fn add_element(&mut self, value: T) {
        self.elements.push(value);
    }

    fn get_element(&self, index: usize) -> Option<T> {
        self.elements.get(index).cloned()
    }

    fn remove_element(&mut self, index: usize) -> Option<T> {
        if index < self.elements.len() {
            Some(self.elements.remove(index))
        } else {
            None
        }
    }
}

fn task6() {
    println!("Task 6:");
    let mut c = Collection::new();
    c.add_element(10);
    c.add_element(20);

    println!("Element at index 1: {:?}", c.get_element(1));
    c.remove_element(0);
    println!("Collection after removal: {:?}", c);
}

// ---------- Задание 7 ----------
trait Summable {
    fn sum(&self) -> u32;
}

impl<T> Summable for Pair<T>
where
    T: Add<Output = T> + Clone + Into<u32>,
{
    fn sum(&self) -> u32 {
        let a: u32 = self.first.clone().into();
        let b: u32 = self.second.clone().into();
        a + b
    }
}

fn task7() {
    println!("Task 7:");
    let p = Pair::new(5u32, 7u32);
    println!("Sum of pair = {}", p.sum());
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
}



