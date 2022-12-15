import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day15 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input15.txt");
		Scanner sc = new Scanner(input);
		
		String line;
		int minx = 0;
		int maxx = 0;
		int miny = 0;
		int maxy = 0;
		int currentx;
		int currenty;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			String[] lineSplit = line.split("[=,: ]");
			currentx = Integer.parseInt(lineSplit[3]);
			currenty = Integer.parseInt(lineSplit[6]);
			minx = currentx < minx ? currentx : minx;
			maxx = currentx > maxx ? currentx : maxx;
			miny = currenty < miny ? currenty : miny;
			maxy = currenty > maxy ? currenty : maxy;
			
			currentx = Integer.parseInt(lineSplit[13]);
			currenty = Integer.parseInt(lineSplit[16]);
			minx = currentx < minx ? currentx : minx;
			maxx = currentx > maxx ? currentx : maxx;
			miny = currenty < miny ? currenty : miny;
			maxy = currenty > maxy ? currenty : maxy;
		}
		
		//System.out.println(minx + " " + maxx + " " + miny + " " + maxy);
		SensorMap myMap = new SensorMap(2000000);
		
		sc = new Scanner(input);
		
		while(sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			myMap.addInputLine(line);
		}
		
		
		int partI = myMap.partI();
		long partII = myMap.partII();
		
		System.out.println("Day XV"); 
		System.out.println("Part I: " + partI);
		System.out.println("Part II: " + partII);
	}

}

class SensorMap {
	int width;
	int height;
	String[] row;
	int rowy;
	int rowshift;
	ArrayList<Integer> sensorxarr;
	ArrayList<Integer> sensoryarr;
	ArrayList<Integer> radiusarr;
	SensorMap (int rowy){
		width = 4000001;
		height = 4000001;
		row = new String[4*width];
		this.rowy = rowy;
		rowshift = -width;
		sensorxarr = new ArrayList<Integer>();
		sensoryarr = new ArrayList<Integer>();
		radiusarr = new ArrayList<Integer>();
		System.out.println("Grid dimension: " + height + " x " + width);
	}
	
	void addInputLine(String line) {
		String[] lineSplit = line.split("[=,: ]");
		int sensorx = Integer.parseInt(lineSplit[3]);
		int sensory = Integer.parseInt(lineSplit[6]);
		int beaconx = Integer.parseInt(lineSplit[13]);
		int beacony = Integer.parseInt(lineSplit[16]);
		
		int manhattan = Math.abs(sensorx-beaconx) + Math.abs(sensory-beacony);
		
		sensorxarr.add(sensorx);
		sensoryarr.add(sensory);
		radiusarr.add(manhattan);
		mark(sensorx, sensory, manhattan, beaconx, beacony);
	}
	
	void mark(int x, int y, int r, int beaconx, int beacony) {
		// part I
		for (int j = 0; j < row.length; j++) {
			if (manhattan(x, y, j+rowshift, rowy) <= r) {
				row[j] = "#";
			}
		}
		if (y == rowy) {
			row[x-rowshift] = "S";
		}
		if (beacony == rowy) {
			row[beaconx-rowshift] = "B";
		}
	}
	
	public int manhattan (int x1, int y1, int x2, int y2) {
		return Math.abs(x1-x2) + Math.abs(y1-y2);
	}
	
	int partI () {
		int out = 0;
		for (String s : row) {
			if (s != null && s.equals("#")) {
				out++;
			}
		}
		return out;
	}
	
	long partII () {
		for (int i = 0; i < height; i++) {
			for (long j = 0; j < width; j++) {
//				System.out.println("checking " + j + " " + i);
				boolean detected = false;
				int maxdelta = 0;
				for (int k = 0; k < sensorxarr.size(); k++) {
					int x = sensorxarr.get(k);
					int y = sensoryarr.get(k);
					int r = radiusarr.get(k);
					int dist = manhattan((int) j, i, x, y);
					if (dist <= r) {
						maxdelta = r - dist;
						detected = true;
						break;
					}
				}
				if (!detected) {
					System.out.println(j + " " + i);
					return i + 4000000 * j;
				}
				j += maxdelta;
			}
		}
		return -1;
	}
}











