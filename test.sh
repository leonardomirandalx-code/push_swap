

#!/bin/bash

make all || exit 1

SMALL="10 3 8 1 6 2 9 4 7 5"
MEDIUM="$(seq 100 -1 1)"
LARGE="$(seq 500 -1 1)"

BLUE='\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
RESET='\033[0m'

TOTAL=0
ERRORS=0
FAILED_TESTS="/tmp/ps_failed"

: > "$FAILED_TESTS"

section()
{
	printf "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
	printf "  %s\n" "$1"
	printf "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
}

subsection()
{
	printf "\n${YELLOW}%s${RESET}\n" "$1"
}

start_group()
{
	TOTAL=0
	ERRORS=0
	printf "  %-40s" "$1"
}

valid()
{
	./push_swap "$@" >/tmp/ps_out 2>/tmp/ps_err
	if [ $? -ne 0 ]; then
		ERRORS=$((ERRORS + 1))
		printf "  [EXPECTED: VALID] %s\n" "$*" >> "$FAILED_TESTS"
	fi
	TOTAL=$((TOTAL + 1))
}

invalid()
{
	./push_swap "$@" >/tmp/ps_out 2>/tmp/ps_err
	if [ $? -eq 0 ] || ! grep -qx "Error" /tmp/ps_err; then
		ERRORS=$((ERRORS + 1))
		printf "  [EXPECTED: INVALID] %s\n" "$*" >> "$FAILED_TESTS"
	fi
	TOTAL=$((TOTAL + 1))
}

end_group()
{
	if [ "$ERRORS" -eq 0 ]; then
		printf "${GREEN}PASS${RESET}  (%d tests)\n" "$TOTAL"
	else
		printf "${RED}FAIL${RESET}  (%d/%d failed)\n" "$ERRORS" "$TOTAL"
	fi
}

run_bench()
{
	local mode=$1
	local size=$2
	local name=${mode#--}
	local status
	local operations
	local result="/tmp/ps_result_${name}_${size}"

	shift 2
	./push_swap --bench "$mode" "$@" >/tmp/ps_out 2>/dev/null
	status=$?
	operations=$(wc -l < /tmp/ps_out)
	operations=${operations//[[:space:]]/}

	if [ "$status" -ne 0 ]; then
		printf "FAIL" > "$result"
	elif [ "$size" -eq 10 ]; then
		if [ "$operations" -le 10 ]; then
			printf "EXCELLENT" > "$result"
		elif [ "$operations" -le 20 ]; then
			printf "GOOD" > "$result"
		else
			printf "PASS" > "$result"
		fi
	elif [ "$size" -eq 100 ]; then
		if [ "$operations" -le 700 ]; then
			printf "EXCELLENT" > "$result"
		elif [ "$operations" -le 900 ]; then
			printf "GOOD" > "$result"
		else
			printf "PASS" > "$result"
		fi
	else
		if [ "$operations" -le 5500 ]; then
			printf "EXCELLENT" > "$result"
		elif [ "$operations" -le 7000 ]; then
			printf "GOOD" > "$result"
		else
			printf "PASS" > "$result"
		fi
	fi
}

show_result()
{
	local result

	result=$(cat "$1")
	case "$result" in
		EXCELLENT)
			printf "${GREEN}%-10s${RESET}" "$result"
			;;
		GOOD)
			printf "${YELLOW}%-10s${RESET}" "$result"
			;;
		PASS)
			printf "${BLUE}%-10s${RESET}" "$result"
			;;
		FAIL)
			printf "${RED}%-10s${RESET}" "$result"
			;;
	esac
}

section "1. FUNCTIONAL TESTS"

subsection "LOW DISORDER — SIMPLE"
./push_swap --bench --adaptive 1 2 3 4 5 6 7 9 8 > /tmp/ps_out
printf "  Operations: %s\n" "$(wc -l < /tmp/ps_out)"
./checker_linux 1 2 3 4 5 6 7 9 8 < /tmp/ps_out

subsection "MEDIUM DISORDER — MEDIUM"
./push_swap --bench --adaptive 5 4 3 2 1 6 7 8 9 10 > /tmp/ps_out
printf "  Operations: %s\n" "$(wc -l < /tmp/ps_out)"
./checker_linux 5 4 3 2 1 6 7 8 9 10 < /tmp/ps_out

