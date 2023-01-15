let estZero_v1 n =
  match n with
  | 0 -> "zero"

(*
2022: Exception: "Match_failure //toplevel//:2:2"
*)
 
let estZero_v2 n =
  match n with
  | 0 -> "zero"
  | _ -> "nonZero" 
    
let voyelle c = 
  match c with
  | 'a' | 'e' | 'i' | 'o' | 'u' | 'y'
  | 'E' | 'I' | 'O' | 'U' | 'Y' -> true
  | _ -> false 

let rang j = 
  match j with
  | "lundi" -> 1
  | "mardi" -> 2
  | "mercredi" -> 3
  | "jeudi" -> 4
  | "vendredi" -> 5
  | "samedi" -> 6
  | "dimanche" -> 7
  | _ -> 0 

let inf a b = 
  match rang a, rang b with
  | 1, 2 | 2, 3 | 3, 4 | 4, 5 | 5, 6 | 6, 7 | 7, 1 -> true
  | _, _ -> false
    
let jsem j = 
  match j with
  | 1 -> "lundi"
  | 2 -> "mardi"
  | 3 -> "mercredi"
  | 4 -> "jeudi"
  | 5 -> "vendredi"
  | 6 -> "samedi"
  | 7 -> "dimanche"
  | _ -> "jour inconnu"
    
let jourSucc1 j =
  match j with
  | "lundi" -> "mardi"
  | "mardi" -> "mercredi"
  | "mercredi" -> "jeudi"
  | "jeudi" -> "vendredi"
  | "vendredi" -> "samedi"
  | "samedi" -> "dimanche"
  | "dimanche" -> "lundi"
  | _ -> "jour inconnu"
    
let jourSucc2 j = let j2 = rang j in
  if j2 = 7 then
    "lundi"
  else if j2 = 0 then
    "jour inconnu"
  else
    jsem (j2+1) 
      
let jourSucc3 j = let j2 = rang j in 
  if j2 = 0 then
    "jour inconnu"
  else
    jsem ((j2 mod 7) + 1)
      
let jourPred1 j =
  match j with
  | "lundi" -> "dimanche"
  | "mardi" -> "lundi"
  | "mercredi" -> "mardi"
  | "jeudi" -> "mercredi"
  | "vendredi" -> "jeudi"
  | "samedi" -> "vendredi"
  | "dimanche" -> "samedi"
  | _ -> "jour inconnu"
    
let jourPred2 j = let j2 = rang j in
  if j2 = 1 then
    "dimanche"
  else if j2 = 0 then
    "jour inconnu"
  else
    jsem (j2-1)
      
let jourPred3 j = let j2 = rang j in 
  if j2 = 0 then
    "jour inconnu"
  else
    jsem (((j2+5) mod 7)+1)
      
let bissextile a = (a mod 4 = 0 && a mod 100 <> 0) || a mod 400 = 0
                                                    
let nbjour m a =
  match m with
  | 4 | 6 | 9 | 11 -> 30
  | 2 -> if bissextile a then 29 else 28
  | _ -> 31