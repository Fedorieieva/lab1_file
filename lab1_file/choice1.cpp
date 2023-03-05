#include "choice1.h"
#include "file_pointer.h"
#include "print_msg.h"

void choice1() {
    char filename[25];
    char filename3[45] = "file2_";
    char substr_ptr[10];
    int count = 0, ch;

    cout << "Please enter name of the file you want to create/open:" << endl;
    cin.ignore();
    enter_filename_or_substr(filename);
    strcat_s(filename3, 45, filename);
    char* contents = arr_input_ptr();
    cout << "Please enter the substring you want to find in your file:" << endl;
    enter_filename_or_substr(substr_ptr);
    write_file_ptr(filename, contents, 1);

    char* file_contents = read_file_ptr(filename);
    print_contents_file_ptr(file_contents, 1);

    char* file_contents2 = find_substr_ptr(file_contents, substr_ptr, count, 1);
    print_contents_file_ptr(file_contents2, 2);

    char* file_contents3 = find_substr_ptr(file_contents2, substr_ptr, count, 2);
    print_contents_file_ptr(file_contents3, 3);
    write_file_ptr(filename3, file_contents3, 2);

    if (remove(filename) != 0) {
        cout << "Error deleting file" << endl;
    }
    if (rename(filename3, filename) != 0) {
        cout << "Error renaming file" << endl;
    }

    cout << endl << "If you want to append your file, enter 1, if not please enter 2" << endl;
    cin >> ch;
    if (ch == 1) {
        cin.ignore();
        char* contents2 = arr_input_ptr();
        print_contents_file_ptr(file_contents, 1);
        print_contents_file_ptr(contents2, 0);

        char* contents3 = find_substr_ptr(contents2, substr_ptr, count, 3);
        print_contents_file_ptr(file_contents2, 2);
        print_contents_file_ptr(contents3, 0);

        char* contents4 = find_substr_ptr(contents3, substr_ptr, count, 4);
        print_contents_file_ptr(file_contents3, 3);
        print_contents_file_ptr(contents4, 0);
        write_file_ptr(filename, contents4, 1);

        delete[] contents2;
        delete[] contents3;
        delete[] contents4;
    }
    delete[] contents;
    delete[] file_contents;
    delete[] file_contents2;
    delete[] file_contents3;
}