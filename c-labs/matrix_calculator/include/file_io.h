#ifndef FILE_IO_H
#define FILE_IO_H

#include "student.h"

int save_students_to_json(const StudentList* list, const char* filename);
StudentList* load_students_from_json(const char* filename);

#endif
