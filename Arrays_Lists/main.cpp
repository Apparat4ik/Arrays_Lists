#include <sstream>
#include <vector>
#include "List_header.h"
#include "MyArray.h"
#include "MyFList.h"
#include "MyDoubleList.h"
#include "MyQueue.h"
#include "MyStack.h"
#include "BinaryTree.h"
#include "MySet.h"



int main(){
    try {
        bool run = true;
        MyArray<string> ar{10};
        ForwardList<string> fl;
        DoubleList<string> dl;
        MyStack<string> st;
        MyQueue<string> q;
        FBTree<int> tree;
        MySet<string> mset{10};
        
        while(run){
            cout << "> ";
            string command;
            getline(cin, command);
            stringstream s(command);
                    
            vector<string> line;
            string word;
                    
            while (s >> word) {
                line.push_back(word);
            }
                    
            if (line.empty()) {
                continue;
            } else if (line[0] == "EXIT"){return 0;}
            
            string filename = line[0];
            Command cmd = parseCommand(line[1]);
            Containers container;
            switch(cmd) {
                case Command::MPUSH_back:
                    array_read_file(ar, filename);
                    MPUSH_back(ar, line[2]);
                    array_write_file(ar, filename);
                    break;
                    
                case Command::MPUSH_index:
                    array_read_file(ar, filename);
                    MPUSH_index(ar, stoi(line[2]), line[3]);
                    array_write_file(ar, filename);
                    break;
                    
                case Command::MGET:
                    array_read_file(ar, filename);
                    cout << MGET(ar, stoi(line[2])) << endl;
                    
                    array_write_file(ar, filename);
                    break;
                    
                case Command::MDEL:
                    array_read_file(ar, filename);
                    MDEL(ar, stoi(line[2]));
                    array_write_file(ar, filename);
                    break;
                    
                case Command::MSWAP:
                    array_read_file(ar, filename);
                    MSWAP(ar, stoi(line[2]), line[3]);
                    array_write_file(ar, filename);
                    break;
                    
                case Command::MSIZE:
                    array_read_file(ar, filename);
                    MSIZE(ar);
                    break;
                    
                case Command::FGET:
                    flist_read_file(fl, filename);
                    FGET(fl, line[2]);
                    break;
                    
                case Command::FGET_index:
                    flist_read_file(fl, filename);
                    FGET_index(fl, stoi(line[2]));
                    break;
                    
                case Command::FGET_key:
                    flist_read_file(fl, filename);
                    FGET_key(fl, stoi(line[2]));
                    break;
                    
                case Command::FPUSH_next:
                    flist_read_file(fl, filename);
                    FPUSH_next(fl, stoi(line[2]), line[3]);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FPUSH_prev:
                    flist_read_file(fl, filename);
                    FPUSH_prev(fl, stoi(line[2]), line[3]);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FPUSH_front:
                    flist_read_file(fl, filename);
                    FPUSH_front(fl, line[2]);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FPUSH_back:
                    flist_read_file(fl, filename);
                    FPUSH_back(fl, line[2]);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FDEL_next:
                    flist_read_file(fl, filename);
                    FDEL_next(fl, stoi(line[2]));
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FDEL_prev:
                    flist_read_file(fl, filename);
                    FDEL_prev(fl, stoi(line[2]));
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FDEL_front:
                    flist_read_file(fl, filename);
                    FDEL_front(fl);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FDEL_back:
                    flist_read_file(fl, filename);
                    FDEL_back(fl);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::FDEL_val:
                    flist_read_file(fl, filename);
                    FDEL_val(fl, line[2]);
                    flist_write_file(fl, filename);
                    break;
                    
                case Command::LGET:
                    dlist_read_file(dl, filename);
                    LGET(dl, line[2]);
                    break;
                    
                case Command::LGET_index:
                    dlist_read_file(dl, filename);
                    LGET_index(dl, stoi(line[2]));
                    break;
                    
                case Command::LGET_key:
                    dlist_read_file(dl, filename);
                    LGET_key(dl, stoi(line[2]));
                    break;
                    
                case Command::LPUSH_next:
                    dlist_read_file(dl, filename);
                    LPUSH_next(dl, stoi(line[2]), line[3]);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LPUSH_prev:
                    dlist_read_file(dl, filename);
                    LPUSH_prev(dl, stoi(line[2]), line[3]);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LPUSH_front:
                    dlist_read_file(dl, filename);
                    LPUSH_front(dl, line[2]);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LPUSH_back:
                    dlist_read_file(dl, filename);
                    LPUSH_back(dl, line[2]);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LDEL_next:
                    dlist_read_file(dl, filename);
                    LDEL_next(dl, stoi(line[2]));
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LDEL_prev:
                    dlist_read_file(dl, filename);
                    LDEL_prev(dl, stoi(line[2]));
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LDEL_front:
                    dlist_read_file(dl, filename);
                    LDEL_front(dl);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LDEL_back:
                    dlist_read_file(dl, filename);
                    LDEL_back(dl);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::LDEL_val:
                    dlist_read_file(dl, filename);
                    LDEL_val(dl, line[2]);
                    dlist_write_file(dl, filename);
                    break;
                    
                case Command::SPUSH:
                    stack_read_file(st, filename);
                    SPUSH(st, line[2]);
                    stack_write_file(st, filename);
                    break;
                    
                case Command::SPOP:
                    stack_read_file(st, filename);
                    SPOP(st);
                    stack_write_file(st, filename);
                    break;
                    
                case Command::QPUSH:
                    queue_read_file(q, filename);
                    QPUSH(q, line[2]);
                    queue_write_file(q, filename);
                    break;
                    
                case Command::QPOP:
                    queue_read_file(q, filename);
                    QPOP(q);
                    queue_write_file(q, filename);
                    break;
                    
                case Command::TISMEMBER:
                    tree_read_file(tree, filename);
                    cout << TISMEMBER(tree, stoi(line[2])) << endl;
                    break;
                    
                case Command::TINSERT:
                    tree_read_file(tree, filename);
                    TINSERT(tree, stoi(line[2]));
                    tree_write_file(tree, filename);
                    break;
                    
                case Command::TISFULL:
                    tree_read_file(tree, filename);
                    cout << TISFULL(tree.root) << endl;
                    break;
                    
                case Command::SETADD:
                    mset.set_read_file(filename);
                    mset.SETADD(line[2]);
                    mset.set_write_file(filename);
                    break;
                    
                case Command::SETDEL:
                    mset.set_read_file(filename);
                    mset.SETDEL(line[2]);
                    mset.set_write_file(filename);
                    break;
                    
                case Command::SET_AT:
                    mset.set_read_file(filename);
                    cout << mset.SET_AT(line[2]) << endl;
                    mset.set_write_file(filename);
                    break;
                    
                case Command::PRINT:
                    container = parseContainer(line[2]);
                    switch (container) {
                        case Containers::MYARRAY:
                            PRINT(ar);
                            break;
                            
                        case Containers::MYFLIST:
                            PRINT(fl);
                            break;
                            
                        case Containers::MYDLIST:
                            PRINT(dl);
                            break;
                            
                        case Containers::MYSTACK:
                            PRINT(st);
                            break;
                            
                        case Containers::MYQUEUE:
                            PRINT(q);
                            break;
                            
                        case Containers::TREE:
                            PRINT(tree.root);
                            break;
                            
                        case Containers::MYSET:
                            mset.SPRINT();
                            break;
                            
                        case Containers::UNKNOWN:
                            cerr << "Такой команды нет" << endl;
                            
                        default:
                            break;
                    }
                    break;
                    
                case Command::UNKNOWN:
                    cerr << "Такой команды нет" << endl;
                    
                default:
                    break;
            }
        }
    } catch (const exception& error){
        cerr << error.what() << endl;
    }
    return 0;
}


