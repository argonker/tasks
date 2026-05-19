# Yacc Examples

Two programs built with yacc/bison demonstrating bottom-up parsing.

## Programs

### stretch — Bracket System Stretch

Computes the *stretch* of a bracket system — the number of top-level irreducible bracket systems concatenated together.

**Examples:**
```
()()()    → 3
(()())    → 1
()(()())  → 2
          → 0  (empty input)
```

### calc — Integer Calculator

Evaluates arithmetic expressions with correct operator precedence and associativity.

**Supported operations:** `+`, `-`, `*`, `/`, unary minus, parentheses.

**Examples:**
```
2 + 3 * 4    → 14
(2 + 3) * 4  → 20
-3 * 4       → -12
-2 / 22      → 0   (integer division)
```