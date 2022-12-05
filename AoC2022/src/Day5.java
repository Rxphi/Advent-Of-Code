import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class Day5 {
	
	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./src/input5.txt");
		Scanner sc = new Scanner(input);
		
		Stacks craneStacks = new Stacks(9);
		craneStacks.stacks.get(0).addAll(new ArrayList<String> (Arrays.asList("F", "R", "W")));
		craneStacks.stacks.get(1).addAll(new ArrayList<String> (Arrays.asList("P", "W", "V", "D", "C", "M", "H", "T")));
		craneStacks.stacks.get(2).addAll(new ArrayList<String> (Arrays.asList("L", "N", "Z", "M", "P")));
		craneStacks.stacks.get(3).addAll(new ArrayList<String> (Arrays.asList("R", "H", "C", "J")));
		craneStacks.stacks.get(4).addAll(new ArrayList<String> (Arrays.asList("B", "T", "Q", "H", "G", "P", "C")));
		craneStacks.stacks.get(5).addAll(new ArrayList<String> (Arrays.asList("Z", "F", "L", "W", "C", "G")));
		craneStacks.stacks.get(6).addAll(new ArrayList<String> (Arrays.asList("C", "G", "J", "Z", "Q", "L", "V", "W")));
		craneStacks.stacks.get(7).addAll(new ArrayList<String> (Arrays.asList("C", "V", "T", "W", "F", "R", "N", "P")));
		craneStacks.stacks.get(8).addAll(new ArrayList<String> (Arrays.asList("V", "S", "R", "G", "H", "W", "J")));

		for (int i = 0; i < 10; i++) {
			sc.nextLine();
		}
		
		String line;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			// part I
			//craneStacks.moveI(line);
			
			// part II
			craneStacks.moveII(line);
		}
		
		//String partI = craneStacks.getTop();
		String partII = craneStacks.getTop();
		
		System.out.println("Day V");
		//System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}
}

class Stacks {
	ArrayList<LinkedList<String>> stacks;
	
	Stacks (int size) {
		stacks = new ArrayList<LinkedList<String>>();
		for (int i = 0; i < size; i++) {
			stacks.add(new LinkedList<String>());
		}
	}
	
	void moveI(String instruction) {
		String[] instructionList = instruction.split(" ");
		int amount = Integer.parseInt(instructionList[1]);
		int from = Integer.parseInt(instructionList[3]) - 1;
		int to = Integer.parseInt(instructionList[5]) - 1;
		
		for (int i = 0; i < amount; i++) {
			stacks.get(to).addFirst(stacks.get(from).removeFirst());
		}
	}
	
	void moveII(String instruction) {
		String[] instructionList = instruction.split(" ");
		int amount = Integer.parseInt(instructionList[1]);
		int from = Integer.parseInt(instructionList[3]) - 1;
		int to = Integer.parseInt(instructionList[5]) - 1;
		
		LinkedList<String> toAdd = new LinkedList<String>();
		
		for (int i = 0; i < amount; i++) {
			stacks.get(to).add(i, stacks.get(from).remove(0));
		}
	}
	
	String getTop() {
		String out = "";
		
		for (LinkedList stack : stacks) {
			if (stack.size() < 1) {
				continue;
			} else {	
				out += stack.getFirst();
			}
		}
		
		return out;
	}
}
