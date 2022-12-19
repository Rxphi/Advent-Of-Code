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
		return 0;
	}
}

class State implements Comparable{
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
	
	public Set<State> advanceState(State s) {
		if (s.t > s.maxt) {
			return new HashSet<State>(Arrays.asList(s));
		}
		Set<State> out = new HashSet<State>();
		System.out.println("t: " + s.t + ", ore-robots: " + s.numOfOreRobots + ", clay-robots: " + s.numOfClayRobots + ", obsidian-robots: " + s.numOfObsidianRobots + ", geode-robots: " + s.numOfGeodeRobots + ", ore: " + s.ore + ", clay: " + s.clay + ", obsidian: " + s.obsidian + ", opened: " + s.openGeodes);
		int nextNumOfOreRobots = s.numOfOreRobots;
		int nextNumOfClayRobots = s.numOfClayRobots;
		int nextNumOfObsidianRobots = s.numOfObsidianRobots;
		int nextNumOfGeodeRobots = s.numOfGeodeRobots;
		int nextOpenGeodes = s.openGeodes + s.numOfGeodeRobots;
		int nextOre = s.ore + s.numOfOreRobots;
		int nextClay = s.clay + s.numOfClayRobots;
		int nextObsidian = s.obsidian + s.numOfObsidianRobots;
		
		ArrayList<State> states = new ArrayList<State>();
		
		if (s.bp.geodeRobotOre <= s.ore && s.bp.geodeRobotObsidian <= s.obsidian) { // build geode robot
			out.add(new State(s.bp, s.t+1, s.maxt, nextNumOfOreRobots, nextNumOfClayRobots, nextNumOfObsidianRobots, nextNumOfGeodeRobots+1, nextOpenGeodes, nextOre-s.bp.geodeRobotOre, nextClay, nextObsidian-s.bp.geodeRobotObsidian));
		}
		if (s.bp.obsidianRobotOre <= s.ore && s.bp.obsidianRobotClay <= s.clay) { // build obsidian robot
			out.add(new State(s.bp, t+1, s.maxt, nextNumOfOreRobots, nextNumOfClayRobots, nextNumOfObsidianRobots+1, nextNumOfGeodeRobots, nextOpenGeodes, nextOre-s.bp.geodeRobotOre, nextClay-s.bp.obsidianRobotClay, nextObsidian));
		}
		if (s.bp.clayRobot <= s.ore) { // build clay robot
			out.add(new State(s.bp, s.t+1, s.maxt, nextNumOfOreRobots, nextNumOfClayRobots+1, nextNumOfObsidianRobots, nextNumOfGeodeRobots, nextOpenGeodes, nextOre-s.bp.clayRobot, nextClay, nextObsidian));
		}
		if (s.bp.oreRobot <= s.ore) { // build ore robot
			out.add(new State(s.bp, s.t+1, s.maxt, nextNumOfOreRobots+1, nextNumOfClayRobots, nextNumOfObsidianRobots, nextNumOfGeodeRobots, nextOpenGeodes, nextOre-s.bp.oreRobot, nextClay, nextObsidian));
		}
		// add the "do nothing" state
		out.add(new State(s.bp, s.t+1, s.maxt, nextNumOfOreRobots, nextNumOfClayRobots, nextNumOfObsidianRobots, nextNumOfGeodeRobots, nextOpenGeodes, nextOre, nextClay, nextObsidian));
		
		return out;
	}

	@Override
	public int compareTo(Object o) {
		return Integer.compare(this.openGeodes, ((State) o).openGeodes);
	}
}





































