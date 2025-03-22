__authors__ = ['1600861']
__group__ = 'DL.17'

import numpy as np
import utils


'''print("c1 = [[i1 for i1 in range(32) ] for i in range(13)]\nc1[6][30:31] = []")
for ia,a in enumerate(c):
    for ib,b in enumerate(a):
        aux = type(c[ia][ib])
        aux2 = [["--"]]
        aux1 = type(aux2[0][0])
        if(aux==aux1):
            print("c1[",ia,"][",ib,"]=\"", b ,"\"")#, "|" , aux)
            
c1 = [[i1 for i1 in range(32) ] for i in range(13)]
c1[6][30:31] = []
c1[ 5 ][ 31 ]=" Ultim_dia_Clases_AC "
c1[ 6 ][ 2 ]=" Ultim_dia_IA "
c1[ 6 ][ 13 ]=" Parcial_2_IA "
c1[ 6 ][ 14 ]=" Parical_2_OGE "
c1[ 6 ][ 15 ]=" Parical_2_X "
c1[ 6 ][ 19 ]=" Parcial_2_AC "
c1[ 6 ][ 23 ]=" Parcial_2_ES "
c1[ 6 ][ 27 ]=" Parcial_Recuperacio_IA "
c1[ 6 ][ 28 ]=" Parcial_Recuperacio_OGE "
c1[ 6 ][ 29 ]=" Parcial_Recuperacio_X "
c1[ 7 ][ 3 ]=" Parcial_Recu._AC "
c1[ 7 ][ 7 ]=" Parcial_Recu._ES "''''

