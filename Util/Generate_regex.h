//
// Created by 黄鸿 on 2023/6/7.
//

#ifndef REDOSHUNTER_GENRATE_REGEX_H
#define REDOSHUNTER_GENRATE_REGEX_H

#endif //REDOSHUNTER_GENRATE_REGEX_H

#include "string"
using namespace std;


class Generate_regex_class{
public:
    string Generate_regex(Tree_node *root);
};

string Generate_regex_class::Generate_regex(Tree_node *root) {
    string regex_string;
    Tree_node *node = root;
    int begin = 0;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                regex_string.insert(begin, node->node_str);
                break;
            }

            case 1:{
                regex_string.insert(begin, Generate_regex(node->child));
                break;
            }

            case 2:{
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin += string1.length();
                regex_string.insert(begin, "?");
                begin += 1;
                break;
            }

            case 3:{
                string str_left = Generate_regex(node->lchild);
                regex_string.insert(begin, str_left);
                begin = begin + str_left.length();
                regex_string.insert(begin, "|");
                string str_right = Generate_regex(node->child);
                regex_string.insert(begin, str_right);
                begin += str_right.length();
                break;
            }

            case 4:{
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin += string1.length();
                regex_string.insert(begin, "*");
                begin += 1;
                break;
            }

            case 5: {
                regex_string.insert(begin, "()");
                begin += 1;
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin = begin + 1 + string1.length();
                break;
            }

            case 6:{
                /*
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin += string1.length();
                string str1 = to_string(node->couting_min);
                string str2 = to_string(node->couting_max);
                string str3 = "{" + str1 + "," + str2 + "}";
                regex_string.insert(begin, str3);
                begin += str3.length();
                break;
                */
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin += string1.length();
                regex_string.insert(begin, "*");
                begin += 1;
                break;
            }

            case 10:{
                string string1 = Generate_regex(node->child);
                regex_string.insert(begin, string1);
                begin += string1.length();
                regex_string.insert(begin, "*");
                begin += 1;
                break;
            }

            default:
                break;

        }
        node = node->Next;
    }
    return regex_string;
}