import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day16 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input16.txt");
		
		Graph cave = new Graph(input);
		
		Node startNode = cave.intToNode.get(cave.stringToInt.get("AA"));
		int partI = 0;//cave.pressureReleaseI(startNode, 0, new boolean[cave.n], 0, 0, 0);
		int partII = cave.pressureReleaseII(startNode, startNode, 0, new boolean[cave.n], 0, 0, "both", 0);
		
		System.out.println("Day XVI");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
		
		// 2490 to high for partII
		// 2225 and 2020 was wrong
	}

}

class Graph {
	Map<String, Integer> stringToInt;
	Map<Integer, Node> intToNode;
	int[][] matrix;
	int[][] apsp;
	int n;
	
	Graph(File input) throws FileNotFoundException {
		stringToInt = new HashMap<String, Integer>();
		intToNode = new HashMap<Integer, Node>();
		Scanner sc = new Scanner(input);
		String line = "";
		int i = 0;
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			String[] lineSplit = line.split("[=; ]");
			String label = lineSplit[1];
			int flowRate = Integer.parseInt(lineSplit[5]);
			Node newNode = new Node(i, label, flowRate);
			stringToInt.put(label, i);
			intToNode.put(i, newNode);
			i++;
		}
		matrix = new int[i][i];
		n = i;
		// get the neighbors
		sc = new Scanner(input);
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			String[] lineSplit = line.split("[, ]");

