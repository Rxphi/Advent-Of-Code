import java.util.*;
import java.io.FileNotFoundException;
import java.io.File;

public class Day16 {

	public static void main(String[] args) throws FileNotFoundException{
		File input = new File("./inputFiles/test.txt");
		
		Graph cave = new Graph(input);
		
		int partI = cave.partI();
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
			Node newNode = new Node(label, flowRate);
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
			System.out.println(intToNode.get(from));
		}
		apsp = apsp();
	}
	
	int partI() {
		boolean visited[] = new boolean[n];
		int totalFlowRate = 0;
		int out = 0;
		String currentLabel = "AA";
		for (int t = 0; t <= 30; t++) {
			int from = stringToInt.get(currentLabel);
			visited[from] = true;
			Node current = intToNode.get(from);
			int maxval = Integer.MIN_VALUE;
			int next = current;
			for (int node = 0; node < n; node++) {
				if (visited[node]) {
					continue;
				}
				Node neighNode = intToNode.get(node);
				int dist = apsp[from][node];
				int val = (30-t-dist) * neighNode.flowRate;
				
				if (val > maxval) {
					maxval = val;
					next = node;
				}
			}
			
			System.out.print("Move to " + next.label);
			out += totalFlowRate * apsp[from][];
			totalFlowRate += next.flowRate;
			System.out.println(" " + totalFlowRate);
			
			currentLabel = next.label;
		}
		return out;
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
		printMatrix(current);
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
	String label;
	ArrayList<Integer> neighbors;
	int flowRate;
	
	Node (String label, int flowRate) {
		this.label = label;
		neighbors = new ArrayList<Integer>();
		this.flowRate = flowRate;
	}
	
	public String toString () {
		return label + " " + flowRate + " " + neighbors;
	}
}


























