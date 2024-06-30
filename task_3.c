// Задача 3. Изменить расширение
// В файле .txt записан полный адрес файла (возможно, без расширения).
// Необходимо изменить его расширение на ".html" и записать результат в файл
// .txt.
// Данные на входе: Строка состоящая из символов: a-z, A-Z, 0-9, /
// Данные на выходе: Исходная строка с измененным расширением.
// Пример №1
// Данные на входе: /DOC.TXT/qqq
// Данные на выходе: /DOC.TXT/qqq.html
// Пример №2
// Данные на входе: /DOC.TXT/qqq.com
// Данные на выходе: /DOC.TXT/qqq.html

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void print_line_to_file(FILE* f, const char* line) {
    fprintf(f, "%s\n", line);
}

void change_extension(char* line) {
    int len = strlen(line);
    int counter_dot = 0;
    int counter_slash = 0;

    int i = len - 1;
    while (line[i] != '.' && i > 0)
    {
        counter_dot++;
        i--;
    }

    int j = len - 1;
    while (line[j] != '/' && j > 0)
    {
        counter_slash++;
        j--;
    }

    if(counter_slash <= counter_dot) {
        strcat(line, ".html");
    } else {
        line[len - counter_dot] = '\0';
        strcat(line, "html");
    }
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
    
    change_extension(my_line);

    FILE* f_write = fopen("output.txt", "w");
    if(f_write == NULL) {
        perror("Error opening file");
        free(my_line);
        return EXIT_FAILURE;
    }

    printf("%s\n", my_line);
    print_line_to_file(f_write, my_line);
    
    free(my_line);
    fclose(f_write);

    return 0;
}