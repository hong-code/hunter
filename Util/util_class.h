//
// Created by 黄鸿 on 2023/6/8.
//

#ifndef REDOSHUNTER_UTIL_CLASS_H
#define REDOSHUNTER_UTIL_CLASS_H
#include "set"
#endif //REDOSHUNTER_UTIL_CLASS_H

using namespace std;

class First_Class{
public:
    set<char> first_list;
    bool certain = false;
    bool end_Flags = false;
};

class Follow_Class{
public:
    set<char> follow_list;
    bool certain = false;
    bool end_Flags = false;
};