subsection "HIGH DISORDER — COMPLEX"
./push_swap --bench --adaptive 10 9 8 7 6 5 4 3 2 1 > /tmp/ps_out
printf "  Operations: %s\n" "$(wc -l < /tmp/ps_out)"
./checker_linux 10 9 8 7 6 5 4 3 2 1 < /tmp/ps_out

section "2. PERFORMANCE BENCHMARK"

run_bench --simple 10 $SMALL
run_bench --simple 100 $MEDIUM
run_bench --simple 500 $LARGE

run_bench --medium 10 $SMALL
run_bench --medium 100 $MEDIUM
run_bench --medium 500 $LARGE

run_bench --complex 10 $SMALL
run_bench --complex 100 $MEDIUM
run_bench --complex 500 $LARGE

printf "\n  %-12s | %-10s | %-10s | %-10s\n" \
	"ALGORITHM" "10 NUMS" "100 NUMS" "500 NUMS"
printf "  ─────────────┼────────────┼────────────┼────────────\n"

for mode in simple medium complex
do
	printf "  %-12s | " "${mode^^}"
	show_result "/tmp/ps_result_${mode}_10"
	printf " | "
	show_result "/tmp/ps_result_${mode}_100"
	printf " | "
	show_result "/tmp/ps_result_${mode}_500"
	printf "\n"
done

section "3. PARSING TESTS"

subsection "PHASE 1 — NUMERIC VALIDATION"

start_group "VALID INPUT"
valid 3 2 1
valid -42 0 42
valid +42 -42 0
end_group

start_group "INVALID TEXT AND CHARACTERS"
invalid abc
invalid 1 abc 3
invalid 123abc
invalid abc123
invalid 3.14
invalid 1,2
invalid 1/2
invalid 1:2
invalid 1_2
invalid "1@2"
invalid "1#2"
end_group

start_group "ISOLATED SIGNS"
invalid +
invalid -
invalid + ""
invalid - ""
end_group

start_group "REPEATED SIGNS"
invalid ++1
invalid --1
invalid +-1
invalid -+1
invalid +++1
invalid ---1
invalid ++-1
invalid --+1
end_group

start_group "INTERLEAVED SIGNS"
invalid 1-2
invalid 1+2
invalid 12-3
invalid 12+3
invalid 1--2
invalid 1++2
invalid 1+-2
invalid 1-+2
invalid 1-2-3
invalid 1+2+3
invalid 1+-2+3
invalid 1 -2+3
invalid 1 2-3
invalid 1 2 3-4
invalid 1- 2
valid 1 -2
invalid 1 + 2
invalid 1 - 2
end_group

start_group "TRAILING SIGNS"
invalid 42+
invalid 42-
invalid 42++
invalid 42--
end_group

start_group "MIXED INVALID CHARACTERS"
invalid "++42abc"
invalid "--42abc"
invalid "+-42abc"
invalid "42abc+"
invalid "42abc-"
invalid "1 2abc 3"
invalid "1 abc2 3"
invalid "1 2.0 3"
invalid "1 +abc 3"
invalid "1 -abc 3"
end_group

subsection "PHASE 2 — NUMERIC LIMITS"

start_group "VALID LIMITS"
valid 2147483647
valid -2147483648
valid 2147483647 -2147483648
valid +2147483647
valid -0
valid 00
valid -00
valid 00000000002147483647
valid -00000000002147483648
end_group

start_group "POSITIVE OVERFLOW"
invalid 2147483648
invalid 2147483649
invalid 2147483650
invalid 9999999999
invalid 99999999999
invalid 999999999999
invalid 999999999999999
invalid 999999999999999999
invalid 999999999999999999999
invalid 999999999999999999999999999999999999
end_group

start_group "NEGATIVE OVERFLOW"
invalid -2147483649
invalid -2147483650
invalid -9999999999
invalid -99999999999
invalid -999999999999
invalid -999999999999999
invalid -999999999999999999
invalid -999999999999999999999
invalid -999999999999999999999999999999999999
end_group

