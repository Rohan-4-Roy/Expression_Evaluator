/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"


// Write your code below this line
EPPCompiler::EPPCompiler()
{
    memory_size = 0;
    output_file = "";
    ofstream file(output_file);
    file.close();
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    memory_size = mem_limit;
    output_file = out_file;
    for (int i = 0; i < memory_size; i++)
    {
        least_mem_loc.push_heap(i);
    }
    ofstream file(output_file);
    file.close();
}

void EPPCompiler::compile(vector<vector<string>> code)
{

    for (int i = 0; i < code.size(); i++)
    {
        targ.parse(code[i]);
        if (code[i][0] != "del" && code[i][0] != "ret")
        {
            
            if (targ.symtable->search(code[i][0]) == -2 || targ.symtable->search(code[i][0]) == -1)
            {
                targ.symtable->insert(code[i][0]);
                targ.symtable->assign_address(code[i][0], least_mem_loc.get_min());
                least_mem_loc.pop();
            }
        }
        write_to_file(generate_targ_commands());
    }
}
void strGenerate(ExprTreeNode *root, Parser &targ, vector<string> &v)
{
    string s;
    if (root == NULL)
        return;
    else if (root->left == NULL && root->right == NULL)
    {
        if (root->type == "VAR")
        {
            int a = targ.symtable->search(root->id);
            
            s = "PUSH mem[" + to_string(a) + "]";
        }
        else if (root->type == "VAL")
        {
            s = "PUSH " + to_string(root->num);
        }
        v.push_back(s);
    }
    else
    {
        strGenerate(root->right, targ, v);
        strGenerate(root->left, targ, v);
        if (root->type == "ADD")
            s = "ADD";
        else if (root->type == "MUL")
            s = "MUL";
        else if (root->type == "SUB")
            s = "SUB";
        else if (root->type == "DIV")
            s = "DIV";
        v.push_back(s);
    }
}
vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> v;
    string s;
    ExprTreeNode *root = targ.expr_trees.back();
    if (root->left->type == "VAR")
    {
        strGenerate(root->right, targ, v);
        int a = targ.symtable->search(root->left->id);
        s = "mem[" + to_string(a) + "] = POP";
        v.push_back(s);
    }
    else if (root->left->type == "DEL")
    {
        int a = targ.last_deleted;
        least_mem_loc.push_heap(a);
        
        s = "DEL = mem[" + to_string(a) + "]";
        v.push_back(s);
    }
    else
    {
        strGenerate(root->right, targ, v);
        s = "RET = POP";
        v.push_back(s);
    }
    return v;
}
void EPPCompiler::write_to_file(vector<string> commands)
{
    int i;
    string com;
    for (i = 0; i < commands.size(); i++)
        com = com + commands[i] + "\n";
    fstream file(output_file, ios::app);
    file << com << endl;
    file.clear();
}
EPPCompiler::~EPPCompiler()
{
}