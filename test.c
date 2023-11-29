#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT_LIMIT 1000
#define DAY_COUNT 10

typedef struct Food {
    char* name;
    int weight;
    int remaining_days;
    int cals;
    int carb;
    int protein;
    int fat;
    double priority;
} food;

double priority(food foods, int *prio) {
    //  탄단지 가중치 - 10 * 칼로리/무게
	double w1 = (double)foods.cals / foods.weight;

    double priority[3];
    for (int i = 0; i < 3; i++) {
        switch (prio[i]) {
        case 1:
            priority[i] = 1.0;
            break;
        case 2:
            priority[i] = 0.7;
            break;
        case 3:
            priority[i] = 0.4;
            break;
        }
    }
	double w2 = priority[0] * foods.carb + priority[1] * foods.protein + priority[2] * foods.fat;

    return w2 - (w1 * 10);
}

food* consumeList(food* foods, int n, int* prio) {

    food consume_list[100];

    //  1. 소비기한 기본으로 먼저 정렬
    int i, j, min;
    food temp;
    int total_weight = 0;
    
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (foods[j].remaining_days < foods[min].remaining_days)
                min = j;
        }

        if (i != min) {
            temp = foods[i];
            foods[i] = foods[min];
            foods[min] = temp;
        }
    }

    //  1-1. 남은 기간이 2일 이하가 100 초과 하는지 체크
    int total = 0;
    for(int i = 0; i < n; i++){
        if (foods[i].remaining_days > 3) {
            break;
        }
        total += foods[i].weight;
    }

    //  초과한다면 용량이 큰 것부터 드랍
    if (total > 100) {
        int max_index = 0;
        for (int j = 0; j < i; j++) {
            if (foods[j].weight > foods[max_index].weight) {
                max_index = j;
            }
        }
        for (int j = max_index; j < n - 1; j++) {
            foods[j] = foods[j + 1];
        }
        break;
    }

    //  소비기한이 1남은 음식들이 있을경우 소비리스트에 추가
    if (foods[0].remaining_days == 1) {
        int k = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < foods[i].weight; j++) {

            }
            total_weight++;
            foods[i].weight--;
            //  total full
            if (total_weight == 100) {
                break;
            }
            //  food -> zero
            if (foods[i].weight == 0) {
                break;
            }

            //  no remain foods

        }
    }

    //  탄단지  - 칼/용 * 10
    // 우선순위 
    for (i = 0; i < n; i++) {
        foods[i].priority = priority(foods[i], prio);
    }
    //  우선순위대로 정렬
    int max;
    for (i = 0; i < n - 1; i++) {
        max = i;
        for (j = i + 1; j < n; j++) {
            if (foods[j].priority > foods[max].priority)
                max = j;
        }

        if (i != max) {
            temp = foods[i];
            foods[i] = foods[max];
            foods[max] = temp;
        }
    }

    int k = 0;
    for (i = 0; i < n; i++) {
        total_weight += foods[i].weight;
        if (total_weight < 100) {
            consume_list[k] = foods[i];
            k++;
        }
        else
            break;
    }
    return consume_list;
    
}

int main() {
    food foods[] = {
        {"chicken breast", 30, 10, 160, 0, 75, 25},
        {"burrito", 50, 3, 350, 60, 30, 10},
        {"yogurt", 80, 4, 100, 20, 50, 30},
        {"meetball spagetti", 100, 5, 480, 65, 25, 10},
        {"bread", 40, 2, 300, 80, 10, 10},
        {"egg", 18, 7, 25, 10, 65, 25},
        {"Kimchi Fried Rice", 150, 2, 650, 88, 7, 5 },
        {"pork cutlet", 50, 15, 425, 15, 65, 20},
        {"pizza", 110, 5, 510, 60, 5, 35},
        {"tteokbokki", 150, 11, 550, 75, 2, 23}
    };
    int arr[3] = { 1, 2, 3 };
    for (int i = 0; i < 10; i++) {
        foods[i].priority = priority(foods[i], arr);
    }
    for (int i = 0; i < 10; i++) {
        printf("%s %f\n", foods[i].name, foods[i].priority);
    }
    return 1;
}

