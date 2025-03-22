AI - KMeans y KNN para Clasificación de Colores

Este proyecto implementa algoritmos de aprendizaje automático para clasificación y agrupación de datos, utilizando K-Means para segmentación de colores y K-Nearest Neighbors (KNN) para clasificación basada en vecinos cercanos.

Estructura del Proyecto

Algoritmos Principales

Kmeans.py: Implementación del algoritmo K-Means para agrupar colores en imágenes.

KNN.py: Implementación del algoritmo K-Nearest Neighbors para clasificar imágenes basadas en datos de entrenamiento.

Scripts Auxiliares

my_labeling.py: Script para cargar datos y definir clases y etiquetas de colores.

utils.py: Funciones auxiliares para procesamiento de imágenes y transformación de espacios de color.

utils_data.py: Manejo y carga de datos de imágenes para entrenamiento y prueba.

Pruebas

TestCases_kmeans.py: Conjunto de pruebas unitarias para validar el correcto funcionamiento del algoritmo K-Means.

TestCases_knn.py: Conjunto de pruebas unitarias para validar el correcto funcionamiento del algoritmo KNN.

test_cases_kmeans.pkl y test_cases_knn.pkl: Archivos pickle con datos de prueba para los algoritmos.

Uso del Proyecto

Instalación de Dependencias

Asegúrate de tener instaladas las siguientes librerías antes de ejecutar el código:

pip install numpy scipy matplotlib pillow

Ejecución de K-Means

from Kmeans import KMeans
import numpy as np

# Datos de prueba
X = np.random.rand(100, 3)  # 100 puntos en un espacio de 3 dimensiones

# Inicializar y ejecutar K-Means con 3 clusters
kmeans = KMeans(X, K=3)
kmeans.fit()
print("Centroides finales:", kmeans.centroids)

Ejecución de KNN

from KNN import KNN
import numpy as np

# Datos de entrenamiento y etiquetas
train_data = np.random.rand(50, 4800)  # 50 imágenes representadas como vectores
labels = np.random.randint(0, 10, 50)  # Etiquetas de clase

# Crear el modelo y predecir
knn = KNN(train_data, labels)
test_data = np.random.rand(5, 4800)
predictions = knn.predict(test_data, k=3)
print("Predicciones:", predictions)

Ejecución de Pruebas

Para validar la correcta implementación de los algoritmos:

python -m unittest discover
