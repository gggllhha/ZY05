#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
const int N = 100005;
const double MAX = 10e100;
const double eps = 0.00001;
typedef struct Point {
	double x;
	double y;
    int index;
}Point;
Point a[N], b[N], c[N];
double Distance(Point a, Point b) {                                 /*����֮�����*/
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int cmp_x(const void* p, const void* q)                               /*����x������*/
{
    double temp = ((Point*)p)->x - ((Point*)q)->x;
    if (temp > 0)
        return 1;
    else if (fabs(temp) < eps)
        return 0;
    else
        return -1;
}
int cmp_y(const void* p, const void* q)                             /*����y������*/
{
    double temp = ((Point*)p)->y - ((Point*)q)->y;
    if (temp > 0)
        return 1;
    else if (fabs(temp) < eps)
        return 0;
    else
        return -1;
}
double min(double a, double b) {                        /*��Сֵ����*/
	return a > b ? b : a;
}

int merge(Point p[], Point q[], int s, int m, int t)
{
    int i, j, k;
    for (i = s, j = m + 1, k = s; i <= m && j <= t;)
    {
        if (q[i].y > q[j].y)
            p[k++] = q[j], j++;
        else
            p[k++] = q[i], i++;
    }
    while (i <= m)
        p[k++] = q[i++];
    while (j <= t)
        p[k++] = q[j++];
    memcpy(q + s, p + s, (t - s + 1) * sizeof(p[0]));
    return 0;
}
double closest(Point a[], Point b[], Point c[], int p, int q) {               /*������Ծ��뺯��*/
    if (q - p == 1)                                             /*ʣ��������*/
        return Distance(a[p], a[q]);
    if (q - p == 2)                                             /*ʣ��������*/
    {
        double x1 = Distance(a[p], a[q]);
        double x2 = Distance(a[p + 1], a[q]);
        double x3 = Distance(a[p], a[p + 1]);
        if (x1 < x2 && x1 < x3)
            return x1;
        else if (x2 < x3)
            return x2;
        else
            return x3;
    }
    int m = (p + q) / 2;                                      /*����m*/
    int i, j, k;
    double d1, d2;
    for (i = p, j = p, k = m + 1; i <= q; i++)        /*�������Ұ���*/
        if (b[i].index <= m)                  
            c[j++] = b[i];                             /*���*/
        else
            c[k++] = b[i];                             /*�Ұ�*/
    d1 = closest(a, c, b, p, m);       /*�ݹ��������߷ֱ�����С*/
    d2 = closest(a, c, b, m + 1, q);
    double dm = min(d1, d2);
    merge(b, c, p, m, q);              /*��c�������Һϲ���b����*/
    for (i = p, k = p; i <= q; i++)      /*���ֳ�����m���Ҳ�����dm�Ĳ���*/
        if (fabs(b[i].x - b[m].x) < dm)
            c[k++] = b[i];
    for (i = p; i < k; i++)                                         /*Ѱ������m�����Ƿ��ɾ����С�ĵ��*/
        for (j = i + 1; j < k && c[j].y - c[i].y < dm; j++)
        {
            double temp = Distance(c[i], c[j]);
            if (temp < dm)
                dm = temp;
        }
    return dm;
}
int main(void) {
    int n, i;
    double d;
    scanf("%d", &n);
    while (n)
    {
        for (i = 0; i < n; i++)
            scanf("%lf%lf", &(a[i].x), &(a[i].y));
        qsort(a, n, sizeof(a[0]), cmp_x);
        for (i = 0; i < n; i++)
            a[i].index = i;
        memcpy(b, a, n * sizeof(a[0]));
        qsort(b, n, sizeof(b[0]), cmp_y);
        d = closest(a, b, c, 0, n - 1);
        printf("%.2lf\n", d);
        scanf("%d", &n);
    }
	system("pause");
}