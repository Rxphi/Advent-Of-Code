import java.util.*;
import java.util.stream.Collectors;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Day20 {

	public static void main(String[] args) throws IOException {
		File input = new File("./inputFiles/input20.txt");
		long decriptionKey = 811589153;
		
		List<ListNode> nodes = Files.lines(input.toPath())
			.map(l -> new ListNode(Integer.parseInt(l)))
			.collect(Collectors.toList());
		
		CircularLinkedList c = new CircularLinkedList(nodes);
		c.swap();
		long partI = c.getResult();
		
		nodes.forEach(node -> node.value *= decriptionKey);
						
		c = new CircularLinkedList(nodes);
		for (int i = 0; i < 10; i++) {
			c.swap();
		}
		long partII = c.getResult();
			
		
		System.out.println("Day XX");
		System.out.println("Part I : " + partI);
		System.out.println("Part II : " + partII);
	}
}

class CircularLinkedList {
	ListNode zero;
	List<ListNode> nodes;
	
	CircularLinkedList (List<ListNode> list) {
		nodes = list;
		// Link the first and last node
		ListNode first = list.get(0);
		ListNode last = list.get(list.size()-1);
		first.prev = last;
		last.next = first;
		// Link the other nodes in between
		for (int i = 0; i < list.size()-1; i++) {
			ListNode n1 = list.get(i);
			ListNode n2 = list.get(i+1);
			n1.next = n2;
			n2.prev = n1;
			if (n1.value == 0) { // look for node with value 0
				zero = n1;
			}
		}
		if (last.value == 0) { // look for node with value 0
			zero = last;
		}
	}
	
	void swap() {
		// do all the swapping 
		for (ListNode n : nodes) {
			n.swap(nodes.size());
		}
	}
	
	long getResult() {
		// get nodes at 1000th, 2000th and 3000th index after node with value 0 and add their value
		long out = 0;
		ListNode current = zero;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 1000; j++) {
				current = current.next;
			}
			out += current.value;
		}
		return out;
	}
	
	@Override
	public String toString() {
		String out = "";
		ListNode current = zero;
		for (long i = 0; i < nodes.size(); i++) {
			out += current.value + " ";
			current = current.next;
		}
		return out;
	}
}

class ListNode {
	ListNode prev;
	ListNode next;
	long value;
	
	ListNode (long value) {
		this.value = value;
	}
	
	void swap (long listSize) {
		if (value < 0) { // swap to the left
			for (long i = value % (listSize-1); i < 0; i++) {
				// Before swap n1 <-> n2 <-> n3 <-> n4 (swapping n3)
				ListNode n1 = this.prev.prev;
				ListNode n2 = this.prev;
				ListNode n3 = this;
				ListNode n4 = this.next;
				
				n1.next = n3;
				n2.next = n4;
				n2.prev = n3;
				n3.next = n2;
				n3.prev = n1;
				n4.prev = n2;
				// After swap n1 <-> n3 <-> n2 <-> n4 (swapped n3 with n2)
			}
		} else if (value > 0) { // swap to the right
			for (long i = 0; i < value % (listSize-1); i++) {
				// Before swap n1 <-> n2 <-> n3 <-> n4 (swapping n2)
				ListNode n1 = this.prev;
				ListNode n2 = this;
				ListNode n3 = this.next;
				ListNode n4 = this.next.next;
				
				n1.next = n3;
				n2.next = n4;
				n2.prev = n3;
				n3.next = n2;
				n3.prev = n1;
				n4.prev = n2;
				// After swap n1 <-> n3 <-> n2 <-> n4 (swapped n2 with n3)
			}
		}
	}
}
