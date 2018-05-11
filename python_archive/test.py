import math, random
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw

im = Image.open('.\\4_images\\mario.png')
color_temp = []
color = []

for i in range(0, im.size[1]-im.size[1]/15, im.size[1]/15):
    for j in range(0, im.size[0] - im.size[0]/15, im.size[0]/15):
        color_temp.append(im.getpixel((j + im.size[0]/30, i + im.size[1]/30)))

for i in range(len(color_temp)):
    if not color:
        color.append(color_temp[0])
        continue
    flag = True

    for j in range(len(color)):
        if abs(color[j][0] - color_temp[i][0]) < 30 and abs(color[j][1] - color_temp[i][1]) < 30 and abs(color[j][2] - color_temp[i][2]) < 30:
            color.append(color[j])
            flag = False
            break
    if flag:
        color.append(color_temp[i])

cal = list(set(color))
color_dic = {}
for i in range(len(cal)):
    color_dic[cal[i]] = i+5 #5~13

Image.new('RGB', (im.size[0], im.size[1]), (255,255,255)).save('.\\4_images\\mario1.png')
im = Image.open('.\\4_images\\mario1.png')

cnt = 0
draw = ImageDraw.Draw(im)
font = ImageFont.truetype("arial.ttf", 10)

for i in range(0, im.size[1]-im.size[1]/15, im.size[1]/15):
    for j in range(0, im.size[0] - im.size[0]/15, im.size[0]/15):
        for k in range(i, i + im.size[1]/15):
            for l in range(j, j+im.size[0]/15):
                im.putpixel((l,k), (color[cnt]))
        
        while True:
            a = random.randint(0,9)
            b = random.randint(0,9)
            if a+b == color_dic[color[cnt]]:
                break
        if color[cnt][0] < 50 and color[cnt][1] < 50 and color[cnt][2] < 50:
            draw.text((j+2, i+4), str(a) + '+' +str(b), (255,255,255), font=font)
        else:
            draw.text((j+2, i+4), str(a) + '+' +str(b), (0,0,0), font=font)
        cnt += 1

for i in range(im.size[1]):
    for j in range(0, im.size[0] - im.size[0]/15, im.size[0]/15):
        im.putpixel((j,i), (0,0,0))

for i in range(im.size[0]):
    for j in range(0, im.size[1] - im.size[1]/15, im.size[1]/15):
        im.putpixel((i,j), (0,0,0))

im.save('.\\4_images\\mario1.png')