#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/student.h"
#include "../include/file_io.h"
#include "../include/network.h"
#include "../include/gui.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    printf("========================================\n");
    printf("     СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ\n");
    printf("========================================\n\n");

    /* 1. СЕТЬ */
    if (init_network() != 0) {
        printf("[WARN] Продолжаю без сетевых функций\n");
    }

    /* 2. ЗАГРУЗКА ДАННЫХ */
    printf("[1] Загрузка данных студентов...\n");
    StudentList* students = load_students_from_json("data/students.json");

    if (!students) {
        printf("[INFO] Файл не найден/пуст — создаю новый список...\n");
        students = create_student_list(10);

        add_student(students, "2023001", "Иванов Иван Иванович", 20, 4.5);
        add_student(students, "2023002", "Петрова Анна Сергеевна", 21, 4.7);
        add_student(students, "2023003", "Сидоров Алексей Петрович", 19, 4.2);
        add_student(students, "2023004", "Кузнецова Мария Владимировна", 22, 4.9);
        add_student(students, "2023005", "Смирнов Дмитрий Алексеевич", 20, 4.3);
    }

    printf("Загружено студентов: %d\n\n", students->count);

    /* 3. ВЫВОД */
    printf("[2] Текущий список студентов:\n");
    print_students(students);

    /* 4. СОРТИРОВКА */
    printf("[3] Сортировка студентов по среднему баллу...\n");
    sort_students_by_gpa(students);
    print_students(students);

    /* 5. СЕТЕВАЯ ЗАГРУЗКА */
    printf("[4] Попытка загрузки дополнительных данных...\n");
    if (download_file(
            "https://jsonplaceholder.typicode.com/users",
            "data/external_data.json") == 0) {
        printf("[INFO] Дополнительные данные успешно загружены\n");
    }

 printf("\n[5] Запуск графического интерфейса...\n");

if (init_gui() == 0) {
    if (create_window("Система управления студентами", 800, 600) == 0) {

        render_students(renderer, students);

        SDL_Delay(5000);   
        close_window();
    }
    cleanup_gui();
}


    /* 7. СОХРАНЕНИЕ */
    printf("\n[6] Сохранение данных...\n");
    save_students_to_json(students, "data/students_updated.json");

    /* 8. ОЧИСТКА */
    printf("\n[7] Очистка ресурсов...\n");
    free_student_list(students);
    cleanup_network();

    printf("\n========================================\n");
    printf("   ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА\n");
    printf("========================================\n");

    return 0;
}
