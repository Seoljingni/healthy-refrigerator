#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_FOOD_ITEMS 100     //입력할 수 있는 최대 음식의 개수
#define MAX_NAME_LENGTH 50     //음식 이름이 최대 길이


int total_fooditem = 0;              //현재 냉장고에 남아있는 음식의 개수
int total_selectitem = 0;            //섭취할 음식의 개수
int first_total_fooditem = 0;        //처음 냉장고에 있는 음식의 개수


typedef struct {                              //냉장고에 담을 음식의 구조체
    char name[MAX_NAME_LENGTH];   //이름
    int weight;      //용량
    int expiration;     //유통기한
    float calories;     //칼로리
    int carbo;       //탄수화물
    int protein;      //단백질
    int fat;         //지방
    double value;        //가중치
} FoodItem;


typedef struct {                            //하루에 섭취할 음식의 구조체
    FoodItem* choose_food;       //섭취 음식
    int intake_weight;        //섭취 용량
    float intake_calories;       //섭취 칼로리
} SelectItem;



void fooditem_swap(FoodItem* a, FoodItem* b)        //두 개의 음식 포인터 변수를 서로 바꾸는 함수
{
    FoodItem temp = *a;
    *a = *b;
    *b = temp;
}



void load_food_items(FILE* file, FoodItem food_items[], int* num_items) {         //파일 형태로 음식을 받고 구조체에 저장하는 함수
    *num_items = 0;
    while (fscanf(file, "%99[^,],%d,%d,%f,%d,%d,%d\n",
        food_items[*num_items].name, &food_items[*num_items].weight, &food_items[*num_items].expiration,
        &food_items[*num_items].calories, &food_items[*num_items].carbo,
        &food_items[*num_items].protein, &food_items[*num_items].fat) == 7) {
        (*num_items)++;
        total_fooditem++; 
        first_total_fooditem++;        //음식을 입력받을 때마다 현재 음식의 개수와 처음 음식의 개수를 모두 증가시킴
    }
}



void set_value(FoodItem* food_items, int carbo_prior, int protein_prior, int fat_prior) {           //음식 구조체의 value(가중치)를 할당하는 함수

    for (int i = 0; i < total_fooditem; i++) {                 //가중치 계산식에 따라 가중치를 계산한 후 이를 food_items의 value에 할당

        if (carbo_prior == 1 && protein_prior == 2 && fat_prior == 3)
            food_items[i].value = (food_items[i].carbo * 1.0) + (food_items[i].protein * 0.7) + (food_items[i].fat * 0.4) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;

        else if (carbo_prior == 1 && protein_prior == 3 && fat_prior == 2)
            food_items[i].value = (food_items[i].carbo * 1.0) + (food_items[i].protein * 0.4) + (food_items[i].fat * 0.7) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;

        else if (carbo_prior == 2 && protein_prior == 1 && fat_prior == 3)
            food_items[i].value = (food_items[i].carbo * 0.7) + (food_items[i].protein * 1.0) + (food_items[i].fat * 0.4) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;

        else if (carbo_prior == 2 && protein_prior == 3 && fat_prior == 1)
            food_items[i].value = (food_items[i].carbo * 0.4) + (food_items[i].protein * 1.0) + (food_items[i].fat * 0.7) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;

        else if (carbo_prior == 3 && protein_prior == 1 && fat_prior == 2)
            food_items[i].value = (food_items[i].carbo * 0.7) + (food_items[i].protein * 0.4) + (food_items[i].fat * 1.0) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;

        else if (carbo_prior == 3 && protein_prior == 2 && fat_prior == 1)
            food_items[i].value = (food_items[i].carbo * 0.4) + (food_items[i].protein * 0.7) + (food_items[i].fat * 1.0) - ((roundf(food_items[i].calories / (float)food_items[i].weight * 100)) / 100) * 10;
    }

}



