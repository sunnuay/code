from PIL import Image

with open("nyancat/nyancat.txt", "r") as f:
    txt = f.read()

colors = [
    (0, 0, 0, 0),
    (0, 0, 0, 255),
    (255, 204, 153, 255),
    (255, 153, 255, 255),
    (255, 51, 153, 255),
    (153, 153, 153, 255),
    (255, 255, 255, 255),
    (255, 153, 153, 255),
]

images = [Image.new("RGBA", (34, 21)) for _ in range(6)]

for i in range(6):
    for j in range(21):
        for k in range(34):
            n = int(txt[i * 35 + j * 35 * 6 + k])
            images[i].putpixel((k, j), colors[n])

images[0].save(
    fp="nyancat/nyancat.gif",
    save_all=True,
    append_images=images[1:],
    loop=0,
    disposal=2,
    duration=70,
)
