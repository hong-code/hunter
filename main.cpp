#include <iostream>
#include "string.h"
//#include "regex_tree/regex.h"
#include "print_regex_tree/print_tree.h"
#include "NQPattern/NQPattern.h"
#include "Util/Preprocessing_Re.h"

using namespace std;
//主调试程序
int main() {

    std::cout << "input regex" << std::endl;
    Regex regex_test;

    std::string string1;
    //cin >> string1;
    regex_test.regex_str = string1;
    regex_test.parser("(y|a)c?f+g", regex_test.regex_root);
    cout << TreeToString(regex_test.regex_root) << endl;
    class NQPattern NQ_test;
    class Preprocessing_Re_class Pre;
    Pre.Generate_All_First(&regex_test.regex_root);
    regex_test.regex_root.char_set = Pre.Generate_All_set(regex_test.regex_root.child);
    Pre.Generate_ALL_Follow(&regex_test.regex_root);
    auto TT = Pre.Generate_followlast(regex_test.regex_root.child);
    NQ_test.Is_inside_NQ(&regex_test.regex_root);

    cout << string1 << endl;
    return 0;
}
