import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Collections;
import java.util.LinkedList;

public class Day6 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./src/input6.txt");
		Scanner sc = new Scanner(input);
		
		LinkedList<Character> fourChars = new LinkedList<Character>();
		LinkedList<Character> fourteenChars = new LinkedList<Character>();
		
		String line = sc.nextLine();
		
		
		for (int i = 0; i < 4; i++) {
			fourChars.add(line.charAt(i));
		}
		int partI = 4;
		while (!isDistinct(fourChars)) {
			fourChars.removeFirst();
			fourChars.addLast(line.charAt(partI++));
			
		}
		
		for (int i = 0; i < 14; i++) {
			fourteenChars.add(line.charAt(i));
		}
		int partII = 14;
		while (!isDistinct(fourteenChars)) {
			fourteenChars.removeFirst();
			fourteenChars.addLast(line.charAt(partII++));
		}
		
		
		System.out.println("Day VI");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}
	
	public static boolean isDistinct(LinkedList<Character> input) {	
		for (int i = 0; i < input.size()-1; i++) {
			for (int j = i + 1; j < input.size(); j++){	
				if (input.get(i) == input.get(j)) {
					return false;
				}
			}
		}
		return true;
	}
}
