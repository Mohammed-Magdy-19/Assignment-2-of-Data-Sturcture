#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct Book{
    int id;
    string title;
    string author;
};
struct  Node{
    Book book;
    Node*left;
    Node*right;
    Node(Book b) {
        book=b;
        left=right=nullptr;
    }
};
 class BST {
 private:
 Node*root;

    //insert
    Node*insert(Node*node,Book b) {
        if (node==nullptr) {
            return new Node(b);
        }
        if (b.id<node->book.id) {
            node->left=insert(node->left,b);
        }else if (b.id>node->book.id) {
            node->right=insert(node->right,b);
        }
        return node;

    }
    //Search
    Node*search(Node*node,int id ,int &steps) {
        steps++;
        if (node==nullptr||node->book.id==id) {
            return node;
        }if (id<node->book.id) {
            return search(node->left,id,steps);
        }else {
            return search (node->right,id,steps);
        }

    }
    //inorder display
    void inorder(Node*node) {
        if (node==nullptr) return;
        inorder(node->left);
        cout<<" ID : "<<node->book.id
        <<" |Title : "<<node->book.title
        <<" |Author : "<<node->book.author<<endl;
        inorder(node->right);
    }
    //findmin
    Node*findmin(Node*node) {
        while (node->left!=nullptr) {
            node=node->left;
        }
        return node;
    }
    //Delete
    Node*deletenode(Node*node,int id) {
        if (node==nullptr)return nullptr;

        if (id<node->book.id) {
            node->left=deletenode(node->left,id);
        }else if (id>node->book.id){
            node->right=deletenode(node->right,id);
        }else {
            if (node->left==nullptr&&node->right==nullptr) {
                delete node;
                return nullptr;
            }else if (node->left==nullptr) {
                Node*temp=node->right;
                delete node;
                return temp;
            }
            else if (node->right==nullptr) {
                Node*temp=node->left;
                delete node;
                return temp;
            }else {
                Node*temp=findmin(node->right);
                node->book=temp->book;
                node->right=deletenode(node->right,temp->book.id);

            }


        }
        return node;
    }
    //range search
    void rangesearch(Node*node,int low,int high) {
        if (node==nullptr)return;
        if (node->book.id>low) {
            rangesearch(node->left,low,high);
        }
        if (node->book.id>=low&&node->book.id<=high) {
            cout<<" ID : "<<node->book.id<<" Title : "<< node->book.title<<endl;
        }
        if (node->book.id<high) {
            rangesearch(node->right,low,high);
        }
    }

    //close id
    void closeid(Node*node,int target,int&closest) {
        if (node==nullptr)return;
        if (abs(node->book.id-target)<abs(closest-target))
            closest=node->book.id;
        if (target<node->book.id)
            closeid(node->left,target,closest);
        else if (target>node->book.id)
            closeid(node->right,target,closest);
    }
    //hight
    int height(Node*node){
    if (node==nullptr)
    return 0;
    int leftheight=height(node->left);
    int rightheight=height(node->right);
        return max(leftheight,rightheight)+1;


}
    public:
    BST() {
        root=nullptr;
    }
    //insert
    void insert(Book b) {
        root=insert(root,b);
    }
    //search
    void search(int id) {
        int steps=0;
        Node*result=search(root,id,steps);
        if (result){
            cout<<"Book Found\n"<<result->book.title<<endl;
            cout<<"Steps = "<<steps<<endl;
        }else {
            cout<<"Book Not Found\n";
            cout<<"Steps = "<<steps<<endl;
        }
    }
    //Display
    void display() {
        inorder(root);
    }
    //delete
    void deletebook(int id) {
        root=deletenode(root,id);
    }
    //range
    void printrange(int low,int high) {
        rangesearch(root,low,high);
    }
    //close
    void findclose(int target) {
        if (root==nullptr) {
            cout<<"Tree is empty\n";
            return;
        }
        int closest=root->book.id;
        closeid(root,target,closest);
        cout<<"Closest Id to: "<<target<<"is: "<<closest<<endl;
    }

    //hight
    int gethight() {
        return height(root);
    }



};



int main() {
    BST tree;
    tree.insert({100,"C++","Eman"});
    tree.insert({90,"Java","Mariem"});
    tree.insert({150,"DS","Sara"});
    tree.insert({50,"Python","Salma"});
    tree.insert({75,"Network","Ali"});
    tree.insert({125,"Database","Nour"});
    tree.insert({25,"OS","Malak"});
    tree.insert({60,"AI","Omar"});
    tree.insert({110,"Math","Hassan"});
    tree.insert({140,"Physics","Laila"});
    tree.insert({160,"ML","Khaled"});
    tree.insert({170,"Security","Yara"});
    tree.insert({30,"Web","Alaa"});
    tree.insert({45,"OOP","Heba"});
    tree.insert({55,"Logic","Mostafa"});
    tree.insert({65,"Linux","Ziad"});
    tree.insert({85,"Algorithms","Noha"});
    tree.insert({95,"Design","Mina"});
    tree.insert({115,"management","Youssef"});
    tree.insert({135,"DBMS","Dina"});
    //display
    cout<<"Book is sorted order:\n";
    tree.display();
    cout<<"\n-----------------------------------\n";
    tree.search(50);
    //delete
    cout<<"\n-----------------------------------\n";
    cout<<"Delete book id 25 \n";
    tree.deletebook(25);

    cout<<"Books after deletion: \n";
    tree.display();
    //range search
    cout<<"Books between 100 and 150\n";
    tree.printrange(100,150);
    //close id
    cout<<"\n-------------------------------\n";
    tree.findclose(24);
    //Height
    cout<<"\n--------------------------------\n";
    cout<<"Tree Height= "<<tree.gethight()<<endl;

}

