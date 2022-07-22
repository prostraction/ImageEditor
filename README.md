# ImageEditor

Fedora:

```
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Compilation:

```
g++ src/main.cpp src/GUI/MainApp.cpp src/GUI/MainFrame.cpp src/GUI/ImagePanel.cpp src/GUI/EditPanel.cpp `wx-config --cxxflags --libs` -o bin/main && ./bin/main
```
