__authors__ = ['XXXXXXX']
__group__ = 'DL.17'

import numpy as np
import utils


'''
print("c1 = [[i1 for i1 in range(32) ] for i in range(13)]\nc1[6][30:31] = []")
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
c1[ 7 ][ 7 ]=" Parcial_Recu._ES "
'''

'''
a=[[' 2.         27.71084291  0.29388499'],
 [' 0.         23.63397053  0.64404392'],
 [' 4.         13.77419918  1.33989978'],
 [' 5.         10.76045841  2.44962049'],
 [' 6.          8.46520085  2.59100008'],
 [' 7.          6.56766158  4.28544068'],
 [' 8.          7.54772266  5.82653761'],
 [' 9.          6.9268035   7.28366756'],
 ['10.          6.40453555  7.22856402'],
 ['11.          6.3772221   6.9662106 '],
 ['12.          6.27948123  7.53096247'],
 ['13.          6.2266839  14.64601946'],
 ['14.          6.17739749 15.86005545'],
 ['15.          6.43033438 16.87193561'],
 ['16.          5.84725651 19.5814817 '],
 ['17.          5.8075863  20.47081566'],
 ['18.          5.83701543 20.10909462'],
 ['19.          5.60419535 18.09270048'],
 ['20.          5.81961716 20.33980727']]
nueva_UCL = [c[0].replace('.', ',') for c in a]
nueva_UCL
'''

