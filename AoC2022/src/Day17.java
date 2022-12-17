import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day17 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input17.txt");
		
		Chamber location = new Chamber(new Scanner(input));
		int partI = location.partI();
		long partII = 0;//location.partII();
		
		System.out.println("Day XVII");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}

}

class Chamber {
	List<List<String>> grid;
	
	ArrayList<String> jets;
	int j = 0;
	
	ArrayList<String> shapes = new ArrayList<String>(Arrays.asList("-", "+", "J", "I", "o"));
	int s = 0;
			
	Chamber(Scanner sc) {
		jets = new ArrayList<String>(Arrays.asList(sc.nextLine().split("")));
	}
	
	int partI() {
		grid = new ArrayList<List<String>>();

		j = 0;
		int height = 0;
		for (int n = 0; n < 2022; n++) {
			String shape = shapes.get(s);
			int x = 2;
			int y = height + 3;
			
			if (shape.equals("+")) {
				x++;
			}
			int numOfRowsToAdd = Math.max(0, height-grid.size()+7);
			
			for (int k = 0; k < numOfRowsToAdd; k++) {
				List<String> newRow = new ArrayList<String>(Arrays.asList(".", ".", ".", ".", ".", ".", "."));
				grid.add(grid.size(), newRow);
			}
			
			
			boolean falling = true;
			while (falling) {
				boolean blocked = false;
				String jet = jets.get(j);
				/*System.out.println("x = " + x + ", y = " + y);
				System.out.println(jet);*/
				
				if (shape.equals("-")) {
					// push
					if (jet.equals("<") && !(x-1 < 0) && !(get(x-1, y).equals("#"))) {
						x--;
					} else if (jet.equals(">") && !(x+4 > 6) && !(get(x+4, y).equals("#"))){
						x++;
					}
					// fall
					for (int l = 0; l < 4; l++) {
						if (y == 0 || get(x+l, y-1).equals("#")) {
							blocked = true;
						}
					}
				} else if (shape.equals("+")) {
					// push
					if (jet.equals("<") && !(x-2 < 0) && !(get(x-1,y).equals("#")) && !(get(x-2,y+1).equals("#")) && !(get(x-1,y+2).equals("#"))) {
						x--;
					} else if (jet.equals(">") && !(x+2 > 6) && !(get(x+1,y).equals("#")) && !(get(x+2,y+1).equals("#")) && !(get(x+1,y+2).equals("#"))) {
						x++;
					}
					// fall
					if (y == 0 || get(x,y-1).equals("#") || get(x-1,y).equals("#") || get(x+1,y).equals("#")) {
						blocked = true;
					}
				} else if (shape.equals("J")) {
					// push
					if (jet.equals("<") && !(x-1 < 0) && !(get(x-1,y).equals("#")) && !(get(x+1,y+1).equals("#")) && !(get(x+1,y+2).equals("#"))) {
						x--;
					} else if (jet.equals(">") && !(x+3 > 6) && !(get(x+3,y).equals("#")) && !(get(x+3,y+1).equals("#")) && !(get(x+3,y+2).equals("#"))) {
						x++;
					}
					// fall
					if (y == 0 || get(x,y-1).equals("#") || get(x+1,y-1).equals("#") || get(x+2,y-1).equals("#")) {
						blocked = true;
					}
				} else if (shape.equals("I")) {
					// push
					if (jet.equals("<") && !(x-1 < 0) && !(get(x-1,y).equals("#")) && !(get(x-1,y+1).equals("#")) && !(get(x-1,y+2).equals("#")) && !(get(x-1,y+3).equals("#"))) {
						x--;
					} else if (jet.equals(">") && !(x+1 > 6) && !(get(x+1,y).equals("#")) && !(get(x+1,y+1).equals("#")) && !(get(x+1,y+2).equals("#")) && !(get(x+1,y+3).equals("#"))) {
						x++;
					}
					// fall
					if (y == 0 || get(x,y-1).equals("#")) {
						blocked = true;
					}
				} else if (shape.equals("o")) {
					// push
					if (jet.equals("<") && !(x-1 < 0) && !(get(x-1,y).equals("#")) && !(get(x-1,y+1).equals("#"))) {
						x--;
					} else if (jet.equals(">") && !(x+2 > 6) && !(get(x+2,y).equals("#")) && !(get(x+2,y+1).equals("#"))) {
						x++;
					}
					if (y == 0 || get(x,y-1).equals("#") || get(x+1,y-1).equals("#")) {
						blocked = true;
					}
				}
				
				// actually falling
				if (blocked) {
					falling = false;
				} else {
					y--;
				}
				// next jet
				j = (j+1) % (jets.size());
				
			}
			// draw the shape into the grid with #
			if (shape.equals("-")) {
				for (int l = 0; l < 4; l++) {
					grid.get(y).set(x+l, "#");
				}
				height = y+1 > height ? y+1 : height;
			} else if (shape.equals("+")) {
				for (int l = -1; l < 2; l++) {
					grid.get(y+1+l).set(x, "#");
					grid.get(y+1).set(x+l, "#");
				}
				height = y+3 > height ? y+3 : height;
			} else if (shape.equals("J")) {
				for (int l = -2; l < 1; l++) {
					grid.get(y).set(x-l, "#");
					grid.get(y-l).set(x+2, "#");
				}
				height = y+3 > height ? y+3 : height;
			} else if (shape.equals("I")) {
				for (int l = 0; l < 4; l++) {
					grid.get(y+l).set(x, "#");
				}
				height = y+4 > height ? y+4 : height;
			} else if (shape.equals("o")) {
				grid.get(y).set(x, "#");
				grid.get(y).set(x+1, "#");
				grid.get(y+1).set(x, "#");
				grid.get(y+1).set(x+1, "#");
				height = y+2 > height ? y+2 : height;
			}
			//System.out.println(this);
			s = (s+1)%(shapes.size());
		}
		
		return height;
	}
	
