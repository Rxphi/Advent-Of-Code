
let entire_file = Helper_lib.Helper.read_input 3
let file_length = String.length entire_file 

let headOffString s = 
  String.sub s 1 (String.length s - 1) 

let rec aux s acc = 
  let len = String.length s in 
  try 
    match String.sub s 0 4 with
      | "mul("  -> match_mul (String.sub s 4 (len - 4)) acc
      | _ -> 
        aux (headOffString s) acc
  with 
    Invalid_argument _ -> "", acc

and match_mul s acc =
  try 
    let a1, s1 = match_maxThree s in 
    if "," <> String.sub s1 0 1 then
      aux s1 acc 
    else 
      let a2, s2 = match_maxThree (headOffString s1) in 
      if ")" <> String.sub s2 0 1 then 
        aux s2 acc
      else 
        begin
        aux (headOffString s2) (acc + a1 * a2)
        end
  with 
    _ -> aux (headOffString s) acc


and match_maxThree s = 
  let len = String.length s in
  let minus1 = (Int32.of_int (-1)) in  
  let a = ref minus1 in 
  begin 
  try
    a := Int32.of_string (String.sub s 0 1);
    a := Int32.of_string (String.sub s 0 2);
    a := Int32.of_string (String.sub s 0 3)
  with
    _ -> ()
  end;
  begin
  if !a = minus1 then 
    raise (Failure "")
  else 
    let matched_int = Int32.to_int (!a) in  
    let match_len = String.length @@ Int.to_string matched_int in 
    matched_int, String.sub s (match_len) (len - match_len)
  end

let partI = snd @@ aux entire_file 0

(* PART II *)

type ctrlPos = CtrlPos of bool * int 

let ctrlPosRef = ref [] 

let ctrlPosList = begin
  for i = 0 to (String.length entire_file) do
    try
      let sub4 = String.sub entire_file i 4 in 
      let sub7 = String.sub entire_file i 7 in 
      if sub4 = "do()" then begin
        ctrlPosRef := (CtrlPos (true, i))::(!ctrlPosRef)
      end;
      if sub7 = "don't()" then begin
        ctrlPosRef := (CtrlPos (false, i))::(!ctrlPosRef)
      end
    with
      _ -> ()
  done;
  CtrlPos (true,0)::List.rev (!ctrlPosRef) (* Don't forget the first part of the string that is enabled*)
end

let rec aux2 ctrlPoses acc = 
  match ctrlPoses with
    | CtrlPos (true,i1)::CtrlPos (_,i2)::_ -> 
      aux2 (List.tl ctrlPoses) (snd @@ aux (String.sub entire_file (i1+4) (i2 - i1 - 4)) acc)
    | CtrlPos (false,_)::rest -> aux2 rest acc 
    | CtrlPos (true,i1)::[] -> 
      snd @@ aux (String.sub entire_file (i1+4) (file_length - i1 - 4)) acc
    | [] -> acc

let partII = aux2 ctrlPosList 0

let () = Helper_lib.Helper.pp_result 3 partI partII