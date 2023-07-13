//
// Created by 黄鸿 on 2023/6/8.
//

#ifndef REDOSHUNTER_PREPROCESSING_RE_H
#define REDOSHUNTER_PREPROCESSING_RE_H

#endif //REDOSHUNTER_PREPROCESSING_RE_H

#include "vector"
//#include "regex_tree/regex.h"
#include "set"
//#include "Util/util_class.h"
using namespace std;


class Preprocessing_Re_class{
public:
    First_Class Generate_first(Tree_node *root);
    vector<char> Generate_last(Tree_node *root);
    Follow_Class Generate_followlast(Tree_node *root);
    set<char> Generate_All_set(Tree_node *root);
    void Generate_All_First(Tree_node *root);
    void Generate_ALL_Follow(Tree_node *root);
    //vector<>
};

void Preprocessing_Re_class::Generate_ALL_Follow(Tree_node *root) {
    Tree_node *node = root;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                if (node->followlast.end_Flags = true)
                    break;
                else{
                    for (int i = 1; i < node->node_str.length(); i++){
                        node->followlast.follow_list.insert(node->node_str[i]);
                    }
                    node->followlast.end_Flags = true;
                    break;
                }
            }

            case 1:{
                if (node->followlast.end_Flags != true){
                    node->followlast = Generate_followlast(node->child);
                }
                Generate_ALL_Follow(node->child);
                break;
            }

            case 2:{
                if (node->followlast.end_Flags != true){
                    node->followlast = Generate_followlast(node->child);
                }
                Generate_ALL_Follow(node->child);
                break;
            }

            case 3:{
                if (node->followlast.end_Flags != true){
                    auto Follow_L = Generate_followlast(node->lchild);
                    auto Follow_R = Generate_followlast(node->child);
                    node->followlast.follow_list.insert(Follow_L.follow_list.begin(), Follow_L.follow_list.end());
                    node->followlast.follow_list.insert(Follow_R.follow_list.begin(), Follow_R.follow_list.end());
                }
                Generate_ALL_Follow(node->lchild);
                Generate_ALL_Follow(node->child);
                break;
            }

            case 4:{
                if (node->followlast.end_Flags != true){
                    node->followlast.follow_list = node->char_set;
                    node->followlast.end_Flags = true;
                }
                Generate_ALL_Follow(node->child);
                break;
            }

            case 5:{
                if (node->followlast.end_Flags != true){
                    node->followlast = Generate_followlast(node->child);
                }
                Generate_ALL_Follow(node->child);
                break;
            }

            case 6:{
                if (node->followlast.end_Flags != true){
                    if (node->couting_max > 1){
                        node->followlast.follow_list = node->char_set;
                        node->followlast.end_Flags = true;
                    } else
                        node->followlast = Generate_followlast(node->child);
                }
                Generate_ALL_Follow(node->child);
            }

            case 7:{
                if (node->followlast.end_Flags != true){
                    node->followlast.end_Flags = true;
                    break;
                }
                node->followlast.end_Flags = true;
                break;
            }

            case 10:{
                if (node->followlast.end_Flags != true){
                    node->followlast.follow_list = node->char_set;
                    node->followlast.end_Flags = true;
                }
                Generate_ALL_Follow(node->child);
                break;
            }

            default:{
                break;
            }
        }
        node = node->Next;
    }
}

