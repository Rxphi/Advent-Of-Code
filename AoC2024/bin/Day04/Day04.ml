let entire_file = Helper_lib.Helper.read_input 4
(* let entire_file = Helper_lib.Helper.read_test  *)

let rows = String.split_on_char '\n' entire_file
let n = List.length rows 

let get_byte s_arr i j = String.to_bytes @@ String.sub (List.nth s_arr i) j 1

let build_string dir (i,j,len) = 
  let byte_list = ref Bytes.empty in 
    for k = 0 to len-1 do 
      let b = get_byte rows (if dir then i+k else i-k) (j+k) in  
      byte_list := Bytes.cat !byte_list b
    done;
    String.of_bytes !byte_list

let diag_main = 
  let pos_len = (0,0,n)::(List.concat @@ List.mapi (fun i _ -> [(i+1,0,n-i-1); (0,i+1,n-i-1)]) (List.tl rows)) in 
  List.map (build_string true) pos_len 

let diag_alt = 
  let pos_len = (n-1,0,n)::(List.concat @@ List.mapi (fun i _ -> [(n-i-1,0,n-i-1); (n-1,i+1,n-i-1)]) (List.tl rows)) in 
  
  List.map (build_string false) pos_len 

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

let partI = count_fd_back rows + count_fd_back cols + count_fd_back diag_main +  count_fd_back diag_alt

type block = Block of (bytes * bytes * bytes * bytes * bytes)

let all_blocks =
  let ref_blocks = ref [] in 
  let get_byte' = get_byte rows in 
  for i = 0 to n-3 do 
    for j = 0 to n-3 do 
      let topleft = get_byte' i j in 
      let topright = get_byte' i (j+2) in
      let middle = get_byte' (i+1) (j+1) in
      let bottomleft = get_byte' (i+2) j in 
      let bottomright = get_byte' (i+2) (j+2) in
      ref_blocks := Block (topleft,topright,middle,bottomleft,bottomright) :: !ref_blocks
    done
  done;
  !ref_blocks

let m = String.to_bytes "M"
let a = String.to_bytes "A"
let s = String.to_bytes "S"

let valid_x_mas block = 
  let Block (tl, tr, mid, bl, br) = block in 
  let d_main_m_s = tl = m && br = s in 
  let d_main_s_m = tl = s && br = m in 
  let d_alt_m_s = bl = m && tr = s in 
  let d_alt_s_m = bl = s && tr = m in 
  mid = a && ((d_main_s_m || d_main_m_s) && (d_alt_m_s || d_alt_s_m))

let partII = List.length @@ List.filter valid_x_mas all_blocks

let _ = Helper_lib.Helper.pp_result 4 partI partII
