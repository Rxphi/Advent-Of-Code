import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Day7 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input7.txt");
		Scanner sc = new Scanner(input);
		
		ArrayList<Long> horizontalPos = new ArrayList<Long>();
		
		for (String s : sc.nextLine().split(",")) {
			long toAdd = Long.parseLong(s);
			horizontalPos.add(toAdd);
		}

		// get min and max
		long min = horizontalPos.get(0);
		long max = min;
		for (long n : horizontalPos) {
			min = n < min ? n : min;
			max = n > max ? n : max;
		}
		
		// calculate partI & partIi
		long partI = Long.MAX_VALUE;
		long partII = Long.MAX_VALUE;
		for (long align = min; align <= max; align++) {
			long currentI = 0;
			long currentII = 0;
			for (long h : horizontalPos) {
				long delta = Math.abs(h - align);
				currentI += delta;
				currentII += (delta+1)*(delta/2);   
				if (delta % 2 != 0) {
					currentII += (delta + 1) / 2;
				}
			}
			partI = currentI < partI ? currentI : partI;
			partII = currentII < partII ? currentII : partII;
		}
		
		System.out.println("Day VII");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}
}
