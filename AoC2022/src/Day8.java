import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;

public class Day8 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input8.txt");
		Scanner sc = new Scanner(input);
		
		Forest map = new Forest();
		
		String line;
		while(sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			ArrayList<Integer> newRow = new ArrayList<Integer>();
			for (String stringN : line.split("")) {
				newRow.add(Integer.parseInt(stringN));
			}
			map.grid.add(newRow);
		}
		
		
		int partI = 0;
		int partII = 0;
		
		for (int i = 0; i < map.grid.size(); i++) {
			for (int j = 0; j < map.grid.get(0).size(); j++) {
				// Part I
				if (map.isVisibleFromOutside(i, j)) {
					partI++;
				}
				// Part II
				int scenic = map.scenicScore(i, j);
				if (scenic > partII) {
					partII = scenic;
					//System.out.println(i + " " + j + " " + scenic);
				}
			}
		}
		
		
		System.out.println("Day VIII");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}

class Forest {
	ArrayList<ArrayList<Integer>> grid;
	
	Forest () {
		grid = new ArrayList<ArrayList<Integer>>();
	}
	
	boolean isVisibleFromOutside(int i, int j) {
		if (i == 0 || i == grid.size()-1 || j == 0 || j == grid.get(0).size()-1) {
			return true;
		}
		
		int height = get(i, j);
		
		boolean visibleFromTop = true;
		for (int ci = 0; ci < i; ci++) {
			if (height <= get(ci, j)) {
				visibleFromTop = false;
				break;
			}
		}
		
		boolean visibleFromBottom = true;
		for (int ci = grid.size()-1; ci > i; ci--) {
			if (height <= get(ci, j)) {
				visibleFromBottom = false;
				break;
			}
		}
		
		boolean visibleFromLeft = true;
		for (int cj = 0; cj < j; cj++) {
			if (height <= get(i, cj)) {
				visibleFromLeft = false;
				break;
			}
		}
		
		boolean visibleFromRight = true;
		for (int cj = grid.get(0).size()-1; cj > j; cj--) {
			if (height <= get(i, cj)) {
				visibleFromRight = false;
				break;
			}
		}
		
		return visibleFromTop || visibleFromBottom || visibleFromLeft || visibleFromRight;
	}
	
	int scenicScore(int i, int j) {
		int height = get(i, j);
		
		int top = 0;
		for (int ci = i-1; ci >= 0; ci--) {
			top++;
			if (height <= get(ci, j)) {
				break;
			}
		}
		
		int bottom = 0;
		for (int ci = i+1; ci < grid.size(); ci++) {
			bottom++;
			if (height <= get(ci, j)) {
				break;
			}
		}
		
		int left = 0;
		for (int cj = j-1; cj >= 0; cj--) {
			left++;
			if (height <= get(i, cj)) {
				break;
			}
		}
		
		int right = 0;
		for (int cj = j+1; cj < grid.get(0).size(); cj++) {
			right++;
			if (height <= get(i, cj)) {
				break;
			}
		}
		//System.out.println("t: " + top + " b: " + bottom + " l: " + left + " r: " + right);
		return top * bottom * left * right;
	}
	
	int get(int i, int j) {
		return grid.get(i).get(j);
	}
	
	void printMe() {
		for (ArrayList<Integer> row : grid) {
			for (int h : row) {
				System.out.print(h);
			}
			System.out.println();
		}
	}
}
