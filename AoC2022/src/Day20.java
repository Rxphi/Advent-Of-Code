import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Day20 {

	public static void main(String[] args)throws FileNotFoundException {
		File input = new File("./inputFiles/input20.txt");
		Scanner sc = new Scanner(input);
		
		List<Integer> list = new LinkedList<Integer>();
		while (sc.hasNextInt()) {
			int x = sc.nextInt();
			list.add(x);
		}
		int n = list.size();
		// create arrays
		int[] arr = new int[n];
		for (int i = 0; i < n; i++) arr[i] = list.get(i);
		int[] swapped = new int[n]; // 0 = false and 1 = true (didnt want to write new swapleft and swapright)
		
		for(int current : list) {
			
			int i = 0;
			for(i = 0; i < n; i++) {
				if (arr[i] == current && swapped[i] == 0) {
					break;
				}
			}
			int j = 0;
			if (current < 0) {
				for (j = 0; j > current; j--) {
					swapleft(arr, i+j);
					swapleft(swapped, i+j);
				}
			} else if (current > 0) {
	
				for (j = 0; j < current; j++) {
					swapright(arr, i+j);
					swapright(swapped, i+j);
				}
			}
			swapped[Math.floorMod(i+j, n)] = 1;
			/*for (int x : arr) {
				System.out.print(x + " ");
			}
			System.out.println();*/
		}
				
		int ind = 0;
		for (ind = 0; ind < n; ind++) {
			if (arr[ind] == 0) {
				ind--;
				break;
			}
		}
		


		System.out.println(arr[(ind + 1001) % n]);
		System.out.println(arr[(ind + 2001) % n]);
		System.out.println(arr[(ind + 3001) % n]);
		int partI =  arr[(ind + 1001) % n] + arr[(ind + 2001) % n] + arr[(ind + 3001) % n];
		
		System.out.println("Day XX");
		System.out.println("Part I : " + partI);
		
	}
	
	public static void swapleft(int[] arr, int index) {
		index = Math.floorMod(index, arr.length);
		int temp = arr[index];
		
		if (index == 0) {
			arr[0] = arr[arr.length-1];
			arr[arr.length-1] = temp;
		} else {
			arr[index] = arr[index-1];
			arr[index-1] = temp;
		}
	}
	
	public static void swapright(int[] arr, int index) {
		index = Math.floorMod(index, arr.length);
		
		int temp = arr[index];
		
		if (index == arr.length-1) {
			arr[arr.length-1] = arr[0];
			arr[0] = temp;
		} else {
			arr[index] = arr[index+1];
			arr[index+1] = temp;
		}
	}
}







