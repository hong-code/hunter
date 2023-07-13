//
// Created by 黄鸿 on 2023/3/27.
//
#include "string"
#include "stack"
#include "queue"
#include "unordered_map"
#include "iostream"
#include "Util/util_class.h"
#ifndef REDOSHUNTER_REGEX_H
#define REDOSHUNTER_REGEX_H

#endif //REDOSHUNTER_REGEX_H

using namespace std;

/*
 * 正则表达的语法分析树
 *
 * */
class Tree_node{
public:
    enum node_flag{
        Init  =  1,    //语法树头节点的标号
        Que   =  2,    //？ token
        Alt   =  3,    //|  token
        Star  =  4,    //*  token
        Bracket = 5,   //()  token
        Couting = 6,   //{nun_1, nun2}   token
        Char_class = 7, //[asd]    token
        begin   = 8,    // ^
        end     = 9,    // $
        plus    = 10,   // +
    };
    string node_str;
    Tree_node* child{};
    Tree_node* parent{};
    Tree_node* Pre{};
    Tree_node* Next{};
    Tree_node* Header{};
    Tree_node* lchild{};

    First_Class first;

    First_Class last;

    Follow_Class followlast;

    set<char> char_set;

    int NQFlag = 0;
    unordered_map<char, char> char_block;
    unordered_map<char, int> char_map;
    int couting_min;
    int couting_max;
    int flags;
    Tree_node(){
        flags = 0;
    }
};

/*
 *
 * 正则表达式存储的类
 *
 * */
class Regex{

public:
    Tree_node regex_root;
    std::string regex_str;
    void parser(string, Tree_node&);
    Regex(){
        regex_root.flags = 1;
    }

};



