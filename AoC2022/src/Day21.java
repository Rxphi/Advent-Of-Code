import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day21 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		Map<String, String> yell = new HashMap<String, String>();
		
		String line = "";
		
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			yell.put(line.split(": ")[0], line.split(": ")[1]);
		}
		
		System.out.println(yell);
		
		long partI = partI(yell);
		long partII = partII(yell);
		
		System.out.println("Day XXI");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}
	
	static long partI(Map<String, String> yell) {
		return resolveI("root", yell);
	}
	
	static long resolveI(String current, Map<String, String> yell) {
		String[] currentsplit = yell.get(current).split(" ");
		if (currentsplit.length == 1) {
			return Long.parseLong(currentsplit[0]);
		} else {
			String left = currentsplit[0];
			String op = currentsplit[1];
			String right = currentsplit[2];
			if (op.equals("+")) {
				return resolveI(left, yell) + resolveI(right, yell);
			} else if (op.equals("-")) {
				return resolveI(left, yell) - resolveI(right, yell);
			} else if (op.equals("*")) {
				return resolveI(left, yell) * resolveI(right, yell);
			} else if (op.equals("/")) {
				return resolveI(left, yell) / resolveI(right, yell);
			}
		}
		return -1;
	}
	
	static long partII(Map<String, String> yell) {
		long left = Long.MAX_VALUE;
		long right = Long.MAX_VALUE;
		try {
			left = resolveII(yell.get("root").split(" ")[0], yell);
		} catch (Exception e) {
			try {
				right = resolveII(yell.get("root").split(" ")[2], yell);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
		
		if (left == Long.MAX_VALUE) {
			return mustEqual(right, yell.get("root").split(" ")[0], yell);
		} else {
			return mustEqual(left, yell.get("root").split(" ")[2], yell);
		}
	}
	
	static long mustEqual(long equal, String current, Map<String, String> yell) {
		System.out.println("Must equal " + current);
		if (current.equals("humn")) {
			return equal;
		}
		long left = Long.MAX_VALUE;
		long right = Long.MAX_VALUE;
		
		String currentleft = yell.get(current).split(" ")[0];
		String currentright = yell.get(current).split(" ")[2];
		String op = yell.get(current).split(" ")[1];
		
		try {
			left = resolveII(currentleft, yell);
		} catch (Exception e) {
			try {
				right = resolveII(currentright, yell);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
		
		if (left == Long.MAX_VALUE) {
			if (op.equals("+")) {
				return mustEqual(equal-right, currentleft, yell);
			} else if (op.equals("-")) {
				return mustEqual(equal+right, currentleft, yell);
			} else if (op.equals("*")) {
				return mustEqual(equal/right, currentleft, yell);
			} else if (op.equals("/")) {
				return mustEqual(equal*right, currentleft, yell);
			}
		} else {
			if (op.equals("+")) {
				return mustEqual(equal-left, currentright, yell);
			} else if (op.equals("-")) {
				return mustEqual(left-equal, currentright, yell);
			} else if (op.equals("*")) {
				return mustEqual(equal/left, currentright, yell);
			} else if (op.equals("/")) {
				return mustEqual(left/equal, currentright, yell);
			}
		}
		return Long.MIN_VALUE;
	}
	
	static long resolveII(String current, Map<String, String> yell) throws Exception{
		System.out.println("Resolving " + current);
		if (current.equals("humn")) {
			throw new Exception("Found humn");
		} 
		String[] currentsplit = yell.get(current).split(" ");
		if (currentsplit.length == 1) {
			return Long.parseLong(currentsplit[0]);
		} else {
			String left = currentsplit[0];
			String op = currentsplit[1];
			String right = currentsplit[2];
			long out = 0;
			if (op.equals("+")) {
				return resolveII(left, yell) + resolveII(right, yell);
			} else if (op.equals("-")) {
				return resolveII(left, yell) - resolveII(right, yell);
			} else if (op.equals("*")) {
				return resolveII(left, yell) * resolveII(right, yell);
			} else if (op.equals("/")) {
				return resolveII(left, yell) / resolveII(right, yell);
			}
		}
		return -1;
	}
}


























