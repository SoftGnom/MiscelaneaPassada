___authors__ = '1600861'
__group__ = 'DL.17'

import numpy as np
import math
import operator
from scipy.spatial.distance import cdist
#from statistics import mode


class KNN:
    def __init__(self, train_data, labels):
        self._init_train(train_data)
        self.labels = np.array(labels)


    def _init_train(self, train_data):
        """ 
        initializes the train data
        :param train_data: PxMxNx3 matrix corresponding to P color images
        :return: assigns the train set to the matrix self.train_data shaped as PxD (P points in a D dimensional space)
        ----------------------
        inicialitza les dades del tren
         :param train_data: matriu PxMxNx3 corresponent a P imatges en color
         :return: assigna el conjunt de trens a la matriu self.train_data en forma de PxD (punts P en un espai dimensional D)
        """
        
        P, M, N = train_data.shape
        self.train_data = np.reshape(np.asarray(train_data, dtype=float) ,(P, M * N))
        
            

    def get_k_neighbours(self, test_data, k):
        """
        given a test_data matrix calculates de k nearest neighbours at each point (row) of test_data on self.neighbors
        :param test_data: array that has to be shaped to a NxD matrix (N points in a D dimensional space)
        :param k: the number of neighbors to look at
        :return: the matrix self.neighbors is created (NxK)
                 the ij-th entry is the j-th nearest train point to the i-th test point
                 ------------------------------
        donada una matriu de dades_test, calcula els k veïns més propers a cada punt (fila) de dades_test a self.neighbors
         :param test_data: matriu que s'ha de donar forma a una matriu NxD (N punts en un espai dimensional D)
         :param k: el nombre de veïns a mirar
         :return: es crea la matriu self.neighbors (NxK)
                  l'entrada ij és el punt j-è del tren més proper al punt i-è de prova
        """

        P, M, N = test_data.shape
        testData = np.reshape(np.asarray(test_data, dtype=float) ,(P, M * N))
        self.neighbors = np.zeros((testData.shape[0],k), dtype='<U10')
        indexNeighbors = np.zeros((testData.shape[0],k), dtype=np.int64)
        matriu = np.array(cdist(testData, self.train_data, metric='euclidean'))
        
        for i,v in enumerate(matriu):#trobar els k mes iguals
            for j in range(k):#asignar valors no valids
                indexNeighbors[i][j] = -1#comprobar mida,  intenta acedir a una pocicio masa gran -> arranys de difarents mides
            
            for j in range(len(v)):
                aux=j
                h=0
                while h<k and aux != -1:
                    if indexNeighbors[i][h] == -1:#asignar valors valids
                        indexNeighbors[i][h] = aux
                        aux = -1
                    elif v[indexNeighbors[i][h]] > v[aux]:#actualitzar valors
                        aux1 = indexNeighbors[i][h]
                        indexNeighbors[i][h] = aux
                        aux = aux1
                    h+=1
                
        for i in range(testData.shape[0]):#traduir index per el nom
            for j in range(k):
                self.neighbors[i][j]=self.labels[indexNeighbors[i][j]]

        

    def get_class(self):
        """
        Get the class by maximum voting
        :return: 2 numpy array of Nx1 elements.
                1st array For each of the rows in self.neighbors gets the most voted value
                            (i.e. the class at which that row belongs)
                2nd array For each of the rows in self.neighbors gets the % of votes for the winning class
        """

        sortida = np.empty(self.neighbors.shape[0], dtype='<U12')
        for i in range(self.neighbors.shape[0]):
            freq = {}
            for v in self.neighbors[i]:
                freq[v] = freq.get(v, 0) + 1
            sortida[i] = max(freq, key=freq.get)
    
        return sortida   
        #return np.array([mode(self.neighbors[i])  for i in range(self.neighbors.shape[0])])

    def predict(self, test_data, k):
        """
        predicts the class at which each element in test_data belongs to
        :param test_data: array that has to be shaped to a NxD matrix (N points in a D dimensional space)
        :param k: the number of neighbors to look at
        :return: the output form get_class (2 Nx1 vector, 1st the class 2nd the  % of votes it got
        """

        self.get_k_neighbours(test_data, k)
        return self.get_class()
