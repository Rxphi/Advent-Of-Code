let dayToString day = 
  "Day" ^ if day < 10 then "0" ^ Int.to_string day else Int.to_string day

let test_file_name = Filename.dirname Sys.argv.(0) ^ "/../../../../bin/test.txt"
let input_file_name (day:int) = 
  let ds = dayToString day in 
  (Filename.dirname Sys.argv.(0) ^ "/../../../../bin/" ^ ds ^ "/" ^ ds ^".txt")

let read_file file_name = 
  let ch = open_in_bin file_name in 
  let s = really_input_string ch (in_channel_length ch) in 
  close_in ch; s
let read_test = read_file test_file_name

let read_input (day:int) = 
  read_file (input_file_name day)


let pp_result day sol1 sol2 = 
  let ds = dayToString day in 
  print_endline ("AoC2024 " ^ ds ^ "\nPartI:\t" ^ (Int.to_string sol1) ^ "\nPartII:\t" ^ (Int.to_string sol2))

