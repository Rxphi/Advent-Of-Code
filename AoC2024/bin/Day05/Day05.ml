(* open Graph *)

module Node = struct                                                                
  type t = int                                                                     
  let compare = Int.compare                                                 
  let hash = Hashtbl.hash                                                          
  let equal = (=)                                                                  
end                                                                                 

module G = Graph.Persistent.Digraph.Concrete(Node)

(* let entire_file = Helper_lib.Helper.read_input 5 *)
let entire_file = Helper_lib.Helper.read_test 

let lines = String.split_on_char '\n' entire_file 

let constraints = let const_list = List.map (fun s -> List.map (fun n -> Int32.to_int @@ Int32.of_string n) (String.split_on_char '|' s)) (List.filter (fun s -> (String.length s > 1) && s.[2] = '|') lines) in 
  List.map (fun ls -> (List.hd ls, List.hd (List.tl ls))) const_list
let updates = List.map (fun s -> List.map (fun n -> Int32.to_int @@ Int32.of_string n) (String.split_on_char ',' s)) (List.filter (fun s -> (String.length s > 1) && s.[2] = ',') lines) 

let all_nodes = List.sort_uniq Int.compare (List.concat_map (fun (src,dst) -> [src;dst]) constraints @ List.concat updates)

let g = List.fold_left (fun g new_n -> G.add_vertex g new_n) G.empty all_nodes
let g = List.fold_left (fun g (src,dst) -> G.add_edge g src dst) g constraints

let _ = G.iter_edges (fun src dst -> print_endline @@ Int.to_string src ^ "->" ^ Int.to_string dst) g

let reachable g src dst = 
  let frontier = ref [src] in 
  let found = ref false in 
  while !frontier <> [] do 
    let curr = List.hd !frontier in 
    if curr = dst then 
      found := true 
    else 
      begin
      let neighbours = Graph.Oper.Neighbourhood(G).list_from_vertex g curr in 
      false
    end
  done;
  !found