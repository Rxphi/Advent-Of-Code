import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day9 {
	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		HeightMap seefloor = new HeightMap(sc);
		seefloor.printMe();
	}
}


class HeightMap {
	ArrayList<ArrayList<Integer>> map;
	
	HeightMap (Scanner sc) {
		map = new ArrayList<ArrayList<Integer>>();
		
		String line;
		while (sc.hasNext() && !(line = sc.nextLine()).isEmpty()) {
			ArrayList<Integer> newRow = new ArrayList<Integer>();
			for (String s : line.split("")) {
				newRow.add(Integer.parseInt(s));
			}
			map.add(newRow);
		}
	}
	
	void printMe() {
		for (ArrayList<Integer> row : map) {
			for (int h : row) {
				System.out.print(h);
			}
			System.out.println();
		}
	}
}