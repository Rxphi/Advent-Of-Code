import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

public class Day5 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./src/input5.txt");
		Scanner sc = new Scanner(input);
		
		ArrayList<Line> lines = new ArrayList<Line>();
		
		String line;
		
		int width = 1;
		int height = 1;
		
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			Line toAdd = new Line(line);
			lines.add(toAdd);
			
			if (toAdd.x1 >= width) {
				width = toAdd.x1 + 1;
			}
			if (toAdd.x2 >= width) {
				width = toAdd.x2 + 1;
			}
			if (toAdd.y1 >= height) {
				height = toAdd.y1 + 1;
			}
			if (toAdd.y2 >= height) {
				height = toAdd.y2 + 1;
			}
		}
		
		int[][] diagram = new int[height][width];
		//System.out.println(height + " " + width);
		for (Line l : lines) {
			// PART I & II
			if (l.isHorizontal()) {
				int i = l.y1;
				for (int j = l.x1; j <= l.x2; j++) {
					diagram[i][j]++;
				}
				for (int j = l.x2; j <= l.x1; j++) {
					diagram[i][j]++;
				}
			} else if (l.isVertical()) {
				int j = l.x1;
				for (int i = l.y1; i <= l.y2; i++) {
					diagram[i][j]++;
				}
				for (int i = l.y2; i <= l.y1; i++) {
					diagram[i][j]++;
				}
			
			// ONLY FOR PART II
			} else {
				if (l.x1 < l.x2) {
					if (l.y1 < l.y2) {
						for (int d = 0; d < l.x2 - l.x1 + 1; d++) {
							diagram[l.y1+d][l.x1+d]++;
						}
					} else {
						for (int d = 0; d < l.x2 - l.x1 + 1; d++) {
							diagram[l.y1-d][l.x1+d]++;
						}
					}
				} else {
					if (l.y1 < l.y2) {
						for (int d = 0; d < l.x1 - l.x2 + 1; d++) {
							diagram[l.y1+d][l.x1-d]++;
						}
					} else {
						for (int d = 0; d < l.x1 - l.x2 + 1; d++) {
							diagram[l.y2+d][l.x2+d]++;
						}
					}
				}
			}
		}
		
		int partI = 0;
		int partII = 0;
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (diagram[i][j] > 1) {
					partI++;
					partII++;
				}
				/*
				if (diagram[i][j] > 0) {
					System.out.print(diagram[i][j]);
				} else {
					System.out.print(".");
				}
				*/
			}
			//System.out.println();
		}
		
		System.out.println("Day V");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}
}

class Line {
	int x1;
	int y1;
	int x2;
	int y2;
	
	Line(String input) {
		x1 = Integer.parseInt(input.split(" -> ")[0].split(",")[0]);
		y1 = Integer.parseInt(input.split(" -> ")[0].split(",")[1]);
		x2 = Integer.parseInt(input.split(" -> ")[1].split(",")[0]);
		y2 = Integer.parseInt(input.split(" -> ")[1].split(",")[1]);
		
		//System.out.println("New Line with x1 = " + x1 + " y1 = " + y1 + " x2 = " + x2 + " y2 = " + y2);
	}
	
	boolean isHorizontal() {
		return y1 == y2;
	}
	
	boolean isVertical() {
		return x1 == x2;
	}
	
	boolean isOrthogonal() {
		return isHorizontal() || isVertical();
	}
}