void sort_item(FoodItem* food_items, FoodItem* sort_list[]) {                   //가중치에 따라 음식을 내림차순으로 정렬하는 함수

    int m = 0;

    for (int i = 0; i < first_total_fooditem; i++)                 //음식의 이름이 NULL이 아니라면 food_item의 음식을 sort_list에 할당함
        if (strcmp(food_items[i].name, "NULL") != 0) {
            sort_list[m] = &food_items[i];
            m++;
        }

    total_fooditem = m;             //sort_list에 할당된 개수만큼 현재 남아있는 음식의 개수가 정해짐

    for (int j = 0; j < m; j++) {                //가중치가 큰 순서대로 정렬 (selection sort 방식 사용)
        int temp = j;
        for (int k = j + 1; k < m; k++) {
            if (sort_list[temp]->value <= sort_list[k]->value)
                temp = k;
        }
        fooditem_swap(sort_list[temp], sort_list[j]);
    }

}



void select(FoodItem* sort_list[], SelectItem select_item[]) {                 //greedy 알고리즘에 따라 섭취할 음식을 선택하는 함수

    int remain_weight = 100;       //하루에 섭취 가능한 용량은 100으로 고정
    int t = 0;

    for (int i = 0; i < total_fooditem; i++) {              //첫 반복문에서는 유통기한이 1일 남은 음식을 먼저 탐색

        if (sort_list[i]->expiration <= 1) {
            select_item[t].choose_food = sort_list[i];     //sort_list의 배열을 처음부터 탐색하면서 select_item에 넣음
            if (sort_list[i]->weight <= remain_weight) {         //sort_list의 음식 용량이 현재 남은 용량보다 작을 경우
                select_item[t].intake_weight = sort_list[i]->weight;
                select_item[t].intake_calories = sort_list[i]->calories;
                sort_list[i]->weight = 0;
            }
            else {                //sort_list의 음식 용량이 현재 남은 용량보다 클 경우
                select_item[t].intake_weight = remain_weight;
                select_item[t].intake_calories = ((roundf(sort_list[i]->calories / (float)sort_list[i]->weight * 100)) / 100) * remain_weight;
                sort_list[i]->weight = sort_list[i]->weight - select_item[t].intake_weight;
                sort_list[i]->calories = sort_list[i]->calories - select_item[t].intake_calories;
            }
            remain_weight = remain_weight - select_item[t].intake_weight;
            t++;
            if (remain_weight == 0) break;       //남은 용량이 0이 되면 선택을 끝내기 위해 반복문 탈출
        }
    }

    for (int i = 0; i < total_fooditem; i++) {                //두 번째 반복문에서는 가중치에 따른 우선순위로 음식을 선택 (유통기한이 2일 이상 남은 음식)

        if (sort_list[i]->expiration > 1) {
            if (sort_list[i]->expiration <= 2 && sort_list[i]->weight > 100)     //유통기한이 2일 이하로 남았고 용량이 100일 이상 남은 음식은 진행하지 않고 건너뜀
                continue;
            else {
                select_item[t].choose_food = sort_list[i];    //sort_list의 배열을 처음부터 탐색하면서 select_item에 넣음
                if (sort_list[i]->weight <= remain_weight) {        //sort_list의 음식 용량이 현재 남은 용량보다 작을 경우
                    select_item[t].intake_weight = sort_list[i]->weight;
                    select_item[t].intake_calories = sort_list[i]->calories;
                    sort_list[i]->weight = 0;
                }
                else {              //sort_list의 음식 용량이 현재 남은 용량보다 클 경우
                    select_item[t].intake_weight = remain_weight;           
                    select_item[t].intake_calories = ((roundf(sort_list[i]->calories / (float)sort_list[i]->weight * 100)) / 100) * remain_weight;
                    sort_list[i]->weight = sort_list[i]->weight - select_item[t].intake_weight;
                    sort_list[i]->calories = sort_list[i]->calories - select_item[t].intake_calories;
                }
                remain_weight = remain_weight - select_item[t].intake_weight;       //남은 용량을 선택한 음식의 섭취 용량만큼 감소
                t++;
                if (remain_weight == 0) break;       //남은 용량이 0이 되면 선택을 끝내기 위해 반복문 탈출
            }
        }
    }

    total_selectitem = t;      //음식이 선택될 때마다 증가하는 t의 값을 total_selectitem에 할당

}



void print_selectitem(SelectItem select_item[]) {                            //선택한 음식을 출력하는 함수

    for (int i = 0; i < total_selectitem; i++) {
        if (i == total_selectitem - 1) {         //마지막 item 출력할 때 , 제외
            printf("%s %d ", select_item[i].choose_food->name, select_item[i].intake_weight);
        }
        else {
            printf("%s %d, ", select_item[i].choose_food->name, select_item[i].intake_weight);
        }
    }
}



