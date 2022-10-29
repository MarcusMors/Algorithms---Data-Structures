// Copyright (C) 2022 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

namespace fstd {

int busqueda_binaria_recursiva(int array[], int inicio, int final, int buscado)
{
  if (inicio > final) { return -1; }

  int indice_del_medio = (inicio + final) / 2;
  int valor_del_medio = array[indice_del_medio];

  if (buscado == valor_del_medio) { return indice_del_medio; }
  if (buscado < valor_del_medio) {// está a la izquierda
    final = indice_del_medio - 1;
  } else {// está a la derecha
    inicio = indice_del_medio + 1;
  }

  return busqueda_binaria_recursiva(array, inicio, final, buscado);
}

int busqueda_binaria_iterativa(int array[], int n, int buscado)
{
  int inicio = 0;
  int final = n - 1;
  int indice_del_medio = 0;
  while (inicio <= final) {
    indice_del_medio = (inicio + final) / 2;
    if (buscado == array[indice_del_medio]) { return indice_del_medio; }
    if (buscado < array[indice_del_medio]) {// está a la izquierda
      final = indice_del_medio - 1;
    } else {
      inicio = indice_del_medio + 1;
    }
  }
  return -1;
}

int busqueda_secuencial(int arr[], int n, int buscado)
{
  for (int i = 0; i < n; i++) {
    if (buscado == arr[i]) { return i; }
  }
  return -1;
}

// int busqueda_binaria(int array[], int x, int inicio, int final)
// {
//   if (final < inicio) { return -1; }

//   int medio = (inicio + final) / 2;

//   if (array[medio] == x) { return medio; }

//   if (array[medio] > x) {// x está en la parte izquierda
//     return busqueda_binaria(array, x, inicio, medio - 1);
//   }

//   // x está en la parte derecha
//   return busqueda_binaria(array, x, medio + 1, final);
// }

// int busqueda_binaria(int arr[], int inicio, int final, int n)
// {

//   if (inicio > final) { return -1; }

//   int medio = (inicio + final) / 2;

//   if (n == arr[medio]) {
//     return medio;
//   } else if (n > arr[medio]) {// n está en el lado derecho
//     return busqueda_binaria(arr, medio + 1, final, n);
//   }// n está en el lado izquierdo
//   return busqueda_binaria(arr, inicio, medio - 1, n);
// }

}// namespace fstd
