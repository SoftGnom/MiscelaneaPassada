__autimagenesors__ = 'TO_BE_FILLED'
__group__ = 'TO_BE_FILLED'

from utils_data import read_dataset, read_extended_dataset, crop_images, visualize_retrieval, visualize_k_means


from Kmeans import *
from KNN import *
import time
import copy

def Visualitzar(imagenes,nFotos=28,pregunta=0):
    if pregunta != 0: 
        v=input("Visualtizar(Si->S)?\t")
    else:
        v='S'
    
    l=len(imagenes)
    #print("l:",l)
    if  l > 0 and (v=='S' or v=='s'):
        #print(l/nFotos," == ",int(l/nFotos))
        if l/nFotos == int(l/nFotos):
            l=int(l/nFotos)
            #print("l.2:",l)
        else:
            l=int(l/nFotos)+1
            #print("l.2:",l)
        for i in range(l):
            #print((i*nFotos),((i+1)*nFotos), len(imagenes))
            visualize_retrieval(imagenes[(i*nFotos):((i+1)*nFotos)], len(imagenes[(i*nFotos):((i+1)*nFotos)]))


def Retrieval_by_Xo(imagenes,etiquetes,busqueda):
    sortida=[]
    for vi,ve in zip(imagenes,etiquetes):
        bol=False
        l=len(busqueda)
        i=0
        while i < l and bol == False:
            if busqueda[i] in ve:
                bol=True
            i+=1
                
        if bol:
            sortida.append(vi)
        #else: -> sortidaNo.append(vi)
        
    return sortida

def Retrieval_by_Xi(imagenes,etiquetes,busqueda):
    sortida=[]
    for vi,ve in zip(imagenes,etiquetes):
        bol=True
        l=len(busqueda)
        i=0
        while i < l and bol == True:
            
            if (busqueda[i] in ve and bol==True)==False:
                bol=False
            i+=1
                
        if bol:
            sortida.append(vi)
        #else: -> sortidaNo.append(vi)
        
    return sortida

def Retrieval_by_XoX(imagenes,etiquetes1,etiquetes2,busqueda):
    sortida=[]
    for vi,ve1,ve2 in zip(imagenes,etiquetes1,etiquetes2):
        bol=False
        l=len(busqueda)
        i=0
        while i < l and bol == False:
            if (busqueda[i] in ve1 ) or ( busqueda[i] in ve2):
                bol=True
            i+=1
                
        if bol:
            sortida.append(vi)
        #else: -> sortidaNo.append(vi)
    return sortida

def Retrieval_by_XiX(imagenes,etiquetes1,etiquetes2,busqueda):
    sortida=[]
    for vi,ve1,ve2 in zip(imagenes,etiquetes1,etiquetes2):
        bol=True
        l=len(busqueda)
        i=0
        while i < l and bol == True:
            if ((busqueda[i] in ve1) or (busqueda[i] in ve2))==False:
                bol=False
            i+=1
        if bol==True:
            sortida.append(vi)
    return sortida
    
        
    
def CambiColor(test_imgs):#cambiar el color de RGB->grisos
    
    # Obtener las dimensiones de la matriz de imágenes de prueba
    l, l1, l2, l3 = test_imgs.shape
    
    # Crear una matriz vacía del mismo tamaño que las imágenes de prueba, pero con un solo canal
    testImgs = np.zeros((l, l1, l2))
    
    # Recorrer las imágenes y convertirlas a escala de grises
    for i in range(l):
        for i1 in range(l1):
            for i2 in range(l2):
                # Aplicar la fórmula de conversión a escala de grises
                testImgs[i, i1, i2] = 0.299 * test_imgs[i, i1, i2, 0] + 0.587 * test_imgs[i, i1, i2, 1] + 0.114 * test_imgs[i, i1, i2, 2]
    
    return testImgs

def Kmeans_Etiquetes(imagenes,max_K,extend=0,options=None):    
    etiquetes=[]
    for i,vi in enumerate(imagenes):
        km = KMeans(vi, 2,copy.deepcopy(options))
        km.find_bestK( max_K)
        if extend != 1:
            etiquetes.append( get_colors(km.centroids) )
        else:
            visualize_k_means(km, vi.shape)
    
    return etiquetes
    

