import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class Day6 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input6.txt");
		Scanner sc = new Scanner(input);
		
		SchoolI schoolI = new SchoolI();
		SchoolII schoolII = new SchoolII();
		
		for (String x : sc.nextLine().split(",")) {
			Lanternfish toAdd = new Lanternfish(Integer.parseInt(x));
			schoolI.add(toAdd);
			schoolII.add(toAdd);
		}
		
		// Part I 
		for (int d = 0; d < 80; d++) {
			schoolI.nextDay();
		}
		int partI = schoolI.numOfFish();
		
		// Part II
		for (int d = 0; d < 256; d++) {
			/*if (d < 10) {
				System.out.print("Day " + d + ": ");
				schoolII.printMe();
			}*/
			schoolII.nextDay();
		}
		long partII = schoolII.numOfFish();
		
		System.out.println("Day VI");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}

class SchoolI {
	ArrayList<Lanternfish> allFish = new ArrayList<Lanternfish>();
	
	void add(Lanternfish fish) {
		allFish.add(fish);
	}
	
	void add() {
		allFish.add(new Lanternfish());
	}
	
	void nextDay() {
		int numOfNewFish = 0;
		
		for (Lanternfish f : allFish) {
			if (f.timeToReproduce()) {
				numOfNewFish++;
			}
			f.nextDay();
		}
		
		for (int i = 0; i < numOfNewFish; i++) {
			add();
		}
	}
	
	int numOfFish () {
		return allFish.size();
	}
}

class SchoolII {
	long[] timerList = new long[9];
	
	void add(Lanternfish fish) {
		timerList[fish.timer]++;
	}
	
	void nextDay() {
		long numOfNewFish = timerList[0];
		
		for (int i = 0; i < 8; i++) {
			timerList[i] = timerList[i+1];
		}
		timerList[6] += numOfNewFish;
		timerList[8] = numOfNewFish;
	}
	
	long numOfFish () {
		long sum = 0;
		for (long n : timerList) {
			sum += n;
		}
		return sum;
	}
	
	void printMe () {
		for (long n : timerList) {
			System.out.print(n + " ");
		}
		System.out.println();
	}
}

class Lanternfish {
	int timer;
	
	Lanternfish () {
		timer = 8;
	}
	
	Lanternfish (int t) {
		timer = t;
	}
	
	boolean timeToReproduce() {
		return timer == 0;
	}
	
	void nextDay() {
		if (timer == 0) {
			timer = 6;
		} else {
			timer--;
		}
	}
}