import cv2
import time

final_time_taken = 0
cap = cv2.VideoCapture(0)

while True:
    start_time = time.time()
    ret, webcam = cap.read()
    webcam = cv2.flip(webcam, 1)
    gray = cv2.cvtColor(webcam, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 50, 150)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    largest_area = 0
    largest_contour_index = 0
    for i in range(len(contours)):
        area = cv2.contourArea(contours[i])
        if area > largest_area:
            largest_area = area
            largest_contour_index = i
    cv2.drawContours(webcam, contours, largest_contour_index, (0, 255, 0), 3)
    cv2.imshow("webcam", edges)
    final_time_taken = time.time() - start_time
    key = cv2.waitKey(1)
    if key == 27:
        print("Time taken:", final_time_taken)
        break

cap.release()
cv2.destroyAllWindows()
