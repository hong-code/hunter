//
// Created by 黄鸿 on 2023/4/22.
//
#include "regex_tree/regex.h"


string TreeToString(Tree_node&);
string StarToString(Tree_node&);
string BracketToString(Tree_node&);
string AltSubToString(Tree_node&);
string AltToString(Tree_node&);
string QueToString(Tree_node&);
string CoutTostring(Tree_node&);
string CharClassToString(Tree_node&);
string PlusToString(Tree_node&);

string PlusToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("plus_string{}");
    int begin = 12;
    Tree_node* begin_node = root.child;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}

string CharClassToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("CharClass{}");
    int begin = 10;
    Tree_node* begin_node = &root;
    if (begin_node->char_map.count('a'))
        cout << "find" << endl;
    for (unordered_map<char, char>::iterator it = begin_node->char_block.begin(); it != begin_node->char_block.end() ; ++it) {
        if (it != begin_node->char_block.begin())
            string1.push_back(' ');
        if (it->first == it->second){
            string1.push_back(it->first);
        } else{
            string1.push_back(it->first);
            string1.push_back('-');
            string1.push_back(it->second);
        }
    }
    output_string.insert(begin, string1);
    return output_string;
}

/*
 * 将a{2,5}进行可视化
 * couting_string{word{b}}{2,5}}
 * */

string CoutTostring(Tree_node& root) {
    string output_string, string1;
    output_string.append("couting_string{}");
    int begin = 15;
    Tree_node* begin_node = root.child;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}

/*
 * ?表达式使用字符串输出可视化
 * que{}
 * 形式*/
string QueToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("que{}");
    int begin = 4;
    Tree_node* begin_node = root.child;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}


/*
 * 选择表达使用字符串输出进行可视化
 * alt{sub{}sub{}}
 * 形式*/
string AltToString(Tree_node& root) {
    string output_string, stringL, stringR;
    output_string.append("Alt{}");
    int begin = 4;
    stringL = AltSubToString(*root.lchild); //左孩子
    stringR = AltSubToString(*root.child);  //右孩子
    output_string.insert(begin, stringL);
    begin += stringL.length();
    output_string.insert(begin, stringR);
    return output_string;
}


/*
 * 选择表达式中子节点的字符可视化
 * sub{}
 * */
string AltSubToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("Sub{}");
    int begin = 4;
    Tree_node* begin_node = &root;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }
            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}

/*
 * 括号表达式的字符可视化
 * bracket{}
 * */
string BracketToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("bracket{}");
    int begin = 8;
    Tree_node* begin_node = root.child;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}

/*\
 *  * 星型表达式的字符可视化
 * star{}*/
string StarToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("star{}");
    int begin = 5;
    Tree_node* begin_node = root.child;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }

        begin_node = begin_node->Next;
    }
    return output_string;
}

/*
 * 将整个语法树进行字符输出的可视化
 * 例如
 * (sd)|a**|s
 * begin{Alt{Sub{bracket{word{sd}}}Sub{Alt{Sub{star{star{word{a}}}}Sub{word{s}}}}}}
 * */
string TreeToString(Tree_node& root) {
    string output_string, string1;
    output_string.append("begin{}");
    Tree_node* begin_node = root.child;

    int begin = 6;
    while (begin_node != nullptr){
        switch (begin_node->flags) {
            /*
             * 单纯的字符节点*/
            case 0:{
                if (begin_node->node_str != ""){
                    string1 = "word{" + begin_node->node_str + "}";
                    output_string.insert(begin, string1);
                    begin += string1.length();
                }
                break;
            }

            case 4:{
                string1 = StarToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 5:{
                string1 = BracketToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 3:{
                string1 = AltToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 2:{
                string1 = QueToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 6:{
                string1 = CoutTostring(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                string1 = '{' + to_string(begin_node->couting_min) + ',' + to_string(begin_node->couting_max) + '}';
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }

            case 7:{
                string1 = CharClassToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            case 10:{
                string1 = PlusToString(*begin_node);
                output_string.insert(begin, string1);
                begin += string1.length();
                break;
            }
            default:
                break;
        }
        begin_node = begin_node->Next;
    }
    return output_string;
}