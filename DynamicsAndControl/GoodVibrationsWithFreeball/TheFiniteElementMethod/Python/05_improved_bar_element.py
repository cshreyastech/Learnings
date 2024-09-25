# https://www.youtube.com/watch?v=nGN9uqP67Ak&list=PL2ym2L69yzkaue8Ly2Oz51LALRzUV8LZ0&index=3

import numpy as np
import math

from scipy.linalg import eigh
from matplotlib import pyplot as plt
import time

def Bar2(num_elems):
  restrained_dofs = [0,]
  """  
  [m] = (p A l / 6) * 2   1
                      1   2


  [k] = E A /l * 1  -1
                -1   1
  """

  # element mass and stiffness matrices for a bar 
  # (2, 2)
  m = np.array([[2,  1], [1, 2]]) / (6. * float(num_elems))
  k = np.array([[1, -1], [-1, 1]]) * float(num_elems)

  # construct global mass and stiffness matrices
  # (num_elems + 1, num_elems + 1)
  M = np.zeros((num_elems + 1, num_elems + 1))
  K = np.zeros((num_elems + 1, num_elems + 1))

  # assembley of elements
  for i in range(num_elems):
    # print('num_elems: {} \ti: {}'.format(num_elems, i))
    #(num_elems + 1, num_elems + 1)
    M_temp = np.zeros((num_elems + 1, num_elems + 1))
    K_temp = np.zeros((num_elems + 1, num_elems + 1))

    M_temp[i : i + 2, i : i + 2] = m
    K_temp[i : i + 2, i : i + 2] = k

    M += M_temp
    K += K_temp

  # print("restrained_dofs")
  # print(restrained_dofs)
  # removed the fixed degree of freedom
  for dof in restrained_dofs:
    for i in [0, 1]:
      M = np.delete(M, dof, axis=i)
      K = np.delete(K, dof, axis=i)

  # eigen value problem
  evals, evecs = eigh(K, M)
  frequencies = np.sqrt(evals)

  return M, K, frequencies, evecs


def Bar3(num_elems):
  restrained_dofs = [0,]
  # element mass and stiffness matrices for a bar 
  # (3, 3)
  m = np.array([[4,  2, -1], [ 2, 16,  2], [-1,  2, 4]]) / (30.0 * float(num_elems))
  k = np.array([[7, -8,  1], [-8, 16, -8], [ 1, -8, 7]]) / 3.0 * float(num_elems)

  # construct global mass and stiffness matrices
  # (2 * num_elems + 1, 2 * num_elems + 1)
  M = np.zeros((2 * num_elems + 1, 2 * num_elems + 1))
  K = np.zeros((2 * num_elems + 1, 2 * num_elems + 1))

  # assembley of elements
  for i in range(num_elems):
    #(2 * num_elems + 1, 2 * num_elems + 1)
    M_temp = np.zeros((2 * num_elems + 1, 2 * num_elems + 1))
    K_temp = np.zeros((2 * num_elems + 1, 2 * num_elems + 1))

    first_node = 2 * i
    M_temp[first_node : first_node + 3, first_node : first_node + 3] = m
    K_temp[first_node : first_node + 3, first_node : first_node + 3] = k

    M += M_temp
    K += K_temp

  # print("restrained_dofs")
  # print(restrained_dofs)
  # removed the fixed degree of freedom
  for dof in restrained_dofs:
    for i in [0, 1]:
      M = np.delete(M, dof, axis=i)
      K = np.delete(K, dof, axis=i)

  # eigen value problem
  evals, evecs = eigh(K, M)
  frequencies = np.sqrt(evals)

  return M, K, frequencies, evecs


def PlotFrequencies(n):
  print("2 Node bar element")
  exact_frequency = math.pi / 2
  results = []

  for i in range(1, n):
    start = time.perf_counter()
    M, K, frequencies, evecs = Bar2(i)
    time_taken = time.perf_counter() - start
    error = (frequencies[0] - exact_frequency) / exact_frequency * 100.0
    results.append((i, error))

    print('Num Elems: {} \tFund. Frequency: {} \t Error: {}% \tShape: {} \tTime: {}'.format(i, round(frequencies[0], 3), round(error, 3), K.shape, round(time_taken*1000, 3)))


  print('Exact frequency: ', round(exact_frequency, 3))

  # plot the results
  elements = np.array([x[0] for x in results])
  errors2   = np.array([x[1] for x in results])

  print("3 Node bar element")
  exact_frequency = math.pi / 2
  results = []

  for i in range(1, n):
    start = time.perf_counter()
    M, K, frequencies, evecs = Bar3(i)
    time_taken = time.perf_counter() - start
    error = (frequencies[0] - exact_frequency) / exact_frequency * 100.0
    results.append((i, error))

    print('Num Elems: {} \tFund. Frequency: {} \t Error: {}% \tShape: {} \tTime: {}'.format(i, round(frequencies[0], 3), round(error, 3), K.shape, round(time_taken*1000, 3)))


  print('Exact frequency: ', round(exact_frequency, 3))

  # plot the results
  elements = np.array([x[0] for x in results])
  errors3   = np.array([x[1] for x in results])


  plt.plot(elements, errors2, 'o-')
  plt.plot(elements, errors3, 'o-')
  plt.xlim(elements[0], elements[-1])
  plt.xlabel('Number of Elements')
  plt.ylabel('Error (%)')
  plt.show()
if __name__ == '__main__':
  PlotFrequencies(11)
