
#!/bin/bash

SMALL="10 3 8 1 6 2 9 4 7 5"
MEDIUM="$(seq 100 -1 1)"
LARGE="$(seq 500 -1 1)"

echo "========== 1. TESTE FUNCIONAL =========="

echo "--- DISORDER BAIXO: SIMPLE ---"
./push_swap --bench --adaptive 1 2 3 4 5 6 7 9 8 > /tmp/ps_out
wc -l < /tmp/ps_out
./checker_linux 1 2 3 4 5 6 7 9 8 < /tmp/ps_out

echo "--- DISORDER MEDIO: MEDIUM ---"
./push_swap --bench --adaptive 5 4 3 2 1 6 7 8 9 10 > /tmp/ps_out
wc -l < /tmp/ps_out
./checker_linux 5 4 3 2 1 6 7 8 9 10 < /tmp/ps_out

echo "--- DISORDER ALTO: COMPLEX ---"
./push_swap --bench --adaptive 10 9 8 7 6 5 4 3 2 1 > /tmp/ps_out
wc -l < /tmp/ps_out
./checker_linux 10 9 8 7 6 5 4 3 2 1 < /tmp/ps_out


echo "========== 2. TESTE DE PERFORMANCE =========="

echo "========== SIMPLE =========="
echo "--- 10 NUMEROS ---"
./push_swap --bench --simple $SMALL
echo "--- 100 NUMEROS ---"
./push_swap --bench --simple $MEDIUM
echo "--- 500 NUMEROS ---"
./push_swap --bench --simple $LARGE

echo "========== MEDIUM =========="
echo "--- 10 NUMEROS ---"
./push_swap --bench --medium $SMALL
echo "--- 100 NUMEROS ---"
./push_swap --bench --medium $MEDIUM
echo "--- 500 NUMEROS ---"
./push_swap --bench --medium $LARGE

echo "========== COMPLEX =========="
echo "--- 10 NUMEROS ---"
./push_swap --bench --complex $SMALL
echo "--- 100 NUMEROS ---"
./push_swap --bench --complex $MEDIUM
echo "--- 500 NUMEROS ---"
./push_swap --bench --complex $LARGE


echo "========== 3. TESTE DE PARSING =========="

echo "========== FASE 1: VALIDACAO NUMERICA =========="

echo "--- INPUT VALIDO ---"
./push_swap 3 2 1
./push_swap -42 0 42
./push_swap +42 -42 0

echo "--- TEXTO E CARACTERES INVALIDOS ---"
./push_swap abc
./push_swap 1 abc 3
./push_swap 123abc
./push_swap abc123
./push_swap 3.14
./push_swap 1,2
./push_swap 1/2
./push_swap 1:2
./push_swap 1_2
./push_swap "1@2"
./push_swap "1#2"

echo "--- SINAIS ISOLADOS ---"
./push_swap +
./push_swap -
./push_swap + ""
./push_swap - ""

echo "--- SINAIS REPETIDOS ---"
./push_swap ++1
./push_swap --1
./push_swap +-1
./push_swap -+1
./push_swap +++1
./push_swap ---1
./push_swap ++-1
./push_swap --+1

echo "--- SINAIS INTERCALADOS ---"
./push_swap 1-2
./push_swap 1+2
./push_swap 12-3
./push_swap 12+3
./push_swap 1--2
./push_swap 1++2
./push_swap 1+-2
./push_swap 1-+2
./push_swap 1-2-3
./push_swap 1+2+3
./push_swap 1+-2+3
./push_swap 1 -2+3
./push_swap 1 2-3
./push_swap 1 2 3-4
./push_swap 1- 2
./push_swap 1 -2
./push_swap 1 + 2
./push_swap 1 - 2

echo "--- SINAIS NO FIM ---"
./push_swap 42+
./push_swap 42-
./push_swap 42++
./push_swap 42--

echo "--- CARACTERES INVALIDOS MISTURADOS ---"
./push_swap "++42abc"
./push_swap "--42abc"
./push_swap "+-42abc"
./push_swap "42abc+"
./push_swap "42abc-"
./push_swap "1 2abc 3"
./push_swap "1 abc2 3"
./push_swap "1 2.0 3"
./push_swap "1 +abc 3"
./push_swap "1 -abc 3"


echo "========== FASE 2: LIMITES NUMERICOS =========="

echo "--- LIMITES VALIDOS ---"
./push_swap 2147483647
./push_swap -2147483648
./push_swap 2147483647 -2147483648
./push_swap +2147483647
./push_swap -0
./push_swap 00
./push_swap -00
./push_swap 00000000002147483647
./push_swap -00000000002147483648

