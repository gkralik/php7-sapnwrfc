FUNCTION Z_PHPSAP_DECFLOAT_TEST.
*"----------------------------------------------------------------------
*"*"Local interface:
*"  IMPORTING
*"     VALUE(ZDECF16_IN) TYPE  DECFLOAT16 OPTIONAL
*"     VALUE(ZDECF34_IN) TYPE  DECFLOAT34 OPTIONAL
*"  EXPORTING
*"     VALUE(ZDECF) TYPE  DECFLOAT34
*"     VALUE(ZDECF16_OUT) TYPE  DECFLOAT16
*"     VALUE(ZDECF34_OUT) TYPE  DECFLOAT34
*"----------------------------------------------------------------------

ZDECF = '1.23456'.

" copy values
ZDECF16_OUT = ZDECF16_IN.
ZDECF34_OUT = ZDECF34_IN.

ENDFUNCTION.