	String get(int x, int y) {
		return grid.get(y).get(x);
	}
	
	long partII() {
		long base = 0;
		long height = 0;
		int gridHeight = 0;
		j = 0;
		s = 0;
		
		Map<Integer, ArrayList<Integer>> intToBitMask = new HashMap<Integer, ArrayList<Integer>>();
		intToBitMask.put(0, new ArrayList<Integer>(Arrays.asList(15)));
		intToBitMask.put(1, new ArrayList<Integer>(Arrays.asList(2, 7, 2)));
		intToBitMask.put(2, new ArrayList<Integer>(Arrays.asList(7, 1, 1)));
		intToBitMask.put(3, new ArrayList<Integer>(Arrays.asList(1, 1, 1, 1)));
		intToBitMask.put(4, new ArrayList<Integer>(Arrays.asList(3, 3)));
		
		Map<Integer, Integer> grid = new HashMap<Integer, Integer>(); // from row number to integer that represents this row (bits represent cells) 

		long upTo = 2022;
		
		for (long n = 0; n < upTo; n++) {
			ArrayList<Integer> shape = intToBitMask.get(s);
			int y = ((int) (height - base)) + 3;
			
			int rowsToAdd = Math.max(0, y - gridHeight);
			
			for (int k = 0; k < rowsToAdd; k++) {
				grid.put(gridHeight + k, 0);
			}
			
			boolean falling = true;
			while (falling) {
				// push
				
				// fall
				j = j+1 > jets.size() ? 0 : j+1;
			}
			
			
			
			s = (s+1) % 5;
		}
		
		return height;
	}
	
	public String toString() {
		String out = "";
		for (int i = grid.size()-1; i >= 0; i--) {
			out += "|";
			List<String> row = grid.get(i);
			for (String s : row) {
				out += s;
			}
			out += "|\n";
		}
		out += "+-------+\n";
		return out;
	}
	
	public String toString(Map<Integer, Integer> grid, int gridHeight) {
		return null;
	}
}