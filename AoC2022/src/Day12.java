import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day12 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input12.txt");
		Scanner sc = new Scanner(input);
		
		HeightMap myMap = new HeightMap(sc);
		//System.out.println(myMap);
		
		int partI = myMap.partI();
		myMap.reset();
		int partII = myMap.partII();
		
		//System.out.println("Start: " + myMap.start + "End: " + myMap.end);
		
		System.out.println("Day XII");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}

class HeightMap {
	ArrayList<ArrayList<Pos>> grid;
	Pos start;
	Pos end;
	int width;
	int height;
	
	HeightMap (Scanner sc){
		grid = new ArrayList<ArrayList<Pos>>();
		String line;
		int i = 0;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			ArrayList<Pos> newRow = new ArrayList<Pos>();
			for (int j = 0; j < line.length(); j++) {
				char c = line.charAt(j);
				if (c == 'S') {
					start = new Pos(i, j, 0);
					newRow.add(start);
				} else if (c == 'E') {
					end = new Pos(i, j, 25);
					newRow.add(end);
				} else {
					newRow.add(new Pos(i, j, (int) c - 97));
				}
			}
			grid.add(newRow);
			i++;
		}
		width = grid.get(0).size();
		height = grid.size();
		System.out.println("Heightmap dimensions: " + height + " x " + width + " -> Num. of points: " + height*width);
	}
	
	// BFS starting at the start vertex
	int partI () {
		LinkedList<Pos> q = new LinkedList<Pos>();
		q.add(start);
		
		while (!q.isEmpty()) {
			Pos current = q.removeFirst();
			if (current.equals(end)) { // if at the end return
				return current.pathLength;
			}
			ArrayList<Pos> neigh = getNeighI(current);
			for (Pos n : neigh) {
				n.explored = true;
				n.pathLength = current.pathLength + 1;
				q.addLast(n);
			}
		}
		return -1;
	}
	
	void reset() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				grid.get(i).get(j).explored = false;
				grid.get(i).get(j).pathLength = 0;
			}
		}
	}
	
	// BFS starting at the end vertex
	int partII () {
		LinkedList<Pos> q = new LinkedList<Pos>();
		q.add(end);
		
		while(!q.isEmpty()) {
			Pos current = q.removeFirst();
			if (current.h == 0) { // if found an 'a' vertex return
				return current.pathLength;
			}
			ArrayList<Pos> neigh = getNeighII(current);
			for (Pos n : neigh) {
				n.explored = true;
				n.pathLength = current.pathLength + 1;
				q.addLast(n);
			}
		}
		return -1;
	}
	
	ArrayList<Pos> getNeighI (Pos p) {
		ArrayList<Pos> out = new ArrayList<Pos>();
		
		for (int di = -1; di < 2; di+=2) {
			if (p.i+di >= 0 && p.i+di < height && !grid.get(p.i+di).get(p.j).explored && (grid.get(p.i+di).get(p.j).h - p.h) < 2) {
				out.add(grid.get(p.i+di).get(p.j));
			}
		}
		for (int dj = -1; dj < 2; dj+=2) {
			if (p.j+dj >= 0 && p.j+dj < width && !grid.get(p.i).get(p.j+dj).explored && (grid.get(p.i).get(p.j+dj).h - p.h) < 2) {
				out.add(grid.get(p.i).get(p.j+dj));
			}
		}
		return out;
	}
	
	ArrayList<Pos> getNeighII (Pos p) {
		ArrayList<Pos> out = new ArrayList<Pos>();
		
		for (int di = -1; di < 2; di+=2) {
			if (p.i+di >= 0 && p.i+di < height && !grid.get(p.i+di).get(p.j).explored && (p.h - grid.get(p.i+di).get(p.j).h) < 2) {
				out.add(grid.get(p.i+di).get(p.j));
			}
		}
		for (int dj = -1; dj < 2; dj+=2) {
			if (p.j+dj >= 0 && p.j+dj < width && !grid.get(p.i).get(p.j+dj).explored && (p.h - grid.get(p.i).get(p.j+dj).h) < 2) {
				out.add(grid.get(p.i).get(p.j+dj));
			}
		}
		return out;
	}
	
	public String toString() {
		String out = "HeightMap:" + System.lineSeparator();
		out += "Start: " + start;
		out += "End: " + end;
		for (ArrayList<Pos> row : grid) {
			for (Pos p : row) {
				out += p.h + " ";
				if (p.h < 11) {
					out += " ";
				}
			}
			out += System.lineSeparator();
		}
		return out;
	}
}

class Pos{
	int i;
	int j;
	int h;
	boolean explored;
	int pathLength;
	
	Pos (int i, int j, int h) {
		this.i = i;
		this.j = j;
		this.h = h;
		explored = false;
		pathLength = 0;
	}
	
	public String toString() {
		return "i = " + i + ", j = " + j + System.lineSeparator();
	}
	
	public boolean equals(Pos other) {
		return this.i == other.i && this.j == other.j && this.h == other.h;
	}
	
}