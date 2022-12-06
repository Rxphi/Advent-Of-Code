import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class Day4 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input4.txt");
		Scanner sc = new Scanner(input);
		
		// get the random numbers from the first line of input
		String firstLine = sc.nextLine();
		ArrayList<Integer> randomNumbers = new ArrayList<Integer>();
		for (String n : firstLine.split(",")) {
			randomNumbers.add(Integer.parseInt(n));
		}
		
		// initialize all bingo bords
		ArrayList<BingoBord> allBords = new ArrayList<BingoBord>();
		
		String line;
		while (sc.hasNextInt()) {
			sc.nextLine();
			BingoBord newBord = new BingoBord();
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					newBord.numbers[i][j] = sc.nextInt();
				}
			}
			allBords.add(newBord);
		}
		
		// run the game for partI
		int partI = -1;
		for (int randomNum : randomNumbers) {
			for (BingoBord bord : allBords) {
				bord.mark(randomNum);
				
				if (bord.won()) {
					partI = bord.getScore(randomNum);
				}
			}
			if (partI != -1) break;
		}
		
		// partII
		int partII = 0;
		
		for (BingoBord bord : allBords) {
			bord.reset();
		}
		
		while (allBords.size() > 0) {
			int randomNum = randomNumbers.remove(0);
			
			for (int i = 0; i < allBords.size(); i++) {
				BingoBord bord = allBords.get(i);
				bord.mark(randomNum);
				
				if (bord.won()) {
					allBords.remove(bord);
				}
				if (allBords.size() == 0) {
					partII = bord.getScore(randomNum);
				}
			}
		}
		
		
		
		
		System.out.println("Day IV");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}


class BingoBord {
	int[][] numbers = new int[5][5];
	boolean[][] marked = new boolean[5][5];
	
	void mark(int num) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (numbers[i][j] == num) {
					marked[i][j] = true;
				}
			}
		}
	}
	
	boolean won() {
		// check rows
		for (boolean[] row : marked) {
			boolean w = true;
			for (int i = 0; i < 5; i++) {
				if (!row[i]) {
					w = false;
					break;
				}
			}
			if (w) return true;
		}
		
		// check columns
		for (int j = 0; j < 5; j++) {
			boolean w = true;
			for (int i = 0; i < 5; i++) {
				if (!marked[i][j]) {
					w = false;
					break;
				}
			}
			if (w) return true;
		}
		
		return false;
	}
	
	int getScore(int justCalled) {
		int out = 0;
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (!marked[i][j]) {
					out += numbers[i][j];
				}
			}
		}
		
		out *= justCalled;
		return out;
	}
	
	void reset() {
		marked = new boolean[5][5];
	}
	
	void printMe() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(numbers[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
}