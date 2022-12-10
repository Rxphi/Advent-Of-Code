import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class Day10 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input10.txt");
		Scanner sc = new Scanner(input);
		
		CPU chip = new CPU();
		
		String line;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			chip.tick(line);
		}
		
		int partI = chip.sum;
		
		System.out.println("Day X");
		System.out.println("Part I " + partI);
		System.out.println("Part II ");
		chip.drawScreen();
	}

}



class CPU {
	int x; // sprite position
	int cycle;
	ArrayList<Integer> storeAt;
	ArrayList<Integer> visited;
	int sum;
	int crt;
	int row;
	boolean[] image;
	
	CPU () {
		x = 1;
		cycle = 0;
		// for Part I
		storeAt = new ArrayList<Integer>(Arrays.asList(20, 60, 100, 140, 180, 220));
		visited = new ArrayList<Integer>();
		sum = 0;
		// for part II
		crt = 0;
		row = 0;
		image = new boolean[40*6];
	}
	
	void tick(String instruction) {
		check();
		cycle++;
		drawPixel();
		if (!instruction.equals("noop")) { // addx
			check();
			tick(Integer.parseInt(instruction.split(" ")[1]));
		}
		
	}
	
	void tick(int toAdd) {
		drawPixel();
		cycle++;
		check();
		x += toAdd;
	}
	
	void check() {
		if (!visited.contains(cycle) && storeAt.contains(cycle)) {
			sum += x * cycle; // add signal strength to sum
			visited.add(cycle);
		}
		
	}
	
	void drawPixel() {
		if (x-1 <= crt && crt <= x+1) {
			image[row * 40 + crt] = true;
		}
		crt++;
		if (crt > 39) {
			crt = 0;
			row++;
		}
	}
	
	void drawScreen() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 40; j++) {
				int p = i * 40 + j;
				if (image[p]) {
					System.out.print("#");
				} else {
					System.out.print(".");
				}
			}
			System.out.println();
		}
	}
	
	// not needed
	void drawFirstLine() {
		for (int j = 0; j < 40; j++) {
			if (image[j]) {
				System.out.print("#");
			} else {
				System.out.print(".");
			}
		}
		System.out.println(" " + crt);
	}
}