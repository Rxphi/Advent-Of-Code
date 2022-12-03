import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Day3 {

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		File inputFile = new File("./src/input3.txt");
		Scanner sc = new Scanner(inputFile);
		
		ArrayList<String> lines = new ArrayList<String>();
		
		int totalI = 0;
		int totalII = 0;

		String line;
		/*int test = duplicatePriority("jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL");
		System.out.println(test);*/
		
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			lines.add(line);
		}
		
		// PartI
		for (String l : lines) {
			totalI += duplicatePriority(l);
		}
		
		// PartII 
		for (int i = 1; i < lines.size()-1; i += 3) {
			totalII += triplePriority(lines.get(i-1), lines.get(i), lines.get(i+1));
		}
		
		System.out.println("Day III");
		System.out.println("Part I : " + totalI);
		System.out.println("Part II: " + totalII);
		sc.close();
		
	}
	
	public static int duplicatePriority(String line) {
		String left = line.substring(0, line.length()/2);
		String right = line.substring(line.length()/2, line.length());
		
		for (char letterleft : left.toCharArray()) {
			for (char letterright : right.toCharArray()) {
				if (letterleft == letterright) {
					return getValue(letterleft);
				}
			}
		}
		return 0;
	}
	
	public static int triplePriority (String line1, String line2, String line3) {
		for (char letter1 : line1.toCharArray()) {
			for (char letter2 : line2.toCharArray()) {
				if (letter1 != letter2) {
					continue;
				} else {
					for (char letter3 : line3.toCharArray()) {
						if (letter1 == letter3) {
							return getValue(letter1);
						}
					}
				}
			}
		}
		return 0;
	}
	
	public static int getValue(char c) {
		if (Character.isUpperCase(c)) {
			return ((int) c) - 64 + 26;
		} else {
			return ((int) c) - 96;
		}
	}

}