def KNN_(train_imgs,train_class_labels,img,k):    
    
    knn = KNN(CambiColor(train_imgs), train_class_labels)
    S_Img = CambiColor(img)
    S_eti = knn.predict(S_Img, k)
    
    return S_eti


def Kmean_statistics(img,max_K,options=None):#V2
    e=[]#etiquetes
    t=[]
    t.append(time.time())
    km = KMeans(img, 2,options) 
    #km.K = 2
    old = 1
    k=0
    bol=True
    bol1=True
    decK=0
    if options['fitting'] == 'WCD':
        tolerance = options['tolerance']
        sortida=np.zeros((max_K-1,4))  #4 -> k,WCD,decK,temps
    elif options['fitting'] == 'IaC':
        tolerance = options['tolerance']
        sortida=np.zeros((max_K-1,4))  #4 -> k,IaC,decK,temps
    elif options['fitting'] == 'IeC':
        tolerance = options['tolerance']
        sortida=np.zeros((max_K-1,4)) #4 -> k,IeC,decK,temps
    elif options['fitting'] == 'Fisher':
        tolerance = options['tolerance']
        sortida=np.zeros((max_K-1,6)) #6 -> k,F,IeC,IaC,decK,temps
    
    while (km.K <= max_K ) or km.K <= 3:
        #print("Kfit:",km.K,"Kout:",k,"decK:",decK,"tolerance:",tolerance,"bol:",bol,"if:",( abs(decK) > tolerance ) )
        if (( abs(decK) > tolerance ) or bol ) and bol1:
            #print("a")
            k=km.K
            if ( abs(decK) > tolerance ) and km.K > 3:
                #print("b")
                bol = False
        else:
            bol1=False
        
        centroids = km.centroids #copia per si es la ultima
        km.fit()
        print("K:",km.K)
        e.append( get_colors(km.centroids) )
        if options['fitting'] == 'WCD':
            km.withinClassDistance()
            t.append(time.time())
            sortida[km.K-2][0] = km.K
            sortida[km.K-2][1] = km.WCD
            sortida[km.K-2][2] = decK
            sortida[km.K-2][3] = t[-1]-t[-2]
            decK = 100 - (100*(km.WCD / old))
            old = km.WCD
        elif options['fitting'] == 'IaC':
            km.intraClass()
            t.append(time.time())
            sortida[km.K-2][0] = km.K
            sortida[km.K-2][1] = km.IaC
            sortida[km.K-2][2] = decK
            sortida[km.K-2][3] = t[-1]-t[-2]
            decK = 100 - (100*(km.IaC / old))
            old = km.IaC
        elif options['fitting'] == 'IeC':
            km.interClass()
            t.append(time.time())
            sortida[km.K-2][0] = km.K
            sortida[km.K-2][1] = km.IeC
            sortida[km.K-2][2] = decK
            sortida[km.K-2][3] = t[-1]-t[-2]
            decK = 100 - (100*(km.IeC / old))
            old = km.IeC
        elif options['fitting'] == 'Fisher':
            km.intraClass()
            km.interClass()
            km.Fisher()
            t.append(time.time())
            sortida[km.K-2][0] = km.K
            sortida[km.K-2][1] = km.F
            sortida[km.K-2][2] = km.IeC
            sortida[km.K-2][3] = km.IaC
            sortida[km.K-2][4] = decK
            sortida[km.K-2][5] = t[-1]-t[-2]
            decK = 100 - (100*(km.F / old))
            old = km.F
        km.K+=1
        #print("1-",self.K,"WCD:",self.WCD,"|WCD-1:",old_WCD,"-",decK,decK > 1.20, max_K)
    if options['fitting'] == 'WCD':
        km.WCD = old
    elif options['fitting'] == 'IaC':
        km.IaC = old
    elif options['fitting'] == 'IeC':
        km.IeC = old
    elif options['fitting'] == 'Fisher':
        km.F = old
    km.K = (km.K-2)-1#formato(-2) cortesia(-1)
    km.centroids = centroids #copia la ultima per recuperar la informacio correcte
    sortida[k-2-1][0]=0#formato(-2) cortesia(-1)
    return [sortida,e]



