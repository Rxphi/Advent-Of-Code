import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day14 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input14.txt");
		Scanner sc = new Scanner(input);
		
		int maxWidth = 0;
		int maxHeight = 0;
		String line;
		while(sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			String[] points = line.split(" -> ");		
			for (String point : points) {
				int pointj = Integer.parseInt(point.split(",")[0]);
				int pointi = Integer.parseInt(point.split(",")[1]);
				maxWidth = pointj > maxWidth ? pointj : maxWidth;
				maxHeight = pointi > maxHeight ? pointi : maxHeight;
			}
		}
		
		Cave behindWaterfall = new Cave(new Scanner(input), maxWidth+1, maxHeight+1);
		System.out.println("Input Cave");
		behindWaterfall.printMe();	
		int partI = behindWaterfall.simulateSandI();
		System.out.println("After Part I Simulation");
		behindWaterfall.printMe();
		
		behindWaterfall.resetForPartII();
		System.out.println("After Reset for Part II");
		behindWaterfall.printMe();
		
		int partII = behindWaterfall.simulateSandII();
		System.out.println("After Part II Simulation");
		behindWaterfall.printMe();
		System.out.println("Scroll to the right --->\n");
		System.out.println("Day XIV");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);

	}

}

class Cave {
	ArrayList<ArrayList<String>> map;
	int width;
	int height;
	int shift;
	
	Cave(Scanner sc, int width, int height) {
		System.out.println("Map Size: " + height + " x " + width);
		map = new ArrayList<ArrayList<String>>();
		for (int i = 0; i < height; i++) {
			ArrayList<String> newRow = new ArrayList<String>();
			for (int j = 0; j < width; j++) {
				newRow.add(".");
			}
			map.add(newRow);
		}
		this.width = width;
		this.height = height;;
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
			//System.out.println("(" + point1j + "," + point1i + "), (" + point2j + "," + point2i + ")");
			int diffi = point2i - point1i;
			int diffj = point2j - point1j;
			
			if (diffi == 0) {
				if (diffj < 0) {
					for (int dj = 0; dj >= diffj; dj--) {
						map.get(point1i).set(point1j + dj, "#");
					}
				} else {
					for (int dj = 0; dj <= diffj; dj++) {
						map.get(point1i).set(point1j + dj, "#");
					}
				}
			} else if (diffj == 0) {
				if (diffi < 0) {
					for (int di = 0; di >= diffi; di--) {
						map.get(point1i + di).set(point1j, "#");
					}
				} else {
					for (int di = 0; di <= diffi; di++) {
						map.get(point1i + di).set(point1j, "#");
					}
				}
			}
		}
	}
	
	int simulateSandI() {
		int out = 0;
		boolean stable = true;
		while (stable) {
			int oldi = -1;
			int oldj = 500;
			int currenti = 0;
			int currentj = 500;
			while (oldi != currenti || oldj != currentj) {
				if (currenti == height-1 || currentj == -1 || currentj == width) {
					stable = false;
					break;
				}
				if (map.get(currenti+1).get(currentj).equals(".")) { // check directly down
					oldi = currenti;
					currenti++;
				} else if (map.get(currenti+1).get(currentj-1).equals(".")) { // check down left
					oldi = currenti;
					oldj = currentj;
					currenti++;
					currentj--;
				} else if (map.get(currenti+1).get(currentj+1).equals(".")) { // check down right
					oldi = currenti;
					oldj = currentj;
					currenti++;
					currentj++;
				} else { // place sand unit at its resting position
					out++;
					map.get(currenti).set(currentj, "o");
					break;
				}
			}
		}
		return out;
	}
	
	int simulateSandII() {
		int out = 0;
		boolean openSource = true;
		while (openSource) {
			int oldi = -1;
			int oldj = 500 + shift;
			int currenti = 0;
			int currentj = 500 + shift;
						
			while (oldi != currenti || oldj != currentj) {
				if (map.get(currenti+1).get(currentj).equals(".")) { // check directly down
					oldi = currenti;
					currenti++;
				} else if (map.get(currenti+1).get(currentj-1).equals(".")) { // check down left
					oldi = currenti;
					oldj = currentj;
					currenti++;
					currentj--;
				} else if (map.get(currenti+1).get(currentj+1).equals(".")) { // check down right
					oldi = currenti;
					oldj = currentj;
					currenti++;
					currentj++;
				} else { // place sand unit at its resting position
					out++;
					map.get(currenti).set(currentj, "o");
					break;
				}
			}
			if (currenti == 0 && currentj == 500 + shift) { // source is blocked
				map.get(currenti).set(currentj, "o");
				break;
			}
		}
		return out;
	}
	
	void resetForPartII() {
		shift = height;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (map.get(i).get(j).equals("o")) {
					map.get(i).set(j, ".");
				}
			}
			for (int x = 0; x < shift; x++) {
				map.get(i).add(".");
				map.get(i).add(0, ".");
			}
		}
		
		width += shift * 2;
		height+=2;
		System.out.println("New Map Size: " + height + " x " + width);
		ArrayList<String> newRow1 = new ArrayList<String>();
		ArrayList<String> newRow2 = new ArrayList<String>();
		for (int j = 0; j < width; j++) {
			newRow1.add(".");
			newRow2.add("#");
		}
		map.add(newRow1);
		map.add(newRow2);
	}
	
	void printMe(int starti, int endi, int startj, int endj) {
		for (int di = 0; di <= endi-starti; di++) {
			for (int dj = 0; dj <= endj-startj; dj++) {
				System.out.print(map.get(starti+di).get(startj+dj));
			}
			System.out.println();
		}
		System.out.println();
	}
	
	void printMe() {
		printMe(0, height-1, 0, width-1);
	}
}
































