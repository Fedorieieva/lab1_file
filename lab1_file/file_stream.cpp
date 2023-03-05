#include "file_stream.h"
#include "print_msg.h"

void input_to_file(string filename) {
    ofstream file;
    file.open(filename, ofstream::app);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    string input;
    cout << "Enter text for the file (words should be separated by spaces only):" << endl;
    getline(cin, input);
    file << input + " ";
    file.close();
}

void write_to_file_change(string filename, string file_contents, int num) {
    ofstream file;
    if (num == 2) {
        file.open(filename);
    }
    else file.open(filename, ofstream::app);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    file << file_contents;
    file.close();
}

void read_file(string filename, string& contents, int num) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    print_msg(num);
    while (getline(file, contents)) {
        cout << contents;
    }
    file.close();
}

void find_substr(string& contents, string substr, int& idx, int num) {
    if (num != 2) {
        idx = 1;
    }
    size_t pos = 0;
    string change;
    while ((pos = contents.find(substr, pos)) != string::npos) {
        change = "[" + substr + "-" + to_string(idx) + "]";
        contents.replace(pos, substr.length(), change);
        idx++;
        pos += change.length();
    }
}

void swap_substr_num(string& contents, string substr) {
    size_t pos = 0;
    int num = 1;
    string num_str = to_string(num);
    while ((pos = contents.find(substr + "-" + num_str)) != string::npos) {
        num++;
        contents.replace(pos, substr.length() + 1 + num_str.length(), num_str + "-" + substr);
        num_str = to_string(num);
        //pos += substr.length() + 1 + num_str.length();
    }
}