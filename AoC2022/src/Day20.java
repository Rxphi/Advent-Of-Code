import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day20 {

	public static void main(String[] args)throws FileNotFoundException {
		File input = new File("./inputFiles/test.txt");
		Scanner sc = new Scanner(input);
		
		LinkedList list = new LinkedList();
		
		String line = "";
		
		while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
			int v = Integer.parseInt(line);
			list.add(new IntNode(v, list));
			
		}
		
		ArrayList<Integer> order = list.toArrayList();
		System.out.println("Iterator: " + order);
		
		Iterator<Integer> itr = order.iterator();
		
		while (itr.hasNext()) {
			list.find(itr.next()).rotate();
		}
		
		
		
		IntNode current = list.find(0);
		
		int partI = 0;
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1000; j++) {
				current = current.next;
			}
			partI += current.val;
		}
		
		
		System.out.println("Day XX");
		System.out.println("Part I : " + partI);
		
	}
}

class LinkedList {
	IntNode head;
	IntNode tail;
	int size = 0;
	
	public IntNode get(int index) {
		IntNode current = head;
		for (int i = 0; i < index; i++) {
			current = current.next;
		}
		return current;
	}
	
	public IntNode find(int value) {
		IntNode current = head;
		for(int i = 0; i < size; i++) {
			if (current.val == value) {
				return current;
			}
			current = current.next;
		}
		return null;
	}
	
	public void add(IntNode node) {
		if (head == null) {
			head = node;
			tail = node;
		} else {	
			tail.next = node;
			node.prev = tail;
			node.next = head;
			head.prev = node;
			tail = node;
		}
		size++;
	}
	
	public void printMe() {
		System.out.println(toArrayList());
	}
	
	public ArrayList<Integer> toArrayList() {
		ArrayList<Integer> out = new ArrayList<Integer>();
		IntNode current = head;
		for (int i = 0; i < size; i++) {
			out.add(current.val);
			current = current.next;
		}
		return out;
	}
}

class IntNode {
	IntNode prev;
	IntNode next;
	int val;
	LinkedList parent;
	
	public IntNode(int val, LinkedList parent) {
		this.val = val;
		this.parent = parent;
	}
	
	public void rotate() {
		System.out.println("Rotating " + this.val);
		if (val < 0) {
			for (int i = val; i < 0; i++) {
				this.prev.next = next;
				this.next.prev = prev;
				IntNode rem = prev;
				this.prev = rem.prev;
				this.next = rem;
				rem.prev.next = this;
				rem.prev = this;
				
				System.out.println("Head: " + parent.head.val + ", Tail: " + parent.tail.val);
				if (parent.head.next == this) {
					parent.tail = this;
					parent.head = this.next;
				} else if (parent.head == this) {
					parent.head = this.next.next;
				} else if (parent.tail == this) {
					parent.tail = this.next;
				}
				parent.printMe();
			}
		} else if (val > 0) {
			for (int i = 0; i < val; i++) {
				this.prev.next = next;
				this.next.prev = prev;
				IntNode rem = next;
				this.prev = rem;
				this.next = rem.next;
				rem.next.prev = this;
				rem.next = this;
				
				System.out.println("Head: " + parent.head.val + ", Tail: " + parent.tail.val);
				if (parent.head == this) {
					parent.head = this.prev;
				} else if (parent.tail == this) {
					parent.tail = this.prev.prev;
				} else if (parent.tail.prev == this) {
					parent.tail = this;
				}
				parent.printMe();
			}
		}
	}
}