void Regex::parser(string str, Tree_node& root) {
    queue<char> str_q;
    int Bracket_nun = 0;
    for (auto c:str) {
        str_q.push(c);
    }

    root.Header = &root;
    Tree_node *node = new Tree_node;
    root.child = node;
    node->parent = &root;
    node->Header = node;

    while (!str_q.empty()){
        //cout << str_q.front() <<endl;
        switch (str_q.front()) {
            /*
             * 星节点只拥有一个孩子
             * */
            case '*': {
                if (node->flags != 0) {
                    Tree_node *node_star = new Tree_node;
                    node_star->Header = node->Header;
                    node_star->Pre = node->Pre;
                    if (node->Pre != nullptr)
                        node->Pre->Next = node_star;
                    node_star->child = node;
                    node->Pre = nullptr;
                    node->Header = node;
                    node_star->flags = 4;
                    node = node_star;
                } else {
                    char t = node->node_str.back();
                    Tree_node *node_star = new Tree_node;
                    node_star->Header = node->Header;
                    node_star->child = new Tree_node;
                    node_star->child->Header = node_star->child;
                    node_star->child->node_str = t;
                    node_star->child->parent = node_star;
                    node_star->flags = 4;
                    node->node_str = node->node_str.substr(0, node->node_str.length() - 1);
                    node->Next = node_star;
                    node_star->Pre = node;
                    node = node_star;
                }
                break;
            }
            case '+': {
                if (node->flags != 0) {
                    Tree_node *node_star = new Tree_node;
                    node_star->Header = node->Header;
                    node_star->Pre = node->Pre;
                    if (node->Pre != nullptr)
                        node->Pre->Next = node_star;
                    node_star->child = node;
                    node->Pre = nullptr;
                    node->Header = node;
                    node_star->flags = 10;
                    node = node_star;
                } else {
                    char t = node->node_str.back();
                    Tree_node *node_star = new Tree_node;
                    node_star->Header = node->Header;
                    node_star->child = new Tree_node;
                    node_star->child->Header = node_star->child;
                    node_star->child->node_str = t;
                    node_star->child->parent = node_star;
                    node_star->flags = 10;
                    node->node_str = node->node_str.substr(0, node->node_str.length() - 1);
                    node->Next = node_star;
                    node_star->Pre = node;
                    node = node_star;
                }
                break;
            }
            case '(': {
                /*if (node->node_str == "" && node->flags == 0){
                    Tree_node* node_bracket = new Tree_node;
                    node_bracket->flags = 5;
                    node_bracket->Pre = node->Pre;
                    if (node->Header == node)
                        node_bracket->Header = node_bracket;
                    else{
                        node_bracket->Header = node->Header;
                        node->Pre->Next = node_bracket;
                    }
                    node_bracket->parent = node->parent;
                    //node = new Tree_node;
                    node_bracket->child = new Tree_node;
                    node = node_bracket->child;
                    node->parent = node_bracket;
                    node->Header = node;
                    node->Pre = nullptr;
                    Bracket_nun++;
                } else*/{
                    Tree_node* node_bracket = new Tree_node;
                    node_bracket->flags = 5;
                    node_bracket->Pre = node;
                    node_bracket->Header = node->Header;
                    node->Next = node_bracket;
                    /*if (node->node_str == "" && node->flags == 0){
                        if (node->Header == node){
                            node_bracket->Pre == nullptr;
                            node_bracket->Header = node_bracket;
                            node->parent->child = node_bracket;
                            node_bracket->parent == node->parent;
                        } else{
                            node->Pre->Next = node_bracket;
                            node_bracket->Pre = node->Pre;
                        }
                    }*/
                    node_bracket->child = new Tree_node;
                    node = node_bracket->child;
                    node->parent = node_bracket;
                    node->Header = node;
                    Bracket_nun++;
                };
                break;
            }
            case ')': {
                while (node->flags != 5)
                    node = node->Header->parent;
                //node = node->Header->parent;
                Bracket_nun--;
                /*
                node->Header->parent->Next = new Tree_node;
                node->Header->parent->Next->Pre = node->Header->parent;
                node = node->Header->parent->Next;
                node->Header = node->Pre->Header;
                Bracket_nun--;
                 */
                break;
            }
            case '|': {
                Tree_node *alt_node = new Tree_node;
                node->Header->parent->child = alt_node;
                alt_node->parent = node->Header->parent;
                node->Header->parent = alt_node;
                alt_node->lchild = node->Header;
                alt_node->Header = alt_node;
                alt_node->flags = 3;
                alt_node->child = new Tree_node;
                node = alt_node->child;
                node->parent = alt_node;
                node->Header = node;
                break;
            }
            case '?': {
                if (node->flags != 0) {
                    Tree_node *node_que = new Tree_node;
                    node_que->Header = node->Header;
                    node_que->Pre = node->Pre;
                    if (node->Pre != nullptr)
                        node->Pre->Next = node_que;
                    node_que->child = node;
                    node->Pre = nullptr;
                    node->Header = node;
                    node_que->flags = 2;
                    node = node_que;
                } else {
                    char t = node->node_str.back();
                    Tree_node *node_que = new Tree_node;
                    node_que->Header = node->Header;
                    node_que->child = new Tree_node;
                    node_que->child->Header = node_que->child;
                    node_que->child->node_str = t;
                    node_que->child->parent = node_que;
                    node_que->flags = 2;
                    node->node_str = node->node_str.substr(0, node->node_str.length() - 1);
                    node->Next = node_que;
                    node_que->Pre = node;
                    node = node_que;
                }
                break;
            }
            case '{':{
                string str_left;
                string str_right;
                str_q.pop();
                if (str_q.front() == ','){
                    str_q.pop();
                    while (1){
                        if (str_q.front() == '}')
                            break;
                        else if (str_q.front() <= '9' && str_q.front() >= '0'){
                            str_right.push_back(str_q.front());
                            str_q.pop();
                        }
                        else {
                            cout << "regex false" << endl;
                            return;
                        }
                    }
                }
                else{
                    while (1){
                        if (str_q.front() == '}'){
                            str_right = str_left;
                            break;
                        } else if (str_q.front() <= '9' && str_q.front() >= '0'){
                            str_left.push_back(str_q.front());
                            str_q.pop();
                        }
                        else if (str_q.front() == ','){
                            break;
                        }
                    }
                    if (str_q.front() == ','){
                        str_q.pop();
                        while (1){
                            if (str_q.front() == '}')
                                break;
                            else if (str_q.front() <= '9' && str_q.front() >= '0'){
                                str_right.push_back(str_q.front());
                                str_q.pop();
                            }
                            else {
                                cout << "regex false" << endl;
                                return;
                            }
                        }
                    }
                }
                cout << str_left << endl;
                cout << str_right << endl;
                if (node->flags != 0) {
                    Tree_node *node_couting = new Tree_node;
                    node_couting->Header = node->Header;
                    node_couting->Pre = node->Pre;
                    if (node->Pre != nullptr)
                        node->Pre->Next = node_couting;
                    node_couting->child = node;
                    node->Pre = nullptr;
                    node->Header = node;
                    node_couting->flags = 6;
                    if (str_left == "")
                        node_couting->couting_min = 0;
                    else
                        node_couting->couting_min = std::stoi(str_left);
                    if (str_right == "")
                        node_couting->couting_max = 0;
                    else
                        node_couting->couting_max = std::stoi(str_right);
                    if (node_couting->couting_max < node_couting->couting_min){
                        cout << "regex couting error" << endl;
                        return;
                    }
                    node = node_couting;
                } else {
                    char t = node->node_str.back();
                    Tree_node *node_couting = new Tree_node;
                    node_couting->Header = node->Header;
                    node_couting->child = new Tree_node;
                    node_couting->child->Header = node_couting->child;
                    node_couting->child->node_str = t;
                    node_couting->child->parent = node_couting;
                    node_couting->flags = 6;
                    if (str_left == "")
                        node_couting->couting_min = 0;
                    else
                        node_couting->couting_min = std::stoi(str_left);
                    if (str_right == "")
                        node_couting->couting_max = 0;
                    else
                        node_couting->couting_max = std::stoi(str_right);
                    if (node_couting->couting_max < node_couting->couting_min){
                        cout << "regex couting error" << endl;
                        return;
                    }
                    node->node_str = node->node_str.substr(0, node->node_str.length() - 1);
                    node->Next = node_couting;
                    node_couting->Pre = node;
                    node = node_couting;
                }
                break;
            }
            case '[':{
                str_q.pop();
                unordered_map<char, char> char_block;
                unordered_map<char, int> char_map;
                //std::pair<std::unordered_map<char, int>::iterator, bool> ret;
                while (str_q.front() != ']'){
                    char word;
                    word = str_q.front();
                    if (word == '-' | word == ']'){
                        cout << "char class error" << endl;
                        return;
                    }
                    else
                        char_map.insert(std::make_pair(word, 1));
                    str_q.pop();
                    if (str_q.front() == '-'){
                        str_q.pop();
                        if (str_q.front() == '-' | str_q.front() == ']'){
                            cout << "char class error" << endl;
                            return;
                        }
                        char_block.insert(std::make_pair(word, str_q.front()));
                        for (int i = word + 1; i <= str_q.front(); ++i)
                            char_map.insert(std::make_pair(i, 1));
                        str_q.pop();
                    }
                    else
                        char_block.insert(std::make_pair(word, word));
                }
                auto node_char_class = new Tree_node;
                node_char_class->Header = node->Header;
                node->Next = node_char_class;
                node_char_class->Pre = node;
                node_char_class->flags = 7;
                node_char_class->char_map = char_map;
                node_char_class->char_block = char_block;
                node = node_char_class;
                break;
            }
            default:
                if (node->flags == 0) {
                    node->node_str.push_back(str_q.front());
                    //cout << node->node_str << endl;
                }
                else{
                    node->Next = new Tree_node;
                    node->Next->Pre = node;
                    node->Next->Header = node->Header;
                    node = node->Next;
                    node->node_str.push_back(str_q.front());
                }
                break;
        }
        str_q.pop();
    }
    if (Bracket_nun != 0)
        cout << "regex false" << endl;
    //cout << "sda" <<endl;
}