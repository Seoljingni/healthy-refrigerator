import java.util.*;
import java.util.stream.Collectors;

public class test {
    public static ArrayList<food> foods = new ArrayList<food>();

    public static int out_weight = 100;

    public static int refrigeratior = 1000;

    public static int days = 1;

    public static double priority(food food, int prio[]) {	
        //
        System.out.println("PRIO before: " + food);
        //
        double w1 =(double)food.cals / food.weight;
        int[] arr = new int[3];
        double[] priority = new double[3];

        for (int i = 0; i < 3; i++) {
            switch (prio[i]) {
                case 1:
                //탄수
                    arr[0] = i + 1 ;
                    break;
                case 2:
                //단백질
                    arr[1] = i + 1;
                    break;
                case 3:
                //지방
                    arr[2] = i + 1;
                    break;
                }
        }
        //System.out.println(Arrays.toString(arr));
        for (int i = 0; i < 3; i++) {
            switch (arr[i]) {
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
        double w2 = priority[0] * food.carb + priority[1] * food.protein + priority[2] * food.fat;
        double result = w2 - (w1 * 10);
        return Math.round(result);
    }

    public static void remainReduce() {
        for(food food : foods) {
            food.remaining_days--;
        }
    }

    public static void initialInputCheck() {
        //  기간 2이하로 남은 음식 용량이 100을 넘는가
        List<food> list = foods.stream().filter(f -> f.remaining_days < 3).collect(Collectors.toList());
        ArrayList<food> near_exp = new ArrayList<food>(list);

        int near_exp_weight = 0;
        for(food food : near_exp) {
            near_exp_weight += food.weight;
        }

        //  넘는다면 용량이 큰 순서부터 드랍하여 100 이하로 맞춤
        //  Collections.max(near_exp);
        while (near_exp_weight > out_weight) {
            food maxFood = Collections.max(near_exp, (f1, f2) -> f1.weight - f2.weight);
            System.out.println("drop food: " + maxFood.name + "\n");
            foods.remove(maxFood);
            near_exp.remove(maxFood);
            near_exp_weight -= maxFood.weight;
        }
    }

    public static ArrayList<food> solution() {
        ArrayList<food> consume_list = new ArrayList<food>();

        //  소비기한으로 정렬
        Collections.sort(foods,new RemainComparator());

        //---------------
        for (food food : foods) {
            System.out.printf("%s %d,", food.name, food.remaining_days);
        }
        System.out.println("\n");
        //------------

        // //  기간 2이하로 남은 음식 용량이 100을 넘는가
        // List<food> list = foods.stream().filter(f -> f.remaining_days < 3).collect(Collectors.toList());
        // ArrayList<food> near_exp = new ArrayList<food>(list);

        // int near_exp_weight = 0;
        // for(food food : near_exp) {
        //     near_exp_weight += food.weight;
        // }

        // //  넘는다면 용량이 큰 순서부터 드랍하여 100 이하로 맞춤
        // //  Collections.max(near_exp);
        // while (near_exp_weight > out_weight) {
        //     food maxFood = Collections.max(near_exp, (f1, f2) -> f1.weight - f2.weight);
        //     System.out.println("drop food: " + maxFood.name + "\n");
        //     foods.remove(maxFood);
        //     near_exp.remove(maxFood);
        //     near_exp_weight -= maxFood.weight;
        // }

        //  기간 1남은 음식을 리스트에 추가
        List<food> list = foods.stream().filter(f -> f.remaining_days < 2).collect(Collectors.toList());
        ArrayList<food> remain_one_day = new ArrayList<food>(list);

        int total_weight = 0;
        for(food food : remain_one_day) {
            total_weight += food.weight;
        }
        if(total_weight > 100) {
            while (total_weight > 100) {
                food minFood = remain_one_day.get(0);
                for(int i =1; i < remain_one_day.size(); i++) {
                    food food1 = foods.get(i);
                    if(minFood.priority > food1.priority){
                        minFood = food1;
                    }
                }
                total_weight -= minFood.weight;
                remain_one_day.remove(minFood);
                foods.remove(minFood);
            }
        }
        consume_list.addAll(remain_one_day);
        foods.removeAll(remain_one_day);
        
        //  이외의 것 중 우선순위 높은순서부터 리스트에 추가
        Collections.sort(foods, new PriorityComparator());

        while (total_weight < out_weight) {
            if (foods.size() == 0)
                break;

            food food = foods.get(0);

            // -----
            System.out.println(food.name + " \n");
            // -----

            if(total_weight == out_weight) {
                
            System.out.println(" total : " + total_weight + "\n");
                break;
            }
                

            //  용량이 100 안
            else if((total_weight + food.weight) <= out_weight) {
                total_weight += food.weight;
                consume_list.add(food);
                foods.remove(food);
            System.out.println(" FW : " + food.weight + "\n");         
            System.out.println(" total : " + total_weight + "\n");
            }

            //  용량이 100 초과
            else if((total_weight + food.weight) > out_weight) {
                food food1 = new food(food.name, food.weight, food.remaining_days, food.cals, food.carb, food.protein, food.fat);
                int rest = (out_weight - total_weight);
                double weight = food.weight;

                food.cals = food.cals * (1 - (rest / weight));
                food.cals = Math.round(food.cals);
                food.weight -= rest;

                food1.cals = food1.cals * (rest / weight);
                food.cals = Math.round(food.cals);
                food1.weight = rest;

                total_weight += rest;
                consume_list.add(food1);
                
            System.out.println(" FW : " + food.weight + "\n");  
            System.out.println(" FW : " + food1.weight + "\n");  
            System.out.println(" total : " + total_weight + " rest : " + rest + "\n");
                break;
            }
        }

        return consume_list;
    }

    public static void main(String[] args) {
        foods.add(new food("chicken breast", 30, 10, 160, 0, 75, 25));
        foods.add(new food("burrito", 50, 3, 350, 60, 30, 10));
        foods.add(new food("yogurt", 80, 4, 100, 20, 50, 30));
        foods.add(new food("meetball spagetti", 100, 5, 480, 65, 25, 10));
        foods.add(new food("bread", 40, 2, 300, 80, 10, 10));
        foods.add(new food("egg", 18, 7, 25, 10, 65, 25));
        foods.add(new food("Kimchi Fried Rice", 150, 2, 650, 88, 7, 5));
        foods.add(new food("pork cutlet", 50, 15, 425, 15, 65, 20));
        foods.add(new food("pizza", 110, 5, 510, 60, 5, 35));
        foods.add(new food("tteokbokki", 150, 11, 550, 75, 2, 23));

        int[] prio = new int[3];
        Scanner scanner = new Scanner(System.in);
        initialInputCheck();
        while(foods.size() != 0) {
            System.out.println("\nPlace in the order of importance: 1 carbohydrates, 2 proteins, and 3 fats.\r\n" + 
                    "(ex: 2 1 3)-> This means that it is weighted in the order of protein, carbohydrates, and fat.\r\n" + 
                    "");
                    
            String input = scanner.nextLine();
            String[] numbersStr = input.split(" ");
            for (int i = 0 ; i < 3 ; i++) {
                prio[i] = Integer.parseInt(numbersStr[i]);		
            }

            for (int i = 0 ; i < foods.size() ; i++) {
                food food = foods.get(i);
                food.priority = priority(food, prio);
                        //
        System.out.println("PRIO after: " + food);
        //
            }

            ArrayList<food> consume_lists = solution();
            double total_cals = 0;
            
            System.out.printf("Day: %d\n", days);
            for (int i = 0; i < consume_lists.size(); i++) {
                food food = consume_lists.get(i);
                total_cals += food.cals;
               // System.out.printf("%s", food.name);
            //-------
                System.out.println(food);
            //-------    
                if(i < consume_lists.size() - 1)
                    System.out.printf(", ");
                else 
                    System.out.printf("\n");
            }
            System.out.printf("total calories : %f\n", total_cals);
            for (int i = 0; i < foods.size(); i++) {
                food food = foods.get(i);
                //System.out.printf("%s", food.name);
            //-------
                System.out.println(food);
            //-------    
                if(i < foods.size() - 1)
                    System.out.printf(", ");
                else 
                    System.out.printf("\n");
            }
            remainReduce();
            days++;
        }
        System.out.println("end");
    }
}

class food //implements Cloneable //implements Comparable<food>
{
    
    /**
     * 이름
     * 용량(무게)
     * 남은 기간(유통기한)
     * 총 칼로리
     * 탄
     * 단
     * 지
     * 우선순위
     */
    String name;
    int weight;
    int remaining_days;
    double cals;
    int carb;
    int protein;
    int fat;
    double priority; 
    food(String name, int weight, int remaining_days, double cals, int carb, int protein, int fat) {
        this.name = name;
        this.weight = weight;
        this.remaining_days = remaining_days;
        this.cals = cals;
        this.carb = carb;
        this.protein = protein;
        this.fat = fat;
    }
    public void setRemainingDays(int remaining_days) {
        this.remaining_days = remaining_days;
    }
    public void setWeight(int weight) {
        this.weight = weight;
    }
    public void priority(double priority) {
        this.priority = priority;
    }

    public String toString() {
        return name + ", " + weight + ", " + remaining_days + ", " + cals + ", " + carb + ", " + protein + ", " + fat + ", " + priority + "\n";
    }

    // @Override
	// public Object clone() throws CloneNotSupportedException {
    //     food f1 = (food)super.clone();
	// 	return f1;
    // }
    // @Override
    // public int compareTo(food food) {
    //   return (this.weight > food.weight) ? 1 : -1;
    // }
}

/**
 * 남은 소비기한 기준으로 정렬
 */
class RemainComparator implements Comparator<food>{
	@Override
	public int compare(food a,food b){
		if(a.remaining_days>b.remaining_days) return 1;
		if(a.remaining_days<b.remaining_days) return -1;
		return 0;
	}
}

/**
 * 우선순위 기준으로 정렬
 */
class PriorityComparator implements Comparator<food>{
	@Override
	public int compare(food a,food b){
		if(a.priority>b.priority) return -1;
		if(a.priority<b.priority) return 1;
		return 0;
	}
}
