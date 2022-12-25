import java.util.*;
import java.util.stream.Collectors;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Day22 {

	public static void main(String[] args) throws IOException {
		File input = new File("./inputFiles/test.txt");
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
	Map<Pair, Pair> cubenext;
	ArrayList<ArrayList<String>> grid;
	ArrayList<String> path;
	int height = 0;
	int width = 0;
	
	Board(File input) throws IOException {
		mapdirection = new HashMap<Integer, Pair>();
		mapdirection.put(0, new Pair(1,0,0));
		mapdirection.put(1, new Pair(0,1,1));
		mapdirection.put(2, new Pair(-1,0,2));
		mapdirection.put(3, new Pair(0,-1,3));
		directionString = new HashMap<Integer, String>();
		directionString.put(0, ">");
		directionString.put(1, "v");
		directionString.put(2, "<");
		directionString.put(3, "^");
		grid = new ArrayList<ArrayList<String>>();
		
		// read input and construct grid
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
		
		// construct the map for part II
		cubenext = new HashMap<Pair, Pair>();
		
		for (int j = 0; j < 50; j++) {
			cubenext.put(new Pair(j, 199, 1), new Pair(100+j, 0, 1));
			cubenext.put(new Pair(100+j, 0, 3), new Pair(j, 199, 3));
		}
		for (int i = 0; i < 50; i++) {
			cubenext.put(new Pair(0, 150+i, 2), new Pair(50+i, 0, 1));
			cubenext.put(new Pair(50+i, 0, 3), new Pair(0, 150+i, 0));
		}
		for (int i = 0; i < 50; i++) {
			cubenext.put(new Pair(49, 150+i, 0), new Pair(50+i, 149, 3));
			cubenext.put(new Pair(50+i, 149, 1), new Pair(49, 150+i, 2));
		}
		for (int i = 0; i < 50; i++) {
			cubenext.put(new Pair(0, 100+i, 2), new Pair(50, 49-i, 0));
			cubenext.put(new Pair(50, 49-i, 2), new Pair(0, 100+i, 0));
		}
		
	}
	
	int partI() {
		// find starting position
		Pair pos = null;
		outerloop:
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
			if (grid.get(i).get(j).equals(".")) {
					pos = new Pair(j, i, 0);
					break outerloop;
				}
			}
		}		

		// walk along the given directions
		for (String move : path) {
			if (move.equals("R")) {
				//System.out.println("Turn right");
				pos.facing = pos.facing == 3 ? 0 : pos.facing+1;
				
			} else if (move.equals("L")) {
				//System.out.println("Turn left");
				pos.facing = pos.facing == 0 ? 3 : pos.facing-1;
				
			} else { // move forward 
				//System.out.println("Move forward by " + move);
				String sign = directionString.get(pos.facing);
				grid.get(pos.i).set(pos.j, sign);
				for (int i = 0; i < Integer.parseInt(move); i++) {
					if (next(pos).equalPos(pos)) {
						break;
					}
					pos = next(pos);
					grid.get(pos.i).set(pos.j, sign);	
				}
			}
			// Print after the current instruction ends
			// System.out.println(this);
		}
		System.out.println("Row: " + (pos.i+1));
		System.out.println("Column: " + (pos.j+1));
		System.out.println("Facing: " + pos.facing);
		return 1000 * (pos.i+1) + 4 * (pos.j+1) + pos.facing;
	}
	
	Pair next(Pair pos) {
		Pair toAdd = mapdirection.get(pos.facing);
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
	
	Pair nextCube(Pair pos, int dir) {
		return null;
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
	int facing;
	
	Pair(int j, int i) {
		this.j = j;
		this.i = i;
	}
	
	Pair(int j, int i, int facing) {
		this.j = j;
		this.i = i;
		this.facing = facing;
	}
	
	public Pair add(Pair other) {
		return new Pair(j+other.j, i+other.i, other.facing);
	}
	
	public boolean equalPos(Pair other) {
		return j == other.j && i == other.i;
	} 
	
	public boolean equals(Pair other) {
		return j == other.j && i == other.i && facing == other.facing;
	}

	@Override
	public String toString() {
		return "(" + j + ", " + i + ")";
	}
}