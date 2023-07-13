//
// Created by 黄鸿 on 2023/6/7.
//

#ifndef REDOSHUNTER_NQCLASS_H
#define REDOSHUNTER_NQCLASS_H

#endif //REDOSHUNTER_NQCLASS_H

//#include "regex.h"
#include "string"

class NQClass{
public:
    bool is_NQ;
    Tree_node *Begin_node;
    Tree_node *mid_node;
    Tree_node *end_node;
    string mid_str;
};