import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day16 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/input16.txt");
		
		Graph cave = new Graph(input);
		
		int partI = cave.pressureRelease(cave.intToNode.get(cave.stringToInt.get("AA")), 0, new boolean[cave.n], 0, 0, 0);
		
		System.out.println("Day XVI");
		System.out.println("Part I : " + partI);
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
	
	int pressureRelease(Node current, int t, boolean visited[], int totalFlowRate, int out, int recursionDepth) {
		for (int i = 0; i < recursionDepth; i++) {
			System.out.print("  ");
		}
		System.out.println(current + ", t=" + t + ", total=" + out);
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
			int currentval = pressureRelease(candidate, t+d+1, newvisited, totalFlowRate+candidate.flowRate, out+((d+1)*totalFlowRate), recursionDepth+1);
			if (currentval > toAdd) {
				toAdd = currentval;
				best = candidate;
			}
		}
		
		for (int i = 0; i < recursionDepth; i++) {
			System.out.print("  ");
		}
		System.out.println("Choose " + best);
		
		return toAdd;
		
		/*
		while (t <= 30) {
			int from = stringToInt.get(currentLabel);
			visited[from] = true;
			Node current = intToNode.get(from);
			int maxval = Integer.MIN_VALUE;
			Node next = current;
			int dist = 0;
			for (int node = 0; node < n; node++) {
				if (visited[node]) {
					continue;
				}
				Node neighNode = intToNode.get(node);
				int d = apsp[from][node];
				int val = (30-t-d) * neighNode.flowRate;
				
				if (val > maxval) {
					maxval = val;
					next = neighNode;
					dist = d;
				}
			}
			System.out.println("Move to valve " + next.label + " Distance: " + dist);
			for (int k = 0; k < dist; k++) {
				if (t >= 30) {
					break;
				} else {					
					System.out.println("Minute " + t + " FlowRate: " + totalFlowRate + " Total: " + out);
					out += totalFlowRate;
					t++;
				}
			}
			System.out.println("Minute " + t + " Open valve " + next.label + " FlowRate: " + totalFlowRate + " Total: " + out);
			totalFlowRate += next.flowRate;
			t++;
			if (t <= 30) {
				out += totalFlowRate;
				currentLabel = next.label;
			}
		}
		*/
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
		System.out.println("\nAll Pairs Shortest Path:");
		printMatrix(current);
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


























