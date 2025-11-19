# Rust ­ Лабораторная работа #2
## Задача 1
### Постановка задачи 
Создайте структуру Pair<T>, которая хранит два значения одного типа T. Реализуйте методы для получения и изменения значений пары. Убедитесь, что использование ссылок и
копирование данных работает корректно.

### Математическая модель 
Структура хранит два значения одного типа и предоставляет методы для их чтения и изменения.
Работа модели основана на использовании ссылок и передаче значений по копированию или перемещению.
Пара служит контейнером для двух взаимосвязанных элементов.

### Список идентификаторов

| Имя переменной | Тип данных          | Описание                                                  |
| -------------- | ------------------- | --------------------------------------------------------- |
| Pair           | struct              | Обобщённая структура, содержащая два значения одного типа |
| first          | T                   | Первое значение пары                                      |
| second         | T                   | Второе значение пары                                      |
| new            | fn(T, T) -> Pair<T> | Создание новой пары                                       |
| get_first      | fn(&self) -> &T     | Получение первого элемента                                |
| get_second     | fn(&self) -> &T     | Получение второго элемента                                |
| set_first      | fn(&mut self, T)    | Изменение первого значения                                |
| set_second     | fn(&mut self, T)    | Изменение второго значения                                |

### Код программы 

```c
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
```
---

## Задача 2
### Постановка задачи 
Определите трейт PrintInfo, который содержит метод print_info(&self). Реализуйте этот
трейт для структуры Person, чтобы можно было вызвать метод print_info на объекте Person.

### Математическая модель 
Трейт определяет единый интерфейс для вывода информации об объекте.
Структура Person реализует данный интерфейс, чтобы обеспечить единообразный вывод данных.
Модель демонстрирует использование трейтов для создания общего поведения.

### Список идентификаторов

| Имя переменной | Тип данных | Описание                                          |
| -------------- | ---------- | ------------------------------------------------- |
| PrintInfo      | trait      | Интерфейс, содержащий метод для вывода информации |
| print_info     | fn(&self)  | Метод вывода данных структуры                     |
| Person         | struct     | Структура, описывающая человека                   |
| name           | String     | Имя человека                                      |
| age            | u32        | Возраст человека                                  |

### Код программы 

```c
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
```
---

## Задача 3
### Постановка задачи 
 Разработайте программу для обработки списка задач (Todo List). Создайте структуру Task с
полями id, title и completed, а также методы для добавления, удаления и изменения статуса
задачи. Реализуйте вывод информации о всех задачах.

### Математическая модель 
Каждая задача описывается структурой Task со своим ID, названием и статусом выполнения.
Коллекция задач хранится в структуре TodoList и обрабатывается через методы управления.
Модель демонстрирует работу с динамическими коллекциями и мутабельными данными.
### Список идентификаторов

| Имя переменной | Тип данных               | Описание                        |
| -------------- | ------------------------ | ------------------------------- |
| Task           | struct                   | Структура задачи                |
| id             | u32                      | Уникальный идентификатор задачи |
| title          | String                   | Название задачи                 |
| completed      | bool                     | Статус выполнения               |
| TodoList       | struct                   | Коллекция задач                 |
| tasks          | Vec<Task>                | Массив задач                    |
| add_task       | fn(&mut self, u32, &str) | Добавление задачи               |
| remove_task    | fn(&mut self, u32)       | Удаление задачи                 |
| toggle_status  | fn(&mut self, u32)       | Изменение статуса               |
| print_all      | fn(&self)                | Вывод всех задач                |

### Код программы 

```c
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
```
---

## Задача 4
### Постановка задачи 
Напишите функцию find_unique_elements, которая принимает вектор элементов типа T и
возвращает вектор уникальных элементов. Определите трейт Unique c методом is_unique,
который проверяет, является ли элемент уникальным.

### Математическая модель 
Каждый элемент проверяется на уникальность внутри коллекции с помощью трейта Unique.
Функция фильтрует элементы, встречающиеся в списке только один раз.
Модель применяет сравнение и анализ данных в коллекции.

### Список идентификаторов

| Имя переменной       | Тип данных              | Описание                            |
| -------------------- | ----------------------- | ----------------------------------- |
| Unique               | trait                   | Интерфейс для проверки уникальности |
| is_unique            | fn(&self, &[T]) -> bool | Проверка уникальности элемента      |
| find_unique_elements | fn(Vec<T>) -> Vec<T>    | Возврат вектора уникальных значений |
| vec                  | Vec<T>                  | Исходная коллекция элементов        |