			String currentLabel = lineSplit[1];
			int from = stringToInt.get(currentLabel);
			for (i = 9; i < lineSplit.length; i+=2) {
				String neighLabel = lineSplit[i];
				int to = stringToInt.get(neighLabel);
				matrix[from][to] = 1;
				matrix[to][from] = 1;
				intToNode.get(from).neighbors.add(to);
			}
			//System.out.println(intToNode.get(from));
		}
		//System.out.println("\nNumber of nodes n = " + n);
		apsp = apsp();
	}
	
	int pressureReleaseI(Node current, int t, boolean visited[], int totalFlowRate, int out, int recursionDepth) {
		/*for (int i = 0; i < recursionDepth; i++) {
			System.out.print("  ");
		}
		System.out.println(current + ", t=" + t + ", total=" + out);*/
		if (t > 30) {
			return out - ((t-30) * (totalFlowRate-current.flowRate));
		}
		
		ArrayList<Node> unvisited = new ArrayList<Node>();
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				unvisited.add(intToNode.get(i));
			}
		}
		
		if (unvisited.isEmpty()) {
			return out + Math.min(0, (30-t)*totalFlowRate);
		}
		
		unvisited.sort(new Comparator<Node>() {

			@Override
			public int compare(Node o1, Node o2) {
				int d1 = apsp[current.index][o1.index];
				int d2 = apsp[current.index][o2.index];
				return -Integer.compare((30-t-d1)*o1.flowRate, (30-t-d2)*o2.flowRate);
			}
			
		});
		
		int check = 3;
		int toAdd = 0;
		Node best = null;
		for (int i = 0; i < Math.min(unvisited.size(), check); i++) {
			Node candidate = unvisited.get(i);
			boolean[] newvisited = Arrays.copyOf(visited, n);
			newvisited[candidate.index] = true;
			int d = apsp[current.index][candidate.index];
			int currentval = pressureReleaseI(candidate, t+d+1, newvisited, totalFlowRate+candidate.flowRate, out+((d+1)*totalFlowRate), recursionDepth+1);
			if (currentval > toAdd) {
				toAdd = currentval;
				best = candidate;
			}
		}
		/*
		for (int i = 0; i < recursionDepth; i++) {
			System.out.print("  ");
		}
		System.out.println("Choose " + best);
		*/
		return toAdd;
	}
	
	int pressureReleaseII(Node current, Node elephant, int t, boolean visited[], int totalFlowRate, int out, String last, int recursionDepth) {
		if (recursionDepth < 3) {
			System.out.println(recursionDepth);
		}
		/*for (int i = 0; i < recursionDepth; i++) {
			System.out.print("  ");
		}
		System.out.println(current + " " + elephant + ", t=" + t + ", total=" + out);*/
		if (t > 26) {

			return out - ((t-26) * (totalFlowRate-current.flowRate-elephant.flowRate));
		}
		
		ArrayList<Node> unvisited = new ArrayList<Node>();
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				unvisited.add(intToNode.get(i));
			}
		}
		
		if (unvisited.isEmpty()) {
			return out + Math.min(0, (26-t)*totalFlowRate);
		}
		
		unvisited.sort(new Comparator<Node>() {

			@Override
			public int compare(Node o1, Node o2) {
				int d1 = apsp[current.index][o1.index];
				int d2 = apsp[current.index][o2.index];
				return -Integer.compare((26-t-d1)*o1.flowRate, (26-t-d2)*o2.flowRate);
			}
			
		});
	
		int check = 3;
		
		ArrayList<Node> candidatesForCurrent = new ArrayList<Node>();
		
		for (int i = 0; i < Math.min(unvisited.size(), check); i++) {
			candidatesForCurrent.add(unvisited.get(i));
		}
		
		unvisited.sort(new Comparator<Node>() {

			@Override
			public int compare(Node o1, Node o2) {
				int d1 = apsp[elephant.index][o1.index];
				int d2 = apsp[elephant.index][o2.index];
				return -Integer.compare((26-t-d1)*o1.flowRate, (26-t-d2)*o2.flowRate);
			}
			
		});
		
		ArrayList<Node> candidatesForElephant = new ArrayList<Node>();
		
		for (int i = 0; i < Math.min(unvisited.size(), check); i++) {
			candidatesForElephant.add(unvisited.get(i));
		}
		
		
		//System.out.println(candidatesForCurrent + " " + candidatesForElephant);
		int toAdd = 0;
		
		for (int i = 0; i < candidatesForCurrent.size(); i++) {
			Node nextcurrent = candidatesForCurrent.get(i);
			for (int j = 0; j < candidatesForElephant.size(); j++) {
				Node nextelephant = candidatesForElephant.get(j);
				// vlt muss ich diesen Fall auch prüfen
				if (nextcurrent.index == nextelephant.index) {
					continue;
				}
				boolean[] newvisited = Arrays.copyOf(visited, n);

				
				int dcurr = apsp[current.index][nextcurrent.index];
				int deleph = apsp[elephant.index][nextelephant.index];
				
				if (dcurr < deleph) {
					Node fakeNext = nextelephant;
					for (int k = 0; k < n; k++) {
						if (apsp[elephant.index][k] == (deleph-dcurr-1)) {
							fakeNext = intToNode.get(k);
						}
					}
					newvisited[nextcurrent.index] = true;
					int currentval = pressureReleaseII(nextcurrent, fakeNext, t+dcurr+1, newvisited, totalFlowRate+nextcurrent.flowRate, out+((dcurr+1)*totalFlowRate), "current", recursionDepth+1);
					toAdd = currentval > toAdd ? currentval : toAdd;
				} else if (dcurr > deleph) {
					Node fakeNext = nextcurrent;
					for (int k = 0; k < n; k++) {
						if (apsp[current.index][k] == (dcurr-deleph-1)) {
							fakeNext = intToNode.get(k);
						}
					}
					newvisited[nextelephant.index] = true;
					int currentval = pressureReleaseII(fakeNext, nextelephant, t+deleph+1, newvisited, totalFlowRate+nextelephant.flowRate, out+((deleph+1)*totalFlowRate), "elephant", recursionDepth+1);
					toAdd = currentval > toAdd ? currentval : toAdd;
				} else {
					newvisited[nextcurrent.index] = true;
					newvisited[nextelephant.index] = true;
					int currentval = pressureReleaseII(nextcurrent, nextelephant, t+dcurr+1, newvisited, totalFlowRate+nextcurrent.flowRate+nextelephant.flowRate, out+((dcurr+1)*totalFlowRate), "both", recursionDepth+1);
					toAdd = currentval > toAdd ? currentval : toAdd;
				}
			}
		}
		
		return toAdd;
	}
	
	
	int[][] apsp() {
		int n = matrix.length;
		int[][] current = new int[n][n];
		// copy matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					matrix[i][j] = 0;
				} else {
					
					current[i][j] = matrix[i][j] == 0 ? n : matrix[i][j];
				}
			}
		}
		// run floyd-warshall
		for (int k = 0; k < n; k++) {
			int[][] next = new int[n][n];
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int opt1 = current[i][j];
					int opt2 = current[i][k] + current[k][j];
					
					if (opt1 < 0 && opt2 < 0) {
						next[i][j] = -1;
					} else if (opt1 < 0) {
						next[i][j] = opt2;
					} else if (opt2 < 0){
						next[i][j] = opt1;
					} else {
						next[i][j] = Math.min(opt1, opt2);
					}
				}
			}
			current = next;
		}
		/*
		System.out.println("\nAll Pairs Shortest Path:");
		printMatrix(current);
		*/
		return current;
		
	}
	
	void printMatrix(int[][] A) {
		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < A[0].length; j++) {
				System.out.print(A[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
}

class Node {
	int index;
	String label;
	ArrayList<Integer> neighbors;
	int flowRate;
	
	Node (int index, String label, int flowRate) {
		this.index = index;
		this.label = label;
		neighbors = new ArrayList<Integer>();
		this.flowRate = flowRate;
	}
	
	public String toString () {
		return label;
	}
}














