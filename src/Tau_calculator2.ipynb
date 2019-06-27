import numpy as np
import os
import pyprind
import matplotlib.pyplot as plt
Dir = r"C:\Users\igna\Desktop\Igna\Facultad\Fisica computacional\TP3-Computacional-Dinamica Molecular\MD_LJ\src"
os.chdir(Dir)

A = np.loadtxt("EPot_ECin_Lambda.txt")
B = np.zeros([len(A[:,0]),2])
B[:,0] = A[:,0]
B[:,1] = A[:,1] + A[:,2]

def corrnp(X,i):
    """
    llama a la funcion corrcoef de numpy, pero
    la hice para que le des la notacion simplificada
    de Correlacion (la casera). Tiene la ventana
    de que tarda 10 veces menos que la casera."""
    if i == 0:
        return np.corrcoef(X,X)[1,0]
    else:
        return np.corrcoef(X[:-i],X[i:])[1,0]

def Correlador(A):
    columna_a_correlar = int(input("\nQue columna vas a ver la correlacion?\n"))
    promedios = int(input("\nCuantos promedios queres hacer?\n"))
    len_data = len(A[:,0])  # longitud de la tira de datos, original
    # redefino A sin esos valores
    A = A[int(len_data/10):]
    len_data = len(A[:,0]) # redefino len_data sin el 10% inicial
    # En estas condiciones, a los datos restantes quiero calcularles la corre.
    # para eso voy a querer armar una matriz en la que cada fila sea un cacho
    # del vector original, para luego promediar las correlaciones.
    # 
    # quiero promediar 20 veces, asi que divido el vector restante en 20
    # voy a armar una matriz de NxM (N columnas, M filas)
    
    M = promedios #esto podría ser numero de promedios
    N = int(len_data/M)
    matriz = np.zeros([M,N])
    for i in range(M):
        for j in range(N):
            matriz[i,j] = A[i*M + j, columna_a_correlar]
    c_k_matrix = np.zeros([M,int(N/2)])
    progrbar = pyprind.ProgBar(M, monitor = True)
    for k in range(M):
        c_k = []
        for i in range(int(N/2)):
            c_k.append(corrnp(matriz[k, :],i))
        c_k_matrix[k] = c_k
        progrbar.update()
    
    return np.mean(c_k_matrix, axis = 0)