### Код программы 

```c
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
```
---

## Задача 5
### Постановка задачи 
Напишите функцию sum_collection, которая принимает коллекцию элементов типа T и
возвращает их сумму. Ограничьте тип T требованием наличия метода addition() в некотором трейте Addable для поддержки суммирования. Просуммируйте затем любую коллекцию
структур вида:
struct Number {
value: u32,
}

### Математическая модель 
Трейт Addable задаёт правило сложения пользовательских типов.
Функция принимает коллекцию элементов и суммирует их, используя метод addition().
Модель демонстрирует абстракцию операций и полиморфизм поведения.

### Список идентификаторов

| Имя переменной | Тип данных               | Описание                           |
| -------------- | ------------------------ | ---------------------------------- |
| Addable        | trait                    | Интерфейс, задающий метод сложения |
| addition       | fn(&self, &Self) -> Self | Операция сложения элементов        |
| Number         | struct                   | Структура с числовым значением     |
| value          | u32                      | Значение числа                     |
| sum_collection | fn(&[T]) -> T            | Суммирование коллекции             |
| collection     | &[T]                     | Входная коллекция элементов        |

### Код программы 

```c
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
```
---

## Задача 6
### Постановка задачи 
Создайте обобщенную структуру Collection<T>, которая содержит вектор элементов типа
T. Реализуйте методы add_element(), get_element() и remove_element(), ограничив тип T
trait’ом Clone:
• https://doc.rust­lang.org/std/clone/trait.Clone.html
• https://doc.rust­lang.org/rust­by­example/trait/clone.html
• https://doc.rust­lang.org/std/clone/index.html
• https://oswalt.dev/2023/12/copy­and­clone­in­rust/
• https://blog.logrocket.com/disambiguating­rust­traits­copy­clone­dynamic/

### Математическая модель
Коллекция представляет собой обёртку над вектором элементов с возможностью добавления, получения и удаления данных.
Тип T ограничен трейтами Clone, чтобы корректно копировать элементы при работе.
Модель демонстрирует управление пользовательскими контейнерами.

### Список идентификаторов

| Имя переменной | Тип данных                        | Описание                       |
| -------------- | --------------------------------- | ------------------------------ |
| Collection     | struct                            | Обобщённая коллекция элементов |
| elements       | Vec<T>                            | Хранилище элементов            |
| add_element    | fn(&mut self, T)                  | Добавление элемента            |
| get_element    | fn(&self, usize) -> Option<T>     | Получение элемента             |
| remove_element | fn(&mut self, usize) -> Option<T> | Удаление элемента              |

### Код программы 

```c
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
```
---

## Задача 7
### Постановка задачи 
Создайте трейт Summable, который требует реализации метода sum(&self) -> u32 для типов,
поддерживающих сложение. Реализуйте этот трейт для структуры Pair<T>, которая содержит
два поля типа T (сумма чисел в этой паре). Добавьте ограничение на тип T для поддержки
сложения:
• https://doc.rust­lang.org/book/ch19­03­advanced­traits.html
• https://doc.rust­lang.org/std/ops/trait.Add.html
• https://doc.rust­lang.org/std/ops/index.html
• https://stackoverflow.com/questions/28005134/how­do­i­implement­the­add­trait­for­areference­to­a­struct
• https://doc.rust­lang.org/book/ch10­02­traits.html#implementing­a­trait­on­a­type
• https://doc.rust­lang.org/book/appendix­03­derivable­traits.html

### Математическая модель 
Трейт Summable задаёт интерфейс вычисления суммы.
Структура Pair<T> реализует суммирование пары значений на основе трейта Add и конверсии в u32.
Модель демонстрирует расширение функциональности обобщённых структур.

### Список идентификаторов

| Имя переменной | Тип данных       | Описание                                       |
| -------------- | ---------------- | ---------------------------------------------- |
| Summable       | trait            | Интерфейс суммирования                         |
| sum            | fn(&self) -> u32 | Метод суммирования для структур                |
| Pair           | struct           | Пара значений одного типа                      |
| T              | тип-параметр     | Обобщённый тип, поддерживающий Add и Into<u32> |
| first          | T                | Первый элемент                                 |
| second         | T                | Второй элемент                                 |

### Код программы 

```c
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
```

### Результаты работы программы  
![result 1](./img/task2.png) 
---  

### Информация о студенте  
Полторацкая Анастасия, 1 курс, группа `1об_ПОО/25` 