/* printf(), etc */
#include <stdio.h>
/* strdup() */
#include <string.h>
/* free() */
#include <stdlib.h>

int main(int argc, char * * argv);

#define BufSize 256

// キモは、終了コード→リソース→例外ブロック→リソース解放→終了処理

// 例外処理が不要であれば、関数、ループ、swtich とも、こんな面倒なこと
// をする必要は無い

int // リターンコードを返す関数なので int
main ( // 検索しやすいよう行頭。宣言と区別するためカッコ前空ける
  int argc, // 扱いはオート変数なので、インデント 2
  char * * argv ) { // 同行に対応が無い場合はカッコ前 1 カラム空け
  int rc = -1; // 関数終了コードを異常で初期化
  FILE * pfile = NULL; // 動的リソースは関数例外ブロック外で初期化
    do { // 関数例外ブロック
      int loop_rc = -1; // ループ終了コード
       // 0 回ループがあり得なければ、初期化不要
       // 0 回ループが正常ならば 0 で、異常ならば -1 で初期化
      char sz[BufSize]; // 静的リソースは例外ブロック内に
      int i; // 同上。基本、初期化なし
        if (! (pfile = fopen("/etc/fstab", "r"))) {
            fprintf(stderr, "Error: Failed to open.\n");
            break; // 遠慮なく braek
        }
        i = 0;
        while (fgets(sz, sizeof (sz), pfile)) { // ループ
          char * psz = NULL; // 動的なものはループ例外ブロック外
            loop_rc = -1; // ループ終了コードに異常を代入
            do { // ループ例外ブロック
                if (! (psz = strdup(sz))) {
                    fprintf(stderr, "Error: No resource.\n");
                    break;
                }
                i ++;
                if (i > 10) {
                    fprintf(stderr, "Error: Count exceeded.\n");
                    break;
                }
                while (0) {
                    goto finally;
                }
                fprintf(stdout, "d: %d %s", i, psz);
                loop_rc = 0; // ループ正常終了
            } while (0);
            if (psz) { free(psz); } // 初期値でなければ解放
            if (loop_rc != 0) { break; } // あるいは continue か
        }
        if (loop_rc != 0) { break; }
        for (i = 0; i < 3; i ++) {
            loop_rc = -1;
            do {
              int switch_rc = -1; // switch は、0 ノーマルでもいいかもな
                printf("d1: %d\n", i);
                switch (i) {
                    case (1): {
                        break;
                    }
                    case (2): {
                        break;
                    }
                    default: {
                        switch_rc = 0;
                    }
                }
                if (switch_rc != 0) {
                    break;
                }
                loop_rc = 0;
            } while (0);
            if (loop_rc != 0) { break; }
        }
        if (loop_rc != 0) { break; }
        rc = 0; // 正常終了
    } while (0);
finally:
    if (pfile) { fclose(pfile); } // 初期値でなければ解放
    return (rc); // 関数終了コードをリターン
}
