*This project has been created as part of the 42 curriculum by tisilva, leomiran.*

# push_swap

Sort a sequence of integers with two stacks and eleven instructions, using as few operations as possible.

## Description

**push_swap** is an algorithmic project from the 42 curriculum. The program reads a list of unique integers, places them in **Stack A**, and prints to standard output a sequence of instructions that leaves Stack A sorted in ascending order (smallest value on top). **Stack B** starts empty and serves as auxiliary storage.

The project focuses on algorithm design, complexity analysis, stack manipulation and optimisation. It also explores how the *initial disorder* of a sequence can guide the choice of sorting strategy: the default `--adaptive` mode measures the disorder first and then picks the strategy that suits it.

## Table of Contents

- [Project Overview](#project-overview)
- [Stack Operations](#stack-operations)
- [Disorder Metric](#disorder-metric)
- [Sorting Strategies](#sorting-strategies)
- [Benchmark Mode](#benchmark-mode)
- [Instructions](#instructions)
- [Usage](#usage)
- [Input Validation](#input-validation)
- [Testing](#testing)
- [Performance Targets](#performance-targets)
- [Code Organisation](#code-organisation)
- [Resources](#resources)
- [AI Usage](#ai-usage)

## Project Overview

- **Stack A** initially contains all input integers and must end sorted in ascending order. The **first** input integer is the **top** of Stack A.
- **Stack B** starts empty.

| Option | Strategy | Operation complexity |
|---|---|---:|
| `--simple` | Simple | O(n²) |
| `--medium` | Medium | O(n√n) |
| `--complex` | Complex | O(n log n) |
| `--adaptive` | Chosen from the initial disorder | Depends on disorder |

`--adaptive` is the default when no strategy option is given.

The complexity classes refer to the **number of push_swap operations generated**, not to the running time of conventional array-based sorting algorithms.

## Stack Operations

Every strategy is built from the following instructions. An operation on a stack with fewer than two elements (or a push from an empty stack) does nothing.

| Instruction | Description |
|---|---|
| `sa` | Swap the first two elements of Stack A. |
| `sb` | Swap the first two elements of Stack B. |
| `ss` | Execute `sa` and `sb` simultaneously. |
| `pa` | Push the top element of B onto A. |
| `pb` | Push the top element of A onto B. |
| `ra` | Rotate A upwards: the first element becomes the last. |
| `rb` | Rotate B upwards: the first element becomes the last. |
| `rr` | Execute `ra` and `rb` simultaneously. |
| `rra` | Reverse rotate A: the last element becomes the first. |
| `rrb` | Reverse rotate B: the last element becomes the first. |
| `rrr` | Execute `rra` and `rrb` simultaneously. |

Both stacks are implemented as singly linked lists; each operation only relinks nodes and never copies values.

## Disorder Metric

Before any operation, the program measures how far Stack A is from being sorted. It counts the **inversions**: every pair of elements in which a larger value appears before a smaller one counts as one mistake.

$$
\text{Disorder} = \frac{\text{Inversions}}{\text{Total Pairs}}
\qquad\text{where}\qquad
\text{Total Pairs} = \frac{n(n-1)}{2}
$$

The result ranges from `0` to `1`:

- `0.00`: the stack is already sorted.
- `1.00`: the stack is in reverse order.
- Anything in between: partially ordered input.

For fewer than two elements the disorder is `0`.

| Stack A (top first) | Inversions | Pairs | Disorder |
|---|---:|---:|---:|
| `1 2 3` | 0 | 3 | 0.00 |
| `3 1 2` | 2 (`3>1`, `3>2`) | 3 | 0.67 |
| `3 2 1` | 3 | 3 | 1.00 |

## Sorting Strategies

For each strategy this section states the technique used, why it suits its role, and the upper-bound reasoning for the operation count and for the auxiliary space.

### Simple — O(n²)

> **To be completed by the team:** describe the technique, why a quadratic bound is acceptable for low-disorder inputs, and the reasoning for the O(n²) operation bound and the auxiliary space.

### Medium — O(n√n)

**Technique: chunk-based partition.**

1. Copy the values into an array and sort the copy. The copy is only a *reference* to know which chunk each value belongs to; it is never used as a stack.
2. Split the sorted values into about `√n / 2` consecutive chunks (5 chunks for 100 numbers, 11 for 500).
3. **Stack A → Stack B**, chunk by chunk from the smallest to the largest: for each chunk, find the element of that chunk that is closest to the top or to the bottom of A, bring it to the top with `ra` or `rra`, and `pb` it. If the element belongs to the **lower half of its chunk**, also `rb` it, which sends the smaller values to the bottom of B and keeps the larger ones near the top.
4. **Stack B → Stack A**: while B is not empty, bring the **maximum** of B to the top by the shorter of `rb` / `rrb`, then `pa`. Pushing the largest value first leaves A sorted with the smallest value on top.

Inputs that are already sorted produce no operations, and two elements in the wrong order are fixed with a single `sa`.

**Why it suits medium disorder (`0.2 ≤ disorder < 0.5`).** The input is partly ordered, but not enough to rely on long sorted runs. The chunk strategy does not depend on any pre-existing order, so its cost stays bounded for these inputs, and it is far cheaper than the quadratic strategy on larger sequences.

**Upper-bound reasoning (sketch).** With `k ≈ √n / 2` chunks:

- *Phase 1.* Handling one chunk takes at most about one sweep over Stack A (at most `n` rotations) plus one `pb` per element of the chunk. Over `k` chunks this is `O(n·k) = O(n√n)` rotations plus `n` pushes.
- *Phase 2.* Stack B is nearly ordered by chunk, so the next maximum is always close to the top or to the bottom (at a distance proportional to the chunk size, `O(√n)`). The `n` pulls therefore cost `O(n√n)` rotations plus `n` pushes.

Total: **O(n√n)** operations. This is an argument sketch, not a formal proof; the operation counts measured on random permutations grow consistently with it.

**Auxiliary space.** O(n) for the sorted copy of the values, plus Stack B (at most `n` nodes). No other data structure grows with the input.

### Complex — O(n log n)

> **To be completed by the team:** describe the technique, why it fits highly disordered inputs, and the reasoning for the O(n log n) operation bound and the auxiliary space.

### Adaptive

Measures the initial disorder and selects the strategy accordingly:

| Disorder | Selected strategy | Required complexity |
|---|---|---|
| `disorder < 0.2` | Simple | O(n²) |
| `0.2 ≤ disorder < 0.5` | Medium | O(n√n) |
| `disorder ≥ 0.5` | Complex | O(n log n) |

These thresholds follow the project specification.

## Benchmark Mode

The optional `--bench` flag enables benchmark reporting. After sorting, the program writes the following to **standard error**:

- the initial disorder, as a percentage with two decimal places;
- the selected strategy and its complexity class;
- the total number of operations;
- the count of every operation type: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.

The operation sequence goes to **standard output** and the benchmark data to **standard error**, so the two never interfere:

```bash
./push_swap --bench 4 67 3 87 23 > operations.txt   # benchmark appears on the terminal
./push_swap --bench 4 67 3 87 23 2> bench.txt       # operations appear on the terminal
```

`--bench` can be combined with any strategy option. Used on its own, it runs the adaptive strategy.

## Instructions

### Requirements

- A C compiler.
- `make`.
- The 42 `checker` program, or an equivalent checker, to validate the output.

### Compilation

```bash
git clone https://github.com/leonardomirandalx-code/push_swap.git
cd push_swap
make
```

This produces the `push_swap` executable.

### Makefile Rules

| Command | Description |
|---|---|
| `make` / `make all` | Compile the project. |
| `make clean` | Remove object files. |
| `make fclean` | Remove object files and the executable. |
| `make re` | Clean and recompile. |

Running `make` again without changing any source file does not relink.

## Usage

```text
./push_swap [strategy] [--bench] integer [integer ...]
```

Options can be placed **anywhere** on the command line; these commands are equivalent:

```bash
./push_swap --medium --bench 4 67 3 87 23
./push_swap 4 67 --bench 3 87 --medium 23
./push_swap 4 67 3 87 23 --medium --bench
./push_swap "4 67 --medium 3" 87 23 --bench
./push_swap "--medium --bench 4 67 3 87 23"
```

### Choose a strategy

```bash
./push_swap 4 67 3 87 23                  # adaptive (default)
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

### Benchmark

```bash
./push_swap --adaptive --bench 4 67 3 87 23
```

### Verify the output

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG     # prints OK when correctly sorted
```

### Count the operations

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
```

## Input Validation

The program accepts a sequence of **unique** integers, given as separate arguments, as one quoted argument, or as a mix of both. At least one integer is required.

Each integer has the form *optional sign followed by one or more decimal digits*, and must fit in a signed 32-bit integer:

$$
-2147483648 \le n \le 2147483647
$$

Options (`--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`) are optional. They can appear **in any position** on the command line (before, between or after the integers), either as separate arguments or **inside a quoted argument** together with the integers. Each option may be given **at most once** (counting every argument and every quoted string), and only one strategy option is allowed.

### Valid inputs

| Case | Example | Notes |
|---|---|---|
| Positive integers | `./push_swap 1 2 3 4 5` | |
| Negative integers | `./push_swap -1 -2 -3` | |
| Mixed signs and zero | `./push_swap -10 42 0 7 -3` | |
| Single integer | `./push_swap 42` | Valid; no operations are needed. |
| Integer limits | `./push_swap -2147483648 2147483647` | Both boundaries are valid. |
| One quoted argument | `./push_swap "4 67 3 87 23"` | |
| Several spaces | `./push_swap "  4    67   3  87   23  "` | |
| Leading zeros | `./push_swap 0042 0007 0001` | The numeric value is what counts. |
| Explicit `+` sign | `./push_swap +42 +7 +1` | |
| Tab-separated | `./push_swap $'4\t67\t3\t87\t23'` | See the separators below. |
| Options in any position | `./push_swap 4 67 --medium 3 87 23`, `./push_swap 4 67 3 87 23 --bench` | The position of an option does not matter. |
| Options inside a quoted argument | `./push_swap "4 67 --medium 3 87 23"`, `./push_swap "--bench 4 67" 3 87 23` | Options are recognised inside a quoted string too. |

**Recognised separators** inside a quoted argument: space, `\t`, `\n`, `\v`, `\f` and `\r`.

### Invalid inputs

Every invalid input prints `Error` to **standard error** and produces no instructions.

| Case | Example | Why |
|---|---|---|
| Duplicates | `./push_swap 1 2 2 3` | Repeated value. |
| Duplicates written differently | `./push_swap 01 1`, `+42 42`, `-0 0` | Duplicates are detected by numeric value, not by text. |
| Non-numeric text | `./push_swap 1 2 abc`, `1a 2 3` | |
| Incomplete sign | `./push_swap +`, `-`, `1 + 2` | A sign must be followed by a digit. |
| Repeated signs | `./push_swap ++42`, `--42`, `+-42`, `-+42` | Only one sign is allowed. |
| Decimals | `./push_swap 1.5 2 3`, `3,5 4` | Only integers are accepted. |
| Above `INT_MAX` | `./push_swap 2147483648`, `999999999999` | Out of range. |
| Below `INT_MIN` | `./push_swap -2147483649` | Out of range. |
| Empty argument | `./push_swap ""` | |
| Only whitespace | `./push_swap "     "` | |
| Wrong separators | `./push_swap "1,2,3"`, `"1;2;3"` | Only whitespace separates numbers. |
| Unknown option | `./push_swap --unknown 1 2 3` | |
| Conflicting strategies | `./push_swap --simple --complex 1 2 3` | One strategy per run. |
| Repeated option | `./push_swap --simple --simple 1 2 3`, `./push_swap --bench --bench 1 2 3`, `./push_swap --simple "--simple 1 2 3"` | Each option may appear only once, even if repeated identically, across separate arguments or inside a quoted argument. |
| No integers | `./push_swap --simple`, `--bench`, `--adaptive --bench` | Options do not replace the integer sequence. |

### Special cases

| Case | Example | Behaviour |
|---|---|---|
| No arguments | `./push_swap` | No output at all. |
| Already sorted | `./push_swap 1 2 3 4 5` | No operations. |

## Testing

### Sizes and arrangements

```bash
./push_swap 2 1
./push_swap 1 2 3 4 5
./push_swap 5 4 3 2 1
./push_swap -10 42 0 7 -3
```

### Limits, duplicates and parsing

```bash
./push_swap -2147483648 2147483647
./push_swap 2147483648            # Error
./push_swap -2147483649           # Error
./push_swap 1 2 2 3               # Error
./push_swap --simple --simple 1 2 3   # Error (repeated option)
./push_swap --simple --complex 1 2 3  # Error (conflicting strategies)
./push_swap 4 67 --medium 3 87 23     # option in the middle: valid
./push_swap "4 67 --medium 3 87 23"   # option inside a quoted argument: valid
./push_swap --simple "--simple 1 2 3" # Error (repeated option across arguments)
./push_swap 01 1                  # Error
./push_swap -0 0                  # Error
./push_swap "4 67 3 87 23"
./push_swap "  4    67   3  87   23  "
./push_swap $'4\t67\t3\t87\t23'
```

Check that errors go to standard error and not to standard output:

```bash
./push_swap 1 1 2>&1 >/dev/null   # prints "Error" (stderr only)
```

### Random permutations

Validate 100 random permutations of 100 numbers (the expected result is `100 OK`):

```bash
for i in $(seq 1 100); do
	ARG=$(shuf -i 0-9999 -n 100 | tr '\n' ' ')
	./push_swap $ARG | ./checker_linux $ARG
done | sort | uniq -c
```

Find the worst operation count over 100 permutations of 500 numbers:

```bash
for i in $(seq 1 100); do
	ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
	./push_swap $ARG | wc -l
done | sort -n | tail -1
```

Compare the strategies on the same input by adding `--simple`, `--medium` or `--complex` to the commands above.

## Performance Targets

Operation-count targets from the project specification:

| Input size | Minimum requirement | Good performance | Excellent performance |
|---|---:|---:|---:|
| 100 numbers | Below 2,000 | Below 1,500 | Below 700 |
| 500 numbers | Below 12,000 | Below 8,000 | Below 5,500 |

## Code Organisation

| Location | Responsibility |
|---|---|
| `main.c` | Program entry point. |
| `push_swap.h` | Types, enums and function prototypes. |
| `parsing/` | Argument parsing and validation: numbers, options, range, duplicates. |
| `helpers/` | Whitespace-aware `split`, `atoi` with range check, string utilities, and the linked-list stack helpers. |
| `actions/` | The eleven stack operations, individual and combined. |
| `Makefile` | `all`, `clean`, `fclean`, `re`. |

## Resources

- [42 School](https://42.fr/)
- [C Reference — cppreference](https://en.cppreference.com/w/c.html)
- [Linux Manual Pages](https://man7.org/linux/man-pages/)
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)
- [AI](#ai-usage)

## AI Usage

- exploring algorithmic approaches and reviewing its operation-count bound;
- reviewing the input parser;
- writing test scripts;
- debugging;
