module ENV_LIST : tENV_LIST = struct
  type ('x, 'v) env = ('x * 'v) list
  let empty = []
  let get x env = List.assoc x env
  (*  let put x v env = (x, v) :: env *)
  let put x v env = (x, v) :: List.remove_assoc x env
end

module ENV_FUN : tENV_FUN = struct
  type ('x, 'v) env = 'x -> 'v
  let empty = fun x -> failwith "empty"
  let get x env = env x
  let put x v env = fun y -> if x = y then v else env y
end

let regle_if e = match e with 
  | If(c, BConst true, BConst false) -> c
  | If(c1, BConst true, c2) -> Call(Or, c1, c2)
  | If(c1, c2, BConst false) -> Call(And, c1, c2) 
  | _ -> e

let rec apply regle e = match e with
  | If(a, e1, e2) -> regle (If(apply regle a, apply regle e1, apply regle e2))
  | Let(b, e1, e2) -> regle (Let(b, apply regle e1, apply regle e2))
  | Call(c, e1, e2) -> regle (Call(c, apply regle e1, apply regle e2))
  | _ -> regle_if e
  
    
    