Follow_Class Preprocessing_Re_class::Generate_followlast(Tree_node *root) {
    Tree_node *node = root;
    Follow_Class RET;
    bool is_first_end = false;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    for (int i = 1; i < node->node_str.length(); i++){
                        node->followlast.follow_list.insert(node->node_str[i]);
                    }
                    node->followlast.end_Flags = true;
                    if (node->node_str.length() != 0){
                        node->followlast.certain = true;
                        RET.certain = true;
                    }
                    RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                    //RET.certain = true;
                }
                //node->followlast.end_Flags = false;
                break;
            }

            case 1:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        auto Follow_C = Generate_followlast(node->child);
                        RET.follow_list.insert(Follow_C.follow_list.begin(), Follow_C.follow_list.end());
                        if (node->followlast.follow_list.empty() != 0){
                            node->followlast.certain = true;
                            RET.certain = true;
                        }
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            case 2:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        auto Follow_C = Generate_followlast(node->child);
                        RET.follow_list.insert(Follow_C.follow_list.begin(), Follow_C.follow_list.end());
                        if (node->followlast.follow_list.empty() != 0){
                            node->followlast.certain = true;
                            RET.certain = true;
                        }
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            case 3:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        auto Follow_l = Generate_followlast(node->lchild);
                        auto Follow_r = Generate_followlast(node->child);
                        node->followlast.follow_list.insert(Follow_l.follow_list.begin(), Follow_l.follow_list.end());
                        node->followlast.follow_list.insert(Follow_r.follow_list.begin(), Follow_r.follow_list.end());
                        node->followlast.end_Flags = true;
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }
            case 4:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        node->followlast.follow_list = node->char_set;
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            case 5:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        auto Follow_C = Generate_followlast(node->child);
                        RET.follow_list.insert(Follow_C.follow_list.begin(), Follow_C.follow_list.end());
                        if (node->followlast.follow_list.empty() != 0){
                            node->followlast.certain = true;
                            RET.certain = true;
                        }
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            case 6:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        node->followlast.follow_list = node->char_set;
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            case 7:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    node->followlast.end_Flags = true;
                    is_first_end = true;
                }
                break;
            }

            case 10:{
                if (is_first_end == true)
                    RET.follow_list.insert(node->char_set.begin(), node->char_set.end());
                else{
                    if (node->followlast.end_Flags == true)
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                    else{
                        node->followlast.follow_list = node->char_set;
                        RET.follow_list.insert(node->followlast.follow_list.begin(), node->followlast.follow_list.end());
                        node->followlast.end_Flags = true;
                    }
                    if (!node->first.first_list.empty())
                        is_first_end = true;
                }
                break;
            }

            default:
                break;
        }
        node = node->Next;
    }
    RET.end_Flags = true;
    return RET;
}

set<char> Preprocessing_Re_class::Generate_All_set(Tree_node *root) {
    Tree_node *node = root;
    set<char> RET;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                for (auto c : node->node_str)
                    node->char_set.insert(c);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 1:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 2:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 3:{
                set<char> SL = Generate_All_set(node->lchild);
                set<char> SR = Generate_All_set(node->child);
                node->char_set.insert(SL.begin(), SL.end());
                node->char_set.insert(SR.begin(), SR.end());
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 4:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 5:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 6:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 7:{
                for (auto m : node->char_map)
                    node->char_set.insert(m.first);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            case 10:{
                node->char_set = Generate_All_set(node->child);
                RET.insert(node->char_set.begin(), node->char_set.end());
                break;
            }

            default:{
                break;
            }
        }
        node = node->Next;
    }

    return RET;
}

void Preprocessing_Re_class::Generate_All_First(Tree_node *root) {
    Tree_node *node = root;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                if (node->first.end_Flags == true){
                    break;
                }
                for (auto c : node->node_str){
                    node->first.first_list.insert(c);
                    break;
                }
                node->first.certain = true;
                node->first.end_Flags = true;
                break;
            }

            case 1: {
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                Generate_All_First(node->child);
                break;
            }

            case 2:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                node->first.certain = false;
                Generate_All_First(node->child);
                break;
            }

            case 3:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->lchild);
                    Generate_All_First(node->child);
                    break;
                } else{
                    First_Class FL = Generate_first(node->lchild);
                    First_Class FR = Generate_first(node->child);
                    node->first.first_list.insert(FL.first_list.begin(), FL.first_list.end());
                    node->first.first_list.insert(FR.first_list.begin(), FR.first_list.end());
                    node->first.end_Flags = true;
                    if (FL.certain == 1 && FR.certain == 1){
                        node->first.certain = true;
                    }
                    else
                        node->first.certain = false;
                    Generate_All_First(node->lchild);
                    Generate_All_First(node->child);
                    break;
                }
            }

            case 4:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                node->first.certain = false;
                Generate_All_First(node->child);
                break;
            }

            case 5:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                Generate_All_First(node->child);
                break;
            }

            case 6:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                if (node->couting_min > 0)
                    node->first.certain = true;
                else
                    node->first.certain = false;
                Generate_All_First(node->child);
                break;
            }

            case 7:{
                if (node->first.end_Flags == true){
                    break;
                }
                for(auto T : node->char_map){
                    node->first.first_list.insert(T.first);
                }
                node->first.certain = true;
                node->first.end_Flags = true;
                break;
            }

            case 10:{
                if (node->first.end_Flags == true){
                    Generate_All_First(node->child);
                    break;
                }
                node->first = Generate_first(node->child);
                node->first.certain = true;
                Generate_All_First(node->child);
                break;
            }
            
        }
        node = node->Next;
    }
}