void print_calories(SelectItem select_item[]) {                              //선택한 음식의 칼로리 총량을 출력하는 함수

    float total_calories = 0;

    for (int i = 0; i < total_selectitem; i++) {        //선택된 음식의 섭취 칼로리를 전부 더해서 칼로리 총량을 계산
        total_calories = total_calories + select_item[i].intake_calories;
    }
    printf("Total calories: %.2f", total_calories);
}



void update_item(FoodItem food_items[]) {                                    //선택이 끝나고 음식을 업데이트하는 함수 (유통기한 감소, 음식 제거)

    for (int i = 0; i < first_total_fooditem; i++) {       
        food_items[i].expiration--;                   //모든 음식의 유통기한을 1 감소
        if (food_items[i].expiration == 0 || food_items[i].weight == 0 || (food_items[i].expiration <= 2 && food_items[i].weight > 100))
            strcpy(food_items[i].name, "NULL");                         //유통기한이 1일 되거나, 용량이 0이 되거나, 유통기한이 2일이하이고 용량이 100 초과하면 item의 이름을 NULL로 함
    }
}



int print_leftitem(FoodItem food_items[]) {                                 //남아있는 음식의 이름을 출력하는 함수
    int flag = 0;       //남은 음식 유무 확인

    printf("Leftovers: ");

    for (int i = 0; i < first_total_fooditem; i++) {
        if (strcmp(food_items[i].name, "NULL") != 0) {         //이름이 NULL이라면 출력하지 않음 (이미 제거된 음식)
            printf("%s, ", food_items[i].name);
            flag++;
        }
    }

    if (flag == 0) {        //flag가 1이면 남은 음식이 없으므로 NONE 출력후 1 반환
        printf("NONE");
        return 1;
    }
    return 0; // 남은 음식 존재하면 0 반환
}



int main() {

    FILE* input_file = fopen("C:/term project/input.txt", "r");

    if (input_file == NULL) {                  //입력 파일이 존재하지 않을 경우 에러 표시
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    FoodItem food_items[MAX_FOOD_ITEMS];
    SelectItem select_item[MAX_FOOD_ITEMS];
    FoodItem* sort_list[MAX_FOOD_ITEMS];

    int num_items;
    int day = 1;
    int value1, value2, value3;


    load_food_items(input_file, food_items, &num_items);

    printf("Place in the order of importance: 1 carbohydrates, 2 proteins, and 3 fats.\n");
    printf("(ex: 2 1 3) -> This means that it is weighted in the order of protein, carbohydrates, and fat.\n");


    while (1) {

        printf("day:%d", day);
        printf("\n");


        scanf("%d %d %d", &value1, &value2, &value3);


        if (value1 == 1 && value2 == 2 && value3 == 3)           //입력값에 따라 서로 다르게 가중치를 할당함
            set_value(food_items, 1, 2, 3);
        else if (value1 == 1 && value2 == 3 && value3 == 2)
            set_value(food_items, 1, 3, 2);
        else if (value1 == 2 && value2 == 1 && value3 == 3)
            set_value(food_items, 2, 1, 3);
        else if (value1 == 2 && value2 == 3 && value3 == 1)
            set_value(food_items, 2, 3, 1);
        else if (value1 == 3 && value2 == 1 && value3 == 2)
            set_value(food_items, 3, 1, 2);
        else if (value1 == 3 && value2 == 2 && value3 == 1)
            set_value(food_items, 3, 2, 1);
        else {
            printf("wrong value!");
            exit(1);
        }


        sort_item(food_items, sort_list);
        select(sort_list, select_item);
        print_selectitem(select_item);
        printf("\n");
        print_calories(select_item);
        printf("\n");
        update_item(food_items);
        int flag = print_leftitem(food_items);      //남은 음식이 없으면 flag 1로 설정되어 반환
        printf("\n\n");
        day++;

        if (flag == 1) {        //flag가 1이면 반복문 종료
            break;
        }

    }

    printf("The refrigerator is empty!\n\n");

    fclose(input_file);

    return 0;
}