let rec hanoi (source, temp, dest) n =
  if n<=0 then []
  else 
    hanoi (source, dest, temp) (n-1) @ 
    (source, dest) :: 
    hanoi (temp, source, dest) (n-1)

let rec map f l =
  match l with 
  | [] -> []
  | p::r -> (f p) :: map f r

(*              
List.filter (fun n -> n mod 2 = 0) ltest ;;
- : int list = [2; 0; 4; 2]

List.for_all (fun n -> n mod 2 = 0) ltest ;;
- : bool = false

List.exists (fun n -> n mod 2 = 0) ltest ;;
- : bool = true

List.filter (fun n -> n > -2) ltest ;;
- : int list = [1; 2; 0; 4; -1; 5; 2]

List.for_all (fun n -> n > -2) ltest ;;
- : bool = true

List.exists (fun n -> n > -2) ltest ;;
- : bool = true
*)

let rec inserer elem list =
  match list with 
  | [] -> elem::[]
  | h::t -> 
      if elem < h then elem::list
      else h :: inserer elem t
             
let rec triInsertion list =
  match list with
  | [] -> []
  | h::t -> inserer h (triInsertion t)
              
let rec partage list = 
  match list with
  | [] -> [],[]
  | [x] -> [x],[]
  | x::y::z -> let liste,a = partage z in x :: liste , y :: a
  
let rec merge left right =
  match (left, right) with
  | (_,[]) -> left
  | ([],_) -> right
  | (tx::qx, ty::qy) -> 
      if tx > ty then ty::(merge left qy)
      else tx::(merge qx right)

let rec triFusion list = 
  match list with
  | [] -> []
  | [_] -> list
  | _ -> 
      let (left, right) = partage list in 
      merge (triFusion left) (triFusion right)
        
let fst (a, b) = a
let snd (a, b) = b
  
let rec estFonction l = 
  match l with 
  | [] -> true 
  | x :: [] -> true 
  | x :: y :: l2 -> 
      if fst x <> fst y then 
        estFonction (x :: l2) && estFonction (y :: l2) 
      else 1 = 0
  
let rec image x l = 
  match l with 
  | [] -> failwith "pas d'image" 
  | y :: [] -> 
      if fst y = x then snd y else failwith "pas d'image" 
  |  y :: l2 -> 
      if fst y = x then snd y else image x l2
          
let rec imageEns l l2 = 
  match l with 
  | [] -> [] 
  | x :: l -> 
      (image x l2) :: (imageEns l l2)
                      
let rec estInjective l = 
  match l with 
  | [] -> true 
  | x :: [] -> true 
  | x :: y :: l2 -> 
      if snd x <> snd y then 
        estInjective (x :: l2) && estInjective (y :: l2) 
      else 1 = 0

let rec surcharge f1 f2 =
  match f1 with 
  | [] -> f2 
  | x::f1' -> 
      if List.exists (fun n -> fst n = fst x) f2
      then surcharge f1' f2
      else x :: surcharge f1' f2

let isDef f x = List.exists (fun n -> fst n = x) f

let rec composition f1 f2 = match f2 with 
  | [] -> []
  | x :: f2' -> 
      if isDef f1 (snd x) 
      then let (a, b) = (fst x, (image (snd x) f1)) 
        in (a, b) :: composition f1 f2'
      else composition f1 f2';;

let rec produit f1 f2 = 
  match f1 with 
  | [] -> [] 
  | (x, y) :: f1' -> List.map(fun (x', y') -> ((x, x'), (y, y'))) f2 @ produit f1' f2;;
