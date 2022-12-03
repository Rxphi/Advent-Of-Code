import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Day1 {
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File inputFile = new File("./src/input1.txt");
		Scanner sc = new Scanner(inputFile);

		int mostCal = 0;
		int currentCal = 0;
		ArrayList<Integer> calories = new ArrayList<Integer>();
		
		while (sc.hasNextLine()) {
			String line;
			while (sc.hasNext() && !(line = sc.nextLine()).isEmpty()) {
				currentCal += Integer.parseInt(line);
			}
			if (currentCal > mostCal) {
				mostCal = currentCal;
			}
			calories.add(currentCal);
			currentCal = 0;
		}
		
		Collections.sort(calories, Collections.reverseOrder());
		//System.out.println(calories);
		
		System.out.println("Day I");
		System.out.println("Part I Most Calories carried by one Elf: " + calories.get(0));
		System.out.println("Part II Total Calories of the top three Elves: " + (calories.get(0)+calories.get(1)+calories.get(2)));
		sc.close();
	}
}