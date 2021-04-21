# GPS

Pre-requisites:
```
$ git clone https://github.com/mikalhart/TinyGPSPlus.git
$ cp -v TinyGPSPlus/src/TinyGPS++.h TinyGPSPlus/src/TinyGPS++.cpp .
```

TODO: Create a GPS.CSVT file.


## How to import into QGIS?

`Layer` > `Add Layer` > `Add Delimeted Text Layer`

Record and Field Options:
* Number of header lines to discard: 0
* [ ] First record has field names
* [ ] Detect field types
* [ ] Decimal separator is comma
* [ ] Trim fields
* [ ] Discard empty fields

Geometry definitions:
* Point coordinates:
    * X field: `field_2`
    * Y field: `field_1`
* [ ] DMS coordinates
* Geometry CRS: `EPSG:4326 - WGS 84`
