
UniqStack
============

UniqStack is QtWaylandCompositor origin based on luna-next and lipstick.


Debugging/Profiling
--------------------

## Show debug info

To show debug info, setup `UNIQSTACK_DEBUG=1` before you launch the
copycat process, then you can use systemd's tool to display the
info.

```
systemctl status uniqstack
```

## QML Debugging/Profiling

When execute copycat, add following args to enable QML
debugging/profiling

```
uniqstack -qmljsdebugger=port:3768,block
```

For more info, please see:

  http://stackoverflow.com/questions/13366495/how-to-qt-qml-debugging-and-or-profiling
