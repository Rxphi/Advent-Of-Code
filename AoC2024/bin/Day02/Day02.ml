let entire_file = Helper_lib.Helper.read_input 2

let lines = String.split_on_char '\n' entire_file

let records = List.map (fun line -> let splitted = String.split_on_char ' ' line in List.map Int64.of_string splitted) lines

let rec isIncrSafe record = match record with
  | [] -> true
  | [_] -> true
  | x::y::rest -> 1L <= Int64.sub y x && Int64.sub y x <= 3L && isIncrSafe (y::rest)

let isDecrSafe record = isIncrSafe (List.rev record)

let isSafe record = isIncrSafe record || isDecrSafe record

let rec getFirstN n list = 
  match n, list with
    | 0, _ -> []
    | n, x::rest -> x::(getFirstN (n-1) rest) 
    | _ -> [] 

let getLastN n list = List.rev @@ getFirstN n (List.rev list)

let remove1 record = List.mapi (fun i _ -> getFirstN i record @ getLastN (List.length record - i - 1) record) record

let isSafe2 record = isSafe record || (List.fold_left (fun b small_rec -> b || isSafe small_rec) false (remove1 record))

let partI = Int.to_string @@ List.length (List.filter isSafe records)

let partII = Int.to_string @@ List.length (List.filter isSafe2 records)
  

let () = print_endline ("AoC2024 Day02\nPartI:\t" ^ partI ^ "\nPartII:\t" ^ partII)