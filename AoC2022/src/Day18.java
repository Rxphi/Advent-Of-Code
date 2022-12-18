import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day18 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input18.txt");
		Scanner sc = new Scanner(input);
		
		Set<xyzPos> positions = new LinkedHashSet<xyzPos>();
		
		int maxx = 0;
		int maxy = 0;
		int maxz = 0;
		
		String line = "";
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			int x = Integer.parseInt(line.split(",")[0]);
			int y = Integer.parseInt(line.split(",")[1]);
			int z = Integer.parseInt(line.split(",")[2]);
			maxx = x > maxx ? x : maxx;
			maxy = y > maxy ? y: maxy;
			maxz = z > maxz ? z : maxz;
			xyzPos newPos = new xyzPos(x, y, z);
			for (xyzPos p : positions) {
				p.isAdjacent(newPos);
			}
			positions.add(newPos);
		}
		
		Grid map = new Grid(maxx, maxy, maxz); // for Part II
		int partI = 0;
		for (xyzPos p : positions) {
			map.add(p);
			partI += p.area;
		}
		
		int partII = map.realSurfaceArea();
		

		
		System.out.println("Day XVIII");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}

}

class Grid {
	int x;
	int y;
	int z;
	boolean[][][] grid;
	boolean[][][] visited;
	
	Grid(int x, int y, int z) {
		this.x = x+3;
		this.y = y+3;
		this.z = z+3;
		grid = new boolean[this.x][this.y][this.z];
		visited = new boolean[this.x][this.y][this.z];
		//System.out.println("New Grid with Dimensions: " + this.x + "x" + this.y + "x" + this.z);
	}
	
	public void add(xyzPos p) {
		grid[p.x+1][p.y+1][p.z+1] = true;
	}
	
	public int realSurfaceArea() { // does a BFS search on the outside, simulating the expanding steam
		int out = 0;
		
		
		LinkedList<xyzPos> q = new LinkedList<xyzPos>();
		
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				for (int k = 0; k < z; k++) {
					if (i == 0 || i == x-1 || j == 0 || j == y-1 || k == 0 || k == z-1) {						
						q.add(new xyzPos(i,j,k));
					}
				}
			}
		}
		
		while (!q.isEmpty()) {
			xyzPos c = q.removeFirst();
			if (visited[c.x][c.y][c.z]) {
				continue;
			}
			visited[c.x][c.y][c.z] = true;
			
			ArrayList<xyzPos> unvisited = new ArrayList<xyzPos>();
			
			for (int dx = -1; dx < 2; dx+=2) {
				if ((c.x+dx < 0) || (c.x+dx >= x)) {
					continue;
				}
				if (grid[c.x+dx][c.y][c.z]) {
					//System.out.println("(" + (c.x+dx-1) + ", " + (c.y-1) + ", " + (c.z-1) + ")");
					out++;
				} else if (!visited[c.x+dx][c.y][c.z]) {
					unvisited.add(new xyzPos(c.x+dx, c.y, c.z));
				}
			}
			
			for (int dy = -1; dy < 2; dy+=2) {
				if ((c.y+dy < 0) || (c.y+dy >= y)) {
					continue;
				}
				if (grid[c.x][c.y+dy][c.z]) {
					//System.out.println("(" + (c.x-1) + ", " + (c.y+dy-1) + ", " + (c.z-1) + ")");
					out++;
				} else if (!visited[c.x][c.y+dy][c.z]) {
					unvisited.add(new xyzPos(c.x, c.y+dy, c.z));
				}
			}
			
			for (int dz = -1; dz < 2; dz+=2) {
				if ((c.z+dz < 0) || (c.z+dz >= z)) {
					continue; 
				}
				if (grid[c.x][c.y][c.z+dz]) {
					//System.out.println("(" + (c.x-1) + ", " + (c.y-1) + ", " + (c.z+dz-1) + ")");
					out++;
				} else if (!visited[c.x][c.y][c.z+dz]) {
					unvisited.add(new xyzPos(c.x, c.y, c.z+dz));
				}
			}
			
			q.addAll(unvisited);
		}
		return out;
	}
}

class xyzPos {
	int x;
	int y; 
	int z;
	int area;
	
	xyzPos(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
		area = 6;
	}

	public String toString() {
		return "(" + x + ", " + y + ", " + z + "), area = " + area;
	}
	
	public void isAdjacent(xyzPos other) {
		int dx = Math.abs(x-other.x);
		int dy = Math.abs(y-other.y);
		int dz = Math.abs(z-other.z);
		
		if (dx == 0 && dy == 0 && dz == 0) {
			this.area = 0;
		} else if (dx == 0 && dy == 0 && dz == 1) {
			this.area -= 1;
			other.area -= 1;
		} else if (dx == 0 && dy == 1 && dz == 0) {
			this.area -= 1;
			other.area -= 1;
		} else if (dx == 1 && dy == 0 && dz == 0) {
			this.area -= 1;
			other.area -= 1;
		}
	}
}
