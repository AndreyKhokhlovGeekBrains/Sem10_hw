// Задача 1. Пары соседних символов
// В файле .txt записаны символы. Необходимо разработать функцию, которая
// меняет местами пары соседних символов не обращая внимание на символы
// пробел. Если количество символов нечетно (пробелы не считаем), то
// последний символ не меняем. Результат записать в файл .txt.
// Данные на входе: Строка из английских букв, пробелов и знаков
// препинания. Не более 1000 символов.
// Данные на выходе: Строка из английских букв, пробелов и знаков
// препинания.
// Пример №1
// Данные на входе: Hello world!
// Данные на выходе: eHllw orodl!
// Пример №2
// Данные на входе: abc def
// Данные на выходе: bad cfe

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void print_line_to_file(FILE* f, const char* line) {
    fprintf(f, "%s\n", line);
}

void change_adjacent_letters(char* line) {
    size_t len = strlen(line);
    for(int i = 0; i < len - 1; i++) {
        if(line[i] == ' ') {
            continue;;
        }

        int j = i + 1;
        while (line[j] == ' ' && j < len)
        {
            j++;
        }

        if(j < len)  {
            char temp = line[i];
            line[i] = line[j];
            line[j] = temp;
            i = j;
        } 
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
    
    change_adjacent_letters(my_line);

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