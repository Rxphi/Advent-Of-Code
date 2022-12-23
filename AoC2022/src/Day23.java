import java.util.*;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.io.File;

public class Day23 {

	public static void main(String[] args) throws IOException {
		File input = new File("./inputFiles/test.txt");
		
		Ground myGround = new Ground(input);
		myGround.round();
		System.out.println(myGround);
		
	}

}

class Ground {
	ArrayList<ArrayList<String>> grid = new ArrayList<ArrayList<String>>();
	int width;
	int height;
	
	LinkedList<Cell> directions = new LinkedList<Cell>();
	
	Ground(File input) throws IOException {
		Files.lines(input.toPath())
			.forEach(l -> grid.add(new ArrayList<String>(Arrays.asList(l.split("")))));
		width = grid.get(0).size();
		height = grid.size();
		directions.add(new Cell(0, -1));
		directions.add(new Cell(0, 1));
		directions.add(new Cell(-1, 0));
		directions.add(new Cell(1, 0));
		System.out.println(this);
		System.out.println("Dimensions: " + height + " x " + width);
	}
	
	public void round() {
		ArrayList<ArrayList<String>> newGrid = new ArrayList<ArrayList<String>>();
		for (int i = 0; i < height; i++) {
			ArrayList<String> newRow = new ArrayList<String>();
			for (int j = 0; j < width; j++) {
				newRow.add(".");
			}
			newGrid.add(newRow);
		}
		
		// first half
		ArrayList<Cell> cellsWithNeighbours = new ArrayList<Cell>();
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (grid.get(i).get(j).equals(".")) {
					continue;
				}
				boolean hasNoNeighbours = true;
				here:
				for (int di = -1; di < 2; di++) {
					for (int dj = -1; dj < 2; dj++) {
						if ((di == 0 && dj == 0) || i+di < 0 || i+di >= height || j+dj < 0 || j+dj >= width) {
							continue;
						} else if (grid.get(i+di).get(j+dj).equals("#")) {
							hasNoNeighbours = false;
							break here;
						}
					}
				}	
				if (hasNoNeighbours) {
					newGrid.get(i).set(j, "#");
				} else {
					cellsWithNeighbours.add(new Cell(j, i));
				}
			}
		}
		
		// Second half
		Map<Cell, ArrayList<Cell>> map = new HashMap<Cell, ArrayList<Cell>>();
		// To-Do
		for (Cell elf : cellsWithNeighbours) {
			for (Cell dir : directions) {
				
			}
		}
		
		grid = newGrid;
		directions.add(directions.removeFirst());
	}
	
	@Override 
	public String toString() {
		String out = "";
		for (ArrayList<String> row : grid) {
			out += row + System.lineSeparator();
		}
		return out;
	}
}

class Cell {
	int j;
	int i;
	
	Cell(int j, int i) {
		this.j = j;
		this.i = i;
	}
	
	public Cell add(Cell other) {
		return new Cell(j+other.j, i+other.i);
	}
}
