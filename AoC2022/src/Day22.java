import java.util.*;
import java.util.stream.Collectors;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Day22 {

	public static void main(String[] args) throws IOException {
		File input = new File("./inputFiles/test.txt");
		Board forceField = new Board(input);
		System.out.println(forceField);
		//forceField.partI();
	}

}

class Board {
	int direction = 0;
	Map<Integer, Pair> mapdirection;
	ArrayList<ArrayList<String>> grid;
	ArrayList<String> path;
	int height = 0;
	int width = 0;
	
	Board(File input) throws IOException {
		mapdirection = new HashMap<Integer, Pair>();
		mapdirection.put(0, new Pair(1,0));
		mapdirection.put(1, new Pair(0,1));
		mapdirection.put(2, new Pair(-1,0));
		mapdirection.put(3, new Pair(-1,0));
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
				row.add("");
			}			
		}
	}
	
	int partI() {
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
		
		
		return -1;
	}
	
	@Override
	public String toString() {
		String out = "";
		for (ArrayList<String> row : grid) {
			// to do concatenate row to string
			out += String.join("", row) + System.lineSeparator();
		}
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
	
	void add(Pair other) {
		j += other.j;
		i += other.i;
	}
	
	@Override
	public String toString() {
		return "(" + j + ", " + i + ")";
	}
}