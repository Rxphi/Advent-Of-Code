import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Day8 {

	static ArrayList<Integer> safeLengths = new ArrayList<Integer>(Arrays.asList(2, 3, 4, 7));

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		String line;
		
		int partI = 0;
		int partII = 0;
		
		
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			ArrayList<String> left = new ArrayList<String>(Arrays.asList(line.split("\\| ")[0].split(" ")));
			ArrayList<String> right = new ArrayList<String>(Arrays.asList(line.split("\\| ")[1].split(" ")));
			for (String s : right) {
				if (safeLengths.contains(s.length())) {
					partI++;
				}
			}
			partII += figureOut(left, right);
			break;
		}
		
		System.out.println("Day XIII");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

	public static int figureOut(ArrayList<String> left, ArrayList<String> right) {
		// Outer ArrayList
		// 0000
		//1    2
		//1    2
		// 3333
		//4    5
		//4    5
		// 6666
		ArrayList<Set<String>> decoder = new ArrayList<Set<String>>();
		for (int i = 0; i < 7; i++) {
			decoder.add(new HashSet<String>());
		}
		
		for (String digit : left) {
			for (int l : safeLengths)
			if (digit.length() == l) {
				for (String c : digit.split("")) {
					switch (l) {
					case 2:
						decoder.get(2).add(c);
						decoder.get(5).add(c);
					case 3:
						decoder.get(0).add(c);
						decoder.get(2).add(c);
						decoder.get(5).add(c);
					case 4:
						decoder.get(1).add(c);
						decoder.get(2).add(c);
						decoder.get(3).add(c);
						decoder.get(5).add(c);
					}
					
				}
			}
		}
		System.out.println(decoder);
		return 0;
	}
}