class KMeans:

    def __init__(self, X, K=1, options=None):
        
        print(options)
        print("i[", sep='',end='')
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
        self.Error = 0 #tot ok
        self.labels = np.empty(self.X.shape[0], dtype=np.int64)
        self._init_centroids()

        #print("i]", sep='',end='')
    def _init_X(self, X):
        #print("iX[", sep='',end='')
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
        
        if(type(X) == "numpy.ndarray"):
            self.X = np.reshape(  (X.astype(float)),(-1,3)  )
        else:
            self.X = np.reshape(  (np.array(X, dtype=np.float64)),(-1,3)  )
            
        #print("iX]", sep='',end='')
    def _init_options(self, options=None):
        #print("iO[", sep='',end='')
        """
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
            options['tolerance'] = 20#0
        if 'max_iter' not in options:
            options['max_iter'] = np.inf
        if 'fitting' not in options:
            options['fitting'] = 'WCD'  # within class distance.

        # If your methods need any other parameter you can add it to the options dictionary
        self.options = options

        #############################################################
        ##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
        #############################################################
        #print("iO]", sep='',end='')


    def _init_centroids(self):
        #print("iC[", sep='',end='')
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
            #print(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;")
            #self.centroids = np.reshape(self.X[:self.K],(self.K,self.X.shape[1]))
            #self.old_centroids = np.zeros( (self.K,self.X.shape[1]) )
            #agafar el principi de self.X i posaru en self.centroids i self.old_centroids  *no iguals
            
            aux = np.empty((self.K,self.X.shape[1]),dtype=np.float64)
            #print(aux.shape,self.X.shape,self.K,self.X.shape[1])
            i = 0
            j = 0
            midaX =len(self.X)
            bol = True
            while(j < self.K and bol):
                b = 1
                k = 0
                #print("a1  [",i,":",self.X[i][0]," and ",self.X[i][1]," and ",self.X[i][2])
                while (k < j and b == 1):
                    #print("a2  [",i,":",aux[k][0]," and ",aux[k][1]," and ",aux[k][2])
                    if (self.X[i][0] == aux[k][0] and self.X[i][1] == aux[k][1] and self.X[i][2] == aux[k][2]):
                        b=0
                        
                        
                    k+=1
                    
                if (b == 1):
                    #print("b1   ",i,":",self.X[i][0]," and ",self.X[i][1]," and ",self.X[i][2],"/j:",j)
                    aux[j][0] = self.X[i][0]
                    aux[j][1] = self.X[i][1]
                    aux[j][2] = self.X[i][2]
                    #print("b2   ",i,":",aux[j][0]," and ",aux[j][1]," and ",aux[j][2],"/j:",j)
                    j+=1
                i+=1
                if i >= midaX:
                    bol = False
                    self.Error = 1 # error no hi han suficiens pixels
            #print(aux)          
            self.centroids = np.copy(aux)
            #self.old_centroids = np.copy(aux)
            
        elif(self.options['km_init'].lower() == 'random'):
            #print(":::::::::::::::::::::::::::::::::::::::::::::::::::")
            #self.centroids = np.random.rand(self.K, self.X.shape[1])
            """for i in range(len(self.centroids)):
                self.centroids[i]=self.X[int((np.random.rand()*10000)%len(self.X))]
                """
            #print("-------------------------------------------------------------------")
            mida = len(self.centroids)
            i = 0
            while i < mida:
                auux = int((np.random.rand()*10000)%len(self.X))
                aux = self.X[auux]
                #print(len(self.X),auux,aux,end='')
                
                j=0
                bol=1
                while (j < i and bol == 1):
                    if (self.centroids[j][0] == aux[0] and self.centroids[j][1] == aux[1] and self.centroids[j][2] == aux[2]):
                        bol=0
                    j += 1
                if bol == 1:
                    self.centroids[i] = aux
                    i += 1
                    #print("(Si)")
                #else:
                    #print("(No)")
        elif(self.options['km_init'].lower() == 'manual'):
            #print(",.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,..,,.,.,.,.,.,.,..,")
            self.centroids = (self.options['centroids'])[:self.K]
        
        #print(self.centroids)
        #print("iC[", sep='',end='')
    
    def get_labels(self):
        #print("iL[", sep='',end='')
        """
        Calcula el centroide más cercano de todos los puntos en X
         y asigna cada punto al centroide más cercano
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODEç
        #self.labels = np.random.randint(self.K, size=self.X.shape[0])
        #######################################################
        d = distance(self.X, self.centroids)
        for i,v in enumerate(d):
            self.labels[i] = v.argmin()
        
        #print("iL]", sep='',end='')

    def get_centroids(self):
        #print("gC[", sep='',end='')
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
        
        suma = np.zeros((self.K,(self.X.shape[1]+1)),dtype=np.float64)
        
        for vx,vl in zip(self.X,self.labels):
            suma[vl][0] += vx[0]
            suma[vl][1] += vx[1]
            suma[vl][2] += vx[2]
            suma[vl][3] += 1 
            
        for i,v in enumerate(suma):
            if v[3] != 0:
                self.centroids[i][0] = (v[0])/(v[3])
                self.centroids[i][1] = (v[1])/(v[3])
                self.centroids[i][2] = (v[2])/(v[3])
        #print("gC]", sep='',end='')

    def converges(self):
        #print("C[", sep='',end='')
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
             #if(c[0] == oc[0] and c[1] == oc[1] and c[2] == oc[2]) == False:
            if(abs(c[0] - oc[0]) < 0.01 and abs(c[1] - oc[1]) < 0.01 and abs(c[2] - oc[2]) < 0.01) == False:
                 df+=1
        #print("C]", sep='',end='')
        #return ((df/self.centroids.size) < 0.005)    #??
        return (df==0)#"""
        #return (self.centroids==self.old_centroids).all()


    def fit(self):
        #print("\n>\tf[", sep='',end='')
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
        #print("f]", sep='',end='\n')
            

    def withinClassDistance(self):
        print("W[", sep='',end='')
        """
         returns the within class distance of the current clustering
        """
        aux = distance(self.X, self.centroids)
        aux =  np.min(aux,axis=1)
        self.WCD = np.sum(np.power(aux,2)) / self.X.shape[0] 
        

    def interClass(self):
        print("ieC[", sep='',end='')
        """
         returns the within class distance of the current clustering
        """
    
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        """
        aux = distance(self.centroids, self.centroids)
        print("---/********\---\n",">  d:",aux,"  <","\n---\********/---")
        
        for i in range(len(aux)):
            aux[i][i]=np.inf
        aux =  np.min(aux,axis=1)
        self.IeC = np.sum(np.power(aux,2)) / self.X.shape[0]
        """
        """
        i=0
        s=0
        recompte=0
        mida= len(self.centroids)
        while i < mida:
            j=i+1
            while j < mida:
                s+=aux[i][j]
                recompte+=1
                j+=1
            i+=1
        self.IeC = s/recompte
        
        #print("--------------------------------------")
        frequenca={}
        for i in range(self.centroids.shape[0]):
            frequenca[i]=0
        for v in self.labels:
            #print(v, sep='',end='')
            frequenca[v]+=1
        #print("frequenca:",frequenca)
        #print("Labels(",len(self.labels),"):",self.labels)
        i=0
        s=0
        mida= len(self.centroids)
        print("-----------------IeC:")
        while i < mida:
            j=i+1
            while j < mida:
                centroide1=i
                centroide2=j
                print("Centroide:",centroide1,centroide2)
                #print("f n |",frequenca[centroide1],centroide1,"|",frequenca[centroide2],centroide2)
                aux=distance(self.X, self.X,1,self.labels,frequenca[centroide1],centroide1,self.labels,frequenca[centroide2],centroide2)#distance(X, C,Vpro=1,Xaray=self.labels,Xlen=frequenca[centroide1],Xbol=centroide1,Caray=self.labels,Clen=frequenca[centroide2],Cbol=centroide2)
                print(":::::::::::::::::::::\n",aux.shape)
                print("\n")
                print("Distancia:",aux,"D:", aux.shape[0], aux.shape[1])
                i1=0
                s1=0
                recompte1=0
                while i1 < aux.shape[0]:
                    j1=i1+1
                    while j1 < aux.shape[1]:
                        s1+=aux[i1][j1]
                        print(s1,"|",i1,j1,":",aux[i1][j1])
                        #print(i1,j1," ", sep='',end='')
                        recompte1+=1
                        j1+=1
                    i1+=1
                if recompte1 != 0:
                    s+= s1/recompte1
                #print("Suma:",s,'+=', s1,'/',recompte1)
                
                j+=1
            i+=1
        self.IeC = s
        print(":-----------------")
        #print("++++++++++++++++++++++++++++++++++++++++++++++++++\n",s,"\n+++++++++++++++++++++++++++++++++++++")
        """
        frequenca={}
        for i in range(self.centroids.shape[0]):
            frequenca[i]=0
        for v in self.labels:
            #print(v, sep='',end='')
            frequenca[v]+=1
        #print("frequenca:",frequenca)
        #print("Labels(",len(self.labels),"):",self.labels)
        i=0
        s=0
        mida= len(self.centroids)
        #print("-----------------IeC:")
        while i < mida:
            j=i+1
            while j < mida:
                centroide1=i
                centroide2=j
                #print("Centroide:",centroide1,centroide2)
                #print("f n |",frequenca[centroide1],centroide1,"|",frequenca[centroide2],centroide2)
                aux=distance(self.X, self.X,1,self.labels,frequenca[centroide1],centroide1,self.labels,frequenca[centroide2],centroide2)#distance(X, C,Vpro=1,Xaray=self.labels,Xlen=frequenca[centroide1],Xbol=centroide1,Caray=self.labels,Clen=frequenca[centroide2],Cbol=centroide2)
                #print(":::::::::::::::::::::\n",aux.shape)
                #print("\n")
                #print("Distancia:",aux,"D:", aux.shape[0], aux.shape[1])
                
                mul=1
                for v in aux.shape:#numero de posicions en aux
                    mul*=v
                
                s+=np.sum(aux)/mul
                
                #print("Suma:",s,'+=', s1,'/',recompte1)
                
                j+=1
            i+=1
        self.IeC = s
        #print(":-----------------")
        #print("++++++++++++++++++++++++++++++++++++++++++++++++++\n",s,"\n+++++++++++++++++++++++++++++++++++++")
        

    def intraClass(self):
        #print("iaC[", sep='',end='')
        """
         returns the within class distance of the current clustering
        """
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        """#Va mes len
        frequenca={}
        for i in range(self.centroids.shape[0]):
            frequenca[i]=0
        for v in self.labels:
            frequenca[v]+=1
        i=0
        s=0
        mida= len(self.centroids)
        while i < mida:
            centroide1=i
            
            aux=distance(self.X, self.X,2,self.labels,frequenca[centroide1],centroide1,self.labels,frequenca[centroide1],centroide1)#distance(X, C,Vpro=1,Xaray=self.labels,Xlen=frequenca[centroide1],Xbol=centroide1,Caray=self.labels,Clen=frequenca[centroide2],Cbol=centroide2)
            recompte1=(( ( (frequenca[centroide1]*frequenca[centroide1]) + frequenca[centroide1]) /2 )-frequenca[centroide1])
            
            if recompte1 != 0:
                s+= np.sum(aux)/recompte1
                
            i+=1
        self.IaC = s
        """
        frequenca={}
        #print("|----------------------------------------------")
        for i in range(self.centroids.shape[0]):
            frequenca[i]=0
        for v in self.labels:
            #print(v, sep='',end='')
            frequenca[v]+=1
        #print("frequenca:",frequenca)
        #print("Labels(",len(self.labels),"):",self.labels)
        i=0
        s=0
        mida= len(self.centroids)
        #print("-----------------IaC:")
        while i < mida:
            centroide1=i
            #print("Centroide:",centroide1)
            aux=distance(self.X, self.X,2,self.labels,frequenca[centroide1],centroide1,self.labels,frequenca[centroide1],centroide1)#distance(X, C,Vpro=1,Xaray=self.labels,Xlen=frequenca[centroide1],Xbol=centroide1,Caray=self.labels,Clen=frequenca[centroide2],Cbol=centroide2)
            #print("\n",aux)
            #print("Distancia:(f[c]):",frequenca[centroide1],"(c):",centroide1,"|Tamany:",aux.shape)
            i1=0
            s1=0
            recompte1=0
            while i1 < aux.shape[0]:
                #print("D_Columna:",i1)
                j1=i1+1
                while j1 < aux.shape[1]:
                    #print("D_Fila:",j1,recompte1)
                    s1+=aux[i1][j1]
                    #print(s1,aux[i1][j1])
                    #print(i1,j1," ", sep='',end='')
                    recompte1+=1
                    j1+=1
                i1+=1
            if recompte1 != 0:
                s+= s1/recompte1
            #else:
                #print("!!!!!!!!!!!!!!!Recompte:",recompte1)
            #print("Suma:",s,'+=', s1,'/',recompte1)
                
            i+=1
        self.IaC = s
        #print(":-------------------------------------")
        #print("++++++++++++++++++++++++++++++++++++++++++++++++++\n",s,"\n+++++++++++++++++++++++++++++++++++++")
        
        
        

    def Fisher(self):
        #print("f[", sep='',end='')
        self.F = self.IaC / self.IeC
        

    def find_bestK(self, max_K):
        #print("----\n-->\tfb[", sep='',end='')
        #######################################################
        ##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
        ##  AND CHANGE FOR YOUR OWN CODE
        #######################################################
        
        self.K = 2
        old = 1
        if self.options['fitting'] == 'WCD':
            tolerance = self.options['tolerance']#20
            #decK = 100 + self.options['tolerance'] + 1
        elif self.options['fitting'] == 'IaC':
            tolerance = self.options['tolerance']#20
            #decK = 100 + self.options['tolerance'] + 1
        elif self.options['fitting'] == 'IeC':
            tolerance = self.options['tolerance']#20
            #decK = 100 + self.options['tolerance'] + 1
        elif self.options['fitting'] == 'Fisher':
            tolerance = self.options['tolerance']#20
            #decK = 100 + self.options['tolerance'] + 1
        bol=True
        decK = 0
        while ((self.K <= max_K and (( abs(decK) > tolerance ) or bol ) ) or self.K <= 3) and self.Error == 0 :
            if ( abs(decK) > tolerance ) and self.K > 3:
                bol=False
            centroids = self.centroids #copia per si es la ultima
            labels= np.ones(self.labels.shape, dtype=np.int64)
            #labels = self.labels #copia per si es la ultima, no funciona
            for i1,v1 in enumerate(self.labels):
                labels[i1] = v1
                
                
                
                
            ii=0
            for jj,vv in enumerate(self.labels):
                if vv > (self.labels[ii]):
                   ii=jj
            print(self.labels[ii])
            self.fit()
            ii=0
            for jj,vv in enumerate(self.labels):
                if vv > (self.labels[ii]):
                   ii=jj
            print("{",self.K,len(self.centroids),self.labels[ii],"}")
            
            
            
            if self.options['fitting'] == 'WCD':
                self.withinClassDistance()
                decK = 100 - (100*(self.WCD / old))
                old = self.WCD
            elif self.options['fitting'] == 'IaC':
                self.intraClass()
                decK = 100 - (100*(self.IaC / old))
                old = self.IaC
            elif self.options['fitting'] == 'IeC':
                self.interClass()
                decK = 100 - (100*(self.IeC / old))
                old = self.IeC
            elif self.options['fitting'] == 'Fisher':
                self.intraClass()
                self.interClass()
                self.Fisher()
                decK = 100 - (100*(self.F / old))
                old = self.F
            #print(self.K,old)
            self.K+=1
            #print("1-",self.K,"WCD:",self.WCD,"|WCD-1:",old_WCD,"-",decK,decK > 1.20, max_K)
        if self.options['fitting'] == 'WCD':
            self.WCD = old
        elif self.options['fitting'] == 'IaC':
            self.IaC = old
        elif self.options['fitting'] == 'IeC':
            self.IeC = old
        elif self.options['fitting'] == 'Fisher':
            self.F = old
        self.K = self.K-2
        self.centroids = centroids #copia la ultima per recuperar la informacio correcte
        self.labels = labels #copia la ultima per recuperar la informacio correcte
        ii=0
        for jj,vv in enumerate(self.labels):
            if vv > (self.labels[ii]):
               ii=jj
        print("{",self.K,len(self.centroids),self.labels[ii],"}")
        if self.Error != 0 :
            return -self.K
        else:
            return self.K
        
        #print("fb,",self.K,",]", sep='',end='\n')

        
        

