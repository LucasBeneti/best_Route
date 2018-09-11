# teste pros calculos dessa porra de lista
from bs4 import BeautifulSoup as Soup
import math
import numpy as np

mapa = "mapa_teste.kml"

with open('mapa_teste.kml') as data:
    kml_soup = Soup(data, 'lxml-xml')

coord_soup = kml_soup.find_all('coordinates')

coord_list = []

for coords in coord_soup:
    coord_list.append(coords.text)
    coord_list = list(map(lambda s: s.strip(), coord_list))

coordenadas = []

for item in coord_list:
    coordenadas.append(item[:-2])

nova_lista = []
for item in coordenadas:
    nova_lista.append(item.split(','))
nova_lista_float = []

for item in nova_lista:
    nova_lista_float.append(list(map(float, item)))

# funcao pra calculo de distancias entre coordenadas
def calculateDistances(coords1, coords2):
    long1 = math.radians(coords1[0]) # Coordenadas ja passadas para radianos
    long2 = math.radians(coords2[0]) # por exigencia da formula
    lat1 = math.radians(coords1[1])
    lat2 = math.radians(coords2[1])

    r = 6371000 # raio da Terra em metros

    a = (pow((math.sin((lat2-lat1)/2)),2)) + (math.cos(lat1)*math.cos(lat2)*(pow((math.sin((long2-long1)/2)),2)))
    c = 2 * (math.atan2(math.sqrt(a),math.sqrt(1-a)))
    distance = r * c # retornad em metros, pois raio da Terra estah em metros

    return distance

# functino that returns the cost matrix for the Dijkstra algorithm
def createWeightedMatrix(places_list):
    places = places_list
    costMatrix = []

    # filling of the cost matrices where each item is calculated with the calculateDistances function
    for i in places:
        for j in places:
            costMatrix.append(calculateDistances(i,j))

    costMatrix = np.reshape(costMatrix,(len(places),len(places)))
    return costMatrix


# places = nova_lista_float
# lista_custos = []
# for i in places:
#     for j in places:
#         lista_custos.append(calculateDistances(i,j))
#
# matriz_custos = np.reshape(lista_custos,(len(places),len(places)))
print(createWeightedMatrix(nova_lista_float))
