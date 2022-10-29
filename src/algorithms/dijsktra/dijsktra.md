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

## Examples A to last letter

### Simple

Best path: A->B->D->E
weights: 3->5->15 = 33


```mermaid
graph LR
    A --- |3|B
    A --- |7|C

    B --- |5|D
    C --- |9|D

    D --- |15|E
```

Best path: A->C->B->D->F
weights: 3->5->5->5 = 18

```mermaid
graph LR
    A --- |7|B
    A --- |3|C

    B --- |5|D

    C --- |12|E
    C --- |5|B

    D --- |5|F

    E --- |5|F
```




### Medium

Best path: A->C->H->I
weights: 7->10->15 = 32
```mermaid
graph LR
    A --- |3|B
    A --- |7|C
    A --- |2|D

    B --- |5|E
    B --- |8|F

    E --- |44|H
    F --- |55|C

    C --- |9|D
    C --- |10|H

    G --- |2|H
    G --- |14|I

    H --- |15|I
```


```mermaid
graph LR
    A --- |3|B
    A --- |7|C
    A --- |2|D

    B --- |5|G
    B --- |20|I

    C --- |9|D
    C --- |10|H

    D --- |15|I

    E --- |5|H
    E --- |2|F

    F --- |10|C
    F --- |2|D

    G --- |2|C
    G --- |14|I

    H --- |16|I
```