def repe(a): #treure les repeticionsen un array
    s=[]
    while len(a)>0:
        aux=a[0]
        a=a[1:]
        if aux not in s:
            s.append(aux)
    return s
        

def Get_shape_accuracy(InfoImgs,InfoLabels,img,k,ImgLabels,modificacions=[0,0,0]):
    if modificacions[0] == 1:
        t=time.time()
    if modificacions[1] == 1:
        vCC=[]
    if modificacions[2] == 1:
        vImg=[]
        
    etiq = KNN_(InfoImgs,InfoLabels,img,k)
    num=0
    for ve,vi,VI in zip(etiq,ImgLabels, imgs):
        if ve != vi:
            num +=1
            VI = VI[ np.newaxis, :]
            if modificacions[1] == 1:#mostrar imatges amb grisos
                print("a ",CambiColor(VI)[0].shape," ",vCC)
                vCC.append(CambiColor(VI)[0])
            if modificacions[2] == 1:#mostrar imatges
                print("b ",VI.shape)
                vImg.append(VI[0])
        
    r=[(1-(num/len(img)))*100]
    if modificacions[0] == 1:#temps en que terda en etiquetar totes les imatges
        r.append(t-time.time())
    if modificacions[1] == 1:
        Visualitzar(vCC)
        print("c")
    if modificacions[2] == 1:
        Visualitzar(vImg)
        print("d")
    return r


def Get_color_accuracy(img,max_K,ImgLabels,options=None):
    #print(len(ImgLabels))
    etiqueta = Kmeans_Etiquetes(img,max_K,options)
    num=0
    for j,vl in enumerate(ImgLabels):
        etiq=repe(etiqueta[j])
        #print("->",etiq,"=?=",vl)
        #print("\n>",etiq,"<\n")
        lenEt=len(etiq)
        lenL=len(vl)
        i=0
        num1=num
        while i < lenEt:
            
            if etiq[i] in vl:
                num += 1/lenL
            i+=1
        #print("num:",num,"///")
        #print(j,vl,etiq,num-num1)
    return (num/len(img))*100

def Get_color_accuracyV2(img,max_K,ImgLabels,options=None):
    
    KMeans = Kmean_statistics(img,max_K,options)
    num=0
    for j,vl in enumerate(ImgLabels):
        etiq=repe(KMeans[0][j])
        #print("\n>",etiq,"<\n")
        lenEt=len(etiq)
        lenL=len(vl)
        i=0
        num1=num
        while i < lenEt:
            
            if etiq[i] in vl:
                num += 1/lenL
            i+=1
        #print(j,vl,etiq,num-num1)
                
            
    return [(num/len(img))*100,KMeans[0],KMeans[1],ImgLabels]

