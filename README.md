# 💪 Healthy Refrigerator
## Algorithm Term Project Team 9
### ✅ Contents
1. [Overview](#👀-Overview)   
2. [Problem Story](#📝-Problem-Story)   
3. [Problem Statement](#✔️-Problem-Statement)   
4. [I/O Format](#🔠-I/O-Format)
<div align="center">

## 👀 Overview

**Project Name**
</br>Healthy Refrigerator

**Team Member**
<div align="center">


| **🧑🏻‍💻곽태일** | **🧑🏻‍💻김건** | **👩🏻‍💻설지은** | **🧑🏻‍💻한수민** | **🧑🏻‍💻허지행** |
| :------: |  :------: | :------: | :------: | :------: |
| 201935007 |  202234859 | 202234901 | 202234944 | 202234948 |
| [<img src="https://avatars.githubusercontent.com/u/121069779?v=4" height=150 width=150> <br/> @dade1011](https://github.com/dade1011) | [<img src="https://avatars.githubusercontent.com/u/104978709?v=4" height=150 width=150> <br/> @lc__lc1m](https://github.com/kimkhann) | [<img src="https://avatars.githubusercontent.com/u/101654488?v=4" height=150 width=150> <br/> @Seoljingni](https://github.com/Seoljingni) | [<img src="https://avatars.githubusercontent.com/u/113187890?v=4" height=150 width=150> <br/> @Ruila](https://github.com/RustTale) | [<img src="https://avatars.githubusercontent.com/u/105281922?v=4" height=150 width=150> <br/> @HIT-haeng](https://github.com/JiHaneggg)

</div>

**Project Duration**</br>
2023.11.10~2023.12.04

**Project Language**
</br>Java

## 📝 Problem Story
Y, a current student at Gachon University living in Bokjeong-dong,
found it inconvenient to daily plan meals and check expiration dates.</br>
To address this, Y invested in an artificial intelligence refrigerator.

Users have the option to input, in sequential order, the types of nutrients for which they want to prioritize the application of weights each day.

This refrigerator is equipped with a feature that suggests a diet for each meal, maximizing the intake of desired nutrients while minimizing calorie consumption relative to the capacity of food that can be taken out at once from the user's refrigerator.

Implement an algorithm for the AI in this refrigerator to minimize the disposal of expired food in Y's refrigerator as much as possible.


## ✔️ Problem Statement
<div align="left">

- **Input is received in file format.**

- **The total capacity of the refrigerator is limited to 1000.**
     - The amount of food added cannot exceed the total capacity and may not fill the refrigerator to its maximum capacity.

- **The user always consumes 100 units of food daily.**
     - When entering the **initial input**, the <u>total amount of food with an expiration period of 2 days or less cannot exceed 100</u>.
     - Foods with an expiration period of 1 day are prioritized for consumption. 
         - *If the total amount of food with an expiration period of 1 day exceeds 100*,
               <u>items with lower weights</u> are discarded first.

- **Weight Calculation Method**
     - Calculate the weight of <u>calories per unit of food capacity & daily input of weight rankings</u> for each food element.
     - Calories/capacity *(rounded to two decimal places)*
     - <u>*1st priority element* X 1.0 + *2nd priority element* X 0.7 + *3rd priority element* X 0.4</u>
     - <u>(Weight Calculation for Macronutrients) - (Calories per unit of capacity * 10)</u>

- **If the remaining food is less than the maximum capacity that can be taken out,
consume all remaining food, output the result, and terminate the program.**
</div>

## 🔠 I/O Format
<div align="left">

### Input
- **Received input in file format**
- **Input file format** 

`Food Name, Weight, Expiration Date, Calories, Carbohydrates Content, Protein Content, Fat Content`
- **Every day, prioritize the intake of carbohydrates, protein, and fat content.**
### Output
- **Print the name of the consumed food and the total calories consumed for each day.**
- **Output a list of the remaining food names in the refrigerator for each day.**
### Example

```
//Input file
chicken breast, 30, 10, 160, 0, 75, 25
buritto, 50, 3, 350, 60, 30, 10
yogurt, 80, 4, 100, 20, 50, 30
meetball spagetti, 100, 5, 480, 65, 25, 10
bread, 40, 2, 300, 80, 10, 10
egg, 18, 7, 25, 10, 65, 25
Kimchi Fried Rice, 150, 2, 650, 88, 7, 5 
pork cutlet, 50, 15, 425, 15, 65, 20
pizza, 110, 5, 510, 60, 5, 35
tteokbokki, 150, 11, 550, 75, 2, 23
```

```
//Day by day input
1 2 3
2 3 1
3 2 1
1 3 2
2 1 3
3 1 2
```

```
//Expected output
Day: 1
yogurt, egg, tteokbokki
Total calories: 132.34
Leftovers: chicken breast, buritto, meetball spagetti, bread, pork cutlet, pizza, tteokbokki

Day: 2
bread, chicken breast, tteokbokki
Total calories: 570.1
Leftovers: buritto, meetball spagetti, pork cutlet, pizza, tteokbokki

Day: 3
buritto, tteokbokki
Total calories: 533.5
Leftovers: meetball spagetti, pork cutlet, pizza, tteokbokki

Day: 4
tteokbokki, pizza
Total calories: 397.54
Leftovers: meetball spagetti, pork cutlet, pizza

Day: 5
meetball spagetti
Total calories: 480
Leftovers: pork cutlet

Day: 6
pork cutlet
Total calories: 425
Leftovers: none

exit
```

</div>
</div>
