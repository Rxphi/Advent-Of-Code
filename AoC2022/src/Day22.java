import java.util.*;
import java.util.stream.Collectors;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Day22 {

	public static void main(String[] args) throws IOException {
		File input = new File("./inputFiles/input22.txt");
		Board forceField = new Board(input);
		
		int partI = forceField.partI();
		System.out.println(forceField);
		
		System.out.println("Day XXII");
		System.out.println("Part I : " + partI);
	}

}

class Board {
	int direction = 0;
	Map<Integer, Pair> mapdirection;
	Map<Integer, String> directionString;
	ArrayList<ArrayList<String>> grid;
	ArrayList<String> path;
	int height = 0;
	int width = 0;
	
	Board(File input) throws IOException {
		mapdirection = new HashMap<Integer, Pair>();
		mapdirection.put(0, new Pair(1,0));
		mapdirection.put(1, new Pair(0,1));
		mapdirection.put(2, new Pair(-1,0));
		mapdirection.put(3, new Pair(0, -1));
		directionString = new HashMap<Integer, String>();
		directionString.put(0, ">");
		directionString.put(1, "v");
		directionString.put(2, "<");
		directionString.put(3, "^");
		grid = new ArrayList<ArrayList<String>>();
		
		Files.lines(input.toPath())
			.forEach(l -> {
				if (l.isEmpty()) {

				} else if (l.contains(".") || l.contains("#")) {
					grid.add(new ArrayList<String>(Arrays.asList(l.split(""))));
					width = l.length() > width ? l.length() : width;
					height++;
				} else {
					path = new ArrayList<String>(Arrays.asList(l.replaceAll("L", " L ").replaceAll("R", " R ").split(" ")));
				}
			});
		
		for (int h = 0; h < height; h++) {
			List<String> row = grid.get(h);
			while (row.size() < width) {
				row.add(" ");
			}			
		}
	}
	
	int partI() {
		// find starting position
		int currentDirection = 0;
		Pair pos = null;
		outerloop:
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
			if (grid.get(i).get(j).equals(".")) {
					pos = new Pair(j, i);
					break outerloop;
				}
			}
		}		

		// walk along the given directions
		for (String move : path) {
			if (move.equals("R")) {
				//System.out.println("Turn right");
				currentDirection  = currentDirection == 3 ? 0 : currentDirection+1;
				
			} else if (move.equals("L")) {
				//System.out.println("Turn left");
				currentDirection = currentDirection == 0 ? 3 : currentDirection-1;
				
			} else { // move forward 
				//System.out.println("Move forward by " + move);
				String sign = directionString.get(currentDirection);
				grid.get(pos.i).set(pos.j, sign);
				for (int i = 0; i < Integer.parseInt(move); i++) {
					if (next(pos, currentDirection).equals(pos)) {
						break;
					}
					pos = next(pos, currentDirection);
					grid.get(pos.i).set(pos.j, sign);	
				}
			}
			// Print after the current instruction ends
			// System.out.println(this);
		}
		System.out.println("Row: " + (pos.i+1));
		System.out.println("Column: " + (pos.j+1));
		System.out.println("Facing: " + currentDirection);
		return 1000 * (pos.i+1) + 4 * (pos.j+1) + currentDirection;
	}
	
	Pair next(Pair pos, int dir) {
		Pair toAdd = mapdirection.get(dir);
		Pair prev = pos;
		Pair current = prev.add(toAdd);
		
		current.j = Math.floorMod(current.j, width);
		current.i = Math.floorMod(current.i, height);
		
		if (!grid.get(current.i).get(current.j).equals(" ") && !grid.get(current.i).get(current.j).equals("#")) {
			return current;
		} else if (grid.get(current.i).get(current.j).equals("#")) {
			return prev;
		} else {
			while (grid.get(current.i).get(current.j).equals(" ")) {
				current = current.add(toAdd);
				current.j = Math.floorMod(current.j, width);
				current.i = Math.floorMod(current.i, height);
			}
			if (grid.get(current.i).get(current.j).equals("#")) {
				return prev;
			} 
			return current;
		}
		
	}
	
	@Override
	public String toString() {
		String out = "";
		for (ArrayList<String> row : grid) {
			out += String.join("", row) + System.lineSeparator();
		}
		out += System.lineSeparator();
		return out;
	}
}

class Pair {
	int j;
	int i;
	
	Pair(int j, int i) {
		this.j = j;
		this.i = i;
	}
	
	public Pair add(Pair other) {
		return new Pair(j+other.j, i+other.i);
	}
	
	public boolean equals(Pair other) {
		return j == other.j && i == other.i;
	}

	@Override
	public String toString() {
		return "(" + j + ", " + i + ")";
	}
}