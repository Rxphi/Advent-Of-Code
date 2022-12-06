import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Day2 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File ("./inputFiles/input2.txt");
		Scanner sc = new Scanner (input);
		
		Submarine submarineI = new Submarine();
		Submarine submarineII = new Submarine();
		
		String line;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			submarineI.moveI(line);
			submarineII.moveII(line);
		}
		
		int partI = submarineI.horizontal * submarineI.vertical;
		int partII = submarineII.horizontal * submarineII.vertical;
		
		System.out.println("2021 Day II");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
		
	}

}


class Submarine {
	int horizontal;
	int vertical;
	int aim;
	
	Submarine (){
		System.out.print("Created new submarine ");
		print();
	}
	
	void moveI(String instruction) {
		String direction = instruction.split(" ")[0];
		int val = Integer.parseInt(instruction.split(" ")[1]);
				
		switch (direction) {
		case "forward":
			horizontal += val;
			break;
		case "down":
			vertical += val;
			break;
		case "up":
			vertical -= val;
			break;
		}
		//print();
	}
	
	void moveII(String instruction) {
		String direction = instruction.split(" ")[0];
		int val = Integer.parseInt(instruction.split(" ")[1]);
				
		switch (direction) {
		case "forward":
			horizontal += val;
			vertical += aim * val;
			break;
		case "down":
			aim += val;
			break;
		case "up":
			aim -= val;
			break;
		}
		//print();
	}
	
	void print() {
		System.out.println("horizontal: " + horizontal + " vertical: " + vertical + " aim: " + aim);
	}
}