class KMeans:

    def __init__(self, X, K=1, options=None):
        """
         Constructor of KMeans class
             Args:
                 K (int): Number of cluster
                 options (dict): dictionary with options
            """
        self.num_iter = 0
        self.K = K
        self._init_X(X)
        self._init_options(options)  # DICT options

    #############################################################
    ##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
    #############################################################
        self.labels = np.empty(self.X.shape[0], dtype=np.int64)
        self._init_centroids()

    def _init_X(self, X):
        """Initialization of all pixels, sets X as an array of data in vector form (PxD)
            Args:
                X (list or np.array): list(matrix) of all pixel values
                    if matrix has more than 2 dimensions, the dimensionality of the sample space is the length of
                    the last dimension
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #self.X = np.random.rand(100, 5)
        #######################################################
        #print(X.ndim == 3)
        #print(X.shape[2] == 3)
        """
        if(X.ndim == 3 and X.shape[2] == 3):
            #self.X = np.reshape(  ((np.array(X)).astype(float)),(-1,3)  )
            if(type(X) != "numpy.ndarray"):
                self.X = np.reshape(  (np.array(X, dtype=np.float)),(-1,3)  )
            else:
                self.X = np.reshape(  (X.astype(float)),(-1,3)  )
            
        else:
            if (type(X) != "numpy.ndarray") :
                self.X = np.array(X, dtype=np.float)
            else:
                self.X = X.astype(float)  
        """  
        """
        if(type(X) != "numpy.ndarray"):
            if(X.ndim == 3 and X.shape[2] == 3):
                self.X = np.reshape(  (np.array(X, dtype=np.float)),(-1,3)  )
            else:
                self.X = np.array(X, dtype=np.float)
        else:
            if(X.ndim != 3 and X.shape[2] == 3):
                self.X = np.reshape(  (X.astype(float)),(-1,3)  )
            else:
                self.X = X.astype(float)
        """
        if(type(X) == "numpy.ndarray"):
            self.X = np.reshape(  (X.astype(float)),(-1,3)  )
        else:
            self.X = np.reshape(  (np.array(X, dtype=np.float)),(-1,3)  )
            
    
    def _init_options(self, options=None):
        """
        Initialization of options in case some fields are left undefined
        Args:
            options (dict): dictionary with options
        -----------------------------------------------------------
        Inicialización de opciones en caso de que algunos campos queden sin definir
         Argumentos:
             opciones (dict): diccionario con opciones
        """
        if options is None:
            options = {}
        if 'km_init' not in options:
            options['km_init'] = 'first'
        if 'verbose' not in options:
            options['verbose'] = False
        if 'tolerance' not in options:
            options['tolerance'] = 0
        if 'max_iter' not in options:
            options['max_iter'] = np.inf
        if 'fitting' not in options:
            options['fitting'] = 'WCD'  # within class distance.

        # If your methods need any other parameter you can add it to the options dictionary
        self.options = options

        #############################################################
        ##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
        #############################################################


    def _init_centroids(self):
        """
        Initialization of centroids
        """
    
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        """if self.options['km_init'].lower() == 'first':
            self.centroids = np.random.rand(self.K, self.X.shape[1])
            self.old_centroids = np.random.rand(self.K, self.X.shape[1])
        else:
            self.centroids = np.random.rand(self.K, self.X.shape[1])
            self.old_centroids = np.random.rand(self.K, self.X.shape[1])"""
        #######################################################
        #print("1")
        
        self.centroids = np.zeros( (self.K,self.X.shape[1]) )
        self.old_centroids = np.zeros( (self.K,self.X.shape[1]) )
        
        if(self.options['km_init'].lower() == 'first'):
            #self.centroids = np.reshape(self.X[:self.K],(self.K,self.X.shape[1]))
            #self.old_centroids = np.zeros( (self.K,self.X.shape[1]) )
            #agafar el principi de self.X i posaru en self.centroids i self.old_centroids  *no iguals
            
            aux = np.empty((self.K,self.X.shape[1]),dtype=np.float)
            i = 0
            j = 0
            while(j < self.K):
                b = 1
                k = 0
                #print(i,":",self.X[i][0]," and ",self.X[i][1]," and ",self.X[i][2])
                while (k < j and b == 1):
                    if (self.X[i][0] == aux[k][0] and self.X[i][1] == aux[k][1] and self.X[i][2] == aux[k][2]):
                        b=0
                        
                        
                    k+=1
                    
                if (b == 1):
                    #print(i,":",self.X[i][0]," and ",self.X[i][1]," and ",self.X[i][2],"/j:",j)
                    aux[j][0] = self.X[i][0]
                    aux[j][1] = self.X[i][1]
                    aux[j][2] = self.X[i][2]
                    #print(i,":",aux[j][0]," and ",aux[j][1]," and ",aux[j][2],"/j:",j)
                    j+=1
                i+=1
            #print(aux)          
            self.centroids = np.copy(aux)
            #self.old_centroids = np.copy(aux)
            
        elif(self.options['km_init'].lower() == 'random'):
            self.centroids = np.random.rand(self.K, self.X.shape[1])
            #self.old_centroids = np.random.rand(self.K, self.X.shape[1])
        
        #elif(self.options['km_init'].lower() == 'otro')
            #...
        #print("8")
    
    def get_labels(self):
        """        Calculates the closest centroid of all points in X
        and assigns each point to the closest centroid
        -----------------------------------------------------
        Calcula el centroide más cercano de todos los puntos en X
         y asigna cada punto al centroide más cercano
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODEç
        #self.labels = np.random.randint(self.K, size=self.X.shape[0])
        #######################################################
        d = distance(self.X, self.centroids)
        #("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-")
        #print(len(d[0]))
        for i,v in enumerate(d):
            self.labels[i] = v.argmin()
            #print(self.labels[i],":",v[0],v[1],v[2],v[3])
            

    def get_centroids(self):
        """
        Calculates coordinates of centroids based on the coordinates of all the points assigned to the centroid
        ------------------------------------------------------------------------------------
        Calcular les coordenades dels centroides basant-se sobre les coordenades de tots els punts assignats al centroide
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        """aux = self.old_centroids
        self.old_centroids = self.centroids    //no funciona es culpa de que son posicions de mamoria de una clase i no es pot intercambia???
        self.centroids = aux"""
        
        self.old_centroids = np.copy(self.centroids)
        
        suma = np.zeros((self.K,(self.X.shape[1]+1)),dtype=np.float)
        
        for vx,vl in zip(self.X,self.labels):
            suma[vl][0] += vx[0]
            suma[vl][1] += vx[1]
            suma[vl][2] += vx[2]
            suma[vl][3] += 1 
            
        for i,v in enumerate(suma):
            self.centroids[i][0] = (v[0])/(v[3])
            self.centroids[i][1] = (v[1])/(v[3])
            self.centroids[i][2] = (v[2])/(v[3])
         

    def converges(self):
        """
        Checks if there is a difference between current and old centroids
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #return True
        #######################################################
        df=0
        for c,oc in zip(self.centroids,self.old_centroids):                 #no fa falta arrivar al final
             if(c[0] == oc[0] and c[1] == oc[1] and c[2] == oc[2]) == False:
                 df+=1
        
        return ((df/self.centroids.size) < 0.005)    #??
        #return (df==0)"""
        #return (self.centroids==self.old_centroids).all()
    


    def fit(self):
        """
        Runs K-Means algorithm until it converges or until the number
        of iterations is smaller than the maximum number of iterations.
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        """
        1. Per a cada punt de la imatge, troba quin és el centroide més proper.(get_labels)
        2. Calcula nous centroides utilitzant la funció (get_centroids)
        3. Augmenta en 1 el nombre d’iteracions
        4. Comprova si convergeix, en cas de no fer-ho torna al primer pas.(converges)
        """
        if self.options['max_iter']>0 :
            i=1
            self._init_centroids()
            self.get_labels()
        while( (self.converges() == False) and (i<self.options['max_iter']) ):
            i+=1
            self.get_centroids()
            self.get_labels()
            #print("\t->",i)


    def withinClassDistance(self):
        """
         returns the within class distance of the current clustering
        """
    
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        aux = distance(self.X, self.centroids)
        self.WCD = np.sum(aux**2) / aux.shape[0]#self.N
    
    



    def find_bestK(self, max_K):
        """
         sets the best k anlysing the results up to 'max_K' clusters
        """""""
        self.withinClassDistance()
        trobat = False
        decK = 0
        for i in range(2,max_K):
            if((100 - decK) < 0.2):
                self.k = i
                trobat = True
            else:
                decK = self.withinClassDistance() * 100 / self.withinClassDistance(i-1)
        if(trobat == True):
            return i
        else:
            return max_K """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        
        print("-------------------------------------")
        self.K = 1
        self.fit()
        self.withinClassDistance()
        decK = 121
        while self.K < max_K and decK >= 1.16:
            old_WCD = self.WCD
            self.K+=1
            self.fit()
            self.withinClassDistance()
            decK = self.WCD / old_WCD
            print(self.K,decK,decK > 1.20)
        self.K-=1
        return self.K

def distance(X, C):
    """
    Calculates the distance between each pixel and each centroid
    Args:
        X (numpy array): PxD 1st set of data points (usually data points)
        C (numpy array): KxD 2nd set of data points (usually cluster centroids points)

    Returns:
        dist: PxK numpy array position ij is the distance between the
        i-th point of the first set an the j-th point of the second set
    ------------------------------------------------
    Calcula la distancia entre cada píxel y cada centroide
     Argumentos:
         X (matriz numpy): PxD 1er conjunto de puntos de datos (generalmente puntos de datos)
         C (matriz numpy): KxD segundo conjunto de puntos de datos (generalmente puntos de centroides de clúster)

     Devoluciones:
         dist: PxK numpy array position ij es la distancia entre el
         i-ésimo punto del primer conjunto y j-ésimo punto del segundo conjunto
    """

    #########################################################
    ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
    ##  AND CHANGE FOR YOUR OWN CODE
    #return np.random.rand(X.shape[0], C.shape[0])
    #########################################################
    dist = np.zeros((X.shape[0],C.shape[0]), dtype=np.float)
    
    for i,ix in enumerate(X):
        for j,jc in enumerate(C):
            #if(ix.size == jc.size):
            s = 0
            for x,z in zip(ix,jc):
                s += ((x-z)**2)
            dist[i][j] = (s**(1/2))
    return dist
            
    
    


def get_colors(centroids):
    """
    for each row of the numpy matrix 'centroids' returns the color label following the 11 basic colors as a LIST
    Args:
        centroids (numpy array): KxD 1st set of data points (usually centroid points)

    Returns:
        labels: list of K labels corresponding to one of the 11 basic colors
    ----------------------------------------------------------------
    per a cada fila de la matriu numpy 'centroides' retorna l'etiqueta de color seguint els 11 colors bàsics com a LLISTA
     Arguments:
         centroides (matriu numpy): KxD 1r conjunt de punts de dades (generalment punts de centroides)

     Devolucions:
         etiquetes: llista d'etiquetes K corresponents a un dels 11 colors bàsics
    """

    #########################################################
    ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
    ##  AND CHANGE FOR YOUR OWN CODE
    #########################################################
    return list(utils.colors)
