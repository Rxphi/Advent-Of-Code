import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day1 {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File input = new File("./src/input1.txt");
		Scanner sc = new Scanner(input);
		
		ArrayList<Integer> nums = new ArrayList<Integer>();
		
		while (sc.hasNextInt()) {
			nums.add(sc.nextInt());
		}
		
		int partI = 0;
		int partII = 0;
		
		for (int i = 0; i < nums.size() - 1; i++) {
			if (nums.get(i) < nums.get(i+1)) {
				partI++;
			}
		}
		
		for (int i = 1; i < nums.size() - 2; i++) {
			if (nums.get(i-1) + nums.get(i) + nums.get(i+1) < nums.get(i) + nums.get(i+1) + nums.get(i+2)) {
				partII++;
			}
		}
		
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}

}
