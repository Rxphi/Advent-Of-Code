let entire_file = 
  let ch = open_in_bin "/home/raphi/Documents/Code/Advent-Of-Code/AoC2024/input/Day01.txt" in 
  let s = really_input_string ch (in_channel_length ch) in 
  close_in ch; s
  
let () = print_endline entire_file