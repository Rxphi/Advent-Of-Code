import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class Day9 {

	public static void main(String[] args) throws FileNotFoundException {
		File input = new File("./inputFiles/input9.txt");
		Scanner sc = new Scanner(input);

		int partI = 0; 
		int partII = 0;
		
		Simulation grid = new Simulation();
		
		String line;
		while (sc.hasNextLine() && ! (line = sc.nextLine()).isEmpty()) {
			grid.moveHead(line);
		}
		
		partI = grid.visited.size();
		partII = grid.visited.size();
		
		System.out.println("Day IX");
		System.out.println("Part I " + partI);
		System.out.println("Part II " + partII);
	}

}

class Simulation {
	ArrayList<Point> visited;
	Point head;
		
	Simulation () {
		visited = new ArrayList<Point>();
		
		head = new Point(0, 0);
		Point current = head;
		for (int i = 1; i < 10; i++) {
			current.next = new Point(0, 0, current);
			current = current.next;
		}
		current.next = null;
		setVisited(0, 0);
	}
	
	
	
	void setVisited(int x, int y) {
		for (Point alreadyVisited : visited) {
			if (alreadyVisited.x == x && alreadyVisited.y == y) {
				return;
			}
		}
		visited.add(new Point(x, y));
	}
	
	
	void moveHead(String instruction) {
		char direction = instruction.charAt(0);
		int numOfSteps = Integer.parseInt(instruction.split(" ")[1]);
		int dx = 0;
		int dy = 0;
		switch (direction) {
		case 'R':
			dx = 1;
			break;
		case 'U':
			dy = 1;
			break;
		case 'L':
			dx = -1;
			break;
		case 'D':
			dy = -1;
			break;
		}
		
		// move the head and let the tail follow it
		Point tail = null;
		for (int i = 0; i < numOfSteps; i++) {
			head.move(dx, dy);
			
			//head.printMe();
			tail = head.getTail();
			setVisited(tail.x, tail.y);
		}
		//System.out.println(tail.x + " " + tail.y);
	}	
}

class Point {
	Point next;
	
	int x;
	int y;
	
	Point () {
		x = 0;
		y = 0;
	}
	
	Point (int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	Point (int x, int y, Point next) {
		this.x = x;
		this.y = y;
		this.next = next;
	}
	
	void move (int dx, int dy) {
		x += dx;
		y += dy;
		
		if (next != null) {
			next.followHead(this);
		}

	}
	
	Point getTail () {
		Point current = this;
		while (current.next != null) {
			current = current.next;
		}
		return current;
	}
	
	void printMe() {
		Point current = this;
		while (current != null) {
			System.out.print("(" + current.x + ", " + current.y + ") ");
			current = current.next;
		}
		System.out.println();
	}
	
	void followHead(Point head) {
		if (Math.abs(this.x-head.x) < 2 && Math.abs(this.y-head.y) < 2) {
			return;
		// head is two steps above or below
		} else if (this.x == head.x && Math.abs(this.y-head.y) == 2) {
			if (this.y > head.y) {
				move(0, -1);
			} else {
				move(0, 1);
			}
		// head is two steps right or left
		} else if (this.y == head.y && Math.abs(this.x-head.x) == 2) {
			if (this.x > head.x) {
				move(-1, 0);
			} else {
				move(1, 0);
			}
		} else {
			int dx = head.x - this.x;
			int dy = head.y - this.y;
			
			if (dx == 2) {
				if (dy == 1 || dy == 2) {
					move(1, 1);
				} else if (dy == -1 || dy == -2) {
					move(1, -1);
				}
			} else if (dx == -2) {
				if (dy == 1 || dy == 2) {
					move(-1, 1);
				} else if (dy == -1 || dy == -2) {
					move(-1, -1);
				}
			} else if (dy == 2) {
				if (dx == 1 || dx == 2) {
					move(1, 1);
				} else if (dx == -1 || dx == -2) {
					move(-1, 1);
				}
			} else if (dy == -2) {
				if (dx == 1 || dx == 2) {
					move(1, -1);
				} else if (dx == -1 || dx == -2) {
					move(-1, -1);
				}
			}
		}
	}
}