start_group "SIGNS AND LIMITS"
invalid +2147483648
invalid -2147483649
invalid ++2147483647
invalid --2147483648
invalid +-2147483648
invalid -+2147483647
end_group

start_group "LEADING ZEROS BEFORE LIMITS"
valid 00000000002147483647
valid -00000000002147483648
valid +00000000002147483647
invalid 00000000002147483648
invalid -00000000002147483649
end_group

subsection "PHASE 3 — WHITESPACE AND EMPTY ARGUMENTS"

start_group "EMPTY ARGUMENTS"
invalid ""
invalid " "
invalid "   "
invalid ""
invalid 1 ""
invalid "" 1
invalid 1 "" 2
invalid "1 2" ""
end_group

start_group "SPACES"
valid "1 2"
valid " 1 2"
valid "1 2 "
valid " 1 2 "
valid "  1  2  "
valid "1   2"
valid "1    2    3"
valid "   1   2   3   "
end_group

start_group "TABS"
valid $'1\t2'
valid $'\t1 2'
valid $'1 2\t'
valid $'1\t\t2'
valid $'1\t2\t3'
valid $' \t1\t 2\t '
end_group

start_group "NEWLINES"
valid $'1\n2'
valid $'\n1 2'
valid $'1 2\n'
valid $'1\n\n2'
valid $'1\n2\n3'
valid $' \n1\n 2\n '
end_group

start_group "CARRIAGE RETURNS"
valid $'1\r2'
valid $'\r1 2'
valid $'1 2\r'
valid $'1\r\r2'
valid $'1\r2\r3'
end_group

start_group "VERTICAL TAB AND FORM FEED"
valid $'1\v2'
valid $'1\f2'
valid $'\v1 2'
valid $'\f1 2'
valid $'1\v2\f3'
end_group

start_group "MIXED WHITESPACE"
valid $'1 \t2'
valid $'1\t 2'
valid $'1\n\t2'
valid $'1\r\n2'
valid $' 1\t\n 2\r '
valid $'\t 1 \n 2 \r 3 \v 4 \f'
end_group

start_group "SIGNS WITH WHITESPACE"
invalid "+ 1"
invalid "- 1"
valid "1 +2"
valid "1 -2"
valid "+1 2"
valid "-1 2"
invalid $'+\t1'
invalid $'-\t1'
valid $'1\t+2'
valid $'1\n-2'
end_group

subsection "PHASE 4 — DUPLICATES"

start_group "SIMPLE DUPLICATES"
invalid 1 1
invalid 1 2 1
invalid 5 5 5
invalid -1 -1
invalid 0 0
end_group

start_group "ZERO: DIFFERENT FORMATS"
invalid 0 00
invalid 0 000
invalid 00 000
invalid 000 0000
invalid 00000 0
invalid +0 0
invalid -0 0
invalid +0 -0
invalid 00 +0
invalid 00 -0
invalid +00 000
invalid -00 000
invalid +000 -000
invalid 000000000 0
invalid -000000000 +0
end_group

start_group "LEADING ZEROS"
invalid 01 1
invalid 001 1
invalid 0001 1
invalid 00001 1
invalid 000001 1
invalid 0000001 1
invalid 00042 42
invalid 0042 042
invalid 00042 +42
invalid 00042 +00042
invalid -00042 -42
invalid -00042 -0042
invalid +00042 42
invalid +0042 +42
end_group

start_group "DUPLICATES WITH SIGNS"
invalid +1 1
invalid +01 1
invalid 001 +1
invalid -01 -1
invalid -001 -1
invalid +10 010
invalid -10 -010
valid +001 -001
invalid +42 042
invalid -42 -042
invalid +0007 7
invalid -0007 -7
end_group

start_group "DUPLICATES IN SAME ARGUMENT"
invalid "1 2 1"
invalid "1 1 2"
invalid "01 1"
invalid "5 05 005"
invalid "1 +1"
invalid "0 -0"
invalid "0 +0"
invalid "10 20 30 20"
invalid "1 2 3 4 5 1"
invalid "1 2 3 2 4"
invalid "5 4 3 2 1 5"
end_group

