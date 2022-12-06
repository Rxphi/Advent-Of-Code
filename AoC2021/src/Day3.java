import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.util.BitSet;
public class Day3 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input3.txt");
		Scanner sc = new Scanner(input);
		
		
		ArrayList<String> nums = new ArrayList<String>();
		
		String line;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty() ) {
			nums.add(line);
		}
		
		int gammaRate = 0;
		int epsilonRate = 0;
		int length = nums.get(0).length();
		
		
		
		// Part I 
		for (int i = 0; i < length; i++) {
			int numberOfOnes = 0;
			for (String num : nums) {
				if (num.charAt(i) == '1') {
					numberOfOnes++;
				}
			}
			if (numberOfOnes >= nums.size() / 2) {
				gammaRate += (int) Math.pow(2, length - i - 1);				
			} else {
				epsilonRate += (int) Math.pow(2, length - i - 1);
			}			
		}
		int partI = gammaRate * epsilonRate;
		
		
		// Part II
		ArrayList<String> oxygenGenerator = new ArrayList<String>(nums);
		ArrayList<String> co2Scrubber = new ArrayList<String>(nums);
		
		int i = 0;
		while (oxygenGenerator.size() != 1) {
			int numberOfOnes = 0;
			int numberOfZeros = 0;
			char mostCommon;
			for (String num : oxygenGenerator) {
				if (num.charAt(i) == '1') {
					numberOfOnes++;
				} else {
					numberOfZeros++;
				}
			}
			if (numberOfOnes >= numberOfZeros) {
				mostCommon = '1';
			} else {
				mostCommon = '0';
			}
			for (int j = oxygenGenerator.size()-1; j >= 0; j--) {
				if (oxygenGenerator.get(j).charAt(i) != mostCommon) {
					oxygenGenerator.remove(j);
				}
			}
			i++;
		}
		//System.out.println("Oxygen: " + oxygenGenerator.get(0));

		
		i = 0;
		while (co2Scrubber.size() != 1) {
			int numberOfOnes = 0;
			int numberOfZeros = 0;
			char leastCommon;
			for (String num : co2Scrubber) {
				if (num.charAt(i) == '1') {
					numberOfOnes++;
				} else {
					numberOfZeros++;
				}
			}
			if (numberOfOnes < numberOfZeros) {
				leastCommon = '1';
			} else {
				leastCommon = '0';
			}
			for (int j = co2Scrubber.size()-1; j >= 0; j--) {
				if (co2Scrubber.get(j).charAt(i) != leastCommon) {
					co2Scrubber.remove(j);
				}
			}
			i++;
		}
		//System.out.println("co2: " + co2Scrubber.get(0));

		int partII = bitStringToInt(oxygenGenerator.get(0)) * bitStringToInt(co2Scrubber.get(0));
		
		System.out.println("Day III");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
		
	}
	
	public static int bitStringToInt(String bitString) {
		int out = 0;
		
		int l = bitString.length();
		
		for (int i = 0; i < l; i++) {
			if (bitString.charAt(i) == '1') {
				out += (int) Math.pow(2, l-i-1);
			}
		}
		return out;
	}

}
