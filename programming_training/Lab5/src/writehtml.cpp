#include "writehtml.h"

void writehtml(char* locate, struct List L[6]) {
    FILE* fp = fopen(locate, "w+");

    fprintf(fp, "<!DOCTYPE html>\n<head>\n");
    //fprintf(fp,"    <meta charset=\"UTF-8\">\n");
    fprintf(fp, "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
    fprintf(fp, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    //��ҳͷ��
    fprintf(fp, "    <title>�����ҳ</title>\n</head>\n<body>\n    <table border=\"1\">\n");
    //��ҳ����
    fprintf(fp, "        <caption>ͳ�ƽ��</caption>\n        <tr>\n");
    //������

    for (int i = 0; i < 6; i++) {
        fprintf(fp, "            <th>%s</th>\n", L[i].name);
    }
    fprintf(fp, "</tr>\n<tr>\n");
    //�����������
    for (int i = 0; i < 6; i++) {
        fprintf(fp, "            <td>%d</td>\n", L[i].num);
    }

    fprintf(fp, "        </tr>\n    </table>\n</body>\n</html>");
    fclose(fp);
}
//��дhtml�ļ���ָ��λ�ã�����fprintf��д��ע��ʹ��������