First_Class Preprocessing_Re_class::Generate_first(Tree_node *root) {
    Tree_node *node = root;
    First_Class  first;
    //bool end_Flags = false;
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                node->first.end_Flags = true;
                for (auto c : node->node_str){
                    first.first_list.insert(c);
                    node->first.first_list.insert(c);
                    break;
                }
                if (!node->node_str.empty()){
                    first.certain = true;
                    first.end_Flags = true;
                    node->first.certain = true;
                }
                break;
            }

            case 1:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                if (!char_list.first_list.empty()){
                    first.first_list.insert( char_list.first_list.begin(), char_list.first_list.end());
                    if (char_list.certain == true){
                        first.certain = true;
                        first.end_Flags = true;
                    }
                }
                break;
            }

            case 2:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                node->first.end_Flags = true;
                node->first = char_list;
                first.first_list.insert( char_list.first_list.begin(), char_list.first_list.end());
                break;
            }

            case 3:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                First_Class Lchar_list;
                First_Class Rchar_list;
                Lchar_list = Generate_first(node->lchild);
                Rchar_list = Generate_first(node->child);
                if (!Lchar_list.first_list.empty()){
                    first.first_list.insert(Lchar_list.first_list.begin(), Lchar_list.first_list.end());
                }
                if (!Rchar_list.first_list.empty()){
                    first.first_list.insert(Rchar_list.first_list.begin(), Rchar_list.first_list.end());
                }
                node->first.first_list.insert(Lchar_list.first_list.begin(), Lchar_list.first_list.end());
                node->first.first_list.insert(Rchar_list.first_list.begin(), Rchar_list.first_list.end());
                node->first.end_Flags = true;
                if (Lchar_list.certain && Lchar_list.certain){
                    node->first.certain = true;
                    first.certain = true;
                    first.end_Flags = true;
                }
                break;
            }

            case 4:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                first.first_list.insert(char_list.first_list.begin(), char_list.first_list.end());
                node->first.first_list.insert(char_list.first_list.begin(), char_list.first_list.end());
                node->first.end_Flags = true;
                break;
            }

            case 5:{
                if (node->first.end_Flags == true){
                    if (!node->first.first_list.empty()){
                        first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                        first.certain = true;
                        first.end_Flags = true;
                    }
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                node->first.end_Flags = true;
                node->first = char_list;
                if (!char_list.first_list.empty()){
                    first.first_list.insert(char_list.first_list.begin(), char_list.first_list.end());
                }
                if (char_list.certain == true){
                    first.certain = true;
                    first.end_Flags = true;
                }
                break;
            }

            case 6:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    if (node->couting_min > 0 && node->first.certain == true){
                        first.certain = true;
                        first.end_Flags = true;
                    }
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                node->first = char_list;
                node->first.end_Flags = true;
                if (!char_list.first_list.empty()){
                    first.first_list.insert(char_list.first_list.begin(), char_list.first_list.end());
                }
                if (node->couting_min > 0 && char_list.certain == true){
                    node->first.certain = true;
                    first.certain = true;
                    first.end_Flags = true;
                } else
                    node->first.certain = false;
                break;
            }

            case 7:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    break;
                }
                for(auto T : node->char_map){
                    first.first_list.insert(T.first);
                }
                first.certain = true;
                first.end_Flags = true;
                break;
            }

            case 10:{
                if (node->first.end_Flags == true){
                    first.first_list.insert(node->first.first_list.begin(), node->first.first_list.end());
                    if (node->first.certain = true){
                        first.certain = true;
                        first.end_Flags = true;
                    }
                    break;
                }
                First_Class char_list;
                char_list = Generate_first(node->child);
                node->first.end_Flags = true;
                node->first = char_list;
                first.first_list.insert(char_list.first_list.begin(), char_list.first_list.end());
                if (char_list.certain = true){
                    first.certain = true;
                    first.end_Flags = true;
                }
                break;
            }
        }
        if (first.end_Flags == true)
            break;
        node = node->Next;
    }
    first.end_Flags = true;
    //root->first = first;
    return first;
}