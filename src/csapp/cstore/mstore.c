long mult2(long, long);

void multstore(long x, long y, long* dest) {
    long t = mult2(x, y);
    *dest = t;
}

// gcc -Og -S mstore.c => mstore.s 汇编代码
// gcc -Og -c mstore.c => mstore.o 目标代码文件

// objdump -d mstore.o

// [root@VM-4-2-centos csapp]# objdump -d mstore.o 

// mstore.o:     file format elf64-x86-64


// Disassembly of section .text:

// 0000000000000000 <multstore>:
//   0:   53                      push   %rbx
//   1:   48 89 d3                mov    %rdx,%rbx
//   4:   e8 00 00 00 00          callq  9 <multstore+0x9>
//   9:   48 89 03                mov    %rax,(%rbx)
//   c:   5b                      pop    %rbx
//   d:   c3                      retq   