echo "--- OVERFLOW POSITIVO ---"
./push_swap 2147483648
./push_swap 2147483649
./push_swap 2147483650
./push_swap 9999999999
./push_swap 99999999999
./push_swap 999999999999
./push_swap 999999999999999
./push_swap 999999999999999999
./push_swap 999999999999999999999
./push_swap 999999999999999999999999999999999999

echo "--- OVERFLOW NEGATIVO ---"
./push_swap -2147483649
./push_swap -2147483650
./push_swap -9999999999
./push_swap -99999999999
./push_swap -999999999999
./push_swap -999999999999999
./push_swap -999999999999999999
./push_swap -999999999999999999999
./push_swap -999999999999999999999999999999999999

echo "--- SINAIS E LIMITES ---"
./push_swap +2147483648
./push_swap -2147483649
./push_swap ++2147483647
./push_swap --2147483648
./push_swap +-2147483648
./push_swap -+2147483647

echo "--- ZEROS ANTES DOS LIMITES ---"
./push_swap 00000000002147483647
./push_swap -00000000002147483648
./push_swap +00000000002147483647
./push_swap 00000000002147483648
./push_swap -00000000002147483649


echo "========== FASE 3: WHITESPACE E ARGUMENTOS VAZIOS =========="

echo "--- ARGUMENTOS VAZIOS ---"
./push_swap ""
./push_swap " "
./push_swap "   "
./push_swap ""
./push_swap 1 ""
./push_swap "" 1
./push_swap 1 "" 2
./push_swap "1 2" ""

echo "--- ESPACOS ---"
./push_swap "1 2"
./push_swap " 1 2"
./push_swap "1 2 "
./push_swap " 1 2 "
./push_swap "  1  2  "
./push_swap "1   2"
./push_swap "1    2    3"
./push_swap "   1   2   3   "

echo "--- TABS ---"
./push_swap $'1\t2'
./push_swap $'\t1 2'
./push_swap $'1 2\t'
./push_swap $'1\t\t2'
./push_swap $'1\t2\t3'
./push_swap $' \t1\t 2\t '

echo "--- NEWLINES ---"
./push_swap $'1\n2'
./push_swap $'\n1 2'
./push_swap $'1 2\n'
./push_swap $'1\n\n2'
./push_swap $'1\n2\n3'
./push_swap $' \n1\n 2\n '

echo "--- CARRIAGE RETURNS ---"
./push_swap $'1\r2'
./push_swap $'\r1 2'
./push_swap $'1 2\r'
./push_swap $'1\r\r2'
./push_swap $'1\r2\r3'

echo "--- VERTICAL TAB E FORM FEED ---"
./push_swap $'1\v2'
./push_swap $'1\f2'
./push_swap $'\v1 2'
./push_swap $'\f1 2'
./push_swap $'1\v2\f3'

echo "--- WHITESPACE MISTURADO ---"
./push_swap $'1 \t2'
./push_swap $'1\t 2'
./push_swap $'1\n\t2'
./push_swap $'1\r\n2'
./push_swap $' 1\t\n 2\r '
./push_swap $'\t 1 \n 2 \r 3 \v 4 \f'

echo "--- SINAIS COM WHITESPACE ---"
./push_swap "+ 1"
./push_swap "- 1"
./push_swap "1 +2"
./push_swap "1 -2"
./push_swap "+1 2"
./push_swap "-1 2"
./push_swap $'+\t1'
./push_swap $'-\t1'
./push_swap $'1\t+2'
./push_swap $'1\n-2'


echo "========== FASE 4: DUPLICADOS =========="

echo "--- DUPLICADOS SIMPLES ---"
./push_swap 1 1
./push_swap 1 2 1
./push_swap 5 5 5
./push_swap -1 -1
./push_swap 0 0

echo "--- ZERO: FORMATOS DIFERENTES ---"
./push_swap 0 00
./push_swap 0 000
./push_swap 00 000
./push_swap 000 0000
./push_swap 00000 0
./push_swap +0 0
./push_swap -0 0
./push_swap +0 -0
./push_swap 00 +0
./push_swap 00 -0
./push_swap +00 000
./push_swap -00 000
./push_swap +000 -000
./push_swap 000000000 0
./push_swap -000000000 +0

echo "--- ZEROS A ESQUERDA ---"
./push_swap 01 1
./push_swap 001 1
./push_swap 0001 1
./push_swap 00001 1
./push_swap 000001 1
./push_swap 0000001 1
./push_swap 00042 42
./push_swap 0042 042
./push_swap 00042 +42
./push_swap 00042 +00042
./push_swap -00042 -42
./push_swap -00042 -0042
./push_swap +00042 42
./push_swap +0042 +42

echo "--- DUPLICADOS COM SINAIS ---"
./push_swap +1 1
./push_swap +01 1
./push_swap 001 +1
./push_swap -01 -1
./push_swap -001 -1
./push_swap +10 010
./push_swap -10 -010
./push_swap +001 -001
./push_swap +42 042
./push_swap -42 -042
./push_swap +0007 7
./push_swap -0007 -7

