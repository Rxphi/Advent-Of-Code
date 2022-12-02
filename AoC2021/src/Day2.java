import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Day2 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File ("./src/input1.txt");
		Scanner sc = new Scanner (input);
		
		Point pos = new Point();
		ArrayList<Integer> nums = new ArrayList<Integer>();
		
		
		String line;
		while (sc.hasNextLine()) {
			if (!(line = sc.next()).isEmpty()) {
				pos.move(line);
			}
		}
		
	}

}

class Point {
	int horizontal;
	int vertical;
	
	void move(String instruction) {
		
	}
}
