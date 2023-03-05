#include "choice2.h"
#include "file_stream.h"
#include "print_msg.h"

void choice2() {
    int ch, idx = 1;
    string path, path2, path3, substr, text, append;
    cout << "Please enter name of the file you want to create/open:" << endl;
    cin.ignore();
    getline(cin, path);

    path2 = "file1_" + path;
    path3 = "file2_" + path;

    input_to_file(path);
    cout << "Please enter the substring you want to find in your file:" << endl;
    getline(cin, substr);
    read_file(path, text, 1);
    //if substr == "" cout << substring is empty, continue

    find_substr(text, substr, idx, 1);
    write_to_file_change(path2, text, 1);
    read_file(path2, text, 2);

    swap_substr_num(text, substr);
    write_to_file_change(path3, text, 1);
    read_file(path3, text, 3);

    cout << endl << endl << "If you want to append your file, enter 1, if not please enter 2" << endl;
    cin >> ch;

    if (ch == 1) {
        cin.ignore();
        cout << "Enter text for the file (words should be separated by spaces only):" << endl;
        getline(cin, append);

        read_file(path, text, 1);
        cout << append;

        find_substr(append, substr, idx, 2);
        write_to_file_change(path2, append, 1);
        read_file(path2, append, 2);

        swap_substr_num(append, substr);
        write_to_file_change(path3, append, 2);
        read_file(path3, append, 3);
    }
    if (remove(path.c_str()) != 0 || remove(path2.c_str()) != 0) {
        cout << endl << "Error deleting file" << endl;
    }
    if (rename(path3.c_str(), path.c_str()) != 0) {
        cout << endl << "Error renaming file" << endl;
    }
}