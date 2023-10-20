/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// Write your code below this line

SymbolTable::SymbolTable()
{

    root = new SymNode();
    size = 0;
}
int getBF(SymNode *node)
{
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 0;
    else if (node->left == NULL)
        return -1 * node->right->height;
    else if (node->right == NULL)
        return node->left->height;
    else
        return node->left->height - node->right->height;
}
SymNode *pres;
void insert1(SymNode *node, string k)
{

    if (node->key == "")
    {
        pres = node;
        node->key = k;
        return;
    }
    else if (node->key == k)
    {
        pres = node;
        return;
    }
    else if (node->key > k)
    {

        if (node->left == NULL)
        {
            SymNode *x = new SymNode(k);
            x->par = node;
            node->left = x;
            insert1(node->left, k);
        }
        else
            insert1(node->left, k);
    }
    else if (node->key < k)
    {

        if (node->right == NULL)
        {
            SymNode *x = new SymNode(k);
            x->par = node;
            node->right = x;
            insert1(node->right, k);
        }
        else
            insert1(node->right, k);
    }
}
void SymbolTable::insert(string k)
{

    size++;
    SymNode *temp = root;

    insert1(temp, k);
    temp = pres;

    while (temp != NULL && temp != root->par)
    {

        SymNode *k1 = temp->par;
        if (temp->left == NULL && temp->right == NULL)
            temp->height = 1;
        else if (temp->left == NULL)
            temp->height = 1 + temp->right->height;
        else if (temp->right == NULL)
            temp->height = 1 + temp->left->height;
        else
            temp->height = max(temp->left->height, temp->right->height) + 1;

        int bf = getBF(temp);
        if (bf > 1 && k < temp->left->key)
        {

            temp->LeftLeftRotation();
            if (temp == root)
            {
                root = temp->par;
                break;
            }
            else if (temp->par == root)
            {
                root = temp;
                root->par = NULL;
            }
        }
        else if (bf < -1 && k > temp->right->key)
        {

            temp->RightRightRotation();
            if (temp == root)
            {

                root = temp->par;
                break;
            }
            else if (temp->par == root)
            {
                root = temp;
                root->par = NULL;
            }
        }
        else if (bf > 1 && k > temp->left->key)
        {

            temp->LeftRightRotation();
            if (temp == root)
            {
                root = temp->par;
                break;
            }
        }
        else if (bf < -1 && k < temp->right->key)
        {

            temp->RightLeftRotation();
            if (temp == root)
            {
                root = temp->par;
                break;
            }
        }
        temp = k1;
    }
}
SymNode *successor(SymNode *node)
{
    node = node->right;

    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}
int flag=0;
void remove1(SymNode *node, string k, SymNode *&root)
{
    if (node == NULL)
      { flag=1;
         return;}
    else if (k < node->key)
        remove1(node->left, k, root);
    else if (k > node->key)
        remove1(node->right, k, root);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            if (node->par != NULL)
            {
                if (node->par->left == node)
                    node->par->left = NULL;
                else
                    node->par->right = NULL;
            }
            delete node;
            node = NULL;
            return;
        }
        else if (node->left == NULL)
        {
            *node = *node->right;
        }
        else if (node->right == NULL)
        {
            *node = *node->left;
        }
        else
        {

            SymNode *snode = successor(node);

            string key1 = snode->key;
            node->key = key1;

            swap(snode->address, node->address);
            remove1(node->right, key1, root);
        }
    }
    if (node->left == NULL && node->right == NULL)
        node->height = 1;
    else if (node->left == NULL)
        node->height = 1 + node->right->height;
    else if (node->right == NULL)
        node->height = 1 + node->left->height;
    else
        node->height = max(node->left->height, node->right->height) + 1;
    int bf = getBF(node);
    if (bf > 1 && getBF(node->left) >= 0)
    {
        node->LeftLeftRotation();
        if (node == root)
        {
            root = node->par;
        }
        else if (node->par == root)
        {
            root = node;
            root->par = NULL;
        }
    }
    else if (bf < -1 && getBF(node->right) <= 0)
    {
        node->RightRightRotation();
        if (node == root)
        {
            root = node->par;
        }
        else if (node->par == root)
        {
            root = node;
            root->par = NULL;
        }
    }
    else if (bf > 1 && getBF(node->left) < 0)
    {
        node->LeftRightRotation();
        if (node == root)
        {
            root = node->par;
        }
    }
    else if (bf < -1 && getBF(node->right) > 0)
    {
        node->RightLeftRotation();
        if (node == root)
        {
            root = node->par;
        }
    }
}
void SymbolTable::remove(string k)
{

    
    SymNode *node = root;
    remove1(node, k, root);
    if(flag==0)
    size--;
}

int SymbolTable::search(string k)
{

    SymNode *temp = root;
    while (temp != NULL)
    {
        if (temp->key == k)
        {
            return temp->address;
        }
        else if (temp->key > k)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return -2;
}

void SymbolTable::assign_address(string k, int idx)
{

    SymNode *temp = root;
    while (true)
    {
        if (temp->key == k)
        {
            temp->address = idx;
            return;
        }
        else if (temp->key > k)
            temp = temp->left;
        else
            temp = temp->right;
    }
}

int SymbolTable::get_size()
{

    return size;
}

SymNode *SymbolTable::get_root()
{

    if (root == NULL)
        return NULL;
    return root;
}

void postdel(SymNode *node)
{
    if (node == NULL)
        return;
    if (node->left != NULL)
        postdel(node->left);
    if (node->right != NULL)
        postdel(node->right);
    delete node;
}
SymbolTable::~SymbolTable()
{

    postdel(root);
}
