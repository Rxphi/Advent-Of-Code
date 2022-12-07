import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;

public class Day7 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input7.txt");
		Scanner sc = new Scanner(input);
		
		TreeNode root = new TreeNode("/");
		TreeNode current = root;
		
		String newLine = "";
		String line = "";
		
		// create the tree
		while (!newLine.isEmpty() || (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty())) {
			String[] commands = null;
			if (!newLine.isEmpty()) {
				commands = newLine.split(" ");
				newLine = "";
			} else {
				commands = line.split(" ");
			}
			
			
			/*for (String c : commands) {
				System.out.print(c + " ");
			}
			
			try {
				System.out.println(" Current: " + current.name + " Parent: " + current.parent);
			} catch (Exception e) {
				System.out.println();
				continue;
			}*/
			
			
			if (commands[0].equals("$")) {
				if (commands[1].equals("cd")) {
					if (commands[2].equals("..")) {
						current = current.parent;
					} else if (commands[2].equals("/")) {
						current = root;
					} else if (current.find(commands[2]) != null){
						current = current.find(commands[2]);
					}
				} else if (commands[1].equals("ls")) {
					while (sc.hasNextLine() && !(newLine = sc.nextLine()).split(" ")[0].equals("$")) {
						
						//System.out.println(newLine);
						
						String[] newCommands = newLine.split(" ");
						if (newCommands[0].equals("dir")) {
							current.add(new TreeNode(newCommands[1], 0, current));
						} else {
							int size = Integer.parseInt(newCommands[0]);
							current.add(new TreeNode(newCommands[1], size, current));
						}
					}
				}
			}
		}
				
		// part I
		int partI = 0;
		ArrayList<TreeNode> stack = new ArrayList<TreeNode>();
		stack.add(root);
		while (!stack.isEmpty()) {
			current = stack.remove(0);
			stack.addAll(current.children);
			if (current.size <= 100000 && !current.children.isEmpty()) {
				partI += current.size;
			}
		}

		
		// part II
		int partII = root.size;
		int usedSpace = root.size;
		int unusedSpace = 70000000 - usedSpace;
		int needed = 30000000 - unusedSpace;
		
		System.out.println("Used: " + usedSpace + " Unused: " + unusedSpace + " Needed: " + needed);
		
		stack = new ArrayList<TreeNode>();
		stack.add(root);
		while (!stack.isEmpty()) {
			current = stack.remove(0);
			stack.addAll(current.children);
			//System.out.println(current.name + " " + current.size);
			if (!current.children.isEmpty() && current.size >= needed && current.size < partII) {
				partII = current.size;
			}
		}
		
		
		
		
		System.out.println("Day VII");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}

class TreeNode {
	TreeNode parent;
	String name;
	int size;
	ArrayList<TreeNode> children;
	
	TreeNode(String name) {
		this.parent = null;
		this.name = name;
		this.size = 0;
		this.children = new ArrayList<TreeNode>();
	}
	
	TreeNode(String name, int size, TreeNode parent) {
		this.parent = parent;
		this.name = name;
		this.size = size;
		this.children = new ArrayList<TreeNode>();
	}
	
	void add(TreeNode child) {
		if (find(child.name) == null) {
			children.add(child);
			int s = child.size;
			// update size of all parents
			this.size += s;
			TreeNode repair = this;
			while (repair.parent != null) {
				repair.parent.size += s;
				repair = repair.parent;
			}
		}
	}
	
	TreeNode find(String name) {
		for (TreeNode c : children) {
			if (c.name.equals(name)){
				return c;
			}
		}
		return null;
	}
}
