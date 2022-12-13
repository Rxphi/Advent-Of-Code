import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day13 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input13.txt");
		Scanner sc = new Scanner(input);
		
		// Part I
		int partI = 0;
		int index = 1;
		while (sc.hasNextLine()) {
			//System.out.println("Index " + index);
			if (compare(sc)) {
				partI += index;
				//System.out.println("Right Order!");
			}
			index++;
		}
		//
		
		// Part II
		sc = new Scanner(input);
		ArrayList<ArrayList<String>> packets = new ArrayList<ArrayList<String>>();
		while(sc.hasNextLine()) {
			ArrayList<String> newPacket = readLine(sc.nextLine());
			if (newPacket != null) {
				packets.add(newPacket);
			}
		}
		packets.add(readLine("[[2]]"));
		packets.add(readLine("[[6]]"));
		
		//System.out.println(packets);
		packets = bubbleSort(packets);
		//System.out.println(packets);
		int partII = decoderKey(packets);
		//
				
		System.out.println("Day XIII");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}
	
	// for part II to find the two dividers and return the decoder key
	public static int decoderKey(ArrayList<ArrayList<String>> kiste) {
		int div1 = 0;
		int div2 = 0;
		
		int i = 0;
		while (div1 == 0 || div2 == 0) {
			ArrayList<String> packet = kiste.get(i);
			if (packet.size() == 1) {
				String elem = packet.get(0);
				if (elem.equals("[2]")) {
					div1 = i+1;
				} else if (elem.equals("[6]")) {
					div2 = i+1;
				}
			}
			i++;
		}
		return div1 * div2;
	}
	
	// for part II to sort the packets
	public static ArrayList<ArrayList<String>> bubbleSort(ArrayList<ArrayList<String>> kiste) {
		for (int i = 0; i < kiste.size()-1; i++) {
			for (int j = i+1; j < kiste.size(); j++) {
				if (compare(kiste.get(i), kiste.get(j)) == 1) {
					//swap
					ArrayList<String> rem = kiste.get(i);
					kiste.set(i, kiste.get(j));
					kiste.set(j, rem);
				}
			}
		}
		return kiste;
	}
	
	// for partI to directly read the pairs
	public static boolean compare(Scanner sc) {
		String line1 = sc.nextLine();
		String line2 = sc.nextLine();
		if (sc.hasNextLine()) {
			sc.nextLine();
		}
		if (compare(readLine(line1), readLine(line2)) == -1) {
			return true;
		}
		return false;
	}

	// returns -1 if arr1 < arr2, 0 if arr1 = arr2, 1 if arr1 > arr2
	public static int compare(ArrayList<String> arr1, ArrayList<String> arr2) {
		
		//System.out.println("Comparing " + arr1 + " with " + arr2);
		
		arr1 = new ArrayList<String>(arr1);
		arr2 = new ArrayList<String>(arr2);
		int out = 0;
		while (!arr1.isEmpty() && !arr2.isEmpty() && out == 0) {
			String left = arr1.remove(0);
			String right = arr2.remove(0);
			
			boolean isLeftInt = left.charAt(0) != '[';
			boolean isRightInt = right.charAt(0) != '[';
			
			if (isLeftInt && isRightInt) {
				int l = Integer.parseInt(left);
				int r = Integer.parseInt(right);
				//System.out.println("Comparing " + l + " with " + r);
				if (l < r) {
					out = -1;
				} else if (l > r) {
					out =  1;
				}
			} else {
				if (isLeftInt) {
					left = "[" + left + "]";
				} else if (isRightInt) {
					right = "[" + right + "]";
				}
				
				int order = compare(readLine(left), readLine(right));
				if (order != 0) {
					out = order;
				}
			}
		}
		
		if (out != 0) {
			return out;
		} else if (arr1.isEmpty() && !arr2.isEmpty()) {
			return -1;
		} else if (arr2.isEmpty() && !arr1.isEmpty()) {
			return 1;
		} else {
			return 0;
		}
	}
	
	// converts a line of input into an actual arraylist of strings
	public static ArrayList<String> readLine(String line1) {
		int n = line1.length();
		if (n == 0) {
			return null;
		}
		ArrayList<String> out = new ArrayList<String>();
		int l = 1;
		
		while(l < n-1) {
			int r = l;
			int opened = 0;
			boolean hasOpen = false;
			if (line1.charAt(r) == '[') {
				opened = 1;
				hasOpen = true;
				r++;
			}
			while(r < n-1) {
				char c = line1.charAt(r);
				if (c == '[') {
					opened++;
				} else if (c == ']') {
					opened--;
				} else if (c == ',' && !hasOpen) {
					break;
				}
				r++;
				if (hasOpen && opened == 0) {
					break;
				}
			}
			out.add(line1.substring(l, r));
			l = r+1;
		}
		return out;
	}
}