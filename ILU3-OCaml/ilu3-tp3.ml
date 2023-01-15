let rec premierCh n = 
  if n<0 then failwith "premierCh: negative number"
  else if n >= 10 then premierCh (toutSaufDer n)
  else n
  
(*
let rec nb_chiffres x =
  if (toutSaufDer x) = 0 then 1
  else 1 + nb_chiffres (toutSaufDer x);; 

let toutSaufPrem n = 
  if n<0 then failwith "toutSaufPrem: negative number"
  else n-(premierCh n)*int_of_float((10.**float_of_int((nb_chiffres n)-1)))
*)

let toutSaufPrem n =
  let rec f n =
    if n < 10 then 0
    else dernierCh n + 10 * f (toutSaufDer n) in
  if n < 0 then failwith "toutSaufPrem: negative number"
  else f n 
                       
let rec estPalindrome n =
  let pos = abs(n) in
  pos<10 || (premierCh pos = dernierCh pos && estPalindrome (toutSaufPrem (toutSaufDer pos)))
      
let rec nbOccs o n = 
  if n=0 then 0
  else if dernierCh n = o 
  then 1 + nbOccs o (toutSaufDer n)
  else nbOccs o (toutSaufDer n)

let rec iterer n f x=
  if n=0 then x
  else iterer (n-1) f (f x) 
      
let id x = x
  
let compose a b c = a (b c)
    
let rec iterer2 n f =
  if n=0 then id else compose f(iterer2 (n-1) f)
      
let rec itererBis f p x =
  if p x then x else itererBis f p (f x)
      
let rec qqsoit n p = n<=0 || qqsoit (n-1) p && p n
                       
let rec fastpow  n e =
  if e<0 then failwith "fastpow: negative number"
  else if e = 0 then 1
  else let y = fastpow n (e asr 1) in
    if e land 1 = 0 then y * y else n * y * y 

let rec ack(m, n) = 
  if n<0 || m<0 then failwith "ack: negative number"
  else 
    match m,n with
    | 0, n -> n + 1
    | m, 0 -> ack ((m - 1), 1)
    | m, n -> ack ((m - 1), (ack (m, (n - 1))))

