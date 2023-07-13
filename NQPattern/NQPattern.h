//NQ模式
// Created by 黄鸿 on 2023/4/14.
//

#ifndef REDOSHUNTER_NQPATTERN_H
#define REDOSHUNTER_NQPATTERN_H

#endif //REDOSHUNTER_NQPATTERN_H
//#include "regex.h"
#include "unordered_map"
#include "vector"
#include "NQClass.h"
#include "Util/Generate_string.h"
#include "Util/Generate_regex.h"
#include <regex>

class NQPattern{
public:
    bool NQDetect(Tree_node *root, string mid_str);
    bool Is_inside_NQ(Tree_node *node);
    void FindAllQ(Tree_node *root, vector<Tree_node> &node_list);
    void init();
    //void Generate_string(Tree_node *node, vector<string> &Gen_Str);
    vector<NQClass> NQList;
    string attack_string;
    bool is_attack = false;
    Tree_node *begin = nullptr;
    Tree_node *mid = nullptr;
    Tree_node *end = nullptr;
    //vector<char> Collect_All_Char_In_star(Tree_node *node);
};


void NQPattern::init() {
    begin = nullptr;
    mid = nullptr;
    end = nullptr;
}

void NQPattern::FindAllQ(Tree_node *root, vector<Tree_node> &node_list) {
    Tree_node *node = root;
    while (node != nullptr){
        switch (node->flags) {

            case 1:{
                FindAllQ(node->child, node_list);
                break;
            }

            case 2:{
                FindAllQ(node->child, node_list);
                break;
            }

            case 3:{
                FindAllQ(node->lchild, node_list);
                FindAllQ(node->child, node_list);
                break;
            }

            case 4:{
                node_list.push_back(*node);
                break;
            }

            case 5:{
                FindAllQ(node->child, node_list);
                break;
            }

            case 6:{
                if (node->couting_min == node->couting_max)
                    FindAllQ(node->child, node_list);
                else{
                    node_list.push_back(*node);
                }
                break;
                //FindAllQ(node->child, node_list);
            }

            case 10:{
                node_list.push_back(*node);
                break;
            }

            default:{
                break;
            }
        }
        node = node->Next;
    }
}


int mark = 0;
unordered_map<char, int> char_map;
//bool is_NQ = false;

vector<char> Collect_All_Char_In_star(Tree_node *node){

}

bool NQPattern::NQDetect(Tree_node *root, string mid_str){
    Tree_node *node = root;
    Tree_node *begin_node = begin;
    class Generate_string_class G_NQ;
    class Generate_regex_class G_Re;
    vector<Tree_node> node_list;
    FindAllQ(root, node_list);
    vector<string> begin_string, mid_string, end_string;
    begin_string.emplace_back("");
    end_string.emplace_back("");
    for (auto mid_node:node_list){
        G_NQ.NQ_Generate_string(root, &mid_node, begin_string, mid_string, end_string);
        G_NQ.Flags = 0;
        vector<string> str_list;
        for (auto str1 : end_string){
            for (auto str2 : begin_string){
                str_list.emplace_back(str1 + str2);
            }
        }
        mid_node.Next = nullptr;
        string string1 = G_Re.Generate_regex(&mid_node);
        std::regex pattern(string1);
        for (auto str : str_list){
            if (regex_match(str, pattern)){
                attack_string = str;
                is_attack = true;
            }
        }

        begin_string.clear();
        end_string.clear();
        begin_string.emplace_back("");
        end_string.emplace_back("");
    }
    /*
    while (node != nullptr){
        switch (node->flags) {
            case 0:{
                begin->Next = node;
                begin = node;
                break;
            }

            case 2:{

            }

        }

        if (node->flags == 4 || node->flags == 10){

        }
        node = node->Next;
    }
    */
}


bool NQPattern::Is_inside_NQ(Tree_node *root){
    Tree_node *node = root;
    bool is_NQ = false;


    while (node != nullptr){
        switch (node->flags) {

            case 1:{
                Is_inside_NQ(node->child);
                break;
            }

            case 2:{
                Is_inside_NQ(node->child);
                break;
            }

            case 3:{
                Is_inside_NQ(node->lchild);
                Is_inside_NQ(node->child);
                break;
            }

            case 4:{
                NQClass NQC;
                init();
                NQC.is_NQ = NQPattern::NQDetect(node->child, NQC.mid_str);
                NQC.Begin_node = node->Pre;
                if (NQC.is_NQ){
                    NQList.push_back(NQC);
                }
                Is_inside_NQ(node->child);
                break;
            }

            case 5:{
                Is_inside_NQ(node->child);
                break;
            }

            case 6:{
                Is_inside_NQ(node->child);
            }


            case 10:{
                NQClass NQC;
                NQC.is_NQ = NQPattern::NQDetect(node->child, NQC.mid_str);
                NQC.Begin_node = node->Pre;
                if (NQC.is_NQ){
                    NQList.push_back(NQC);
                }
                Is_inside_NQ(node->child);
                break;
            }

            default:{
                break;
            }

        }
        node = node->Next;
    }

}

bool NQDetect(Tree_node *root){

}

bool NQPattern(Tree_node *root){
    Tree_node *node = root->child;
    while (node != nullptr){
        switch (node->flags) {
            case '4':{
                if (mark == 1){
                    return true;
                }
                else{
                    mark = 1;
                    if (NQPattern(node)){
                        node->NQFlag = 1;
                    }
                }
                break;
            }
            case '10':{
                if (mark == 1)
                    return true;
                else{
                    mark = 1;
                    if (NQPattern(node)){
                        node->NQFlag = 1;
                    }
                }
                break;
            }
            case '5':{

            }

            default:{
                mark = 0;
                break;
            }
        }
    }
}