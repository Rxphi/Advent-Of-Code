import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Day25 {

	static Map<Integer, String> intToSnafu = new HashMap<Integer, String>();
	static Map<String, Integer> snafuToInt = new HashMap<String, Integer>();
	
	public static void main(String[] args) throws FileNotFoundException{
		intToSnafu.put(-6, "--");
		intToSnafu.put(-5, "-0");
		intToSnafu.put(-4, "-1");
		intToSnafu.put(-3, "-2");
		intToSnafu.put(-2, "0=");
		intToSnafu.put(-1, "0-");
		intToSnafu.put(0, "00");
		intToSnafu.put(1, "01");
		intToSnafu.put(2, "02");
		intToSnafu.put(3, "1=");
		intToSnafu.put(4, "1-");
		intToSnafu.put(5, "10");
		intToSnafu.put(6, "11");
		
		snafuToInt.put("=", -2);
		snafuToInt.put("-", -1);
		snafuToInt.put("0", 0);
		snafuToInt.put("1", 1);
		snafuToInt.put("2", 2);
		
		File input = new File("./inputFiles/input25.txt");
		Scanner sc = new Scanner(input);
		String partI = "0";
		
		while(sc.hasNext()) {
			partI = addSNAFU(partI, sc.next());
		}
		
		System.out.println("Day XXV");
		System.out.println("Part I : " + partI);
	}
	
	static String addSNAFU(String num1, String num2) {
		LinkedList<String> out = new LinkedList<String>();
		
		String carry = "0";
		
		for (int i = 0; i < Math.min(num1.length(), num2.length()); i++) {
			String s1 = num1.substring(num1.length()-1-i, num1.length()-i);
			String s2 = num2.substring(num2.length()-1-i, num2.length()-i);
			
			String res = intToSnafu.get(snafuToInt.get(carry) + snafuToInt.get(s1) + snafuToInt.get(s2));
			out.addFirst(res.substring(1,2));
			carry = res.substring(0,1);
		}
		
		if (num1.length() < num2.length()) {
			for (int i = num2.length()-num1.length(); i > 0 ; i--) {
				String s2 = num2.substring(i-1, i);
				String res = intToSnafu.get(snafuToInt.get(carry) + snafuToInt.get(s2));
				out.addFirst(res.substring(1,2));
				carry = res.substring(0,1);
			}
		} else if (num2.length() < num1.length()) {
			for (int i = num1.length()-num2.length(); i > 0 ; i--) {
				String s1 = num1.substring(i-1, i);
				String res = intToSnafu.get(snafuToInt.get(carry) + snafuToInt.get(s1));
				out.addFirst(res.substring(1,2));
				carry = res.substring(0,1);
			}
		}
		
		if (!carry.equals("0")) {
			out.addFirst(carry);
		}
		
		return String.join("", out);
	}
	
	static long snafuToDecimal(String snafu) {
		long out = 0;
		long stelle = 1;
		for (int i = 0; i < snafu.length(); i++) {
			String s1 = snafu.substring(snafu.length()-1-i, snafu.length()-i);
			out += stelle * snafuToInt.get(s1);
			stelle *= 5;
		}
		return out;
	}

	
}



























