let read_file file_name = 
  let ch = open_in_bin file_name in 
  let s = really_input_string ch (in_channel_length ch) in 
  close_in ch; s
let read_test = read_file (Filename.dirname Sys.argv.(0) ^ "/../../../../bin/test.txt")

let read_input (day:int) = 
  let ds = if day < 10 then "0" ^ Int.to_string day else Int.to_string day in 
  let f_name = (Filename.dirname Sys.argv.(0) ^ "/../../../../bin/Day" ^ ds ^ "/Day" ^ ds ^".txt") in 
  read_file f_name