let entire_file = 
  let ch = open_in_bin "/home/raphi/Documents/Code/Advent-Of-Code/AoC2024/input/Day01.txt" in 
  let s = really_input_string ch (in_channel_length ch) in 
  close_in ch; s

let lines = String.split_on_char '\n' entire_file

let pairs = List.map (fun line -> let splitted = String.split_on_char ' ' line in (Int64.of_string @@ List.hd splitted, Int64.of_string @@ List.hd (List.rev splitted))) lines

let list1 = List.map fst pairs 
let list2 = List.map snd pairs 

let sorted_pairs = List.combine (List.sort Int64.compare list1) (List.sort Int64.compare list2)

let partI = List.fold_left (fun s (e1, e2) -> Int64.add s (Int64.abs (Int64.sub e1 e2))) 0L sorted_pairs

let partII = List.fold_left (fun s e1 -> Int64.add s (Int64.mul e1 (Int64.of_int @@ List.length (List.filter (fun e2 -> e2 = e1) list2)))) 0L list1
  
let () = print_endline ("AoC2024 Day01\nPartI:\t" ^ (Int64.to_string partI) ^ "\nPartII:\t" ^ (Int64.to_string partII))