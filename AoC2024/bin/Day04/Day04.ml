(* let entire_file = Helper_lib.Helper.read_input 4 *)
let entire_file = Helper_lib.Helper.read_test 

let rows = String.split_on_char '\n' entire_file
let n = List.length rows 

let diag_main = 
  let storage = ref [] in 
  let pos_len = (0,0,n)::(List.concat @@ List.mapi (fun i _ -> (i+1,0,n-i-1)::[(0,i+1,n-i-1)]) rows) in 
  let build_string (i,j,len) = 
    let byte_list = Bytes.empty in 
    for k = 0 to len-1 do 
      let b = String.to_bytes @@ String.sub (List.nth rows (i+k)) (j+k) 1 in 
      ignore @@ Bytes.cat byte_list b
    done;
    String.of_bytes byte_list
  in
  List.iter (fun pl -> let s = build_string pl in storage := s::!storage) pos_len;
  !storage


let cols = List.mapi (fun i _ -> let rev_string_bytes = List.mapi (fun j _ -> String.to_bytes @@ String.sub (List.nth rows j) i 1) rows in String.of_bytes @@ List.fold_left Bytes.cat Bytes.empty rev_string_bytes) rows

let count_fd_back_string s = 
  let len = String.length s in 
  let count = ref 0 in 
  for i = 0 to len - 4 do 
    let s' = String.sub s i 4 in 
    if "XMAS" = s' || "SAMX" = s' then 
      incr count 
  done;
  !count

let count_fd_back s_list = List.fold_left (fun acc s -> acc + count_fd_back_string s) 0 s_list


let () = for i = 0 to n-1 do 
  print_endline (List.nth diag_main i)
done

let partI = count_fd_back rows + count_fd_back cols + count_fd_back diag_main (* +  count_fd_back diag_alt *)

let _ = Helper_lib.Helper.pp_result 4 partI 0
