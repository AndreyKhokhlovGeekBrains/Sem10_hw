// Задача 2. Удалить пробелы из текста
// В файле .txt необходимо удалить все лишние пробелы (в начале предложения
// и сдвоенные пробелы). Для решения задачи разработать функцию. Результат
// записать в .txt.
// Данные на входе: Строка из английских букв, знаков препинания и
// пробелов. Не более 1000 символов.
// Данные на выходе: Строка из английских букв, знаков препинания и
// пробелов.
// Пример
// Данные на входе: Hello world!
// Данные на выходе: Hello world!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void print_line_to_file(FILE* f, const char* line) {
    fprintf(f, "%s\n", line);
}

void trim(char* line) {
    int len = strlen(line);
    int counter = 0;
    char* buffer = (char*)malloc(MAX_LENGTH);
    if(buffer == NULL) {
        perror("Memory allocation failed");
        return;
    }

    for(int i = 0; i < len; i++) {
        if(counter == 0 && line[i] == ' ') {
            continue;
        }

        if(i == len - 1 && line[i] == ' ') {
            continue;
        }

        if(line[i] == ' ' && line[i + 1] == ' ') {
            continue;
        }
        buffer[counter++] = line[i];
    }

    buffer[counter] = '\0';
    strcpy(line, buffer);
    free(buffer);
}

int main(void) {
    FILE* f_read = fopen("input.txt", "r");
    if(f_read == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char* my_line = (char*)malloc(MAX_LENGTH);
    if(my_line == NULL) {
        perror("Memory allocation failed");
        fclose(f_read);
        return EXIT_FAILURE;
    }

    if(fgets(my_line, MAX_LENGTH, f_read) == NULL) {
        perror("Error reading file");
        free(my_line);
        fclose(f_read);
        return EXIT_FAILURE;
    }
    fclose(f_read);
    
    trim(my_line);

    FILE* f_write = fopen("output.txt", "w");
    if(f_write == NULL) {
        perror("Error opening file");
        free(my_line);
        return EXIT_FAILURE;
    }

    printf("%s", my_line);
    print_line_to_file(f_write, my_line);
    
    free(my_line);
    fclose(f_write);

    return 0;
}