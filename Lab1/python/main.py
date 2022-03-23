import math
import pandas as pd
from numpy import unique
from sklearn.cluster import KMeans
from sklearn.cluster import MeanShift
from sklearn.cluster import DBSCAN
from sklearn.cluster import OPTICS
from sklearn.cluster import SpectralClustering
from sklearn.cluster import Birch
from sklearn import metrics
from scipy.spatial import distance
from sklearn.decomposition import PCA
from matplotlib import pyplot


def do_plotClustering(data2D, cl, ref, name):
	allClasses = unique(cl)
	allColors = pyplot.cm.get_cmap('Paired', len(allClasses))
	myColor = {}
	for i, _class in enumerate(allClasses):
		myColor[_class] = allColors(i)

	myMarker = {
		"Iris-setosa":'o',
		"Iris-versicolor":'^',
		"Iris-virginica":'*'
	}

	pyplot.title(name)
	for i in range(0, len(data2D)):
		x = data2D[data2D.columns[0]].iloc[i]
		y = data2D[data2D.columns[1]].iloc[i]
		pyplot.scatter(x, y, color = myColor[cl[i]], marker = myMarker[ref[i]], s = 60)

	pyplot.show()
	pyplot.cla()


def do_kmeans(data, data2D, ref):
	model = KMeans(n_clusters=3)
	model.fit(data)
	cl = model.predict(data)

	do_plotClustering(data2D, cl, ref, "K-Means")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("KMeans\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def do_meanShift(data, data2D, ref):
	model = MeanShift(bandwidth = 0.85)
	model.fit(data)
	cl = model.predict(data)

	do_plotClustering(data2D, cl, ref, "Mean Shift")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("Mean Shift\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def do_DBSCAN(data, data2D, ref):
	model = DBSCAN(eps=0.415, min_samples=5)
	cl = model.fit_predict(data)

	do_plotClustering(data2D, cl, ref, "DBSCAN with outliers")

	oldCl = cl.copy()

	for i, myClass in enumerate(cl):
		if myClass == -1:
			minDist = 1e18
			minCl = -1

			for j, myClassOld in enumerate(oldCl):
				if myClassOld == -1:
					continue
				tDist = distance.euclidean(data.iloc[i].values, data.iloc[j].values)
				if tDist < minDist:
					minCl, minDist = myClassOld, tDist

			cl[i] = minCl

	do_plotClustering(data2D, cl, ref, "DBSCAN without outliers")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("DBSCAN\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def do_OPTICS(data, data2D, ref):
	model = OPTICS(min_samples=5)
	cl = model.fit_predict(data)

	do_plotClustering(data2D, cl, ref, "OPTICS with outliers")

	oldCl = cl.copy()

	for i, myClass in enumerate(cl):
		if myClass == -1:
			minDist = 1e18
			minCl = -1

			for j, myClassOld in enumerate(oldCl):
				if myClassOld == -1:
					continue
				tDist = distance.euclidean(data.iloc[i].values, data.iloc[j].values)
				if tDist < minDist:
					minCl, minDist = myClassOld, tDist

			cl[i] = minCl

	do_plotClustering(data2D, cl, ref, "OPTICS without outliers")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("OPTICS\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def do_SpectralClustering(data, data2D, ref):
	model = SpectralClustering(n_clusters=3)
	cl = model.fit_predict(data)

	do_plotClustering(data2D, cl, ref, "SpectralClustering")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("SpectralClustering\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def do_BIRCH(data, data2D, ref):
	model = Birch(threshold=0.2, n_clusters=3)
	model.fit(data)
	cl = model.predict(data)

	do_plotClustering(data2D, cl, ref, "BIRCH")

	hom = metrics.homogeneity_score(ref, cl)
	com = metrics.completeness_score(ref, cl)
	vm = metrics.v_measure_score(ref, cl)
	print("BIRCH\t" + str(hom) + "\t" + str(com) + "\t" + str(vm))


def int_main():
	data = pd.read_csv("IRIS.csv")
	data_ = data.drop('species', axis=1)

	print(data)

	pca = PCA(n_components=2)
	principalComponents = pca.fit_transform(data_)
	data2D = pd.DataFrame(data = principalComponents, columns = ['p1', 'p2'])

	do_plotClustering(data2D, data['species'], data['species'], "Reference")

	# k-means
	do_kmeans(data_, data2D, data['species'])

	# mean shift
	do_meanShift(data_, data2D, data['species'])

	# DBSCAN
	do_DBSCAN(data_, data2D, data['species'])

	# OPTICS
	do_OPTICS(data_, data2D, data['species'])

	# SpectralClustering
	do_SpectralClustering(data_, data2D, data['species'])

	# BIRCH
	do_BIRCH(data_, data2D, data['species'])


if __name__ == '__main__':
	int_main()