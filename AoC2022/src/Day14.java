import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day14 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		int n = 0;
		String line;
		while(sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			String[] points = line.split(" -> ");		
			for (String point : points) {
				int pointi = Integer.parseInt(point.split(",")[0]);
				int pointj = Integer.parseInt(point.split(",")[1]);
				n = pointi > n ? pointi : n;
				n = pointj > n ? pointj : n;
			}
		}
		
		Cave behindWaterfall = new Cave(new Scanner(input), n+1);
		behindWaterfall.toString(0, 9, 494, 503);
		
		int partI = 0;
		int partII = 0;
		
		System.out.println("Day XIV");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);

	}

}

class Cave {
	ArrayList<ArrayList<String>> map;
	int width;
	int height;
	
	Cave (Scanner sc, int n) {
		System.out.println("Map Size: " + n + " x " + n);
		map = new ArrayList<ArrayList<String>>();
		for (int i = 0; i < n; i++) {
			ArrayList<String> newRow = new ArrayList<String>();
			for (int j = 0; j < n; j++) {
				newRow.add(".");
			}
			map.add(newRow);
		}
		width = n;
		height = n;
		String line;
		while(sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			addRockStructure(line);
		}
	}
	
	void addRockStructure(String line) {
		String[] points = line.split(" -> ");
		for (int i = 0; i < points.length - 1; i++) {
			int point1j = Integer.parseInt(points[i].split(",")[0]);
			int point1i = Integer.parseInt(points[i].split(",")[1]);
			int point2j = Integer.parseInt(points[i+1].split(",")[0]);
			int point2i = Integer.parseInt(points[i+1].split(",")[1]);
			System.out.println("(" + point1j + "," + point1i + "), (" + point2j + "," + point2i + ")");
			int diffi = point2i - point1i;
			int diffj = point2j - point1j;
			
			if (diffi == 0) {
				if (diffj < 0) {
					System.out.println("new line to the left");
					for (int dj = 0; dj >= diffj; dj--) {
						System.out.println("(" + (point1j+dj) + "," + point1i + ")");
						map.get(point1i).set(point1j + dj, "#");
					}
				} else {
					System.out.println("new line to the right");
					for (int dj = 0; dj <= diffj; dj++) {
						System.out.println("(" + (point1j+dj) + "," + point1i + ")");
						map.get(point1i).set(point1j + dj, "#");
					}
				}
			} else if (diffj == 0) {
				if (diffi < 0) {
					System.out.println("new line to the top");
					for (int di = 0; di >= diffi; di--) {
						System.out.println("(" + point1j + "," + (point1i+di) + ")");
						map.get(point1i + di).set(point1j, "#");
					}
				} else {
					System.out.println("new line to the bottom");
					for (int di = 0; di <= diffi; di++) {
						System.out.println("(" + point1j + "," + (point1i+di) + ")");
						map.get(point1i + di).set(point1j, "#");
					}
				}
			}
		}
	}
	
	public void toString(int starti, int endi, int startj, int endj) {
		for (int di = 0; di <= endi-starti; di++) {
			for (int dj = 0; dj <= endj-startj; dj++) {
				System.out.print(map.get(starti+di).get(startj+dj));
			}
			System.out.println();
		}
	}
}
































