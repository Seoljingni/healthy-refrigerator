#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 음식 구조체 정의
typedef struct {
    char name[20]; // 음식 이름
    int weight; // 음식 무게
    int calorie; // 음식 칼로리
    float cal_per_weight; // 칼로리/무게
    int selected; // 선택 여부
    int expiry; // 유통기한
    int carb; // 탄수화물
    int protein; // 단백질
    int fat; // 지방
    float priority; // 가중치
} Food;

// 가중치에 따른 정렬 함수
int compare_priority(const void* a, const void* b) {
    Food* foodA = (Food*)a;
    Food* foodB = (Food*)b;
    return foodA->priority < foodB->priority ? 1 : -1;
}

void get_food(Food* fridge, int* fridge_capacity, int* total_calorie, int* max_weight_per_turn) {
    for (int i = 0; i < 10; i++) {
        // 냉장고 용량이 음식 무게보다 적거나, 한 번에 꺼낼 수 있는 용량이 100을 초과하면 건너뜀
        if (*fridge_capacity < fridge[i].weight || fridge[i].weight > *max_weight_per_turn) continue;

        fridge[i].selected = 1; // 음식 선택
        *fridge_capacity -= fridge[i].weight; // 냉장고 용량 감소
        *total_calorie += fridge[i].calorie; // 총 칼로리 증가

        // 한 번에 꺼낼 수 있는 최대 용량 갱신
        *max_weight_per_turn -= fridge[i].weight;
    }
}

int main() {
    Food fridge[10]; // 냉장고에 있는 음식들
    int fridge_capacity = 1000; // 냉장고 용량
    int total_calorie = 0; // 총 칼로리

    // 음식 정보 초기화
    Food food1 = { "chicken breast", 30, 160, 0, 0, 10, 0, 30, 2, 0 };
    Food food2 = { "buritto", 50, 350, 0, 0, 3, 45, 15, 10, 0 };
    Food food3 = { "yogurt", 80, 100, 0, 0, 4, 15, 10, 5, 0 };
    Food food4 = { "meetball spagetti", 100, 480, 0, 0, 5, 60, 20, 15, 0 };
    Food food5 = { "bread", 40, 300, 0, 0, 2, 55, 10, 5, 0 };
    Food food6 = { "egg", 18, 140, 0, 0, 7, 1, 12, 10, 0 };
    Food food7 = { "Kimchi Fried Rice", 150, 650, 0, 0, 2, 70, 15, 12, 0 };
    Food food8 = { "pork cutlet", 50, 425, 0, 0, 15, 15, 65, 20, 0 };
    Food food9 = { "pizza", 110, 510, 0, 0, 5, 0, 60, 5, 35 };
    Food food10 = { "tteokbokki", 150, 550, 0, 0, 11, 0, 75, 2, 23 };

    fridge[0] = food1;
    fridge[1] = food2;
    fridge[2] = food3;
    fridge[3] = food4;
    fridge[4] = food5;
    fridge[5] = food6;
    fridge[6] = food7;
    fridge[7] = food8;
    fridge[8] = food9;
    fridge[9] = food10;

    float arr[100];

    // 각 음식의 용량당 칼로리와 탄단지 가중치 계산
    for (int i = 0; i < 10; i++) {
        fridge[i].cal_per_weight = (float)fridge[i].calorie / fridge[i].weight;
        arr[i] = (fridge[i].carb * 1.0 + fridge[i].protein * 0.7 + fridge[i].fat * 0.4);
        fridge[i].priority = (fridge[i].carb * 1.0 + fridge[i].protein * 0.7 + fridge[i].fat * 0.4) - (fridge[i].cal_per_weight * 10);
    }

    printf("\n\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2lf\n", arr[i]);
    }

    // 가중치에 따라 정렬
    qsort(fridge, 10, sizeof(Food), compare_priority);

    // 한 번에 꺼낼 수 있는 최대 용량
    int max_weight_per_turn = 100;

    while (fridge_capacity > 0 && max_weight_per_turn > 0) {
        get_food(fridge, &fridge_capacity, &total_calorie, &max_weight_per_turn);
    }

    // 선택된 음식과 총 칼로리 출력
    for (int i = 0; i < 10; i++) {
        if (fridge[i].selected) {
            printf("선택된 음식: %s, 무게: %d, 칼로리: %d, 가중치: %.2f, 탄수화물: %d, 단백질: %d, 지방: %d, 용량당 칼로리: %.2f\n", fridge[i].name, fridge[i].weight, fridge[i].calorie, fridge[i].priority, fridge[i].carb, fridge[i].protein, fridge[i].fat, fridge[i].cal_per_weight);
        }
    }
    printf("총 칼로리: %d\n", total_calorie);

    // 남은 음식 이름 출력
    for (int i = 0; i < 10; i++) {
        if (!fridge[i].selected) {
            printf("남은 음식: %s, 가중치: %.2f, 탄수화물: %d, 단백질: %d, 지방: %d, 용량당 칼로리: %.2f\n", fridge[i].name, fridge[i].priority, fridge[i].carb, fridge[i].protein, fridge[i].fat, fridge[i].cal_per_weight);
        }
    }

    return 0;
}
