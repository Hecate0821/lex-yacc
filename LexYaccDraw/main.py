import matplotlib.pyplot as plt

canvas = open("/Users/hecate/Clion/LexInterpreter/canvas.txt", "r")
style = open("/Users/hecate/Clion/LexInterpreter/style.txt", "r")

style_color = style.readline()
style_type = style.readline()
style_size = style.readline()
while True:
    dot_x = canvas.readline()
    if not dot_x:
        break
    dot_y = canvas.readline()
    if not dot_x:
        break


    plt.plot(int(dot_x),int(dot_y), color=style_color.strip(), marker=style_type.strip(), markersize=int(style_size.strip()))

plt.show()

