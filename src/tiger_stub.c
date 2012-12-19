#include <stdio.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/fail.h>

#define HASH_LENGTH 48

extern void tiger(unsigned char *, unsigned long long, unsigned long long *, unsigned int);

typedef unsigned long long uint192_t[3];

CAMLprim value ml_tiger192_hash(value passes, value str)
{
   CAMLparam2(passes, str);
   CAMLlocal1(aux_hv);

   if (Int_val(passes) >= 3) {
      aux_hv = caml_alloc_string(sizeof(uint192_t));

      tiger((unsigned char *)String_val(str), (unsigned long long)caml_string_length(str), (unsigned long long *)String_val(aux_hv), Int_val(passes));

      CAMLreturn(aux_hv);
   } else {
      caml_failwith("Tiger.h192_of_string");
   }
}

CAMLprim value ml_tiger192_hash_string(value passes, value str)
{
   CAMLparam2(passes, str);
   CAMLlocal1(hval);

   if (Int_val(passes) >= 3) {
      uint192_t aux_hv;
      char temp_buffer[HASH_LENGTH + 1];

      tiger((unsigned char *)String_val(str), (unsigned long long)caml_string_length(str), aux_hv, Int_val(passes));

      snprintf(temp_buffer, HASH_LENGTH + 1, "%08X%08X%08X%08X%08X%08X", \
            (unsigned)(aux_hv[0] >> 32), \
            (unsigned)(aux_hv[0]), \
            (unsigned)(aux_hv[1] >> 32), \
            (unsigned)(aux_hv[1]), \
            (unsigned)(aux_hv[2] >> 32), \
            (unsigned)(aux_hv[2]));

      hval = caml_copy_string(temp_buffer);

      CAMLreturn(hval);
   } else {
      caml_failwith("Tiger.h192_printable_of_string");
   }
}
