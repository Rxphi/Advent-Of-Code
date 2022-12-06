import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.LinkedList;

public class Day5 {
	
	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./src/input5.txt");
		Scanner sc = new Scanner(input);
		
		// get the number of stacks
		String line = "";
		while(sc.hasNextLine() && (line = sc.nextLine()).charAt(1) != '1') {
			continue;
		}
		int numOfStacks = line.split("   ").length;
		
		// create two stacks for the two parts
		Stacks craneI = new Stacks(numOfStacks);
		Stacks craneII = new Stacks(numOfStacks);
		
		// restart the scanner
		sc = new Scanner(input);
		
		while (sc.hasNextLine() && (line = sc.nextLine()).charAt(1) != '1') {
			for (int i = 0; i < numOfStacks; i++) {
				String toAdd = line.substring(1+4*i, 2+4*i);
				if (!toAdd.equals(" ")) {
					craneI.stacks.get(i).addLast(toAdd);
					craneII.stacks.get(i).addLast(toAdd);
				}
			}
		}
				
		// skip empty line
		sc.nextLine();
		
		// read the move instructions and execute them on both Stacks
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			craneI.moveI(line);
			craneII.moveII(line);
		}
		
		// get and print the solutions
		String partI = craneI.getTop();
		String partII = craneII.getTop();
		
		System.out.println("Day V");
		System.out.println("Part I " + partI);
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
	
	int[] readInstructions(String instruction) {
		int[] out = new int[3]; // stores "amount", "from" and "to" value
		String[] instructionList = instruction.split(" ");
		out[0] = Integer.parseInt(instructionList[1]); // amount
		out[1] = Integer.parseInt(instructionList[3]) - 1; // from
		out[2] = Integer.parseInt(instructionList[5]) - 1; // to
		return out;
	}
	
	void moveI(String instruction) {
		int[] instructs = readInstructions(instruction);
		for (int i = 0; i < instructs[0]; i++) {
			stacks.get(instructs[2]).addFirst(stacks.get(instructs[1]).removeFirst());
		}
	}
	
	void moveII(String instruction) {
		int[] instructs = readInstructions(instruction);
		for (int i = 0; i < instructs[0]; i++) {
			stacks.get(instructs[2]).add(i, stacks.get(instructs[1]).remove(0));
		}
	}
	
	String getTop() {
		String out = "";
		for (LinkedList<String> stack : stacks) {
			if (stack.size() < 1) {
				continue;
			} else {	
				out += stack.getFirst();
			}
		}
		return out;
	}
	
	// not needed
	void printMe() {
		for (int i = 1; i <= stacks.size(); i++) {
			System.out.println(i + ": " + stacks.get(i-1));
		}
	}
}
