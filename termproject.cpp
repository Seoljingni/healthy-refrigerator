#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_FOOD_ITEMS 100
#define MAX_NAME_LENGTH 50


int total_fooditem = 0;              //���� ����� �����ִ� ������ ����
int total_selectitem = 0;            //������ ������ ����
int first_total_fooditem = 0;        //ó�� ����� �ִ� ������ ����


typedef struct {                              //����� ���� ������ ����ü
    char name[MAX_NAME_LENGTH];
    int weight;
    int expiration;
    float calories;
    int carbo;
    int protein;
    int fat;
    double value;
} FoodItem;


typedef struct {                            //�Ϸ翡 ������ ������ ����ü
    FoodItem* choose_food;
    int intake_weight;
    float intake_calories;
} SelectItem;



void fooditem_swap(FoodItem* a, FoodItem* b)        //�� ���� ���� ������ ������ ���� �ٲٴ� �Լ�
{
    FoodItem temp = *a;
    *a = *b;
    *b = temp;
}



void load_food_items(FILE* file, FoodItem food_items[], int* num_items) {         //���� ���·� ������ �ް� ����ü�� �����ϴ� �Լ�
    *num_items = 0;
    while (fscanf(file, "%99[^,],%d,%d,%f,%d,%d,%d\n",
        food_items[*num_items].name, &food_items[*num_items].weight, &food_items[*num_items].expiration,
        &food_items[*num_items].calories, &food_items[*num_items].carbo,
        &food_items[*num_items].protein, &food_items[*num_items].fat) == 7) {
        (*num_items)++;
        total_fooditem++;
        first_total_fooditem++;
    }
}



void set_value(FoodItem* food_items, int carbo_prior, int protein_prior, int fat_prior) {           //���� ����ü�� value(����ġ)�� �Ҵ��ϴ� �Լ�

    for (int i = 0; i < total_fooditem; i++) {

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



void sort_item(FoodItem* food_items, FoodItem* sort_list[]) {                   //����ġ�� ���� ������ ������������ �����ϴ� �Լ�

    int m = 0;

    for (int i = 0; i < first_total_fooditem; i++)
        if (strcmp(food_items[i].name, "NULL") != 0) {
            sort_list[m] = &food_items[i];
            m++;
        }

    total_fooditem = m;

    for (int j = 0; j < m; j++) {
        int temp = j;
        for (int k = j + 1; k < m; k++) {
            if (sort_list[temp]->value <= sort_list[k]->value)
                temp = k;
        }
        fooditem_swap(sort_list[temp], sort_list[j]);
    }

}



void select(FoodItem* sort_list[], SelectItem select_item[]) {                 //greedy �˰��� ���� ������ ������ �����ϴ� �Լ�

    int remain_weight = 100;
    int t = 0;

    for (int i = 0; i < total_fooditem; i++) {              //ù �ݺ��������� ��������� 1�� ���� ������ ���� Ž��

        if (sort_list[i]->expiration <= 1) {
            select_item[t].choose_food = sort_list[i];
            if (sort_list[i]->weight <= remain_weight) {
                select_item[t].intake_weight = sort_list[i]->weight;
                select_item[t].intake_calories = sort_list[i]->calories;
                sort_list[i]->weight = 0;
            }
            else {
                select_item[t].intake_weight = remain_weight;
                select_item[t].intake_calories = ((roundf(sort_list[i]->calories / (float)sort_list[i]->weight * 100)) / 100) * remain_weight;
                sort_list[i]->weight = sort_list[i]->weight - select_item[t].intake_weight;
                sort_list[i]->calories = sort_list[i]->calories - select_item[t].intake_calories;
            }
            remain_weight = remain_weight - select_item[t].intake_weight;
            t++;
            if (remain_weight == 0) break;
        }
    }

    for (int i = 0; i < total_fooditem; i++) {                //�� ��° �ݺ��������� ����ġ�� ���� �켱������ ������ ����

        if (sort_list[i]->expiration > 1) {
            if (sort_list[i]->expiration <= 2 && sort_list[i]->weight > 100)
                continue;
            else {
                select_item[t].choose_food = sort_list[i];
                if (sort_list[i]->weight <= remain_weight) {
                    select_item[t].intake_weight = sort_list[i]->weight;
                    select_item[t].intake_calories = sort_list[i]->calories;
                    sort_list[i]->weight = 0;
                }
                else {
                    select_item[t].intake_weight = remain_weight;
                    select_item[t].intake_calories = ((roundf(sort_list[i]->calories / (float)sort_list[i]->weight * 100)) / 100) * remain_weight;
                    sort_list[i]->weight = sort_list[i]->weight - select_item[t].intake_weight;
                    sort_list[i]->calories = sort_list[i]->calories - select_item[t].intake_calories;
                }
                remain_weight = remain_weight - select_item[t].intake_weight;
                t++;
                if (remain_weight == 0) break;
            }
        }
    }

    total_selectitem = t;

}



void print_selectitem(SelectItem select_item[]) {                            //������ ������ ����ϴ� �Լ�
    
    for (int i = 0; i < total_selectitem; i++) {
        printf("%s %d, ", select_item[i].choose_food->name, select_item[i].intake_weight);
    }
}



void print_calories(SelectItem select_item[]) {                              //������ ������ Į�θ� �ѷ��� ����ϴ� �Լ�

    float total_calories = 0;

    for (int i = 0; i < total_selectitem; i++) {
        total_calories = total_calories + select_item[i].intake_calories;
    }
    printf("Total calories: %.2f", total_calories);
}



void update_item(FoodItem food_items[]) {                                    //������ ������ ������ ������Ʈ�ϴ� �Լ� (������� ����, ���� ����)

    for (int i = 0; i < first_total_fooditem; i++) {
        food_items[i].expiration--;
        if (food_items[i].expiration == 0 || food_items[i].weight == 0 || (food_items[i].expiration <= 2 && food_items[i].weight > 100))
            strcpy(food_items[i].name, "NULL");
    }
}



void print_leftitem(FoodItem food_items[]) {                                 //�����ִ� ������ �̸��� ����ϴ� �Լ�

    printf("Leftovers: ");

    for (int i = 0; i < first_total_fooditem; i++) {
        if (strcmp(food_items[i].name, "NULL") != 0)
            printf("%s, ", food_items[i].name);
    }
}

    
   
int main() {

    FILE* input_file = fopen("C:/term project/input.txt", "r");

    if (input_file == NULL) {
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

    
    for (int i = 0; i<7; i++) {

        printf("day:%d", day);
        printf("\n");


        scanf("%d %d %d", &value1, &value2, &value3);


        if (value1 == 1 && value2 == 2 && value3 == 3)
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
        print_leftitem(food_items);
        printf("\n\n");
        day++;

    }
   

    fclose(input_file);

    return 0;
}