start_group "DUPLICATES ACROSS ARGUMENTS"
invalid "1 2" "3 2"
invalid "1 2" "02"
invalid "001" 1
invalid "0 1" "00"
invalid "10 20" "030 30"
invalid "1 2 3" "4 5 1"
invalid "100" "0100"
invalid "+42" "42"
invalid "-42" "-042"
invalid "0007 8" "+007 9"
invalid "1" "2" "3" "01"
invalid "1 2" "3" "4" "02"
invalid "001 002" "1 2"
invalid "+1 +2" "01 02"
invalid "-1 -2" "-01 -02"
invalid "1 2 3" "4 5" "3"
invalid "10 20" "30 40" "10"
invalid "1 2" "3 4" "5 6" "4"
invalid "7" "8 9" "10 7"
invalid "1 2 3 4" "5 6 7 8" "9 10 1"
invalid "42 43" "44 45" "+042"
invalid "-10 -20" "-30 -40" "-010"
invalid "001 002 003" "004 005" "3"
invalid "+1" "2" "3" "4" "5" "01"
invalid "-1" "-2" "-3" "-4" "-5" "-01"
end_group

subsection "PHASE 5 — FLAGS"

start_group "DUPLICATE FLAGS"
invalid --simple --simple 2 3 4
invalid --medium --medium 2 3 4
invalid --complex --complex 2 3 4
invalid --adaptive --adaptive 2 3 4
invalid --bench --bench 2 3 4
end_group

start_group "DUPLICATE FLAGS ACROSS ARGUMENTS"
invalid --simple "--simple 2 3 4"
invalid --medium "--medium 2 3 4"
invalid --complex "--complex 2 3 4"
invalid --adaptive "--adaptive 2 3 4"
invalid --bench "--bench 2 3 4"
end_group

start_group "DUPLICATE FLAGS IN SEPARATE ARGUMENTS"
invalid "--simple 2" "--simple 3 4"
invalid "--medium 2 3" "--medium 4"
invalid "--complex" "2 3" "--complex 4"
invalid "--adaptive 2 3" "4 --adaptive"
invalid "--bench 2" "3 --bench 4"
end_group

start_group "FLAGS IN DIFFERENT POSITIONS"
valid 2 3 4 --simple
valid 2 --simple 3 4
valid 2 3 --simple 4
valid "2 3" "--simple 4"
valid "--simple" "2 3 4"
valid "2" "--simple 3" "4"
valid "2 3 --simple" "4"
end_group

start_group "INCOMPATIBLE ALGORITHMS"
invalid --simple --medium 2 3 4
invalid --simple --complex 2 3 4
invalid --medium --complex 2 3 4
invalid --simple --adaptive 2 3 4
invalid --medium --adaptive 2 3 4
invalid --complex --adaptive 2 3 4
invalid --simple --medium --complex 2 3 4
invalid --simple --medium --adaptive 2 3 4
invalid --simple --complex --adaptive 2 3 4
invalid --medium --complex --adaptive 2 3 4
invalid --simple --medium --complex --adaptive 2 3 4
end_group

start_group "UNKNOWN FLAGS"
invalid --unknown 2 3 4
invalid --simp 2 3 4
invalid --mediumx 2 3 4
invalid --adaptivex 2 3 4
invalid --benchx 2 3 4
invalid -simple 2 3 4
invalid -bench 2 3 4
end_group

start_group "FLAGS MIXED WITH INPUT"
valid "2 --simple 3 4"
valid "2 3 --medium 4"
valid "2 3 4 --complex"
valid "2 --adaptive 3" 4
valid "2 3" "--bench 4"
valid "--simple 2" "3 --bench 4"
valid "--bench" "--simple 2 3 4"
valid "--adaptive" "--bench" "2 3 4"
end_group

section "TESTS COMPLETED"

if [ -s "$FAILED_TESTS" ]; then
	printf "\n${RED}FAILED TEST CASES${RESET}\n"
	cat "$FAILED_TESTS"
else
	printf "\n${GREEN}ALL TESTS PASSED${RESET}\n"
fi

rm -f /tmp/ps_out /tmp/ps_err /tmp/ps_result_* "$FAILED_TESTS"
