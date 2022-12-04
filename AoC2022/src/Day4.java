import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Day4 {

	public static void main(String[] args) throws FileNotFoundException {
		File inputFile = new File("./src/input4.txt");
		Scanner sc = new Scanner(inputFile);
		
		int partI = 0;
		int partII = 0;
		
		String line;

		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			if (fullyContains(line)) {
				partI++;
				
			}
			if (overlaps(line)) {
				partII++;
			}
		}
		
		System.out.println("Day IV");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);

	}
	
	public static boolean fullyContains (String line) {
		String left = line.split(",")[0];
		String right = line.split(",")[1];
		
		int leftFrom = Integer.parseInt(left.split("-")[0]);
		int leftTo = Integer.parseInt(left.split("-")[1]);
		int rightFrom = Integer.parseInt(right.split("-")[0]);
		int rightTo = Integer.parseInt(right.split("-")[1]);
		
		
		if (rightFrom >= leftFrom && rightTo <= leftTo) {
			return true;
		} else if (leftFrom >= rightFrom && leftTo <= rightTo) {
			return true;
		}
		return false;
		
	}
	
	public static boolean overlaps (String line) {
		String left = line.split(",")[0];
		String right = line.split(",")[1];
		
		int leftFrom = Integer.parseInt(left.split("-")[0]);
		int leftTo = Integer.parseInt(left.split("-")[1]);
		int rightFrom = Integer.parseInt(right.split("-")[0]);
		int rightTo = Integer.parseInt(right.split("-")[1]);
		
		if (rightFrom <= leftTo && rightFrom >= leftFrom) {
			return true;
		} else if (rightTo <= leftTo && rightTo >= leftFrom) {
			return true;
		} else if (leftTo <= rightTo && leftTo >= rightFrom) {
			return true;
		} else if (leftFrom <= rightTo && leftFrom >= rightFrom) {
			return true;
		}
		return false;
	}

}
