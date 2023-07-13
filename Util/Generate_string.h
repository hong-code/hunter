//
// Created by 黄鸿 on 2023/6/7.
//

#ifndef REDOSHUNTER_GENERATE_STRING_H
#define REDOSHUNTER_GENERATE_STRING_H

#endif //REDOSHUNTER_GENERATE_STRING_H

#include "vector"



class Generate_string_class{
public:
    int Flags = 0;
    void NQ_Generate_string(Tree_node *root, Tree_node *mid_node, vector<string> &begin_str_list, vector<string> &mid_str, vector<string> &end_str_list);
};

void Generate_string_class::NQ_Generate_string(Tree_node *root, Tree_node *mid_node, vector<string> &begin_str_list,
                                               vector<string> &mid_str, vector<string> &end_str_list) {
    Tree_node *node = root;

    while (node != nullptr){
        switch (node->flags) {
            case 0: {
                if (Flags == 0) {
                    if (node->node_str.empty()) {
                        break;
                    }
                    if (begin_str_list.empty()) {
                        string str1 = node->node_str;
                        begin_str_list.push_back(str1);
                    } else {
                        for (vector<string>::iterator iter = begin_str_list.begin();
                             iter != begin_str_list.end(); iter++) {
                            *iter = *iter + node->node_str;
                        }
                    }
                } else {
                    if (node->node_str.empty()) {
                        break;
                    }
                    if (end_str_list.empty()) {
                        string str1 = node->node_str;
                        end_str_list.push_back(str1);
                    } else {
                        for (vector<string>::iterator iter = end_str_list.begin(); iter != end_str_list.end(); iter++) {
                            *iter = *iter + node->node_str;
                        }
                    }
                }
                break;
            }

            case 1: {
                NQ_Generate_string(root->child, mid_node, begin_str_list, mid_str, end_str_list);
                break;
            }

            case 2: {
                vector<string> sub_begin_str_list, sub_end_str_list;
                sub_begin_str_list.emplace_back("");
                sub_end_str_list.emplace_back("");
                if (Flags == 0) {
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    if (Flags == 0){
                        vector<string> str_list = begin_str_list;
                        for (vector<string>::iterator iter = str_list.begin();
                            iter != str_list.end(); iter++) {
                            for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                sub_iter != sub_begin_str_list.end(); sub_iter++) {
                                if (*sub_iter == "")
                                    continue;
                                begin_str_list.emplace_back(*iter + *sub_iter);
                            }
                        }
                    }
                    else{
                        for (vector<string>::iterator iter = begin_str_list.begin();
                             iter != begin_str_list.end(); iter++) {
                            for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                 sub_iter != sub_begin_str_list.end(); sub_iter++) {
                                *iter = *iter + *sub_iter;
                            }
                        }
                        end_str_list = sub_end_str_list;
                    }
                }
                else{
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    vector<string> str_list = end_str_list;
                    for (vector<string>::iterator iter = str_list.begin();
                         iter != str_list.end(); iter++) {
                        for (vector<string>::iterator sub_iter = sub_end_str_list.begin();
                             sub_iter != sub_end_str_list.end(); sub_iter++) {
                            end_str_list.emplace_back(*iter + *sub_iter);
                        }
                    }
                }
                break;
            }

            case 3:{
                vector<string> sub_begin_str_list, sub_end_str_list;
                vector<string> lsub_begin_str_list, lsub_end_str_list;
                sub_begin_str_list.emplace_back("");
                sub_end_str_list.emplace_back("");
                lsub_begin_str_list.emplace_back("");
                lsub_end_str_list.emplace_back("");
                if (Flags == 0){
                    NQ_Generate_string(node->lchild, mid_node, lsub_begin_str_list, mid_str, lsub_end_str_list);
                    if (Flags == 0){
                        NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                        if (Flags == 0){
                            vector<string> str_list = begin_str_list;
                            begin_str_list.clear();
                            for (auto iter = str_list.begin(); iter != str_list.end(); iter++) {
                                for (auto sub_iter = lsub_begin_str_list.begin();
                                    sub_iter != lsub_begin_str_list.end(); iter++) {
                                    begin_str_list.emplace_back(*iter + *sub_iter);
                                }
                            }


                            for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++) {
                                for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                     sub_iter != sub_begin_str_list.end(); iter++) {
                                    begin_str_list.emplace_back(*iter + *sub_iter);
                                }
                            }

                        }
                        else{
                            vector<string> str_list = begin_str_list;
                            begin_str_list.clear();
                            for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++) {
                                for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                     sub_iter != sub_begin_str_list.end(); iter++) {
                                    str_list.emplace_back(*iter + *sub_iter);
                                }
                            }
                            end_str_list = sub_end_str_list;
                        }
                    }
                    else{
                        vector<string> str_list = begin_str_list;
                        begin_str_list.clear();
                        for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++) {
                            for (vector<string>::iterator sub_iter = lsub_begin_str_list.begin();
                                 sub_iter != lsub_begin_str_list.end(); iter++) {
                                begin_str_list.emplace_back(*iter + *sub_iter);
                            }
                        }
                        end_str_list = lsub_end_str_list;
                    }
                }
                else{
                    NQ_Generate_string(node->lchild, mid_node, lsub_begin_str_list, mid_str, lsub_end_str_list);
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    vector<string> str_list = end_str_list;
                    end_str_list.clear();
                    for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++) {
                        for (vector<string>::iterator sub_iter = lsub_end_str_list.begin();
                             sub_iter != lsub_end_str_list.end(); iter++) {
                            end_str_list.emplace_back(*iter + *sub_iter);
                        }
                    }

                    for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++) {
                        for (vector<string>::iterator sub_iter = sub_end_str_list.begin();
                             sub_iter != sub_end_str_list.end(); iter++) {
                            end_str_list.emplace_back(*iter + *sub_iter);
                        }
                    }

                }
            }

            case 4:{
                vector<string> sub_begin_str_list, sub_end_str_list;
                sub_begin_str_list.emplace_back("");
                sub_end_str_list.emplace_back("");
                if (node->child == mid_node->child && node->flags == node->flags){
                    Flags = 1;
                    break;
                }
                else{
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    if (Flags == 0){
                        vector<string> str_list = begin_str_list;
                        for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                            for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                            sub_iter != sub_begin_str_list.end(); sub_iter++){
                                string string1 = *sub_iter;
                                if (string1 == ""){
                                    begin_str_list.push_back(*iter);
                                    continue;
                                }
                                for (int i = 1; i <= 10; i++){
                                    begin_str_list.push_back(*iter + string1);
                                    string1 = *sub_iter + string1;
                                }
                            }
                        }
                    }
                    else {
                        vector<string> str_list = end_str_list;
                        for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                            for (vector<string>::iterator sub_iter = sub_end_str_list.begin();
                                 sub_iter != sub_end_str_list.end(); sub_iter++){
                                string string1 = *sub_iter;
                                if (string1 == ""){
                                    end_str_list.push_back(*iter);
                                    continue;
                                }
                                for (int i = 1; i <= 10; i++){
                                    end_str_list.push_back(*iter + string1);
                                    string1 = string1 + *sub_iter;
                                }
                            }
                        }
                    }
                }
                break;
            }

            case 5:{
                vector<string> sub_begin_str_list, sub_end_str_list;
                sub_begin_str_list.emplace_back("");
                sub_end_str_list.emplace_back("");
                if (Flags == 0){
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    if (Flags == 0){
                        vector<string> str_list = begin_str_list;
                        begin_str_list.clear();
                        for (auto & iter : str_list){
                            for (auto & sub_iter : sub_begin_str_list){
                                begin_str_list.emplace_back(iter + sub_iter);
                            }
                        }
                    }
                    else {
                        vector<string> str_list = begin_str_list;
                        begin_str_list.clear();
                        for (auto & iter : str_list){
                            for (auto & sub_iter : sub_begin_str_list){
                                begin_str_list.emplace_back(iter + sub_iter);
                            }
                        }
                        end_str_list = sub_end_str_list;
                    }
                } else{
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    vector<string> str_list = end_str_list;
                    end_str_list.clear();
                    for (auto & iter : str_list){
                        for (auto & sub_iter : sub_end_str_list){
                            end_str_list.emplace_back(iter + sub_iter);
                        }
                    }
                }
                break;
            }

            case 6:{
                vector<string> sub_begin_str_list, sub_end_str_list;
                sub_begin_str_list.emplace_back("");
                sub_end_str_list.emplace_back("");
                if (node->child == mid_node->child && node->flags == 6){
                    Flags = 1;
                    break;
                }
                else{
                    NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                    if (Flags == 0){
                        vector<string> str_list = begin_str_list;
                        begin_str_list.clear();
                        for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                            for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                 sub_iter != sub_begin_str_list.end(); sub_iter++){
                                string string1 = *sub_iter;
                                if (string1 == ""){
                                    begin_str_list.emplace_back(*iter);
                                    continue;
                                }
                                for (int i = 0; i < node->couting_min; i++)
                                    string1 = *sub_iter + string1;
                                for (int i = node->couting_min; i <= node->couting_max; i++){
                                    begin_str_list.push_back(string1);
                                    string1 = *sub_iter + string1;
                                }
                            }
                        }
                    }
                    else {
                        vector<string> str_list = end_str_list;
                        end_str_list.clear();
                        for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                            for (vector<string>::iterator sub_iter = sub_end_str_list.begin();
                                 sub_iter != sub_end_str_list.end(); sub_iter++){
                                string string1 = *sub_iter;
                                if (string1 == ""){
                                    end_str_list.emplace_back(*iter);
                                    continue;
                                }
                                for (int i = 0; i < node->couting_min; i++)
                                    string1 = *sub_iter + string1;
                                for (int i = node->couting_min; i <= node->couting_max; i++){
                                    end_str_list.push_back(string1);
                                    string1 = *sub_iter + string1;
                                }
                            }
                        }
                    }
                }
                break;
            }

            case 7:{
                if (Flags == 0){
                    vector<string> str_list;
                    str_list = begin_str_list;
                    for (auto & iter : str_list){
                        for (auto char_iter : node->char_map){
                            begin_str_list.emplace_back(iter + char_iter.first);
                        }
                    }
                }
                else{
                    vector<string> str_list;
                    str_list = end_str_list;
                    for (auto & iter : str_list){
                        for (auto char_iter : node->char_map){
                            end_str_list.emplace_back(iter + char_iter.first);
                        }
                    }
                }
                break;
            }


            case 10:{
                    vector<string> sub_begin_str_list, sub_end_str_list;
                    sub_begin_str_list.emplace_back("");
                    sub_end_str_list.emplace_back("");
                    if (node->child == mid_node->child && node->flags == 10){
                        Flags = 1;
                        break;
                    }
                    else{
                        NQ_Generate_string(node->child, mid_node, sub_begin_str_list, mid_str, sub_end_str_list);
                        if (Flags == 0){
                            vector<string> str_list = begin_str_list;
                            begin_str_list.clear();
                            for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                                for (vector<string>::iterator sub_iter = sub_begin_str_list.begin();
                                     sub_iter != sub_begin_str_list.end(); sub_iter++){
                                    string string1 = *sub_iter;
                                    for (int i = 1; i <= 10; i++){
                                        begin_str_list.push_back(string1);
                                        string1 = *sub_iter + string1;
                                    }
                                }
                            }
                        }
                        else {
                            vector<string> str_list = end_str_list;
                            end_str_list.clear();
                            for (vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); iter++){
                                for (vector<string>::iterator sub_iter = sub_end_str_list.begin();
                                     sub_iter != sub_end_str_list.end(); sub_iter++){
                                    string string1 = *sub_iter;
                                    for (int i = 1; i <= 10; i++){
                                        end_str_list.push_back(string1);
                                        string1 = *sub_iter + string1;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
            default:{
                break;
            }

        }
        node = node->Next;
    }
}