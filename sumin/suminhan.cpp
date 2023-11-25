#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD_ITEMS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int expiration;
    int weight;
    int calories;
    int carbo;
    int protein;
    int fat;
    double value;
} FoodItem;


void load_food_items(FILE* file, FoodItem food_items[], int* num_items) {
    *num_items = 0;
    while (fscanf(file, "%s %d %d %d %d %d %d", food_items[*num_items].name, &food_items[*num_items].expiration, &food_items[*num_items].weight,
        &food_items[*num_items].calories, &food_items[*num_items].carbo,
        &food_items[*num_items].protein, &food_items[*num_items].fat) == 7) {
        (*num_items)++;
    }
}


void set_value(FoodItem* food_items, int carbo_prior, int protein_prior, int fat_prior) {

    for (int i = 0; i < 100; i++) {

        if (carbo_prior == 1 && protein_prior == 2 && fat_prior == 3)
            food_items[i].value = (food_items[i].carbo * 1.0) + (food_items[i].protein * 0.7) + (food_items[i].fat * 0.4) - ((food_items[i].calories / food_items[i].weight) * 10);

        else if (carbo_prior == 1 && protein_prior == 3 && fat_prior == 2)
            food_items[i].value = (food_items[i].carbo * 1.0) + (food_items[i].protein * 0.4) + (food_items[i].fat * 0.7) - ((food_items[i].calories / food_items[i].weight) * 10);

        else if (carbo_prior == 2 && protein_prior == 1 && fat_prior == 3)
            food_items[i].value = (food_items[i].carbo * 0.7) + (food_items[i].protein * 1.0) + (food_items[i].fat * 0.4) - ((food_items[i].calories / food_items[i].weight) * 10);

        else if (carbo_prior == 2 && protein_prior == 3 && fat_prior == 1)
            food_items[i].value = (food_items[i].carbo * 0.7) + (food_items[i].protein * 0.4) + (food_items[i].fat * 1.0) - ((food_items[i].calories / food_items[i].weight) * 10);

        else if (carbo_prior == 3 && protein_prior == 1 && fat_prior == 2)
            food_items[i].value = (food_items[i].carbo * 0.4) + (food_items[i].protein * 1.0) + (food_items[i].fat * 0.7) - ((food_items[i].calories / food_items[i].weight) * 10);

        else if (carbo_prior == 3 && protein_prior == 2 && fat_prior == 1)
            food_items[i].value = (food_items[i].carbo * 0.4) + (food_items[i].protein * 0.7) + (food_items[i].fat * 1.0) - ((food_items[i].calories / food_items[i].weight) * 10);
    }

}



int main() {

    FILE* input_file = fopen("C:/term project/input.txt", "r");

    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    FoodItem food_items[MAX_FOOD_ITEMS];
    int num_items;

    load_food_items(input_file, food_items, &num_items);


    for (int i = 0; i < 4; i++) {
        printf("%s %d %d %d %d %d %d\n", food_items[i].name, food_items[i].expiration, food_items[i].calories, food_items[i].weight, food_items[i].carbo, food_items[i].protein, food_items[i].fat);
    }

    set_value(food_items, 1, 2, 3);

    for (int i = 0; i < 4; i++) {
        printf("%s %d %d %d %d %d %d %f\n", food_items[i].name, food_items[i].expiration, food_items[i].calories, food_items[i].weight, food_items[i].carbo, food_items[i].protein, food_items[i].fat, food_items[i].value);
    }

    fclose(input_file);

    return 0;
}




