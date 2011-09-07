/* printf(), etc */
#include <stdio.h>
/* strdup() */
#include <string.h>
/* free() */
#include <stdlib.h>

int main(int argc, char * * argv);

#define BufSize 256

// ����ϡ���λ�����ɢ��꥽�������㳰�֥�å����꥽������������λ����

// �㳰���������פǤ���С��ؿ����롼�ס�swtich �Ȥ⡢��������ݤʤ���
// �򤹤�ɬ�פ�̵��

int // �꥿���󥳡��ɤ��֤��ؿ��ʤΤ� int
main ( // �������䤹���褦��Ƭ������ȶ��̤��뤿�ᥫ�å���������
  int argc, // �����ϥ������ѿ��ʤΤǡ�����ǥ�� 2
  char * * argv ) { // Ʊ�Ԥ��б���̵�����ϥ��å��� 1 ��������
  int rc = -1; // �ؿ���λ�����ɤ�۾�ǽ����
  FILE * pfile = NULL; // ưŪ�꥽�����ϴؿ��㳰�֥�å����ǽ����
    do { // �ؿ��㳰�֥�å�
      int loop_rc = -1; // �롼�׽�λ������
       // 0 ��롼�פ��������ʤ���С����������
       // 0 ��롼�פ�����ʤ�� 0 �ǡ��۾�ʤ�� -1 �ǽ����
      char sz[BufSize]; // ��Ū�꥽�������㳰�֥�å����
      int i; // Ʊ�塣���ܡ�������ʤ�
        if (! (pfile = fopen("/etc/fstab", "r"))) {
            fprintf(stderr, "Error: Failed to open.\n");
            break; // ��θ�ʤ� braek
        }
        i = 0;
        while (fgets(sz, sizeof (sz), pfile)) { // �롼��
          char * psz = NULL; // ưŪ�ʤ�Τϥ롼���㳰�֥�å���
            loop_rc = -1; // �롼�׽�λ�����ɤ˰۾������
            do { // �롼���㳰�֥�å�
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
                loop_rc = 0; // �롼�����ｪλ
            } while (0);
            if (psz) { free(psz); } // ����ͤǤʤ���в���
            if (loop_rc != 0) { break; } // ���뤤�� continue ��
        }
        if (loop_rc != 0) { break; }
        for (i = 0; i < 3; i ++) {
            loop_rc = -1;
            do {
              int switch_rc = -1; // switch �ϡ�0 �Ρ��ޥ�Ǥ⤤�������
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
        rc = 0; // ���ｪλ
    } while (0);
finally:
    if (pfile) { fclose(pfile); } // ����ͤǤʤ���в���
    return (rc); // �ؿ���λ�����ɤ�꥿����
}
