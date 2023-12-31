#include "9cc.h"

// 入力プログラム
char *user_input;

// 現在着目しているトークン
Token *token;

int main(int argc, char **argv) {
    if (argc != 2)
        error("%s: 引数の個数が正しくありません", argv[0]);

    // トークナイズしてパースする
    user_input = argv[1];
    token = tokenize();
    Node *node = expr();

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    // スタックトップに式全体の値が残っているはずなので
    // それをRAXにロードして関数からの返り値とする
    printf("  pop rax\n");
    printf("  ret\n");
    return 0;
}