import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day11 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input11.txt");
		Scanner sc = new Scanner(input);
		
		// Part I
		MonkeyGroup crazyMonkeys = new MonkeyGroup(sc);
		crazyMonkeys.simulate(20, true);
		long partI = crazyMonkeys.business();
		
		// Part II
		sc = new Scanner(input);
		crazyMonkeys = new MonkeyGroup(sc);
		crazyMonkeys.simulate(10000, false);
		long partII = crazyMonkeys.business();
		
		
		System.out.println("Day XI");
		System.out.println("Part I " + partI + " - can't get the correct answer again :)");
		System.out.println("Part II " + partII);
	}

}

class MonkeyGroup {
	ArrayList<Monkey> monkeys;
	int mod;
	
	MonkeyGroup(Scanner sc) {
		monkeys = new ArrayList<Monkey>();
		mod = 1;
		String line;
		while (sc.hasNext() && !(line = sc.nextLine()).isEmpty()) {
			Monkey toAdd = new Monkey(sc);
			monkeys.add(toAdd);
			mod *= toAdd.testdiv;
		}
	}
	
	void simulate(int numOfRounds, boolean partI) {
		if (partI) {
			System.out.println("##### PART I #####");
		} else {
			System.out.println("##### PART II #####");
		}
		for (int i = 0; i < numOfRounds; i++) {	
			for (Monkey m : monkeys) {
				m.turn(mod, partI);
				
				Monkey iftrue = monkeys.get(m.iftrue);
				Monkey iffalse = monkeys.get(m.iffalse);
				
				iftrue.items.addAll(m.throwtotrue);
				iffalse.items.addAll(m.throwtofalse);
			}
			// UNCOMMENT TO PRINT INFOS
			
			if (partI || ((i+1) % 1000 == 0)) {
				printItems(i+1);
			} 
			
		}
	}
	
	long business() {
		long max1 = 0;
		long max2 = 0;
		
		for (int i = 0; i < monkeys.size(); i++) {
			long current = monkeys.get(i).numOfInspectedItems;
			if (current > max1) {
				max2 = max1;
				max1 = current;
			} else if (current > max2) {
				max2 = current;
			}
		}
		return max1 * max2;
	}
	
	void printItems(int round) {
		System.out.println("== After round " + round + " ==");
		for (int i = 0; i < monkeys.size(); i++) {
			System.out.println("Monkey " + i + " inspected " + monkeys.get(i).numOfInspectedItems + " items : " + monkeys.get(i).items);
		}
		System.out.println();
	}
	
	
}
class Monkey {
	LinkedList<Long> items;
	String operandleft;
	String operation;
	String operandright;
	long testdiv;
	int iftrue;
	int iffalse;
	long numOfInspectedItems;
	
	LinkedList<Long> throwtotrue;
	LinkedList<Long> throwtofalse;
	
	Monkey(Scanner sc) {
		String itemsLine = sc.nextLine();
		String operationLine = sc.nextLine();
		String testLine = sc.nextLine();
		String iftrueLine = sc.nextLine();
		String iffalseLine = sc.nextLine();
		if (sc.hasNextLine()) {			
			sc.nextLine();
		}
		
		// 1 items
		items = new LinkedList<Long>();
		for(String i : itemsLine.split(": ")[1].split(", ")) {
			items.addLast(Long.parseLong(i));
		}
		// 2 operation
		String[] operationLineArr = operationLine.split(" ");
		operandleft = operationLineArr[operationLineArr.length-3];
		operation = operationLineArr[operationLineArr.length-2];
		operandright = operationLineArr[operationLineArr.length-1];
		// 3 test
		String[] testLineArr = testLine.split(" ");
		testdiv = Long.parseLong(testLineArr[testLineArr.length-1]);
		// 4 if true
		String[] iftrueLineArr = iftrueLine.split(" ");
		iftrue = Integer.parseInt(iftrueLineArr[iftrueLineArr.length-1]);
		// 5 if false
		String[] iffalseLineArr = iffalseLine.split(" ");
		iffalse = Integer.parseInt(iffalseLineArr[iffalseLineArr.length-1]);	
	
		//System.out.println("Items: " + items + "\nOperation: new = " + operandleft + " " + operation + " " + operandright + "\nDiv: / " + testdiv + "\nIf true: " + iftrue + "\nIf false: " + iffalse); 
	}
	
	void turn(int mod, boolean partI) {
		throwtotrue = new LinkedList<Long>();
		throwtofalse = new LinkedList<Long>();
		
		Iterator<Long> itr = items.iterator();
		while(itr.hasNext()) {
			long worrylvl = itr.next();
			long left, right;
			
			if (operandleft.equals("old")) {
				left = worrylvl;
			} else {
				left = Long.parseLong(operandleft);
			}
			
			if (operandright.equals("old")) {
				right = worrylvl;
			} else {
				right = Long.parseLong(operandright);
			}
			
			if (operation.equals("*")) {
				worrylvl = left * right;
			} else { // +
				worrylvl = left + right;
			}
			
			// ONLY FOR PART i
			if (partI) {
				worrylvl /= 3;
			}
			
			if (worrylvl % testdiv == 0) {
				throwtotrue.addLast(worrylvl % mod);
			} else {
				throwtofalse.addLast(worrylvl % mod);
			}
			
			numOfInspectedItems++;
			itr.remove();
		}
	}
}