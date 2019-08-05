import cv2
import numpy as np

def main():
    im = cv2.imread('ga.jpg')
    #edge = cv2.imread('edge.png', 0)
    edge = cv2.Canny(im, 100, 200, apertureSize=3)
    lines = cv2.HoughLines(edge, 1, np.pi/180, 140)
    for rho, theta in lines[0]:
        a = np.cos(theta)
        b = np.sin(theta)
        x0 = a*rho
        y0 = b*rho
        x1 = int(x0 + 1000*(-b))
        y1 = int(y0 + 1000*(a))
        x2 = int(x0 - 1000*(-b))
        y2 = int(y0 - 1000*(a))
        cv2.line(im, (x1, y1), (x2, y2), (0, 0, 255), 2)
        # TODO: filter the lines by color and line distance

    cv2.imshow('image', im)
    cv2.imshow('edge', edge)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
