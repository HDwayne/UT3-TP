(* GRADE:  100% *)
let multiple_of n d = (n mod d) = 0

let integer_square_root n = 
  int_of_float (sqrt (float_of_int n)) 

let last_character c =
  String.get c (String.length c - 1) 
  
let string_of_bool b =
  if b then "true" else "false" 
    
let pairwise_distinct (a,b,c,d) =
  a <> b && b <> c && c <> d && a <> c && a <> d && b <> d
  
let e1 = (1, true), 2;;
let e2 = (let f x = x in f), 'a';;
let e2bis = (fun a -> a), 'a';;
(*
f1 : int -> bool -> (int * bool)
f2 : 'a -> bool
f3 : 'a -> 'a -> int
f4 : 'a * 'b -> 'b * 'a
f5 : ('a -> 'b) -> ('a -> 'b -> 'c) -> 'a -> 'c
f6 : ('a -> 'b) * ('a * 'b -> 'c) * 'a -> 'c
f7 : ('a -> 'b * 'c) -> ('b -> 'c -> 'd) -> ('d * bool -> 'e) -> 'a -> 'a -> 'e
f8 : 'a -> 'a -> 'b -> 'b -> 'a * 'b
*)   

let f1 = fun x y -> (x, y)
let f2 = fun a -> true;;
let f3 = fun a a -> 1;;
let f4 = fun (a, b) -> (b, a);; 
let f5 = fun a b c  ->  b c (a c);;
let f6 (a, b, c) = b (c, (a c));;
let f7 a b c d e = let (x, y) = a e in c ((b x y), (a (e) = a(d)));;
let f8 = fun a a b b -> (a, b);;










