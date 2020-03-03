## Create text geometry using SHELL script

[tracker.sh][] is an example shell script to create a [text geometry][tg] file `tracker.tg`, which is used in [bend.mac][]:

```sh
$ ./tracker.sh # create tracker.tg
$ gears bend.mac # use tracker.tg
```

You need to have [dawn][] installed to convert the output `g4_0000.prim` to `g4_0000.eps`.

[LINEAR_X.tg][] shows another way to create the same geometry. The problem of this approach is that the copy number cannot start with any number other than 0.

[tracker.sh]:https://github.com/jintonic/gears/blob/master/examples/detector/scripts/tracker.sh
[bend.mac]:https://github.com/jintonic/gears/blob/master/examples/detector/scripts/bend.mac
[tg]: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/Detector/Geometry/geomASCII.html
[dawn]:https://geant4.kek.jp/~tanaka/DAWN/About_DAWN.html
[LINEAR_X.tg]:https://github.com/jintonic/gears/blob/master/examples/detector/scripts/LINEAR_X.tg
