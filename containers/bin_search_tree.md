<!--
 Copyright (C) 2022 José Enrique Vilca Campana

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
-->
<!--

-->
# Balancing a binary tree

A < B < C
```mermaid
  graph TD
  rm[B]--> rl[A] & rr[C]

  1a[A] --> 1n[null] & 1b[B]
  1b --> 1nn[null] & 1c[C]

  2c[C] --> 2b[B] & 2n[null]
  2b --> 2a[A] & 2nn[null]
```

```mermaid
  graph TD
  3c[C] --> 3a[A] & 3n[null]
  3a --> 3nn[null] & 3b[B]

  4a[A] --> 4n[null] & 4c[C]
  4c --> 4b[B] & 4nn[null]
```


### + 2 nodes
```mermaid
  graph TD
  ROOT-->root
  root[h]--> L & R

  L[d]--> LL & LR
    LL[b]--> LLL[a] & LLR[c]
    LR[f]--> LRL[e] & LRR[g]
  R[j]
```
extra nodes: `h,j`
or
```mermaid
  graph TD
  ROOT-->root
  root[h]--> L & R

  L[d]--> LL & LR
    LL[b]--> LLL[a] & LLR[c]
    LR[f]--> LRL[e] & LRR[g]
  R[j]
```

### + 3 nodes
```mermaid
  graph TD
  ROOT-->root
  root[h]--> L & R

  L[d]--> LL & LR
    LL[b]--> LLL[a] & LLR[c]
    LR[f]--> LRL[e] & LRR[g]
  R[j]--> RL[i] & RR[null]
```
extra nodes: 3 : `h,j,i`

or

```mermaid
  graph TD
  ROOT-->root

  root[g]--> L & R
    L[d]--> LL[b] & LR[f]
    R[i]--> RL[h] & RR[j]

  LL--> LLL[a] & LLR[c]
  LR--> LRL[e] & LRR[null]
```
# + 4 nodes
```mermaid
  graph TD
  ROOT-->root
  root[h]--> L & R

  L[d]--> LL & LR
    LL[b]--> LLL[a] & LLR[c]
    LR[f]--> LRL[e] & LRR[g]
  R[j]--> RL[i] & RR[k]
```
extra nodes: 4 : `h,j,i,k` : root & right
note: same tree if we add 4 nodes to the bottom of left

###
```mermaid
  graph TD
  ROOT-->root

  root[g]--> L & R
    L[d]--> LL[b] & LR[f]
    R[i]--> RL[h] & RR[j]

  LL--> LLL[a] & LLR[c]
  LR--> LRL[e] & LRR[null]
```

<!-- a,b,c,d,e,f,g,h,i,k -->
