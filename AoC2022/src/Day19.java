import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day19 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		int partI = 0;
		
		String line ="";
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			Blueprint currentBP = new Blueprint(line);
			int maxGeodes = currentBP.maxNumOfGeodes(24);
			System.out.println(maxGeodes);
			partI += currentBP.index * maxGeodes;
			break;
		}

	}

}

class Blueprint {
	int index;
	int oreRobot;
	int clayRobot;
	int obsidianRobotOre;
	int obsidianRobotClay;
	int geodeRobotOre;
	int geodeRobotObsidian;
	
	Blueprint(String line) {
		String[] lineSplit = line.split("[: ]");
		index = Integer.parseInt(lineSplit[1]);
		oreRobot = Integer.parseInt(lineSplit[7]);
		clayRobot = Integer.parseInt(lineSplit[13]);
		obsidianRobotOre = Integer.parseInt(lineSplit[19]);
		obsidianRobotClay = Integer.parseInt(lineSplit[22]);
		geodeRobotOre = Integer.parseInt(lineSplit[28]);
		geodeRobotObsidian = Integer.parseInt(lineSplit[31]);
		System.out.println("Index: " + index + ", ore-robot: (" + oreRobot + ",0) , clay-robot: (" + clayRobot + ",0), obsidian-robot: (" + obsidianRobotOre + "," + obsidianRobotClay + "), geode-robot: (" + geodeRobotOre + "," + geodeRobotObsidian + ")");
	}
	
	int maxNumOfGeodes(int maxt) {
		State start = new State(this, 0, maxt, 1, 0, 0, 0, 0, 0, 0, 0);
		return start.finalState().openGeodes;
	}
}

class State {
	Blueprint bp;
	int t;
	int maxt;
	int numOfOreRobots;
	int numOfClayRobots;
	int numOfObsidianRobots;
	int numOfGeodeRobots;
	int openGeodes;
	int clay;
	int ore;
	int obsidian;
	
	State(Blueprint bp, int t, int maxt, int numOfOreRobots, int numOfClayRobots, int numOfObsidianRobots, int numOfGeodeRobots, int openGeodes, int ore, int clay, int obsidian) {
		this.bp = bp;
		this.t = t;
		this.maxt = maxt;
		this.numOfOreRobots = numOfOreRobots;
		this.numOfClayRobots = numOfClayRobots;
		this.numOfObsidianRobots = numOfObsidianRobots;
		this.numOfGeodeRobots = numOfGeodeRobots;
		this.openGeodes = openGeodes;
		this.clay = clay;
		this.ore = ore;
		this.obsidian = obsidian;
	}
	
	public State finalState() {
		if (t > maxt) {
			return this;
		}
		System.out.println("t: " + t + ", ore-robots: " + numOfOreRobots + ", clay-robots: " + numOfClayRobots + ", obsidian-robots: " + numOfObsidianRobots + ", geode-robots: " + numOfGeodeRobots + ", ore: " + ore + ", clay: " + clay + ", obsidian: " + obsidian + ", opened: " + openGeodes);
		int nextNumOfOreRobots = numOfOreRobots;
		int nextNumOfClayRobots = numOfClayRobots;
		int nextNumOfObsidianRobots = numOfObsidianRobots;
		int nextNumOfGeodeRobots = numOfGeodeRobots;
		int nextOpenGeodes = openGeodes + numOfGeodeRobots;
		int nextOre = ore + numOfOreRobots;
		int nextClay = clay + numOfClayRobots;
		int nextObsidian = obsidian + numOfObsidianRobots;
		
		ArrayList<State> states = new ArrayList<State>();
		
		if (bp.geodeRobotOre <= ore && bp.geodeRobotObsidian <= obsidian) {
			nextOre -= bp.geodeRobotOre;
			nextObsidian -= bp.geodeRobotObsidian;
			nextNumOfGeodeRobots++;
			System.out.println(t + " build geode robot");
		} else if (bp.obsidianRobotOre <= ore && bp.obsidianRobotClay <= clay) {
			nextOre -= bp.obsidianRobotOre;
			nextClay -= bp.obsidianRobotClay;
			nextNumOfObsidianRobots++;
			System.out.println(t + " build obsidian robot");
		}if (bp.clayRobot <= ore) {
			nextOre -= bp.clayRobot;
			nextNumOfClayRobots++;
			System.out.println(t + " build clay robot");
		}
		
		State next = new State(bp, t+1, maxt, nextNumOfOreRobots, nextNumOfClayRobots, nextNumOfObsidianRobots, nextNumOfGeodeRobots, nextOpenGeodes, nextOre, nextClay, nextObsidian);
		return next.finalState();
	}
}





































