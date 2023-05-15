import numpy as np
from PIL import Image

#box method to blur an image
def blur(image, radius):
    blurred = np.zeros_like(image)
    for r in range(len(image)):
        for c in range(len(image[0])):
            sum = np.zeros(3)
            nums = 0
            for br in range(r-radius,r+radius):
                for bc in range(c-radius,c+radius):
                    try:
                        sum += image[br][bc]
                        nums += 1
                    except Exception as e:
                        pass
            #print(r,c,sum/nums)
            blurred[r][c] = sum/nums
    return blurred

def main():
    file = input("enter file name: ")
    image = Image.open(file)
    image.show()
    arr = np.asarray(image)
    
    blurred = blur(arr, 4)
    image = Image.fromarray(blurred, 'RGB')
    image.show()


main()