echo "--- DUPLICADOS NO MESMO ARGUMENTO ---"
./push_swap "1 2 1"
./push_swap "1 1 2"
./push_swap "01 1"
./push_swap "5 05 005"
./push_swap "1 +1"
./push_swap "0 -0"
./push_swap "0 +0"
./push_swap "10 20 30 20"
./push_swap "1 2 3 4 5 1"
./push_swap "1 2 3 2 4"
./push_swap "5 4 3 2 1 5"

echo "--- DUPLICADOS ENTRE ARGUMENTOS ---"
./push_swap "1 2" "3 2"
./push_swap "1 2" "02"
./push_swap "001" 1
./push_swap "0 1" "00"
./push_swap "10 20" "030 30"
./push_swap "1 2 3" "4 5 1"
./push_swap "100" "0100"
./push_swap "+42" "42"
./push_swap "-42" "-042"
./push_swap "0007 8" "+007 9"
./push_swap "1" "2" "3" "01"
./push_swap "1 2" "3" "4" "02"
./push_swap "001 002" "1 2"
./push_swap "+1 +2" "01 02"
./push_swap "-1 -2" "-01 -02"
./push_swap "1 2 3" "4 5" "3"
./push_swap "10 20" "30 40" "10"
./push_swap "1 2" "3 4" "5 6" "4"
./push_swap "7" "8 9" "10 7"
./push_swap "1 2 3 4" "5 6 7 8" "9 10 1"
./push_swap "42 43" "44 45" "+042"
./push_swap "-10 -20" "-30 -40" "-010"
./push_swap "001 002 003" "004 005" "3"
./push_swap "+1" "2" "3" "4" "5" "01"
./push_swap "-1" "-2" "-3" "-4" "-5" "-01"


echo "========== FASE 5: FLAGS =========="

echo "--- FLAGS DUPLICADAS ---"
./push_swap --simple --simple 2 3 4
./push_swap --medium --medium 2 3 4
./push_swap --complex --complex 2 3 4
./push_swap --adaptive --adaptive 2 3 4
./push_swap --bench --bench 2 3 4

echo "--- FLAGS DUPLICADAS ENTRE ARGUMENTOS ---"
./push_swap --simple "--simple 2 3 4"
./push_swap --medium "--medium 2 3 4"
./push_swap --complex "--complex 2 3 4"
./push_swap --adaptive "--adaptive 2 3 4"
./push_swap --bench "--bench 2 3 4"

echo "--- FLAGS DUPLICADAS EM ARGUMENTOS SEPARADOS ---"
./push_swap "--simple 2" "--simple 3 4"
./push_swap "--medium 2 3" "--medium 4"
./push_swap "--complex" "2 3" "--complex 4"
./push_swap "--adaptive 2 3" "4 --adaptive"
./push_swap "--bench 2" "3 --bench 4"

echo "--- FLAGS EM POSICOES DIFERENTES ---"
./push_swap 2 3 4 --simple
./push_swap 2 --simple 3 4
./push_swap 2 3 --simple 4
./push_swap "2 3" "--simple 4"
./push_swap "--simple" "2 3 4"
./push_swap "2" "--simple 3" "4"
./push_swap "2 3 --simple" "4"

echo "--- ALGORITMOS INCOMPATIVEIS ---"
./push_swap --simple --medium 2 3 4
./push_swap --simple --complex 2 3 4
./push_swap --medium --complex 2 3 4
./push_swap --simple --adaptive 2 3 4
./push_swap --medium --adaptive 2 3 4
./push_swap --complex --adaptive 2 3 4
./push_swap --simple --medium --complex 2 3 4
./push_swap --simple --medium --adaptive 2 3 4
./push_swap --simple --complex --adaptive 2 3 4
./push_swap --medium --complex --adaptive 2 3 4
./push_swap --simple --medium --complex --adaptive 2 3 4

echo "--- FLAGS DESCONHECIDAS ---"
./push_swap --unknown 2 3 4
./push_swap --simp 2 3 4
./push_swap --mediumx 2 3 4
./push_swap --adaptivex 2 3 4
./push_swap --benchx 2 3 4
./push_swap -simple 2 3 4
./push_swap -bench 2 3 4

echo "--- FLAGS MISTURADAS COM INPUT ---"
./push_swap "2 --simple 3 4"
./push_swap "2 3 --medium 4"
./push_swap "2 3 4 --complex"
./push_swap "2 --adaptive 3" 4
./push_swap "2 3" "--bench 4"
./push_swap "--simple 2" "3 --bench 4"
./push_swap "--bench" "--simple 2 3 4"
./push_swap "--adaptive" "--bench" "2 3 4"
