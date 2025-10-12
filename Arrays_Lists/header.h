#pragma once

#include <iostream>
#include <fstream>

using namespace std;

enum class Command{
    MPUSH_back,
    MPUSH_index,
    MGET,
    MDEL,
    MSWAP,
    PRINT,
    MSIZE,
    FGET,
    FGET_index,
    FGET_key,
    FPUSH_next,
    FPUSH_prev,
    FPUSH_front,
    FPUSH_back,
    FDEL_next,
    FDEL_prev,
    FDEL_front,
    FDEL_back,
    FDEL_val,
    LGET,
    LGET_index,
    LGET_key,
    LPUSH_next,
    LPUSH_prev,
    LPUSH_front,
    LPUSH_back,
    LDEL_next,
    LDEL_prev,
    LDEL_front,
    LDEL_back,
    LDEL_val,
    SPUSH,
    SPOP,
    QPUSH,
    QPOP,
    TISMEMBER,
    TINSERT,
    TISFULL,
    UNKNOWN,
};


Command parseCommand(const string& cmd) {
    if (cmd == "MPUSH_back") return Command::MPUSH_back;
    if (cmd == "MPUSH_index") return Command::MPUSH_index;
    if (cmd == "MGET") return Command::MGET;
    if (cmd == "MDEL") return Command::MDEL;
    if (cmd == "MSWAP") return Command::MSWAP;
    if (cmd == "PRINT") return Command::PRINT;
    if (cmd == "MSIZE") return Command::MSIZE;
    if (cmd == "FGET") return Command::FGET;
    if (cmd == "FGET_index") return Command::FGET_index;
    if (cmd == "FGET_key") return Command::FGET_key;
    if (cmd == "FPUSH_next") return Command::FPUSH_next;
    if (cmd == "FPUSH_prev") return Command::FPUSH_prev;
    if (cmd == "FPUSH_front") return Command::FPUSH_front;
    if (cmd == "FPUSH_back") return Command::FPUSH_back;
    if (cmd == "FDEL_next") return Command::FDEL_next;
    if (cmd == "FDEL_prev") return Command::FDEL_prev;
    if (cmd == "FDEL_front") return Command::FDEL_front;
    if (cmd == "FDEL_back") return Command::FDEL_back;
    if (cmd == "FDEL_val") return Command::FDEL_val;
    if (cmd == "LGET") return Command::LGET;
    if (cmd == "LGET_index") return Command::LGET_index;
    if (cmd == "LGET_key") return Command::LGET_key;
    if (cmd == "LPUSH_next") return Command::LPUSH_next;
    if (cmd == "LPUSH_prev") return Command::LPUSH_prev;
    if (cmd == "LPUSH_front") return Command::LPUSH_front;
    if (cmd == "LPUSH_back") return Command::LPUSH_back;
    if (cmd == "LDEL_next") return Command::LDEL_next;
    if (cmd == "LDEL_prev") return Command::LDEL_prev;
    if (cmd == "LDEL_front") return Command::LDEL_front;
    if (cmd == "LDEL_back") return Command::LDEL_back;
    if (cmd == "LDEL_val") return Command::LDEL_val;
    if (cmd == "SPUSH") return Command::SPUSH;
    if (cmd == "SPOP") return Command::SPOP;
    if (cmd == "QPUSH") return Command::QPUSH;
    if (cmd == "QPOP") return Command::QPOP;
    if (cmd == "TISMEMBER") return Command::TISMEMBER;
    if (cmd == "TINSERT") return Command::TINSERT;
    if (cmd == "TISFULL") return Command::TISFULL;
    return Command::UNKNOWN;
}

enum class Containers{
    MYARRAY,
    MYFLIST,
    MYDLIST,
    MYSTACK,
    MYQUEUE,
    TREE,
    UNKNOWN
};

Containers parseContainer(const string& cont){
    if (cont == "MyArray") return Containers::MYARRAY;
    if (cont == "ForwardList") return Containers::MYFLIST;
    if (cont == "DoubleList") return Containers::MYDLIST;
    if (cont == "MyStack") return Containers::MYSTACK;
    if (cont == "MyQueue") return Containers::MYQUEUE;
    if (cont == "FBTree") return Containers::TREE;
    return Containers::UNKNOWN;
}

bool is_file_empty(const string& filename) {
    ifstream file(filename);
    char first_char;
    file >> first_char;
    bool empty = file.eof();
    file.close();
    
    return empty;
}