def distance(X, C,Vpro=None,Xaray=None,Xlen=None,Xbol=None,Caray=None,Clen=None,Cbol=None):#bol-> 0 no tenir amb comte
    #print("d[", sep='',end='')
    """
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
    if Vpro == None:
        Vpro=0
    if Vpro==0:
        dist = np.zeros((X.shape[0],C.shape[0]), dtype=np.float64)
        for i,ix in enumerate(X):
            for j,jc in enumerate(C):
                #if(ix.size == jc.size):
                s = 0
                for x,z in zip(ix,jc):
                    s += ((x-z)**2)
                dist[i][j] = (s**(1/2))
    elif Vpro==1:#array bool per dir quines utilitzar
        #print("*****************************************************************")
        if Xlen is None:
            Xlen=X.shape[0]
            #print("Xlen:",Xlen)
        if Clen is None:
            Clen=C.shape[0]
            #print("Clen:",Clen)
        dist = np.zeros((Xlen,Clen), dtype=np.float64)
        if Xaray is None:
            Xaray=np.ones((X.shape[0]))
            #print("Xaray:",Xaray)
        if Caray is None:
            Caray=np.ones((C.shape[0]))
            #print("Caray:",Caray)
        if Xbol is None:
            Xbol=1
            #print("Xbol:",Xbol)
        if Cbol is None:
            Cbol=1
            #print("Cbol:",Cbol)
        ix=0
        ic=0
        idist=0
        jdist=0
        while ix < len(X) :
            #print(ix,ic,"|",idist,jdist)
            if Xaray[ix] == Xbol and Caray[ic] == Cbol:
                s = 0
                for x,z in zip(X[ix],C[ic]):
                    s += ((x-z)**2)
                dist[idist][jdist] = (s**(1/2))
                #print("c",Xaray[ix],Caray[ic],dist[idist][jdist])
                
                jdist+=1
                if jdist >= Clen:
                    #print("g")
                    idist+=1
                    jdist=0
                ic+=1
                if ic >= len(C):
                    #print("h")
                    ix+=1
                    ic=0
            else:
                if Xaray[ix] != Xbol:
                    #print("a")
                    ix+=1
                if Caray[ic] != Cbol:
                    #print("b")
                    ic+=1
                if ic >= len(C):
                    #print("h")
                    ix+=1
                    ic=0
            #print(ix,ic,"|",idist,jdist,"|",ix < len(X) , ic < len(C))
            
    elif Vpro==2:#+nomes calcular la meitat (el resultat es sumetric) (X == C)
        #print("*****************************************************************")
        #print(X)
        #print(Xaray)
        #print(Xbol)
        #print(C)
        #print(Caray)
        #print(Cbol)
        if Xlen is None:
            Xlen=X.shape[0]
            #print("Xlen:",Xlen)
        if Clen is None:
            Clen=C.shape[0]
            #print("Clen:",Clen)
        dist = np.zeros((Xlen,Clen), dtype=np.float64)
        if Xaray is None:
            Xaray=np.ones((X.shape[0]))
            #print("Xaray:",Xaray)
        if Caray is None:
            Caray=np.ones((C.shape[0]))
            #print("Caray:",Caray)
        if Xbol is None:
            Xbol=1
            #print("Xbol:",Xbol)
        if Cbol is None:
            Cbol=1
            #print("Cbol:",Cbol)
        ix=0
        ic=ix+1
        idist=0
        jdist=idist+1
        XlenReal = len(X)
        ClenReal = len(C)
        #print("::",XlenReal,ClenReal,Xlen,Clen,"::")
        while ix < XlenReal and ic < ClenReal and jdist < Clen and idist < Xlen :
            #print(ix,ic,"|",idist,jdist)
            if Xaray[ix] == Xbol and Caray[ic] == Cbol:
                s = 0
                for x,z in zip(X[ix],C[ic]):
                    #print("\t>",x,z,"|",((x-z)**2))
                    s += ((x-z)**2)
                #print("c",Xaray[ix],Caray[ic],dist[idist][jdist])
                dist[idist][jdist] = (s**(1/2))
                #print("c",Xaray[ix],Caray[ic],dist[idist][jdist])
                
                jdist+=1
                if jdist >= Clen:
                    #print("g")
                    idist+=1
                    jdist=idist+1
                ic+=1
                if ic >= ClenReal:
                    #print("h")
                    ix+=1
                    ic=ix+1
            else:
                if Xaray[ix] != Xbol:
                    #print("a")
                    ix+=1
                if Caray[ic] != Cbol:
                    #print("b")
                    ic+=1
                if ix == ic:
                    #print("a+")
                    ic+=1
                if ic >= ClenReal:
                    #print("h")
                    ix+=1
                    ic=ix+1
        #print("-----------------------------")

    return dist
    #print("d]", sep='',end='')
    ##????????????????????????????????????????np.power(s,(1/2)) vs (s**(1/2))????
            
    
    

def get_colors(centroids):
    #print("gC[", sep='',end='')
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
    aux0 = np.argmax(utils.get_color_prob(centroids),axis=1)
    aux1 = [utils.colors[v] for v in aux0]
    #print("gC]", sep='',end='')
    return aux1
    


