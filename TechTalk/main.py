import cv2


def matchPictures(path1, path2, pathSave, st, en):
	sift = cv2.SIFT_create()
	bf = cv2.BFMatcher(cv2.NORM_L2, crossCheck=True)

	img1 = cv2.imread(path1)
	img2 = cv2.imread(path2)

	keyPoints1, description1 = sift.detectAndCompute(img1, None)
	keyPoints2, description2 = sift.detectAndCompute(img2, None)

	matches = bf.match(description1, description2)
	matches = sorted(matches, key=lambda x: x.distance)

	img3 = cv2.drawMatches(img1, keyPoints1, img2, keyPoints2, matches[st:en], img2, flags=2)

	cv2.imwrite(pathSave, img3)
	cv2.imshow("SIFT", img3)

	cv2.waitKey(0)


def int_main():
	matchPictures("images/1_left.png", "images/1_right.png", "images/1_res.png", 0, 100)
	matchPictures("images/2_1.jpg", "images/2_2.jpg", "images/2_res.jpg", 0, 50)
	matchPictures("images/3_1.jpg", "images/3_2.jpg", "images/3_res.jpg", 0, 50)
	matchPictures("images/4_1.jpg", "images/4_2.jpg", "images/4_res.jpg", 0, 50)


if __name__ == '__main__':
	int_main()
