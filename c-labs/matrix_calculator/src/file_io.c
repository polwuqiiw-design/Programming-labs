#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_io.h"
#include "../include/student.h"
#include "../lib/cJSON.h"

int save_students_to_json(const StudentList* list, const char* filename) {
    if (!list || !filename) {
        fprintf(stderr, "Ошибка: неверные параметры для сохранения\n");
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла %s для записи\n", filename);
        return -1;
    }

    cJSON* root = cJSON_CreateArray();
    if (!root) {
        fclose(file);
        fprintf(stderr, "Ошибка создания JSON массива\n");
        return -1;
    }

    for (int i = 0; i < list->count; i++) {
        cJSON* student_obj = cJSON_CreateObject();
        if (!student_obj) continue;

        cJSON_AddStringToObject(student_obj, "id", list->students[i].id);
        cJSON_AddStringToObject(student_obj, "name", list->students[i].name);
        cJSON_AddNumberToObject(student_obj, "age", list->students[i].age);
        cJSON_AddNumberToObject(student_obj, "gpa", list->students[i].gpa);

        cJSON_AddItemToArray(root, student_obj);
    }

    char* json_str = cJSON_Print(root);
    if (json_str) {
        fprintf(file, "%s\n", json_str);
        free(json_str);
        printf("Данные сохранены в файл: %s\n", filename);
    } else {
        fprintf(stderr, "Ошибка преобразования JSON\n");
    }

    cJSON_Delete(root);
    fclose(file);
    return 0;
}

StudentList* load_students_from_json(const char* filename) {
    if (!filename) {
        fprintf(stderr, "Ошибка: имя файла не указано\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Файл %s не найден, будет создан новый список\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        fclose(file);
        return NULL;
    }

    char* content = (char*)malloc(file_size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(content);
    free(content);

    if (!root || !cJSON_IsArray(root)) {
        cJSON_Delete(root);
        return NULL;
    }

    int count = cJSON_GetArraySize(root);
    StudentList* list = create_student_list(count > 0 ? count : 10);
    if (!list) {
        cJSON_Delete(root);
        return NULL;
    }

    cJSON* item = NULL;
    cJSON_ArrayForEach(item, root) {
        cJSON* id = cJSON_GetObjectItem(item, "id");
        cJSON* name = cJSON_GetObjectItem(item, "name");
        cJSON* age = cJSON_GetObjectItem(item, "age");
        cJSON* gpa = cJSON_GetObjectItem(item, "gpa");

        if (cJSON_IsString(id) && cJSON_IsString(name) &&
            cJSON_IsNumber(age) && cJSON_IsNumber(gpa)) {
            add_student(list,
                        id->valuestring,
                        name->valuestring,
                        age->valueint,
                        (float)gpa->valuedouble);
        }
    }

    cJSON_Delete(root);
    printf("Загружено %d студентов из файла %s\n", list->count, filename);
    return list;
}
