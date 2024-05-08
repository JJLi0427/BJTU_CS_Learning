#include "writehtml.h"

void writehtml(char* locate, struct List L[6]) {
    FILE* fp = fopen(locate, "w+");

    fprintf(fp, "<!DOCTYPE html>\n<head>\n");
    //fprintf(fp,"    <meta charset=\"UTF-8\">\n");
    fprintf(fp, "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
    fprintf(fp, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    //网页头部
    fprintf(fp, "    <title>结果网页</title>\n</head>\n<body>\n    <table border=\"1\">\n");
    //网页标题
    fprintf(fp, "        <caption>统计结果</caption>\n        <tr>\n");
    //表单标题

    for (int i = 0; i < 6; i++) {
        fprintf(fp, "            <th>%s</th>\n", L[i].name);
    }
    fprintf(fp, "</tr>\n<tr>\n");
    //换行输出数据
    for (int i = 0; i < 6; i++) {
        fprintf(fp, "            <td>%d</td>\n", L[i].num);
    }

    fprintf(fp, "        </tr>\n    </table>\n</body>\n</html>");
    fclose(fp);
}
//编写html文件到指定位置，利用fprintf编写，注意使用了缩进