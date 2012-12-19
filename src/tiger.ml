
external of_string           : int -> string -> string = "ml_tiger192_hash"
external printable_of_string : int -> string -> string = "ml_tiger192_hash_string"

let h192_of_string = of_string

let h160_of_string i s =
   try
      String.sub (of_string i s) 0 20
   with
      | Failure _ -> raise (Failure "Tiger.h160_of_string")

let h128_of_string i s =
   try
      String.sub (of_string i s) 0 16
   with
      | Failure _ -> raise (Failure "Tiger.h128_of_string")

let h192_printable_of_string = printable_of_string

let h160_printable_of_string i s =
   try
      String.sub (printable_of_string i s) 0 40
   with
      | Failure _ -> raise (Failure "Tiger.h160_printable_of_string")

let h128_printable_of_string i s =
   try
      String.sub (printable_of_string i s) 0 32
   with
      | Failure _ -> raise (Failure "Tiger.h128_printable_of_string")
