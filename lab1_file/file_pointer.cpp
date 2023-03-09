#include "file_pointer.h"
#include "print_msg.h"

void enter_filename_or_substr(char* str) {
    int size = 0;
    char c;
    while (cin.get(c)) {
        if (c == '\n') break;
        str[size] = c;
        size++;
    }
    str[size] = '\0';
}

char* arr_input_ptr() {
    int capacity = 256, size = 0;
    char* arr = (char*)calloc(capacity, sizeof(char));
    char c;
    cout << "Enter text for the file (words should be separated by spaces only):" << endl;
    while (cin.get(c)) {
        if (c == '\n') break;
        if (size == capacity) {
            capacity *= 2;
            char* temp = (char*)calloc(capacity, sizeof(char));
            for (int i = 0; i < size; i++) {
                temp[i] = arr[i];
            }
            free(arr);
            arr = temp;
        }
        arr[size] = c;
        size++;
    }
    arr[size] = '\0';
    return arr;
}

void write_file_ptr(char* filename, char* contents, int num) {
    FILE* file;
    if (num == 1) {
        fopen_s(&file, filename, "a+");
    }
    else {
        fopen_s(&file, filename, "w");
    }
    if (file == nullptr) {
        printf("cannot open this file\n");
        return;
    }
    fputs(contents, file);
    fputs(" ", file);
    if (fclose(file) == EOF) {
        printf("error closing file");
        return;
    }
}

char* read_file_ptr(char* filename) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == nullptr) {
        printf("cannot open this file\n");
        return nullptr;
    }
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* arr = (char*)calloc(file_size, sizeof(char));
    fread(arr, sizeof(char), file_size, file);
    arr[file_size] = '\0';
    if (ferror(file)) {
        printf("error reading from file\n");
        return nullptr;
    }
    if (fclose(file) == EOF) {
        printf("error closing file");
        return nullptr;
    }
    return arr;
}

void print_contents_file_ptr(char* contents, int num) {
    print_msg(num);
    for (int i = 0; i < strlen(contents); i++) {
        cout << contents[i];
    }
}

int count_substr_ptr(char* contents, char* substr) {
    int j, count, count2 = 0;
    for (int i = 0; i < strlen(contents);) {
        j = 0;
        count = 0;
        while (contents[i] == substr[j]) {
            count++;
            i++;
            j++;
        }
        if (count == strlen(substr)) {
            count2++;
            count = 0;
        }
        else i++;
    }
    return count2;
}

int count_digits(int num) {
    int digits = 0;
    while (num != 0) {
        num /= 10;
        digits++;
    }
    return digits;
}

int count_len_occ(char* contents, char* substr) {
    int len = 0;
    int num = count_substr_ptr(contents, substr);
    for (int i = 1; i <= num; i++) {
        len += count_digits(i);
    }
    return len;
}

void change_substr(char* substr, char* new_substr, int num) {
    char* str_num = (char*)calloc(count_digits(num) + 1, sizeof(char));
    new_substr[0] = '[';
    int i = 1;
    while (i <= strlen(substr) + 1) {
        if (i == strlen(substr) + 1) {
            new_substr[i] = '-';
        }
        else {
            new_substr[i] = substr[i - 1];
        }
        i++;
    }
    sprintf_s(str_num, count_digits(num) + 1, "%d", num);
    for (int j = 0; j < count_digits(num); j++) {
        new_substr[i] = str_num[j];
        i++;
    }
    new_substr[i] = ']';
    new_substr[i + 1] = '\0';
    free(str_num);
}

void swap_n_str(char* substr, char* new_substr, int num) {
    int k = 0, num_size = count_digits(num);
    char* str_num = (char*)calloc(num_size + 1, sizeof(char));
    sprintf_s(str_num, count_digits(num) + 1, "%d", num);
    for (int i = 0; i < num_size; i++) {
        new_substr[i] = str_num[i];
    }
    new_substr[num_size] = '-';
    for (int i = num_size + 1; i <= strlen(substr) + num_size; i++) {
        if (i == strlen(substr) + num_size) {
            new_substr[i + 1] = '\0';
        }
        new_substr[i] = substr[k];
        k++;
    }
    free(str_num);
}

char* find_substr_ptr(char* contents, char* substr, int& count, int num) {
    if (num != 3 && num != 4) {
        count = 1;
    }
    else if (num == 4) {
        count--;
    }
    size_t new_len_sub = ((strlen(substr) + 3) * count_substr_ptr(contents, substr)) + count_len_occ(contents, substr);
    size_t change_con_len = strlen(contents) + new_len_sub;
    size_t i = 0, j = 0;
    char* arr = (char*)calloc(change_con_len + 2, sizeof(char));
    char* new_substr = (char*)calloc((strlen(substr) + count_len_occ(contents, substr) + 4), sizeof(char));
    while (i < strlen(contents)) {
        if (strstr(&contents[i], substr) == &contents[i]) {
            if (num == 1 || num == 3) {
                change_substr(substr, new_substr, count);
                i += strlen(substr);
            }
            else if (num == 2 || num == 4) {
                swap_n_str(substr, new_substr, count);
                i += strlen(substr) + count_digits(count) + 1;
            }
            strcpy_s(&arr[j], change_con_len + 1, new_substr);
            j += strlen(new_substr);
            count++;
        }
        else {
            arr[j] = contents[i];
            i++;
            j++;
        }
    }
    free(new_substr);
    arr[j] = '\0';
    return arr;
}