if __name__ == '__main__':

    # Load all timagenese images and GT
    train_imgs, train_class_labels, train_color_labels, test_imgs, test_class_labels, \
        test_color_labels = read_dataset(root_folder='./images/', gt_json='./images/gt.json')

    # List witimagenes all timagenese existent classes
    classes = list(set(list(train_class_labels) + list(test_class_labels)))

    # Load extended ground trutimagenes
    imgs, class_labels, color_labels, upper, lower, background = read_extended_dataset()
    cropped_images = crop_images(imgs, upper, lower)

    
    # You can start coding your functions imagenesere
  
    """
    t=time.time()
    
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    #options['centroids']=copy.deepcopy(np.array([[179, 5, 5],[179, 104, 5],[5, 17, 179],[0, 0, 0],[255, 255, 255],[212, 227, 9],[12, 242, 0],[60, 138, 56],[91, 252, 239],[187, 0, 255],[252, 0, 227],[97, 44, 1],[1, 97, 57],[97, 1, 35],[166, 117, 12],[90, 140, 25],[158, 95, 95],[77, 77, 77],[179, 179, 179],[105, 82, 82],[86, 82, 105],[105, 105, 82]],dtype=np.float64))
    options['verbose'] = False
    options['tolerance'] = 80
    options['max_iter'] = 20
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'
    
    aux10_IeC = Get_color_accuracy(cropped_images[:50],20,color_labels[:50],options)
    #options['tolerance'] = 18: 23.233333333333327-> 35.68333333333334->35.68333333333334
    print(aux10_IeC,":Acetrs | Temps:",time.time()-t)
    
    
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 1, 'max_iter': 20, 'fitting': 'WCD'}
    i[74.03333333333336 :Acetrs | Temps: 296.51658844947815
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 2, 'max_iter': 20, 'fitting': 'WCD'}
    i[74.03333333333336 :Acetrs | Temps: 268.14081931114197
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 3, 'max_iter': 20, 'fitting': 'WCD'}
    i[73.53333333333336 :Acetrs | Temps: 226.80909419059753
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 4, 'max_iter': 20, 'fitting': 'WCD'}
    i[72.86666666666669 :Acetrs | Temps: 208.634916305542
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 5, 'max_iter': 20, 'fitting': 'WCD'}
    i[71.53333333333335 :Acetrs | Temps: 186.75480580329895
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 10, 'max_iter': 20, 'fitting': 'WCD'}
    i[66.86666666666667 :Acetrs | Temps: 117.08959531784058
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 15, 'max_iter': 20, 'fitting': 'WCD'}
    i[63.96666666666664 :Acetrs | Temps: 89.59618330001831
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 20, 'max_iter': 20, 'fitting': 'WCD'}
    i[62.79999999999997 :Acetrs | Temps: 72.85000705718994
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 25, 'max_iter': 20, 'fitting': 'WCD'}
    i[61.133333333333304 :Acetrs | Temps: 61.46990466117859
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 30, 'max_iter': 20, 'fitting': 'WCD'}
    i[60.299999999999976 :Acetrs | Temps: 50.33415174484253
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 35, 'max_iter': 20, 'fitting': 'WCD'}
    i[60.0333333333333 :Acetrs | Temps: 29.607829809188843
    """
    
    """
    {'km_init': 'first', 'verbose': False, 'tolerance': 4, 'max_iter': 20, 'fitting': 'IeC'}
    [37.683333333333344, 50, 75.36666666666669] :Acetrs | Temps: 4378.014974355698
    {'km_init': 'first', 'verbose': False, 'tolerance': 3, 'max_iter': 20, 'fitting': 'IeC'}
    [37.683333333333344, 50, 75.36666666666669] :Acetrs | Temps: 4376.688052892685
    {'km_init': 'first', 'verbose': False, 'tolerance': 2, 'max_iter': 20, 'fitting': 'IeC'}
    [37.933333333333344, 50, 75.86666666666669] :Acetrs | Temps: 4430.717051267624
    {'km_init': 'first', 'verbose': False, 'tolerance': 1, 'max_iter': 20, 'fitting': 'IeC'}
    [37.933333333333344, 50, 75.86666666666669] :Acetrs | Temps: 4436.409309864044
    
    {'km_init': 'first', 'verbose': False, 'tolerance': 5, 'max_iter': 20, 'fitting': 'IeC'}
    [37.683333333333344, 50, 75.36666666666669] :Acetrs | Temps: 4345.969738960266
    {'km_init': 'first', 'verbose': False, 'tolerance': 10, 'max_iter': 20, 'fitting': 'IeC'}
    [37.683333333333344, 50, 75.36666666666669] :Acetrs | Temps: 3629.031487941742
    {'km_init': 'first', 'verbose': False, 'tolerance': 15, 'max_iter': 20, 'fitting': 'IeC'}
    [35.68333333333334, 50, 71.36666666666667] :Acetrs | Temps: 2377.912624359131
    {'km_init': 'first', 'verbose': False, 'tolerance': 20, 'max_iter': 20, 'fitting': 'IeC'}
    [35.43333333333334, 50, 70.86666666666667] :Acetrs | Temps: 1694.8849856853485
    {'km_init': 'first', 'verbose': False, 'tolerance': 25, 'max_iter': 20, 'fitting': 'IeC'}
    [34.60000000000001, 50, 69.20000000000002] :Acetrs | Temps: 1346.7905819416046
    {'km_init': 'first', 'verbose': False, 'tolerance': 30, 'max_iter': 20, 'fitting': 'IeC'}
    [34.35000000000001, 50, 68.70000000000002] :Acetrs | Temps: 1106.922419309616
    {'km_init': 'first', 'verbose': False, 'tolerance': 35, 'max_iter': 20, 'fitting': 'IeC'}
    [34.01666666666667, 50, 68.03333333333335] :Acetrs | Temps: 964.0763666629791
    """
    
    
    
    """
    t=time.time()
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 4
    options['max_iter'] = 20
    options['fitting'] = 'IaC'#'WCD','IC','Fisher'
    
    
    aux10_IaC= Get_color_accuracy(cropped_images[:51],20,color_labels[:51],options)
    #23.233333333333327->34.48333333333333 -> 34.48333333333333
    print(aux10_IaC,":Acetrs | Temps:",time.time()-t)
    
    
    {'km_init': 'first', 'verbose': False, 'tolerance': 1, 'max_iter': 20, 'fitting': 'IaC'}
    [34.849999999999994, 51, 68.33333333333333] :Acetrs | Temps: 986.9022059440613
    {'km_init': 'first', 'verbose': False, 'tolerance': 2, 'max_iter': 20, 'fitting': 'IaC'}
    [33.59999999999999, 51, 65.88235294117645] :Acetrs | Temps: 828.7380568981171
    {'km_init': 'first', 'verbose': False, 'tolerance': 3, 'max_iter': 20, 'fitting': 'IaC'}
    [33.68333333333332, 51, 66.04575163398691] :Acetrs | Temps: 752.5147261619568
    {'km_init': 'first', 'verbose': False, 'tolerance': 4, 'max_iter': 20, 'fitting': 'IaC'}
    [33.68333333333332, 51, 66.04575163398691] :Acetrs | Temps: 678.4178183078766
    {'km_init': 'first', 'verbose': False, 'tolerance': 5, 'max_iter': 20, 'fitting': 'IaC'}
    [33.849999999999994, 51, 66.37254901960783] :Acetrs | Temps: 554.3084423542023
    {'km_init': 'first', 'verbose': False, 'tolerance': 10, 'max_iter': 20, 'fitting': 'IaC'}
    [32.516666666666644, 51, 63.75816993464048] :Acetrs | Temps: 470.06605792045593
    {'km_init': 'first', 'verbose': False, 'tolerance': 15, 'max_iter': 20, 'fitting': 'IaC'}
    [32.56666666666665, 51, 63.85620915032676] :Acetrs | Temps: 646.068382024765
    {'km_init': 'first', 'verbose': False, 'tolerance': 20, 'max_iter': 20, 'fitting': 'IaC'}
    [35.51666666666666, 51, 69.64052287581698] :Acetrs | Temps: 849.9260230064392
    {'km_init': 'first', 'verbose': False, 'tolerance': 25, 'max_iter': 20, 'fitting': 'IaC'}
    [36.099999999999994, 51, 70.7843137254902] :Acetrs | Temps: 953.7106192111969
    {'km_init': 'first', 'verbose': False, 'tolerance': 30, 'max_iter': 20, 'fitting': 'IaC'}
    [35.93333333333333, 51, 70.45751633986927] :Acetrs | Temps: 1107.3144805431366
    {'km_init': 'first', 'verbose': False, 'tolerance': 35, 'max_iter': 20, 'fitting': 'IaC'}
    [37.266666666666666, 51, 73.0718954248366] :Acetrs | Temps: 1181.2948067188263
    
    
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 40, 'max_iter': 20, 'fitting': 'IaC'}
    i[73.20000000000002 :Acetrs | Temps: 1726.9689362049103
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 45, 'max_iter': 20, 'fitting': 'IaC'}
    i[73.20000000000002 :Acetrs | Temps: 1730.1291341781616
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 50, 'max_iter': 20, 'fitting': 'IaC'}
    i[73.20000000000002 :Acetrs | Temps: 1826.484540462494
    i[{'km_init': 'first', 'verbose': False, 'tolerance': 55, 'max_iter': 20, 'fitting': 'IaC'}
    i[74.53333333333335 :Acetrs | Temps: 1910.6289710998535
    """
    
    """
    t=time.time()
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 2
    options['max_iter'] = 20
    options['fitting'] = 'Fisher'#'WCD','IaC','IeC','Fisher'
    
    aux10_F = Get_color_accuracy(cropped_images[:51],20,color_labels[:51],options)
    #32.64999999999998->32.64999999999998->33.816666666666656
    print(aux10_F,":Acetrs | Temps:",time.time()-t)
    
    
    {'km_init': 'first', 'verbose': False, 'tolerance': 1, 'max_iter': 20, 'fitting': 'Fisher'}
    [38.6, 51, 75.68627450980392] :Acetrs | Temps: 6661.28720498085
    {'km_init': 'first', 'verbose': False, 'tolerance': 2, 'max_iter': 20, 'fitting': 'Fisher'}
    [38.6, 51, 75.68627450980392] :Acetrs | Temps: 4779.470879793167
    {'km_init': 'first', 'verbose': False, 'tolerance': 3, 'max_iter': 20, 'fitting': 'Fisher'}
    [38.6, 51, 75.68627450980392] :Acetrs | Temps: 6558.722487688065
    {'km_init': 'first', 'verbose': False, 'tolerance': 4, 'max_iter': 20, 'fitting': 'Fisher'}
    [38.6, 51, 75.68627450980392] :Acetrs | Temps: 6543.013070821762
    
    {'km_init': 'first', 'verbose': False, 'tolerance': 5, 'max_iter': 20, 'fitting': 'Fisher'}
    [38.26666666666667, 51, 75.03267973856211] :Acetrs | Temps: 6345.087634563446
    {'km_init': 'first', 'verbose': False, 'tolerance': 10, 'max_iter': 20, 'fitting': 'Fisher'}
    [36.18333333333333, 51, 70.94771241830064] :Acetrs | Temps: 3883.2144389152527
    {'km_init': 'first', 'verbose': False, 'tolerance': 15, 'max_iter': 20, 'fitting': 'Fisher'}
    [34.766666666666666, 51, 68.16993464052288] :Acetrs | Temps: 2662.0910561084747
    {'km_init': 'first', 'verbose': False, 'tolerance': 20, 'max_iter': 20, 'fitting': 'Fisher'}
    [32.39999999999998, 51, 63.529411764705834] :Acetrs | Temps: 1839.3289504051208
    {'km_init': 'first', 'verbose': False, 'tolerance': 25, 'max_iter': 20, 'fitting': 'Fisher'}
    [32.06666666666665, 51, 62.87581699346402] :Acetrs | Temps: 1315.0189752578735
    {'km_init': 'first', 'verbose': False, 'tolerance': 30, 'max_iter': 20, 'fitting': 'Fisher'}
    [31.73333333333332, 51, 62.2222222222222] :Acetrs | Temps: 1137.6500039100647
    {'km_init': 'first', 'verbose': False, 'tolerance': 35, 'max_iter': 20, 'fitting': 'Fisher'}
    [30.983333333333327, 51, 60.75163398692809] :Acetrs | Temps: 1709.8023941516876
    
    """
    """
    
    
    3
    2
    1 X
    0123
    
    
    X=[[1,1,1],[1,1,2],[1,2,1],[1,2,2],[1,10,10],[1,10,11],[1,11,10],[1,11,11]]
       0         1       1       h(1,1)
                  0      h(1.1)    1
                           0       1
                  
    (1**2)
    Out[68]: 1

    1+1
    Out[69]: 2

    2**(1/2)
    Out[70]: 1.4142135623730951

    ((2**(1/2))*2)
    Out[71]: 2.8284271247461903

    ((2**(1/2))*2)+4
    Out[72]: 6.82842712474619

    (((2**(1/2))*2)+4)/6
    Out[73]: 1.1380711874576983
    
    
    
    X=[[1,1,1],[1,1,2],[1,2,1],[1,2,2],[1,10,10],[1,10,11],[1,11,10],[1,11,11]]
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = 20
    options['fitting'] = 'IaC'#'WCD','IC','Fisher'
    
    
    
    
    km = KMeans(np.array(X), 2,copy.deepcopy(options))
    print(km.find_bestK( 15))
    print( get_colors(km.centroids) )
    km.fit()
    
    ###
    
    print("\n",km.centroids)
    print("\n",km.labels)
    print(":::::::::::::::::::::::")
    km.interClass()
    km.intraClass()
    km.Fisher()
    print(":::::::::::::::::::::::")
    print("\n",km.IeC,km.IaC,km.F)
    
    """
    
    """
    
    X=[[1,1,1],[1,1,1],[1,1,1],[1,1,1],[1,10,10],[1,10,10],[1,10,10],[1,1,10],[1,1,10],[1,1,10],[1,1,10],[1,1,10]]
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = 20
    options['fitting'] = 'IeC'#'WCD','IC','Fisher'
    
    
    
    
    km = KMeans(np.array(X), 3,copy.deepcopy(options))
    print(km.find_bestK( 15))
    print( get_colors(km.centroids) )
    
    km.fit()
    
    ###
    
    print("\n",km.centroids)
    print("\n",km.labels)
    print(":::::::::::::::::::::::")
    km.interClass()
    #km.intraClass()
    #km.Fisher()
    print(":::::::::::::::::::::::")
    print("\n",km.IeC)#,km.IaC,km.F)
    
    
    
    """
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    """print("--------------------------------------------------------")
    
    #Get_shape_accuracy(test_imgs,test_class_labels,imgs,2,class_labels)
    #print(Get_color_accuracy(imgs[:20],4,20,color_labels[:20]))
    
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'
    
    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs,4,20,color_labels,options))
     
    print("--------------------------------------------------------")
    options = {}
    options['km_init'] = 'random'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs,4,20,color_labels,options))
    
    print("--------------------------------------------------------\n")
    
    options = {}
    options['km_init'] = 'manual'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['centroids']=copy.deepcopy(np.array([[ 56.07377049,  56.07377049,  56.06830601],[254.87167371, 254.87167371, 254.87167371],[143.0625    , 143.0625    , 142.9375    ],[ 80.20327869,  80.20655738,  80.01311475],       [211.6       , 211.6       , 211.53333333],       [239.05925926, 175.6       , 130.41851852],       [124.42021277, 127.63829787, 134.86170213],       [148.57142857,  92.85714286,  70.9047619 ]],dtype=np.float64))
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs,4,20,color_labels,options))
    
    
    print("--------------------------------------------------------")
    """
    """
    print("--------------------------------------------------------")
    
    #Get_shape_accuracy(test_imgs,test_class_labels,imgs,2,class_labels)
    #print(Get_color_accuracy(imgs[:20],4,20,color_labels[:20]))
    
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs,4,20,color_labels,options))
    
    print("--------------------------------------------------------")
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'IC'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs,4,20,color_labels,options))

    print("--------------------------------------------------------\n")
    
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'Fisher'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Get_color_accuracy(imgs[:100],4,20,color_labels[:100],options))
    
    
    print("--------------------------------------------------------")
    
    
    
    
    
    
    
    
    

    print("--------------------------------------------------------")
    
    #Get_shape_accuracy(test_imgs,test_class_labels,imgs,2,class_labels)
    #print(Get_color_accuracy(imgs[:20],4,20,color_labels[:20]))
    
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'


    print("\n>",Kmean_statistics(imgs[:1],20,options))
    
    print("--------------------------------------------------------")
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = np.inf
    options['fitting'] = 'IC'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    print("\n>",Kmean_statistics(imgs[:1],20,options))
    
    print("--------------------------------------------------------\n")
    """
    """
    options = {}
    options['km_init'] = 'first'#'first'random','manual'->self.options['centroids']=np.empty((self.K,self.X.shape[1]),dtype=np.float64)
    options['verbose'] = False
    options['tolerance'] = 20
    options['max_iter'] = 20
    options['fitting'] = 'WCD'#'WCD','IC','Fisher'

    #Kmeans_Etiquetes(imgs,4,20,options)#Kmeans_Etiquetes(imagenes,NCentroides,max_K,options=None)
    #print("\n>",Kmean_statistics(imgs[40:41],20,options))
    print(Get_color_accuracy(imgs[40:41],20,color_labels[40:41],options))
    
    
    print("--------------------------------------------------------")
    #"""
    #i[{'km_init': 'random', 'verbose': False, 'tolerance': 2, 'max_iter': 20, 'fitting': 'WCD'}
    #i[75.7666666666667 :Acetrs | Temps: 240.06574726104736
    