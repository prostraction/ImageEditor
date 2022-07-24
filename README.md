# ImageEditor

Fedora lib's path differs from default wx's:

```
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Compilation:

```
g++ src/main.cpp src/GUI/MainApp.cpp src/GUI/MainFrame.cpp src/GUI/ImagePanel.cpp src/GUI/EditPanel.cpp src/ImageMath/DCT.cpp src/ImageMath/ImagePixel.cpp src/Core/Image.cpp `wx-config --cxxflags --libs` -o bin/main && ./bin/main
```
