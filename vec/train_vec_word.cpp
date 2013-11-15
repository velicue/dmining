#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

const int maxn = 100 + 10;
const int maxl = 30 + 2;
const int maxT = 200000 + 10;
char keyword[maxn][maxl];
char divide_st[30][1024];

struct Vector
{
	int vx[maxn];
	double vy[30];
} vec[maxT];
int n_word;

bool isNum(char x) { return '0' <= x && x <= '9'; }
bool isChr(char x) { return ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z'); }

char toHchr(char x)
{
    if ('a' <= x && x <= 'z') return x - 'a' + 'A';
    return x;
}

double st2r(char * s)
{
	double dr = 10.0, e = 1.0, ans = 0.0;
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == '.') {
			dr = 1.0, e = 0.1;
		} else
		if (isNum(s[i])) {
			ans = ans * dr + e * (s[i] - '0');
			if (dr < 5.0) e = e * 0.1;
		}
	return ans;
}

// "id","tweet","state","location","s1","s2","s3","s4","s5","w1","w2","w3","w4",
//   0	   1 	   2 		3        4    5   6    7    8    9    10   11   12
// "k1","k2","k3","k4","k5","k6","k7","k8","k9","k10","k11","k12","k13","k14","k15"
//  13   14   15   16   17   18   19   20   21    22    23    24    25    26    27

void divide(char * s)
{
	int id = 0, len = 0;
	for (int i = 0; i < strlen(s) - 3; i++)
	if (s[i] == '"' && s[i + 1] == ',' && s[i + 2] == '"') {
		i += 2;
		divide_st[id][len++] = '\0';
		id ++;
		len = 0;
	} else {
		if (isNum(s[i]) || isChr(s[i]) || (id>=4 && s[i]=='.')) {
            if (isChr(s[i])) s[i] = tolower(s[i]);
            divide_st[id][len++] = s[i];
		} else {
		    divide_st[id][len++] = ' ';
		}
	}
	divide_st[id][len++] = '\0';
	// printf("%d\n", id);
	if (id != 27) {
        printf("%s %d\n", s, id);
    }
}

void calc(char * st, Vector * vec)
{
    for (int i = 0; i != n_word; i++)
    if (strcmp(keyword[i], st) == 0) {
        vec->vx[i]++;
    }
}

void Output(FILE * output_file, int id, Vector * vec)
{
    fprintf(output_file, "%d", id);
    for (int i = 0; i != n_word; i++) fprintf(output_file, " %d", vec->vx[i]);
    for (int i = 0; i != 5 + 4 + 15; i++) fprintf(output_file, " %.3lf", vec->vy[i]);
    fprintf(output_file, "\n");
}

void Debug_divide()
{
    for (int i = 0; i != 28; i++) {
        printf("%s", divide_st[i]);
        if (i > 4) printf(" %.3f", st2r(divide_st[i]));
        printf("\n");
    }
    printf("------------\n");
}

int main()
{
	char x[2000 + 10];
	FILE * fp = fopen("important_word.csv_dm", "r");
	for (n_word = 0; fscanf(fp, "%s", keyword[n_word]) != EOF; n_word++) {
        printf("%s\n", keyword[n_word]);
	}
	fclose(fp);

	FILE * input_file = fopen("train.csv", "r");
	FILE * output_file = fopen("train_word_vec.out", "w");
	fprintf(output_file, "%d %d\n", n_word, 5 + 4 + 15);
	int m = 0;
	while (fgets(x, 2000, fp)) {
		divide(x);
		// Debug_divide();
		memset(&vec[m], 0, sizeof(vec[m]));
		int j = 0;
		for (int i = 0; i < strlen(divide_st[1]); i++) {
			if (isNum(divide_st[1][i]) || isChr(divide_st[1][i])) {
                x[j++] = divide_st[1][i];
			} else {
			    x[j++] = '\0';
			    calc(x, vec + m);
                j = 0;
			}
		}

		for (int i = 4; i <= 12; i++) vec[m].vy[i - 4] = 0.0;
		for (int i = 13; i <= 27; i++) vec[m].vy[i - 4] = st2r(divide_st[i]);
		Output(output_file, st2r(divide_st[0]), &vec[m]);
		m ++;
	}
	fclose(input_file);
    fclose(output_file);

	return 0;
}
